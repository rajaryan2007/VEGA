
#include "UHE.h"

#include <imgui/imgui.h>

#include "UHE/Core/EntryPoint.h"

#include "Sandbox2d.h"



class Sandbox : public UHE::Application
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


UHE::Application* UHE::CreateApplication()
{
	return new Sandbox();
}
