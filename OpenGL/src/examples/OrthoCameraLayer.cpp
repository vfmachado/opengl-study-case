#include "OrthoCameraLayer.h"

#include <iostream>
#include <GL/glew.h>
#include <imgui.h>

void OrthoCameraLayer::onAttach()
{
	m_clearColor = glm::vec3(1, 1, 1);
}

void OrthoCameraLayer::onUpdate(float deltatime)
{
	glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OrthoCameraLayer::onDetach()
{
}

void OrthoCameraLayer::onImGuiRender()
{
	ImGui::Begin("Empty Layer Example. Use it as template!");                          
	ImGui::ColorEdit3("clear color", (float*)&m_clearColor);
	ImGui::End();
}

void OrthoCameraLayer::onKeyEvent(KeyEvent ke)
{
	std::cout << "Logging from ortho camera layer: " << ke.key << std::endl;
}
