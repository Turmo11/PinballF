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
	void createSensors();
	void setBonus();


public:
	p2List<PhysBody*> circles;

	//Rects

	SDL_Rect b1rect;
	SDL_Rect b2rect;
	SDL_Rect b3rect;

	SDL_Rect flag1_ON;
	SDL_Rect flag1_OFF;
	SDL_Rect flag2_ON;
	SDL_Rect flag2_OFF;
	SDL_Rect flag3_ON;
	SDL_Rect flag3_OFF;

	SDL_Rect cowboyON;
	SDL_Rect cowboyOFF;

	SDL_Rect bonus_x2_ON;
	SDL_Rect bonus_x4_ON;
	SDL_Rect bonus_x6_ON;
	SDL_Rect bonus_x8_ON;
	SDL_Rect bonus_x10_ON;
	SDL_Rect hold_ON;

	//Textures

	SDL_Texture* background = nullptr;
	SDL_Texture* background2 = nullptr;
	SDL_Texture* barrels1 = nullptr;
	SDL_Texture* barrels2 = nullptr;
	SDL_Texture* bumper = nullptr;
	SDL_Texture* switches = nullptr;
	SDL_Texture* multipliersOFF = nullptr;
	SDL_Texture* multipliersON = nullptr;

	SDL_Texture* final_score = nullptr;

	//Audio

	uint intro_music;

	//Animations

	Animation bumper1_anim;
	Animation bumper2_anim;
	Animation bumper3_anim;

	Animation cowboy1_anim;
	Animation cowboy2_anim;
	Animation cowboy3_anim;
	Animation cowboy4_anim;
	Animation cowboy5_anim;
	Animation cowboy6_anim;
	Animation cowboy7_anim;
	Animation cowboy8_anim;
	Animation cowboy9_anim;
	Animation cowboy10_anim;
	Animation cowboy11_anim;

	//Bools

	bool flag1_state = false;
	bool flag2_state = false;
	bool flag3_state = false;

	bool cowboy1_state = true;
	bool cowboy2_state = true;
	bool cowboy3_state = true;
	bool cowboy4_state = true;
	bool cowboy5_state = true;
	bool cowboy6_state = true;
	bool cowboy7_state = true;
	bool cowboy8_state = true;
	bool cowboy9_state = true;
	bool cowboy10_state = true;
	bool cowboy11_state = true;

	bool bonus_x2 = false;
	bool bonus_x4 = false;
	bool bonus_x6 = false;
	bool bonus_x8 = false;
	bool bonus_x10 = false;
	bool hold = false;

	bool game_over = false;

	//Score

	int score_font = -1;
	char scoreboard[10];
	char life_count[10];

	uint score;
	uint high_score;
	uint bump_points;
	uint flag_points;
	uint cowboy_points;
	uint tunel_points;
	uint wagon_points;

	uint bonus;



	//Collision sensors
	
	PhysBody* flag1_sensor = nullptr;
	PhysBody* flag2_sensor = nullptr;
	PhysBody* flag3_sensor = nullptr;

	PhysBody* barrel1_sensor = nullptr;
	PhysBody* barrel2_sensor = nullptr;

	PhysBody* bumper1_sensor = nullptr;
	PhysBody* bumper2_sensor = nullptr;
	PhysBody* bumper3_sensor = nullptr;
	
	PhysBody* wagon_sensor = nullptr;

	PhysBody* tunel_sensor = nullptr;
};
