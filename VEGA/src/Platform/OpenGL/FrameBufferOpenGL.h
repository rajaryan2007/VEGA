#pragma once

#include "imgui.h"
#include "VEGA/Renderer/FrameBuffer.h"

namespace VEGA {
	class OpenGLFrameBuffer : public FrameBuffer
	{
	   public:
		   OpenGLFrameBuffer(const FrameBufferSpecification& spec);
		   virtual ~OpenGLFrameBuffer() override;

		   void Invalidate();

		   virtual void Bind() override;
		   virtual void UnBind() override;
		   
		   virtual void Resize(u32 width, u32 height) override;
		   
		   virtual const FrameBufferSpecification& GetSpecification() const override { return m_Specification; }
	       

		   virtual u32 GetColorAttacmentRendererID() const override { return m_ColorAttachment; };
	
	private:
		u32 m_RendererID = 0;
		u32 m_ColorAttachment = 0, m_DepthAttachment = 0;
		FrameBufferSpecification m_Specification;

		std::vector<FrameBufferTextureSpecification> m_ColorAttachmentSpecs;
		FrameBufferTextureFromat m_DepthAttachmentFormat = FrameBufferTextureFromat::None;

		std::vector<u32> m_colorAttachments;
		u32 m_DepthAttachmentID = 0;
	};
}