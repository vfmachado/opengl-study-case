#include "TriangleLayer.h"

#include <GL/glew.h>
#include <imgui.h>

void TriangleLayer::onAttach()
{

	m_shader = new Shader("res/shaders/triangleVS.glsl", "res/shaders/triangleFS.glsl");

	m_color = glm::vec3(0.8, 0.2, 0.3);

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	m_vertexbuffer;
	glGenBuffers(1, &m_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_data), m_data, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

}

void TriangleLayer::onUpdate(float deltatime)
{
	glClearColor(0.2, 0.2, 0.2, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_data), m_data, GL_DYNAMIC_DRAW);

	m_shader->bind();
	m_shader->setUniform("color", m_color);

	glDrawArrays(GL_TRIANGLES, 0, 3);

}

void TriangleLayer::onDetach()
{
}

void TriangleLayer::onImGuiRender()
{
	ImGui::Begin("The Triangle Example");
	ImGui::SliderFloat2("V0", m_data, -1.0f, 1.0f);
	ImGui::SliderFloat2("V1", m_data+3, -1.0f, 1.0f);
	ImGui::SliderFloat2("V2", m_data+6, -1.0f, 1.0f);
	ImGui::ColorEdit3("Color", (float*)&m_color);
	ImGui::End();
}
