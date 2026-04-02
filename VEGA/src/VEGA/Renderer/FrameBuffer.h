#pragma once

namespace VEGA {
   enum class FrameBufferTextureFromat {
   		None = 0,
        RGBA8,
   		DEPTH24STENCIL8,
   		Depth = DEPTH24STENCIL8
   	};
   
   struct FrameBufferTextureSpecification {
       FrameBufferTextureSpecification() = default;
       FrameBufferTextureSpecification(FrameBufferTextureFromat format)
	   : TextureFormat(format) {
	   }

       FrameBufferTextureFromat TextureFormat = FrameBufferTextureFromat::None;
   };
   
   struct FrameBufferAttachmentSpecification 
   {
       FrameBufferAttachmentSpecification() = default;
       FrameBufferAttachmentSpecification(std::initializer_list<FrameBufferTextureSpecification> attachments) {};
	   std::vector<FrameBufferTextureSpecification> Attachments;
   };
   
   struct VEGA_API FrameBufferSpecification {
     
   
     u32 Width, Height;
	 FrameBufferAttachmentSpecification Attachments;
     u32 Sample = 1;
     
     bool SwapChainTarget = false;
   };
   
   class VEGA_API FrameBuffer {
   public:
     virtual const FrameBufferSpecification &GetSpecification() const = 0;
   
     virtual ~FrameBuffer() = default;
   
     virtual void Bind() = 0;
     virtual void UnBind() = 0;
   
     virtual void Resize(u32 width, u32 height) = 0;
   
     virtual u32 GetColorAttacmentRendererID() const = 0;
   
     static Ref<FrameBuffer> Create(const FrameBufferSpecification &spec);
};
} // namespace VEGA