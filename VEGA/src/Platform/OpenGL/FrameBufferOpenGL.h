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
	       

		   u32 GetColorAttacmentRendererID(u32 index = 0) const override {
			   VG_CORE_ASSERT(!m_colorAttachments.empty(), "No color attachments!");
			   VG_CORE_ASSERT(index < m_colorAttachments.size(), "Index out of range!");
			   return m_colorAttachments[index];
		   }
	
	private:
		u32 m_RendererID = 0;
	    u32 m_DepthAttachment = 0;
		FrameBufferSpecification m_Specification;

		std::vector<FrameBufferTextureSpecification> m_ColorAttachmentSpecs;
		FrameBufferTextureSpecification m_DepthAttachmentFormat = FrameBufferTextureFromat::None;

		std::vector<u32> m_colorAttachments;
		u32 m_DepthAttachmentID = 0;
	};
}