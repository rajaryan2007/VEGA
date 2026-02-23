#pragma once
#include "vgpch.h"      

#include "VEGA/Renderer/Buffer.h"

namespace VEGA {
	class OpenGLVertexBuffer : public VertexBuffer 
	{
	public:
		OpenGLVertexBuffer(u32 size);
		OpenGLVertexBuffer(float* vertices, u32 size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void SetData(const void* data, u32 size) override;

		virtual const BufferLayout& GetLayout() const override {
			return m_Layout;
		};
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; };

	private:
		u32 m_RendererID;
		BufferLayout m_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(u32* indices,u32 count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		
		virtual u32 GetCount() const { return m_Count; }
	
	private:
		u32 m_RendererID;
		u32 m_Count;

	};

}
