#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"
#include "Animation.h"
#include "Box2D/Box2D/Box2D.h"

struct SDL_Texture;
class PhysBody;

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

	//void OnCollision(PhysBody* BodyA, PhysBody* BodyB);

public:

	PhysBody* ball = nullptr;

	SDL_Texture* ball_tex;

	int score;
	int life;
	int highest_score;

	bool finished_ball;
	bool ball_launched;
	bool lifeadded;

	iPoint initialBallPosition;

public:

};