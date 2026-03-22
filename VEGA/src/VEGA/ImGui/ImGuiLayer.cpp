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
		VG_PROFILE_FUNCTION();
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		//ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO(); (void)io;

		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		io.FontDefault = io.Fonts->AddFontFromFileTTF("assests/Inter/static/Inter_18pt-Italic.ttf", 18);

		ImGui::StyleColorsDark();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		SetDarkThemeColor();

		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
        ImGui_ImplGlfw_InitForOpenGL(window, true);

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{
		VG_PROFILE_FUNCTION();
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnEvent(Event& e)
	{

		if (m_BlockEvents)
		{
			ImGuiIO& io = ImGui::GetIO();
		    e.Handled |= e.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
		    e.Handled |= e.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
	  }
	}

	/*void ImGuiLayer::OnImGuiRender()
	{
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}*/

	void ImGuiLayer::Begin()
	{
		VG_PROFILE_FUNCTION();
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
		VG_PROFILE_FUNCTION();
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
	void ImGuiLayer::SetDarkThemeColor()
	{
		auto& style = ImGui::GetStyle();
		auto& colors = style.Colors;

		// --- Modern Professional Style ---
		style.WindowPadding = ImVec2(8, 8);
		style.FramePadding = ImVec2(5, 2);
		style.ItemSpacing = ImVec2(6, 4);
		style.IndentSpacing = 20.0f;
		style.ScrollbarSize = 12.0f;
		style.GrabMinSize = 10.0f;

		style.TabBorderSize = 0.0f;
		style.TabRounding = 0.0f;

		style.WindowRounding = 0.0f;
		style.FrameRounding = 2.0f; // Sharper buttons
		style.PopupRounding = 2.0f;
		style.GrabRounding = 2.0f;
		style.TabRounding = 2.0f;

		// --- High Contrast Black Theme ---
		// Backgrounds
		colors[ImGuiCol_WindowBg] = ImVec4{ 0.05f, 0.05f, 0.05f, 1.0f };
		colors[ImGuiCol_ChildBg] = ImVec4{ 0.05f, 0.05f, 0.05f, 1.0f };
		colors[ImGuiCol_PopupBg] = ImVec4{ 0.07f, 0.07f, 0.07f, 0.98f };

		// Headers (Tree Nodes / Component Bars)
		colors[ImGuiCol_Header] = ImVec4{ 0.12f, 0.12f, 0.12f, 1.0f };
		colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.18f, 0.18f, 0.18f, 1.0f };
		colors[ImGuiCol_HeaderActive] = ImVec4{ 0.25f, 0.25f, 0.25f, 1.0f };

		// Buttons
		colors[ImGuiCol_Button] = ImVec4{ 0.12f, 0.12f, 0.12f, 1.0f };
		colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.20f, 0.20f, 0.20f, 1.0f };
		colors[ImGuiCol_ButtonActive] = ImVec4{ 0.28f, 0.28f, 0.28f, 1.0f };

		// Frame BG (Inputs, Checkboxes)
		colors[ImGuiCol_FrameBg] = ImVec4{ 0.12f, 0.12f, 0.12f, 1.0f };
		colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.18f, 0.18f, 0.18f, 1.0f };
		colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.22f, 0.22f, 0.22f, 1.0f };

		
		

		
		

		
		colors[ImGuiCol_DockingPreview] = ImVec4{ 0.15f, 0.15f, 0.15f, 0.7f };
		colors[ImGuiCol_TabHovered] = ImVec4{ 0.25f, 0.25f, 0.25f, 1.0f };
		
		colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.08f, 0.08f, 0.08f, 1.0f };
		
		colors[ImGuiCol_TabActive] = ImVec4{ 0.15f, 0.15f, 0.15f, 1.0f }; // Match your header lift
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.10f, 0.10f, 0.10f, 1.0f };
		
		colors[ImGuiCol_TitleBg] = ImVec4{ 0.06f, 0.06f, 0.06f, 1.0f };
		colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.08f, 0.08f, 0.08f, 1.0f };
		colors[ImGuiCol_DockingPreview] = ImVec4{ 0.26f, 0.59f, 0.98f, 0.70f }; 
		colors[ImGuiCol_Border] = ImVec4{ 0.1f, 0.1f, 0.1f, 0.5f }; 
		style.FrameBorderSize = 1.0f; 
	}

}