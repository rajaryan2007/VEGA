#include "VEGA.h"

#include <glm/vec3.hpp>
class ExampleLayer : public VEGA::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{

	}

	void OnUpdate() override
	{
		//VG_INFO("EXAMPleLayer");

		if (VEGA::Input::IsKeyPressed(VG_KEY_TAB))
			VG_INFO("TAB key is pressed!");
	}
	void OnEvent(VEGA::Event& event) override
	{
		//VG_TRACE("{0}", event.ToString());
		if (event.GetEventType() == VEGA::EventType::KeyPressed)
		{
			VEGA::KeyPressedEvent& e = (VEGA::KeyPressedEvent&)event;
			VG_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
	
};

class Sandbox : public VEGA::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer);
		
	}
	~Sandbox()
	{

	}
};


VEGA::Application* VEGA::CreateApplication()
{
	return new Sandbox();
}