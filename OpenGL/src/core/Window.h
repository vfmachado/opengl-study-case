#pragma once

#include <functional>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Core.h"

#include "Event.h"

class Window
{
public:
	using KeyEventCallbackFn = std::function<void(KeyEvent&)>;

	Window(const std::string & name = "Application Tittle");
	~Window();

	void init(const std::string & name);

	void onUpdate();

	//unsigned int GetWidth() const override { return m_Data.Width; }
	//unsigned int GetHeight() const override { return m_Data.Height; }

	// Window attributes
	void setEventCallback(const KeyEventCallbackFn& callback) { m_data.eventCallback = callback; }
	//void SetVSync(bool enabled);
	//bool IsVSync() const;

	GLFWwindow* getNativeWindow() const { return m_window; }

private:
	GLFWwindow * m_window;
	
	struct WindowData
	{
		std::string title;
		KeyEventCallbackFn eventCallback;
	};

	WindowData m_data;

};