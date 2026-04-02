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

		static bool IsDepthFormat(FrameBufferTextureFromat format)
		{
			switch (format)
			{
			  case FrameBufferTextureFromat::DEPTH24STENCIL8: return true;
			}
			return false;
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
        glDeleteTextures(1, &m_ColorAttachment);
        glDeleteTextures(1, &m_DepthAttachment);

    }

    void OpenGLFrameBuffer::Invalidate()
    {
        if (m_RendererID)
        {
            glDeleteFramebuffers(1, &m_RendererID);
            glDeleteTextures(1, &m_ColorAttachment);
            glDeleteTextures(1, &m_DepthAttachment);
        }

        glCreateFramebuffers(1, &m_RendererID);
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
        
		bool multisample = m_Specification.Sample > 1;

		if (m_ColorAttachmentSpecs.size() > 1)
        {
			m_ColorAttachmentSpecs.resize(m_ColorAttachmentSpecs.size());
            Utils::CreateTexture(multisample, m_colorAttachments.data(), m_colorAttachments.size());

			for (size_t i = 0; i)
			{

			}
        }
        

        
        // Color Attachment
        glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment);
        glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,
            m_Specification.Width,
            m_Specification.Height,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            nullptr);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glFramebufferTexture2D(
            GL_FRAMEBUFFER,
            GL_COLOR_ATTACHMENT0,
            GL_TEXTURE_2D,
            m_ColorAttachment,
            0
        );

        // Depth Attachment
        glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachment);
        glBindTexture(GL_TEXTURE_2D, m_DepthAttachment);

        glTexStorage2D(
            GL_TEXTURE_2D,
            1,
            GL_DEPTH24_STENCIL8,
            m_Specification.Width,
            m_Specification.Height
        );

        glFramebufferTexture2D(
            GL_FRAMEBUFFER,
            GL_DEPTH_STENCIL_ATTACHMENT,
            GL_TEXTURE_2D,
            m_DepthAttachment,
            0
        );

        VG_CORE_ASSERT(
            glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE,
            "Framebuffer is incomplete!"
        );

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLFrameBuffer::Bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
        glViewport(0, 0, m_Specification.Width, m_Specification.Height);
    }

    void OpenGLFrameBuffer::UnBind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
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

