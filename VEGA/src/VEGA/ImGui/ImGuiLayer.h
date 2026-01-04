#pragma once

#include "VEGA/Layer.h"
#include "VEGA/Events/ApplicationEvent.h"
#include "VEGA/Events/KeyEvent.h"
#include "VEGA/Events/MouseEvent.h"

namespace VEGA
{
	class VEGA_API ImGuiLayer :public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnDetach() override;
		virtual void OnAttach() override;
		virtual void OnImGuiRender() ;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

	private:
        float m_Time = 0.0f;
		bool m_BlockEvents = true;
		
	};
}