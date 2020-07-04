#pragma once

#include <string>
#include <functional>
#include <GLFW/glfw3.h>

#include "core/Layer.h"
#include "core/Event.h"
#include "core/Window.h"

class Application
{
public:
	
	Application(const std::string& name = "Main Application");
	virtual ~Application();

	void run();
	void close();
	
	//GLFWwindow& getWindow() { return *m_window; }
	void setLayer(Layer *layer) { m_layer = layer;  }

	void onKeyEvent(KeyEvent& ke);
	
private:
	//GLFWwindow *m_window;
	Window * m_window;
	Layer *m_layer;
	bool m_running = true;
	float m_lastFrameTime = 0.0f;

	void imguiInit();
	void imguiPrepare();
	void imguiFinish();

	void showMenu();

};