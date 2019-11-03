#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePhysics.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleWindow.h"
#include "ModuleSceneIntro.h"
#include "Box2D/Box2D/Box2D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled) 
{
	leftFlipper_section = { 2, 3, 72, 21 };
	rightFlipper_section = { 2, 28, 72, 21 };

	horse.PushBack({ 48, 58, 72, 104 });
	horse.PushBack({ 150, 58, 72, 104 });
	horse.PushBack({ 242, 58, 72, 104 });
	horse.PushBack({ 331, 59, 72, 104 });
	horse.PushBack({ 242, 58, 72, 104 });
	horse.PushBack({ 48, 58, 72, 104 });

	horse.speed = 0.15f;
	horse.loop = false;
}

ModulePlayer::~ModulePlayer() {}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	//Audios

	flipperSound = App->audio->LoadFx("Assets/Audio/flipper.wav");
	horseSound = App->audio->LoadFx("Assets/Audio/horse.wav");
	thrillingSound = App->audio->LoadFx("Assets/Audio/thrill.wav");
	henSound = App->audio->LoadFx("Assets/Audio/hen.wav");
	loseSound = App->audio->LoadFx("Assets/Audio/lose.wav");
	touchingHat = App->audio->LoadFx("Assets/Audio/touchingHat.wav");
	wolfSound = App->audio->LoadFx("Assets/Audio/wolf.wav");
	barrelSound = App->audio->LoadFx("Assets/Audio/barrel.wav");
	newBallSound = App->audio->LoadFx("Assets/Audio/newBall.wav");

	//Textures

	ball_tex = App->textures->Load("Assets/Textures/ball.png");
	flipper_tex = App->textures->Load("Assets/Textures/flipper.png");
	horse_tex = App->textures->Load("Assets/Textures/horse.png");

	initialBallPosition = { 620, 200 };

	AddBall(initialBallPosition.x, initialBallPosition.y);
	CreateFlippers();
	CreateLauncher();

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");


	App->textures->Unload(flipper_tex);
	App->textures->Unload(ball_tex);
	App->textures->Unload(horse_tex);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	DrawEverything();

	//Controlls

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT && App->player->life != 0)
	{
		b2Vec2 impulse = b2Vec2(0.0f, -3.5f);
		b2Vec2 point = ball->body->GetLocalCenter();

		ball->body->ApplyLinearImpulse(impulse, point, true);
	}	

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
	{
		leftFlipperJoint->EnableMotor(true);
		if (flipperplayed == false) 
		{
			App->audio->PlayFx(flipperSound);
		}
		flipperplayed = true;
	}
	else if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
	{
		leftFlipperJoint->EnableMotor(false);
		flipperplayed = false;
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		rightFlipperJoint1->EnableMotor(true);
		rightFlipperJoint2->EnableMotor(true);
		if (flipperplayed == false)
		{
			App->audio->PlayFx(flipperSound);
		}
		flipperplayed = true;
	}
	else if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
	{
		rightFlipperJoint1->EnableMotor(false);
		rightFlipperJoint2->EnableMotor(false);
		flipperplayed = false;
	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) {
		propellerJoint->EnableMotor(true);
		App->audio->PlayFx(horseSound);
		horse.Reset();
	}
	else
	{
		propellerJoint->EnableMotor(false);
	}

	SDL_Rect r = horse.GetCurrentFrame();
	App->renderer->Blit(horse_tex, 600, 390, &r);

	//Death check



	return UPDATE_CONTINUE;
}

void ModulePlayer::AddBall(uint x, uint y)
{
	ball = App->physics->CreateCircle(initialBallPosition.x, initialBallPosition.y, 12, b2_dynamicBody, false);
}

