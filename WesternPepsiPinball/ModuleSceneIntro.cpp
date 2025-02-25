#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModuleFonts.h"
#include "ModulePlayer.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	//Bonus flags
	
	flag1_OFF = { 67, 6, 64, 36 };
	flag1_ON = { 2, 6, 64, 36 };
	flag2_OFF = { 75, 57, 50, 41 };
	flag2_ON = { 17, 57, 50, 41 };
	flag3_OFF = { 67, 117, 38, 46 };
	flag3_ON = { 15, 117, 38, 46 };

	//Bonus ON

	bonus_x2_ON = { 63, 221, 26, 19 };
	bonus_x4_ON = { 27, 221, 26, 19 };
	bonus_x6_ON = { 63, 191, 26, 19 };
	bonus_x8_ON = { 101, 220, 26, 19 };
	bonus_x10_ON = { 28, 191, 26, 19 };
	hold_ON = { 101, 190, 26, 19 };

	//Bumper Anim
	bumper1_anim.PushBack({ 116, 7, 45, 36 });
	bumper1_anim.PushBack({ 56, 7, 45, 36 });
	bumper1_anim.loop = false;
	bumper1_anim.speed = 0.2f;

	bumper2_anim.PushBack({ 116, 7, 45, 36 });
	bumper2_anim.PushBack({ 56, 7, 45, 36 });
	bumper2_anim.loop = false;
	bumper2_anim.speed = 0.2f;

	bumper3_anim.PushBack({ 116, 7, 45, 36 });
	bumper3_anim.PushBack({ 56, 7, 45, 36 });
	bumper3_anim.loop = false;
	bumper3_anim.speed = 0.2f;

	//Cowboys

	cowboyON = { 30, 0, 21,46 };
	cowboyOFF = { 0, 0, 21, 46 };

	cowboy1_anim.PushBack(cowboyON);
	cowboy1_anim.PushBack(cowboyOFF);
	cowboy1_anim.loop = false;
	cowboy1_anim.speed = 1.0f;

	cowboy2_anim.PushBack(cowboyON);
	cowboy2_anim.PushBack(cowboyOFF);
	cowboy2_anim.loop = false;
	cowboy2_anim.speed = 1.0f;

	cowboy3_anim.PushBack(cowboyON);
	cowboy3_anim.PushBack(cowboyOFF);
	cowboy3_anim.loop = false;
	cowboy3_anim.speed = 1.0f;

	cowboy4_anim.PushBack(cowboyON);
	cowboy4_anim.PushBack(cowboyOFF);
	cowboy4_anim.loop = false;
	cowboy4_anim.speed = 1.0f;

	cowboy5_anim.PushBack(cowboyON);
	cowboy5_anim.PushBack(cowboyOFF);
	cowboy5_anim.loop = false;
	cowboy5_anim.speed = 1.0f;

	cowboy6_anim.PushBack(cowboyON);
	cowboy6_anim.PushBack(cowboyOFF);
	cowboy6_anim.loop = false;
	cowboy6_anim.speed = 1.0f;

	cowboy7_anim.PushBack(cowboyON);
	cowboy7_anim.PushBack(cowboyOFF);
	cowboy7_anim.loop = false;
	cowboy7_anim.speed = 1.0f;

	cowboy8_anim.PushBack(cowboyON);
	cowboy8_anim.PushBack(cowboyOFF);
	cowboy8_anim.loop = false;
	cowboy8_anim.speed = 1.0f;

	cowboy9_anim.PushBack(cowboyON);
	cowboy9_anim.PushBack(cowboyOFF);
	cowboy9_anim.loop = false;
	cowboy9_anim.speed = 1.0f;

	cowboy10_anim.PushBack(cowboyON);
	cowboy10_anim.PushBack(cowboyOFF);
	cowboy10_anim.loop = false;
	cowboy10_anim.speed = 1.0f;

	cowboy11_anim.PushBack(cowboyON);
	cowboy11_anim.PushBack(cowboyOFF);
	cowboy11_anim.loop = false;
	cowboy11_anim.speed = 1.0f;

}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	//Load textures

	background = App->textures->Load("Assets/Textures/background.png");
	background2 = App->textures->Load("Assets/Textures/background2.png");
	barrels1 = App->textures->Load("Assets/Textures/barrels1.png");
	barrels2 = App->textures->Load("Assets/Textures/barrels2.png");
	bumper = App->textures->Load("Assets/Textures/bouncers.png");
	switches = App->textures->Load("Assets/Textures/switches.png");
	multipliersOFF = App->textures->Load("Assets/Textures/multipliersOFF.png");
	multipliersON = App->textures->Load("Assets/Textures/multipliersON.png");

	final_score = App->textures->Load("Assets/Textures/finalScore.png");

	//Load Music and SFX

	intro_music = App->audio->LoadFx("Assets/Audio/bgMusic.wav");

	//Load Fonts

	score_font = App->fonts->Load("Assets/Fonts/score.png", "0123845679", 2);

	//Each sensor gives a different amount of points to the player

	score = 000000000000;
	high_score = 123123;
	bonus = 0;

	bump_points = 500;
	flag_points = 1000;
	cowboy_points = 1000;
	tunel_points = 250000;
	wagon_points = 500000;

	App->audio->PlayFx(intro_music);
	createSensors();

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	
	App->textures->Unload(barrels1);
	App->textures->Unload(barrels2);
	App->textures->Unload(bumper);
	App->textures->Unload(switches);
	App->textures->Unload(multipliersOFF);
	App->textures->Unload(multipliersON);

	App->textures->Unload(background);
	App->textures->Unload(background2);

	App->textures->Unload(final_score);
	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	//Blit Textures

	App->renderer->Blit(background, 0, 0);

	App->renderer->Blit(barrels1, 146, 340);
	App->renderer->Blit(barrels2, 409, 347);

	App->renderer->Blit(multipliersOFF, 193, 233);

	//Blit Cowboys

	App->renderer->Blit(bumper, 325, 143, &cowboy1_anim.GetCurrentFrame());
	App->renderer->Blit(bumper, 304, 155, &cowboy2_anim.GetCurrentFrame());
	App->renderer->Blit(bumper, 284, 166, &cowboy3_anim.GetCurrentFrame());
	App->renderer->Blit(bumper, 265, 175, &cowboy4_anim.GetCurrentFrame());
	App->renderer->Blit(bumper, 245, 187, &cowboy5_anim.GetCurrentFrame());
	App->renderer->Blit(bumper, 224, 199, &cowboy6_anim.GetCurrentFrame());
	App->renderer->Blit(bumper, 337, 171, &cowboy7_anim.GetCurrentFrame());
	App->renderer->Blit(bumper, 319, 181, &cowboy8_anim.GetCurrentFrame());
	App->renderer->Blit(bumper, 301, 194, &cowboy9_anim.GetCurrentFrame());
	App->renderer->Blit(bumper, 282, 204, &cowboy10_anim.GetCurrentFrame());
	App->renderer->Blit(bumper, 266, 214, &cowboy11_anim.GetCurrentFrame());

	//Blit Bumpers

	b1rect = bumper1_anim.GetCurrentFrame();
	b2rect = bumper2_anim.GetCurrentFrame();
	b3rect = bumper3_anim.GetCurrentFrame();

	App->renderer->Blit(bumper, 398, 146, &b1rect);
	App->renderer->Blit(bumper, 402, 187, &b2rect);
	App->renderer->Blit(bumper, 454, 163, &b3rect);

	//Blit bonus flags

	if (flag1_state)
	{
		App->renderer->Blit(multipliersON, 409, 102, &flag1_ON);
	}
	else
	{
		App->renderer->Blit(multipliersON, 409, 102, &flag1_OFF);
	}
	if (flag2_state)
	{
		App->renderer->Blit(multipliersON, 455, 110, &flag2_ON);
	}
	else
	{
		App->renderer->Blit(multipliersON, 455, 110, &flag2_OFF);
	}
	if (flag3_state)
	{
		App->renderer->Blit(multipliersON, 500, 118, &flag3_ON);
	}
	else
	{
		App->renderer->Blit(multipliersON, 500, 118, &flag3_OFF);
	}

	App->renderer->Blit(switches, 431, 106);
	App->renderer->Blit(background2, 26, 82);

	//Blit active bonuses
	if (bonus_x2)
	{ 
		App->renderer->Blit(multipliersON, 310, 467, &bonus_x2_ON);
	}

	if (bonus_x4)
	{
		App->renderer->Blit(multipliersON, 310, 432, &bonus_x4_ON);
	}

	if (bonus_x6)
	{
		App->renderer->Blit(multipliersON, 267, 421, &bonus_x6_ON);
	}

	if (bonus_x8)
	{
		App->renderer->Blit(multipliersON, 350, 421, &bonus_x8_ON);
	}

	if (bonus_x10)
	{
		App->renderer->Blit(multipliersON, 207, 332, &bonus_x10_ON);
	}

	if (hold)
	{
		App->renderer->Blit(multipliersON, 448, 332, &hold_ON);
	}

	//Scoreboard

	if (App->player->life <= App->player->max_lives)
	{

		sprintf_s(life_count, 10, "%1d", App->player->life);
		App->fonts->BlitText(200, 473, score_font, life_count);

		sprintf_s(scoreboard, 10, "%7d", score);
		App->fonts->BlitText(97, 473, score_font, scoreboard);

		sprintf_s(scoreboard, 10, "%7d", high_score);
		App->fonts->BlitText(97, 525, score_font, scoreboard);
	}

	//Game Over

	if (game_over) 
	{
		App->renderer->Blit(final_score, 170, 100);

		sprintf_s(scoreboard, 10, "%7d", high_score);
		App->fonts->BlitText(280, 130, score_font, scoreboard);
	}

	// Prepare for raycast ------------------------------------------------------

	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();

	return UPDATE_CONTINUE;

}

