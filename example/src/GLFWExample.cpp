#include "GLFWExample.h"
#include "imgui.h"
#include "platform/imgui_impl_glfw.h"
#include "platform/imgui_impl_opengl3.h"
#include <iostream>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Window::Window(int width, int height) : width{ width }, height{ height }
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	window = glfwCreateWindow(width, height, "ImGuiUI", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);
	glfwMaximizeWindow(window);
	//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}
}
Window::~Window() {
	glfwTerminate();
}

void Window::Draw() const
{
	//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT);

	glfwSwapBuffers(window);
	glfwPollEvents();
}
bool Window::WindowShouldClose()const
{
	return glfwWindowShouldClose(window);
}
void Window::Resize(int width, int height)
{
	glViewport(0, 0, width, height);
}

GLFWwindow* Window::getRawWindow()
{
	return window;
}



GLFWWindowManager::GLFWWindowManager() : mainWindow{ SCR_WIDTH, SCR_HEIGHT }
{
	ImGui_ImplGlfw_InitForOpenGL(mainWindow.getRawWindow(), true);
	const char* glsl_version = "#version 410";
	ImGui_ImplOpenGL3_Init(glsl_version);
}
GLFWWindowManager::~GLFWWindowManager()
{
	ImGui_ImplOpenGL3_Shutdown();
}
void GLFWWindowManager::Update()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();

	ImGuiUI::WindowManager::Update();

	ImGuiIO& io = ImGui::GetIO(); (void)io;

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	mainWindow.Draw();
}