#pragma once
#include<string>
#include"Enemy.h"

const float windowX = 800.0f;
const float windowY = 600.0f;



namespace {
	extern std::string spritesPath = "../Media/topdown_shooter/";
	std::vector<Enemy*> *enemies = new std::vector<Enemy*>;
}
