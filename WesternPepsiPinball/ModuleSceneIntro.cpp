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

	//Bumper Anim
	bumper1.PushBack({ 116, 7, 45, 36 });
	bumper1.PushBack({ 56, 7, 45, 36 });
	bumper1.loop = false;
	bumper1.speed = 0.2f;

	bumper2.PushBack({ 116, 7, 45, 36 });
	bumper2.PushBack({ 56, 7, 45, 36 });
	bumper2.loop = false;
	bumper2.speed = 0.2f;

	bumper3.PushBack({ 116, 7, 45, 36 });
	bumper3.PushBack({ 56, 7, 45, 36 });
	bumper3.loop = false;
	bumper3.speed = 0.2f;
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
	multipliersOFF = App->textures->Load("Assets/Textures/multipliersOFF.png");
	switches = App->textures->Load("Assets/Textures/switches.png");

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	
	App->textures->Unload(barrels1);
	App->textures->Unload(barrels2);
	App->textures->Unload(bumper);
	App->textures->Unload(multipliersOFF);
	App->textures->Unload(switches);

	App->textures->Unload(background);
	App->textures->Unload(background2);
	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	//Blit Textures
	App->renderer->Blit(background, 0, 0);
	App->renderer->Blit(background2, 26, 82);
	App->renderer->Blit(barrels1, 146, 340);
	App->renderer->Blit(barrels2, 409, 347);
	App->renderer->Blit(multipliersOFF, 193, 233);
	App->renderer->Blit(switches, 431, 106);


	//Blit Bumpers
	b1rect = bumper1.GetCurrentFrame();
	b2rect = bumper2.GetCurrentFrame();
	b3rect = bumper3.GetCurrentFrame();

	App->renderer->Blit(bumper, 398, 146, &b1rect);
	App->renderer->Blit(bumper, 402, 187, &b2rect);
	App->renderer->Blit(bumper, 454, 163, &b3rect);

	// Prepare for raycast ------------------------------------------------------

	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();

	return UPDATE_CONTINUE;

}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

}

