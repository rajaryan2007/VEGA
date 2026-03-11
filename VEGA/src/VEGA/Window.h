#pragma once
 
#include <vgpch.h>
#include "VEGA/Core.h"
#include "VEGA/Events/Event.h"


namespace VEGA {
	struct WindowProps
	{
		std::string Title;
		u32 Width;
		u32 Height;

		WindowProps(const std::string& title = "VEGA ENGINE",
			u32 width = 1280,
			u32 height = 720)
			:Title(title), Width(width), Height(height)
		{


		}

	};



	class  Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
		
		//Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const  = 0;

		static Window* Create(const WindowProps& props = WindowProps());




	};

}