#pragma once

#include "../Engine/Vec2.h"

class Mediator;

class PopupBox {
protected:
	const Math::vec2 position{ 5000, 5000 };
	const double width = 400;
	const double height = 200;

	int menu = 0;
	int state = 0;

	bool activated = false;

	Mediator* mediator;
public:
	PopupBox(Mediator* mediator);
	void Draw();
	void Update();
	void Activate() { activated = true; }
	void Deactivate() { activated = false; menu = 0; state = 0; }
	bool is_activated() { return activated;  }
};

