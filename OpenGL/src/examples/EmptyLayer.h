#pragma once

#include <glm/vec3.hpp>

#include "../core/Layer.h"

class EmptyLayer : public Layer
{
public:
	EmptyLayer() {
		onAttach();
	}
	void onAttach() override;
	void onUpdate(float deltatime) override;
	void onDetach() override;

	void onImGuiRender() override;

private:
	glm::vec3 m_clearColor;
};