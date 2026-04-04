#include "vgpch.h"
#include "FrameBufferOpenGL.h"

#include <glad/glad.h>

namespace VEGA
{
    constexpr static const u32 MaxFrameBufferSize = 8132;

    namespace Utils {
        static GLenum TextureTarget(bool multisampled)
        {
            return multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
		}

        static void CreateTexture(bool multisampled,u32* outId,u32 count)
        {
            glCreateTextures(TextureTarget(multisampled), count, outId);
        }

        static void BindTexture(bool multisampled , u32 id)
        { 
			glBindTexture(TextureTarget(multisampled), id);
        }

        static void AttachColorTexture(bool multisampled, u32 id,i32 sample, GLenum internalFormat, GLenum format, GLenum type, u32 width, u32 height, i32 index)
        {
			bool multisample = multisampled;
            if (multisample)
            {
                glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, sample, internalFormat, width, height, GL_FALSE);

            }
            else
            {
                glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, nullptr);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            }

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, TextureTarget(multisample), id, 0);
        }

        static void AttachDepthTexture(u32 id, bool multisampled, i32 sample, GLenum format,GLenum attachmentType, u32 width, u32 height)
        {
            if (multisampled)
            {
                glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, sample, format, width, height, GL_FALSE);
            }
            else
            {
                glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            }
            glFramebufferTexture2D(GL_FRAMEBUFFER,attachmentType , TextureTarget(multisampled), id, 0);
        }


		static bool IsDepthFormat(FrameBufferTextureFromat format)
		{
			switch (format)
			{
			  case FrameBufferTextureFromat::DEPTH24STENCIL8: return true;
			}
			return false;
		}

        static GLenum VEGAToGLFrameBufferTextureFormat(FrameBufferTextureFromat format)
        {
            switch (format)
            {
                case FrameBufferTextureFromat::RGBA8: return GL_RGBA8;
                case FrameBufferTextureFromat::RED_INTEGER: return GL_R32I;
            }
            VG_CORE_ASSERT(false, "Unknown FrameBufferTextureFromat!");
            return 0;
		}

        static GLenum VEGAToGLFrameBufferTextureFormatAttachment(FrameBufferTextureFromat format)
        {
            switch (format)
            {
            case FrameBufferTextureFromat::DEPTH24STENCIL8: return GL_DEPTH_STENCIL_ATTACHMENT;
            }
            VG_CORE_ASSERT(false, "Unknown FrameBufferTextureFromat!");
            return 0;

        }

    }


    OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferSpecification& spec)
        : m_Specification(spec)
    {   
        for(auto spec : m_Specification.Attachments.Attachments)
        {
            if (!Utils::IsDepthFormat(spec.TextureFormat))
                m_ColorAttachmentSpecs.emplace_back(spec);
            else
				m_DepthAttachmentFormat = spec.TextureFormat;
		}

        Invalidate();
    }

    OpenGLFrameBuffer::~OpenGLFrameBuffer()
    {
        glDeleteFramebuffers(1, &m_RendererID);
        glDeleteTextures(m_colorAttachments.size(), m_colorAttachments.data());
        glDeleteTextures(1, &m_DepthAttachment);

    }

    void OpenGLFrameBuffer::Invalidate()
    {
        if (m_RendererID)
        {
            glDeleteFramebuffers(1, &m_RendererID);
            glDeleteTextures(m_colorAttachments.size(), m_colorAttachments.data() );
            glDeleteTextures(1, &m_DepthAttachment);

            m_colorAttachments.clear();
            m_DepthAttachment = 0;

        }

        glCreateFramebuffers(1, &m_RendererID);
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
        
		bool multisample = m_Specification.Sample > 1;

		if (m_ColorAttachmentSpecs.size() >= 1)
        {
			m_colorAttachments.resize(m_ColorAttachmentSpecs.size());
            Utils::CreateTexture(multisample, m_colorAttachments.data(), m_colorAttachments.size());

            for (size_t i = 0; i < m_colorAttachments.size(); i++) {
                {
                    Utils::BindTexture(multisample, m_colorAttachments[i]);
                    switch (m_ColorAttachmentSpecs[i].TextureFormat)
                    {
                       case FrameBufferTextureFromat::RGBA8:
                           Utils::AttachColorTexture(multisample,m_colorAttachments[i],m_Specification.Sample,GL_RGBA8,GL_RGBA,GL_UNSIGNED_BYTE,m_Specification.Width,m_Specification.Height,i);
						   break;
                       case FrameBufferTextureFromat::RED_INTEGER:
						   Utils::AttachColorTexture(multisample, m_colorAttachments[i], m_Specification.Sample, GL_R32I, GL_RED_INTEGER, GL_INT, m_Specification.Width, m_Specification.Height, i);

                    }
                }
            }
			
        }
        
        if (m_DepthAttachmentFormat.TextureFormat != FrameBufferTextureFromat::None)
        {
            Utils::CreateTexture(multisample, &m_DepthAttachment, 1);
            Utils::BindTexture(multisample, m_DepthAttachment);
            switch (m_DepthAttachmentFormat.TextureFormat)
            {
            case FrameBufferTextureFromat::DEPTH24STENCIL8:
                Utils::AttachDepthTexture(m_DepthAttachment, multisample, m_Specification.Sample, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, m_Specification.Width, m_Specification.Height);
            };

        }

        if (m_colorAttachments.size())
        {
			VG_CORE_ASSERT(m_colorAttachments.size() <= 4, "VEGA only supports 4 color attachments");
			GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
			glDrawBuffers(m_colorAttachments.size(), buffers);

        }
		else if (m_colorAttachments.empty())
        {
			glDrawBuffer(GL_NONE);
        }
        
        VG_CORE_ASSERT(
            glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE,
            "Framebuffer is incomplete!"
        );

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLFrameBuffer::Bind()
    {
        VG_GPU_ZONE("OpenGLFrameBuffer::Bind");
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
        glViewport(0, 0, m_Specification.Width, m_Specification.Height);
        
        // clearColorAttachment
       
    }

    void OpenGLFrameBuffer::UnBind()
    {
        VG_GPU_ZONE("OpenGLFrameBuffer::UnBind");
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    i32 OpenGLFrameBuffer::ReadPixel(u32 attachmentIndex, i32 x, i32 y)
    {
		VG_CORE_ASSERT(attachmentIndex < m_ColorAttachmentSpecs.size(), "Attachment index out of bounds!");

        glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);
		i32 pixelData;
		glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData);
		return pixelData;

	}

	void OpenGLFrameBuffer::ClearAttachment(u32 attachmentIndex, const i32 value)
	{
		VG_CORE_ASSERT(attachmentIndex < m_ColorAttachmentSpecs.size(), "Attachment index out of bounds!");

		//int value = -1;
		//glClearTexImage(m_colorAttachments[1], 0, GL_RED_INTEGER, GL_INT, &value);

		auto& spec = m_ColorAttachmentSpecs[attachmentIndex];

		glClearTexImage(m_colorAttachments[attachmentIndex], 0,Utils::VEGAToGLFrameBufferTextureFormat(spec.TextureFormat),Utils::VEGAToGLFrameBufferTextureFormatAttachment(spec.TextureFormat), &value);
	}

	void OpenGLFrameBuffer::Resize(u32 width, u32 height)
    {
        if (width == 0 || height == 0 || width == MaxFrameBufferSize || height == MaxFrameBufferSize)
        {
            VG_CORE_WARN("Your Trying to Renderer viewport at {0}, {1}", height, width);
            return;
        }

        m_Specification.Width = width;
        m_Specification.Height = height;

        Invalidate();
    }
}

