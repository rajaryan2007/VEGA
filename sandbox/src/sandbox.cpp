#include "VEGA.h"

class ExampleLayer : public VEGA::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{

	}

	void OnUpdate() override
	{
		
	}
	void OnEvent(VEGA::Event& event) override
	{
		VG_TRACE("{0}", event.ToString());
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