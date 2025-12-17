#pragma once

#include "VEGA/Core.h"

namespace VEGA {
	class VEGA_API Input {
	public:
		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
	
		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float,float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		inline static float GetMouseX(int button) { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY(int button) { return s_Instance->GetMouseYImpl(); }
		
    protected:
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float,float> GetMousePositionImpl() = 0;
		virtual float GetMouseYImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		

		virtual bool IsKeyPressedImpl(int keycode) = 0;
     
	private:
		static Input* s_Instance;

	};
}
