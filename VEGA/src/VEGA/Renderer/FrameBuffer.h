#pragma once

namespace VEGA {
struct VEGA_API FrameBufferSpecification {
  u32 Width, Height;
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