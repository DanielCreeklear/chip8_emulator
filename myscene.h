#pragma once
#include "scene.h"
#include <iostream>

class MyScene: public Scene
{
public:
	MyScene();
	~MyScene();
	void update() override;
};

