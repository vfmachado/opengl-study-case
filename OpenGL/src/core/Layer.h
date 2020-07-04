#pragma once

#include "Event.h"

class Layer
{
public:
	virtual void onAttach() = 0;
	virtual void onUpdate(float deltatime) = 0;
	virtual void onDetach() = 0;

	virtual void onImGuiRender() = 0;
	
	virtual void onKeyEvent(KeyEvent ke) {}
	virtual void onMouseEvent(MouseEvent me) {}
	
private:


};