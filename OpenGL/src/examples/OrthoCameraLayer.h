#pragma once

#include <glm/vec3.hpp>

#include "../core/Layer.h"
#include "../core/Event.h"

class OrthoCameraLayer : public Layer
{
public:
	OrthoCameraLayer() {
		onAttach();
	}
	void onAttach() override;
	void onUpdate(float deltatime) override;
	void onDetach() override;

	void onImGuiRender() override;
	
	void onKeyEvent(KeyEvent ke) override;

private:
	glm::vec3 m_clearColor;
};