#include "Window.h"

#include "Core.h"

#include <GL/glew.h>

Window::Window(const std::string & name)
{
	init(name);
	
}

void Window::init(const std::string & name)
{
	m_data.title = name;

	/* Initialize the library */
	if (!glfwInit())
		exit(EXIT_FAILURE);

	//my pc has 4.6 and activing this hint disable old opengl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	/* Create a windowed mode window and its OpenGL context */
	m_window = glfwCreateWindow(1280, 720, name.c_str(), NULL, NULL);
	if (!m_window)
	{
		glfwTerminate();
		//return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(m_window);

	//modern opengl intilialize

	if (glewInit() != GLEW_OK) {
		LOG("Error initializing GLAD");
	}

	glfwSwapInterval(0);	//vsync

	glfwSetWindowUserPointer(m_window, &m_data);

							//setup callbacks
	glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyEvent ke = { action, key };
			data.eventCallback(ke);

		});
}

Window::~Window()
{
}

void Window::onUpdate()
{
	/* Swap front and back buffers */
	glfwSwapBuffers(m_window);

	/* Poll for and process events */
	glfwPollEvents();

}
