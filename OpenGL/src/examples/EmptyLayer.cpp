#include "EmptyLayer.h"

#include <GL/glew.h>
#include <imgui.h>

void EmptyLayer::onAttach()
{
	m_clearColor = glm::vec3(1, 1, 1);
}

void EmptyLayer::onUpdate(float deltatime)
{
	glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void EmptyLayer::onDetach()
{
}

void EmptyLayer::onImGuiRender()
{
	ImGui::Begin("Empty Layer Example. Use it as template!");                          
	ImGui::ColorEdit3("clear color", (float*)&m_clearColor);
	ImGui::End();
}
