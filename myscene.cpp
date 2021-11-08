#pragma once
#include "myscene.h"

MyScene::MyScene()
{

}

MyScene::~MyScene()
{
	std::cout << "MyScene destructor" << std::endl;
}

void MyScene::update()
{
	std::cout << "MyScene update" << std::endl;

}