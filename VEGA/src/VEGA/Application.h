#pragma once
#include "Core.h"

namespace VEGA {


	class VEGA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//T0 be define in class
	Application* CreateApplication();

}
