#pragma once

#include <string>

#include <glm/vec3.hpp>

#include "../core/Core.h"
#include "../core/Layer.h"

#include "../rendering/Shader.h"

class Assignment0Layer : public Layer
{
public:
	Assignment0Layer() {
		onAttach();
	}
	void onAttach() override;
	void onUpdate(float deltatime) override;
	void onDetach() override;

	void onImGuiRender() override;

private:
	void loadModel(const char * filepath);

	Shader *m_shader;

	glm::mat4 m_projection;
	glm::vec3 m_cameraPosition;

	glm::vec3 m_lightDirection;

	unsigned int m_vao;
	int m_count;
	
	glm::vec3 m_color;

	bool m_rotation = false;
	float m_rotationAngle = 0;

	char m_filepath[256] = "res/assets/cube.obj";
};