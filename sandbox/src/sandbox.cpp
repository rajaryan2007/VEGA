
#include "VEGA.h"

#include <imgui/imgui.h>

#include "VEGA/Core/EntryPoint.h"

#include "Sandbox2d.h"



class Sandbox : public VEGA::Application
{
public:
	Sandbox()

	{
		//PushLayer(new ExampleLayer());	
		PushLayer(new Sandbox2D());
	}

	~Sandbox() override
	{
	}
};


VEGA::Application* VEGA::CreateApplication()
{
	return new Sandbox();
}
