#pragma once

#include "VEGA/Input.h"

namespace VEGA
{
	class WindowInput : public Input
	{
		protected:
			virtual bool IsKeyPressedImpl(int keycode) override;

			virtual bool IsMouseButtonPressedImpl(int button) override;
			virtual std::pair<float, float> GetMousePositionImpl() override;
			virtual float GetMouseXImpl() override;
			virtual float GetMouseYImpl() override;

	};
}