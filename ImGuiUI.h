#pragma once

#include <vector>
#include <memory>
#include <string>

#include "imgui.h"

namespace ImGuiUI
{
	class UIWindow
	{
	public:
		virtual void update() = 0;
		void Show();
		void Hide();
		std::string GetName();
	protected:
		bool showing;
		std::string name;
	};

	class WindowManager
	{
	public:
		WindowManager()
		{
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
			io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
			io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		}

		~WindowManager()
		{
			ImGui::DestroyContext();
		}
		virtual void Update()
		{
			ImGui::NewFrame();
			ImGuiIO& io = ImGui::GetIO();

			bool show = true;
			showDockSpace(&show);

			for (auto i = 0; i < windows.size(); i++)
			{
				windows[i]->update();
			}

			//ImGui::ShowDemoWindow();
			ImGui::Render();

		}
		void AddWindow(std::unique_ptr<UIWindow> newWindow)
		{
			windows.push_back(std::move(newWindow));
		}
	private:
		std::vector<std::unique_ptr<UIWindow>> windows;

		void showDockSpace(bool* p_open)
		{
			static bool opt_fullscreen_persistant = true;
			bool opt_fullscreen = opt_fullscreen_persistant;
			static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

			ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
			if (opt_fullscreen)
			{
				ImGuiViewport* viewport = ImGui::GetMainViewport();
				ImGui::SetNextWindowPos(viewport->Pos);
				ImGui::SetNextWindowSize(viewport->Size);
				ImGui::SetNextWindowViewport(viewport->ID);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
				window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
				window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
			}

			if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
				window_flags |= ImGuiWindowFlags_NoBackground;

			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
			ImGui::Begin("###DockSpace", p_open, window_flags);
			ImGui::PopStyleVar();

			if (opt_fullscreen)
				ImGui::PopStyleVar(2);

			// DockSpace
			ImGuiIO& io = ImGui::GetIO();
			if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
			{
				ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
				ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
			}

			ImGui::End();
		}
	};
}