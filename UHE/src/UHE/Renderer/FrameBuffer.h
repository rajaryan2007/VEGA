#pragma once

namespace UHE {
   enum class FrameBufferTextureFromat {
   		None = 0,
        RGBA8,
		RED_INTEGER,
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
       FrameBufferAttachmentSpecification(std::initializer_list<FrameBufferTextureSpecification> attachments)
		   : Attachments(attachments) {}
	   std::vector<FrameBufferTextureSpecification> Attachments;
   };
   
   struct UHE_API FrameBufferSpecification {
     
   
     u32 Width, Height;
	 FrameBufferAttachmentSpecification Attachments;
     u32 Sample = 1;
     
     bool SwapChainTarget = false;
   };
   
   class UHE_API FrameBuffer {
   public:
     virtual const FrameBufferSpecification &GetSpecification() const = 0;
   
     virtual ~FrameBuffer() = default;
   
     virtual void Bind() = 0;
     virtual void UnBind() = 0;
    
	 virtual void ClearAttachment(u32 attachmentIndex,const i32 value) = 0;

     virtual void Resize(u32 width, u32 height) = 0;
     
	 virtual int ReadPixel(u32 attachmentIndex, i32 x, i32 y) = 0;

     virtual u32 GetColorAttacmentRendererID(u32 index = 0) const = 0;
   
     static Ref<FrameBuffer> Create(const FrameBufferSpecification &spec);
};
} // namespace UHE