//Create Collider Sensors

void ModuleSceneIntro::createSensors() {

	// Sensors for the flags
	flag1_sensor = App->physics->CreateRectangleSensor(440, 114, 10, 10);
	flag2_sensor = App->physics->CreateRectangleSensor(475, 125, 10, 10);
	flag3_sensor = App->physics->CreateRectangleSensor(515, 135, 10, 10);

	// Sensors for the bumpers
	bumper1_sensor = App->physics->CreateRectangleSensor(418, 165, 40, 30);
	bumper2_sensor = App->physics->CreateRectangleSensor(422, 205, 40, 30);
	bumper3_sensor = App->physics->CreateRectangleSensor(473, 183, 40, 30);

	// Sensors for the barrel
	barrel1_sensor = App->physics->CreateRectangleSensor(190, 380, 80, 60);
	barrel2_sensor = App->physics->CreateRectangleSensor(445, 390, 80, 60);
	

	// Sensor for the wagon
	wagon_sensor = App->physics->CreateRectangleSensor(135, 255, 15, 15);

	// Sensors for the path
	tunel_sensor = App->physics->CreateRectangleSensor(550, 275, 15, 15);
	
}



void ModuleSceneIntro::setBonus() {

	if (flag1_state == true && flag2_state == true && flag3_state == true) {
		bonus++;
		score += flag_points;
		flag1_state = false;
		flag2_state = false;
		flag3_state = false;

		switch (bonus) {
		case 1: bonus_x2 = true;
			break;
		case 2: bonus_x4 = true;
			break;
		case 3: bonus_x6 = true;
			break;
		case 4: bonus_x8 = true;
			break;
		case 5: bonus_x10 = true;
			break;
		case 6: hold = true;
			break;
		}

	}
}

