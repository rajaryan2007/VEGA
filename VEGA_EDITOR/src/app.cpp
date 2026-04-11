
#include "VEGA.h"

#include <VEGA/Core/EntryPoint.h>
#include <imgui/imgui.h>


#include "Editor.h"


namespace VEGA
{

	class VEGAEditor : public Application
	{
	public:
		VEGAEditor()
			: Application("EDITOR")
		{
			//PushLayer(new ExampleLayer());	
			PushLayer(new Editor());
		}

		~VEGAEditor() override
		{
			
		}
	};


	Application* CreateApplication()
	{
		return new VEGAEditor();
	}

}