void ModulePlayer::CreateFlippers()
{
	// Right Lower flipper

	rightFlipper1 = App->physics->CreateRectangle(375, 500, 32, 10, b2_dynamicBody);
	rightFlipper1_pivot = App->physics->CreateCircle(393, 489, 3, b2_staticBody, false);

	b2RevoluteJointDef joint;

	joint.bodyA = rightFlipper1->body;
	joint.bodyB = rightFlipper1_pivot->body;

	rightFlipper1->body->SetGravityScale(9.81f);

	joint.localAnchorA.Set(PIXEL_TO_METERS(25), 0);
	joint.localAnchorB.Set(0, 0);
	joint.collideConnected = false;

	joint.enableLimit = true;
	joint.upperAngle = 25 * DEGTORAD;
	joint.lowerAngle = -25 * DEGTORAD;

	joint.motorSpeed = -2000.0f * DEGTORAD;
	joint.maxMotorTorque = 1500.0f;
	joint.enableMotor = false;

	rightFlipperJoint1 = (b2RevoluteJoint*)App->physics->world->CreateJoint(&joint);

	// Right Upper flipper

	rightFlipper2 = App->physics->CreateRectangle(475, 280, 32, 10, b2_dynamicBody);
	rightFlipper2_pivot = App->physics->CreateCircle(499, 295, 3, b2_staticBody, false);

	joint.bodyA = rightFlipper2->body;
	joint.bodyB = rightFlipper2_pivot->body;

	rightFlipper2->body->SetGravityScale(9.81f);

	joint.localAnchorA.Set(PIXEL_TO_METERS(25), 0);
	joint.localAnchorB.Set(0, 0);
	joint.collideConnected = false;

	joint.enableLimit = true;
	joint.upperAngle = 25 * DEGTORAD;
	joint.lowerAngle = -25 * DEGTORAD;

	joint.motorSpeed = -2000.0f * DEGTORAD;
	joint.maxMotorTorque = 1500.0f;
	joint.enableMotor = false;

	rightFlipperJoint2 = (b2RevoluteJoint*)App->physics->world->CreateJoint(&joint);

	//Left Flipper

	leftFlipper = App->physics->CreateRectangle(242, 500, 32, 10, b2_dynamicBody);
	leftFlipper_pivot = App->physics->CreateCircle(255, 489, 3, b2_staticBody, false);

	joint.bodyA = leftFlipper->body;
	joint.bodyB = leftFlipper_pivot->body;

	leftFlipper->body->SetGravityScale(9.81f);

	joint.localAnchorA.Set(PIXEL_TO_METERS(-25), 0);
	joint.localAnchorB.Set(0, 0);
	joint.collideConnected = false;

	joint.enableLimit = true;
	joint.upperAngle = 25 * DEGTORAD;
	joint.lowerAngle = -25 * DEGTORAD;

	joint.motorSpeed = 2000.0f * DEGTORAD;
	joint.maxMotorTorque = 1500.0f;
	joint.enableMotor = false;

	leftFlipperJoint = (b2RevoluteJoint*)App->physics->world->CreateJoint(&joint);
}

void ModulePlayer::CreateLauncher()
{
	propeller = App->physics->CreateRectangle(640, 428, 10, 30, b2_dynamicBody);
	propeller_pivot = App->physics->CreateCircle(640, 428, 5, b2_staticBody, false);

	b2PrismaticJointDef joint;

	joint.bodyA = propeller->body;
	joint.bodyB = propeller_pivot->body;

	joint.localAxisA.Set(0, 1);

	joint.localAnchorA.Set(0, 0);
	joint.localAnchorB.Set(0, 0);
	joint.collideConnected = false;

	joint.upperTranslation = PIXEL_TO_METERS(50);
	joint.enableLimit = true;
	joint.lowerTranslation = 0;

	joint.enableMotor = false;
	joint.maxMotorForce = 700;
	joint.motorSpeed = 5000;

	propellerJoint = (b2PrismaticJoint*)App->physics->world->CreateJoint(&joint);
}

void ModulePlayer::DrawEverything()
{
	ball->GetPosition(position.x, position.y);
	App->renderer->Blit(ball_tex, position.x, position.y, NULL);

	rightFlipper1->GetPosition(position.x, position.y);
	App->renderer->Blit(flipper_tex, position.x, position.y, &rightFlipper_section, 1.0f, rightFlipper1->GetRotation());

	rightFlipper2->GetPosition(position.x, position.y);
	App->renderer->Blit(flipper_tex, position.x, position.y, &rightFlipper_section, 1.0f, rightFlipper2->GetRotation());

	leftFlipper->GetPosition(position.x, position.y);
	App->renderer->Blit(flipper_tex, position.x, position.y, &leftFlipper_section, 1.0f, leftFlipper->GetRotation());

	SDL_Rect r = horse.GetCurrentFrame();
	App->renderer->Blit(horse_tex, 600, 390, &r);
}




