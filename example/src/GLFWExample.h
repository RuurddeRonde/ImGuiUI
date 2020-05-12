#pragma once
#include <vector>
#include "../../ImGuiUI.h"
#include <../GLAD/glad/glad.h>
#include "GLFW/glfw3.h"
#include <memory>

class exampleWindow : public ImGuiUI::UIWindow
{
public:
	exampleWindow()
	{
		count = 0;
	}
	~exampleWindow() {}
	void update() override
	{
		if (showing)
		{
			if (!ImGui::Begin("Settings", &showing))
			{
				ImGui::End();
			}
			else
			{
				ImGui::Text("This is an example window");
				ImGui::Text("Dock this window!");
				ImGui::Separator();
				ImGui::Text("You can create your own windows for any purpose");
				if (ImGui::Button("This is a button"))
				{
					count++;
				}
				
				ImGui::Text("Count: %d", count);

				ImGui::End();
			}
		}
	}
private:
	int count;
};


//glfw needs a window. This becomes our dockspace
class Window
{
public:
	Window(int width, int height);
	~Window();
	void Draw()const;
	bool WindowShouldClose()const;
	int getWidth()const { return width; }
	int getHeight()const { return height; }
	void Resize(int width, int height);
	GLFWwindow* getRawWindow();
private:
	int width, height;
	GLFWwindow* window;
};

//glfw implementation example
	class GLFWWindowManager : public ImGuiUI::WindowManager
	{
	public:
		GLFWWindowManager();
		~GLFWWindowManager();
		virtual void Update();
		bool shouldClose() { return mainWindow.WindowShouldClose(); }
	private:
		Window mainWindow;

	};



