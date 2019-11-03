#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
#include "Animation.h"

class PhysBody;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:
	p2List<PhysBody*> circles;

	SDL_Rect b1rect;
	SDL_Rect b2rect;
	SDL_Rect b3rect;

	//Textures

	SDL_Texture* background = nullptr;
	SDL_Texture* background2 = nullptr;
	SDL_Texture* barrels1 = nullptr;
	SDL_Texture* barrels2 = nullptr;
	SDL_Texture* bumper = nullptr;
	SDL_Texture* switches = nullptr;
	SDL_Texture* multipliersOFF = nullptr;

	//Animations

	Animation bumper1;
	Animation bumper2;
	Animation bumper3;
	
};
