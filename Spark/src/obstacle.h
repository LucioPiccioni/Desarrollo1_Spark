#pragma once

#include <list>

#include "raylib.h"

namespace OBSTACLE
{
	extern float spawnTimer;

	struct Pipe
	{
		Rectangle rect = {};
		float angle = 0;
	};

	struct Obstacle
	{
		bool counted = false;

		Pipe top = {};
		Pipe bottom = {};
	};

	const float minSpeed = 150;
	extern float actualSpeed;
	const float maxSpeed = 300;

	const float maxSpacing = 384;
	extern float actualSpacing;
	const float minSpacing = 70;

	const float maxSpawiningTime = 6;
	extern float actualSpawiningTime;
	const float minSpawiningTime = 3;

	Obstacle Creator();

	void updateObstacle(Obstacle& obstacles, float deltaTime);

	void drawObstacle(Obstacle obstacles, Texture2D& pipeTexture);

	bool relocateObstacle(Obstacle& obstacle);

}
