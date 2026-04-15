
#include "UHE.h"

#include <UHE/Core/EntryPoint.h>
#include <imgui/imgui.h>


#include "Editor.h"


namespace UHE
{

	class UHEEditor : public Application
	{
	public:
		UHEEditor()
			: Application("UNHUMAN ENGINE")
		{
			//PushLayer(new ExampleLayer());	
			PushLayer(new Editor());
		}

		~UHEEditor() override
		{
			
		}
	};


	Application* CreateApplication()
	{
		return new UHEEditor();
	}

}