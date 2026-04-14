#pragma once
#include "UHE/Core/Core.h"
#include "UHE/Events/Event.h"
#include "UHE/Core/Timestep.h"

namespace  UHE {
	class UHE_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnEvent(Event& event) {}
		virtual void OnImGuiRender() {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}