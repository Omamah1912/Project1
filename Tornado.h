#pragma once
#include"Duck.h"
class Tornado: public Obstacle {
public:
	Tornado(float x, float y) {
		setTex("assets/tornado.png");
		setPosition(x, y);
	}

	void affectDuck(Duck& duck) {
		// If duck is in range, apply velocity impulse
	}

	// further the tornado will push away the duck by a bit
};
