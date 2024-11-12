#pragma once

#include "raylib.h"

namespace Obstacle
{

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

		const float speed = 150;

	};

	const float maxSpacing = 384;
	float actualSpacing;
	const float minSpacing = 70;

	Obstacle Creator();

	void updateObstacle(Obstacle& obstacle);

	void drawObstacle(Obstacle obstacle);

	void relocateObstacle(std::list<Obstacle>& obstacle);

}
