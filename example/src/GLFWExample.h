#pragma once
#include <vector>
#include "../../ImGuiUI.h"
#include <../GLAD/glad/glad.h>
#include "GLFW/glfw3.h"
#include <memory>

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


	class GLFWWindowManager : public ImGuiUI::WindowManager
	{
	public:
		GLFWWindowManager();
		~GLFWWindowManager();
		virtual void Update();
		bool shouldClose() { return mainWindow.WindowShouldClose(); }
	private:
		std::vector<std::unique_ptr<ImGuiUI::UIWindow>> windows;
		Window mainWindow;

	};



