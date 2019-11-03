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

	void CreateFlippers();
	void DrawEverything();
	void AddBall(uint x, uint y);

public:

	Animation horse;

	PhysBody* ball = nullptr;

	SDL_Texture* ball_tex = nullptr;
	SDL_Texture* flipper_tex = nullptr;
	SDL_Texture* horse_tex = nullptr;

	SDL_Rect rightFlipper_section;
	SDL_Rect leftFlipper_section;

	int score;
	int life;
	int highest_score;

	iPoint initialBallPosition;
	iPoint position;

	PhysBody* leftFlipper = nullptr;
	PhysBody* leftFlipper_pivot = nullptr;
	PhysBody* rightFlipper1 = nullptr;
	PhysBody* rightFlipper1_pivot = nullptr;
	PhysBody* rightFlipper2 = nullptr;
	PhysBody* rightFlipper2_pivot = nullptr;

	b2PrismaticJoint* propellerJoint = nullptr;
	b2RevoluteJoint* leftFlipperJoint = nullptr;
	b2RevoluteJoint* rightFlipperJoint1 = nullptr;
	b2RevoluteJoint* rightFlipperJoint2 = nullptr;

};