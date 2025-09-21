#include "VEGA.h"

class Sandbox : public VEGA::Application
{
public:
	Sandbox()
	{

	}
	~Sandbox()
	{

	}
};


VEGA::Application* VEGA::CreateApplication()
{
	return new Sandbox();
}