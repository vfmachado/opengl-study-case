#pragma once

#include <glm/vec3.hpp>

#include "../rendering/Shader.h"

#include "../core/Layer.h"

class TriangleLayer : public Layer
{
public:
	TriangleLayer() {
		onAttach();
	}

	void onAttach() override;
	void onUpdate(float deltatime) override;
	void onDetach() override;

	void onImGuiRender() override;

private:
	
	Shader *m_shader;
	
	unsigned int m_vao;
	unsigned int m_vertexbuffer;

	float m_data[9] = { -0.8f, -0.8f, 0.0f,
		0.8f, -0.8f, 0.0f,
		0.0f, 0.8f, 0.0f };
	glm::vec3 m_color;
};