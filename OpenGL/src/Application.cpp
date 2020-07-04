#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <functional>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/gtx/string_cast.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#define IMGUI_IMPL_OPENGL_LOADER_GLEW
#include <imgui.h>
#include <examples/imgui_impl_opengl3.h>
#include <examples/imgui_impl_glfw.h>

#define LOG(x) std::cout << x << std::endl

#include "Utils.h"
#include "./rendering/Shader.h"
#include "./rendering/Texture.h"
#include "Application.h"

#include "core/Event.h"

#include "./examples/EmptyLayer.h" 
#include "./examples/TriangleLayer.h"
#include "./examples/OrthoCameraLayer.h"


Application::Application(const std::string & name)
{

	m_window = new Window("Application  test");
	m_window->setEventCallback(BIND_EVENT_FN(Application::onKeyEvent));

	LOG("OpenGL Info:");
	LOG("  Vendor: " << glGetString(GL_VENDOR));
	LOG("  Renderer: " << glGetString(GL_RENDERER));
	LOG("  Version: " << glGetString(GL_VERSION));

	
	imguiInit();
	
}

Application::~Application()
{
	m_window->~Window();	//is it necessary?

}

void Application::run()
{

	float frameTime = 0;
	float lastTime = 0;
	
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(m_window->getNativeWindow())) {
		
		float currentTime = glfwGetTime();
		
		frameTime = currentTime - lastTime;

		//display(m_window, glfwGetTime());
		if (m_layer)
			m_layer->onUpdate(frameTime);
		else {
			glClearColor(0, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
		

		{
			imguiPrepare();
			showMenu();
			if (m_layer)
			m_layer->onImGuiRender();
			imguiFinish();
		}

		
		m_window->onUpdate();
		lastTime = currentTime;
	}

}

void Application::close()
{
	
}

void Application::onKeyEvent(KeyEvent& ke)
{
	LOG("Application::onKeyEvent");
	
	if (m_layer) {
		LOG("Dispatching to layer");
		m_layer->onKeyEvent(ke);
	}

}


void Application::imguiInit()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
																//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
																//io.ConfigViewportsNoAutoMerge = true;
																//io.ConfigViewportsNoTaskBarIcon = true;

																// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(m_window->getNativeWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 430");
}


void Application::imguiPrepare()
{
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

}

void Application::imguiFinish()
{
	// Rendering
	ImGui::Render();
	/*
	int display_w, display_h;
	glfwGetFramebufferSize(window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT);
	*/
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	// Update and Render additional Platform Windows
	// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
	//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}


}

void Application::showMenu()
{
	ImVec2 buttonSize = { 200, 25 };
	ImGui::Begin("Select a Scene");
	
	ImGui::Text("Application average %.1f FPS", ImGui::GetIO().Framerate);

	if (ImGui::Button("1. NONE          ", buttonSize)) m_layer = nullptr;
	if (ImGui::Button("2. Empty Layer   ", buttonSize)) m_layer = new EmptyLayer();
	if (ImGui::Button("3. Triangle Layer", buttonSize)) m_layer = new TriangleLayer();
	if (ImGui::Button("3. OrthoCamera Layer", buttonSize)) m_layer = new OrthoCameraLayer();
	
	ImGui::End();
}


int main(int argc, char** argv)
{
	Application app;
	app.run();
	return 0;
}