#include "vgpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"

#include "VEGA/Events/Event.h"
#define IMGUI_IMPL_API
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"	
#include "VEGA/Application.h"
//#include "backends/imgui_impl_glfw.h"
//#include "backends/imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace VEGA
{
	ImGuiLayer::ImGuiLayer()
		:Layer("ImGuiLayer")
	{

	}
	ImGuiLayer::~ImGuiLayer()
	{
	}
	void ImGuiLayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		//ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO(); (void)io;

		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGui::StyleColorsDark();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
        ImGui_ImplGlfw_InitForOpenGL(window, true);

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnEvent(Event& e)
	{
	    if (!m_BlockEvents)
	        return;

	    ImGuiIO& io = ImGui::GetIO();
	    if (e.IsInCategory(EventCategoryMouse) && io.WantCaptureMouse)
	        e.Handled = true;
	    if (e.IsInCategory(EventCategoryKeyboard) && io.WantCaptureKeyboard)
	        e.Handled = true;
	}

	void ImGuiLayer::OnImGuiRender()
	{
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}

	void ImGuiLayer::Begin()
	{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGuiIO& io = ImGui::GetIO();
    Application& app = Application::Get();
    io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());
    float time = (float)glfwGetTime();
    io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
    m_Time = time;
	}

	void ImGuiLayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());
		//Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}
	
}