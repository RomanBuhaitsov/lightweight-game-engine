#pragma once
#include "LGE_Components.h"

class LGE_PositionComponent : public LGE_Component {
private:
	int x;
	int y;
public:
	LGE_PositionComponent() : LGE_Component(LGE_ComponentType::CT_POSITION), x(0), y(0) {};
	int getX() { return x; };
	int getY() { return y; };
	void update(const Uint64 gameTime);
	void draw() {};
	void setPos(const int& x, const int& y);
};