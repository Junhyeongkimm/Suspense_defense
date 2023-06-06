#pragma once

#include <iostream>
#include "../Engine/Vec2.h"

class PopupBox {
private:


protected:
	Math::vec2 position;
	double width;
	double height;
	std::string string;
public:
	PopupBox(Math::vec2 position, double width, double height, std::string string);
	void Draw();
	void Update();
};

