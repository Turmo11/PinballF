#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	//Bonus flags
	
	flag1_OFF = { 67, 6, 64, 36 };
	flag1_ON = { 2, 6, 64, 36 };
	flag2_OFF = { 75, 57, 50, 41 };
	flag2_ON = { 17, 57, 50, 41 };
	flag3_OFF = { 67, 117, 38, 46 };
	flag3_ON = { 15, 117, 38, 46 };

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
	// Prepare for raycast ------------------------------------------------------

	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();

	return UPDATE_CONTINUE;

}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

}

