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
	left_flipper = { 2, 3, 72, 21 };
	right_flipper = { 2, 28, 72, 21 };
}

ModulePlayer::~ModulePlayer() {}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	ball_tex = App->textures->Load("Assets/Textures/ball.png");
	flipper_tex = App->textures->Load("Assets/Textures/flipper.png");

	initialBallPosition = { 620, 200 };
	ball = App->physics->CreateCircle(initialBallPosition.x, initialBallPosition.y, 12, b2_dynamicBody, false);

	putRightFlipper();
	putLeftFlipper();
	
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");


	App->textures->Unload(flipper_tex);
	App->textures->Unload(ball_tex);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	//Drawing ball

	if (ball != nullptr) {

		int ballpos_x;
		int ballpos_y;

		ball->GetPosition(ballpos_x, ballpos_y);
		App->renderer->Blit(ball_tex, ballpos_x, ballpos_y, NULL);
	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT && App->player->life != 0)
	{
		b2Vec2 impulse = b2Vec2(0.0f, -3.5f);
		b2Vec2 point = ball->body->GetLocalCenter();

		ball->body->ApplyLinearImpulse(impulse, point, true);
	}

	//Drawing flippers
	
	rightFlipper1->GetPosition(flipper_position.x, flipper_position.y);
	App->renderer->Blit(flipper_tex, flipper_position.x, flipper_position.y, &right_flipper, 1.0f, rightFlipper1->GetRotation());

	rightFlipper2->GetPosition(position.x, position.y);
	App->renderer->Blit(flipper_tex, position.x, position.y, &right_flipper, 1.0f, rightFlipper2->GetRotation());

	leftFlipper->GetPosition(position.x, position.y);
	App->renderer->Blit(flipper_tex, position.x, position.y, &left_flipper, 1.0f, leftFlipper->GetRotation());

	//Death check



	return UPDATE_CONTINUE;
}

void ModulePlayer::putRightFlipper() {
	// Lower flipper
	rightFlipper1 = App->physics->CreateRectangle(375, 500, 32, 10, b2_dynamicBody);
	rightFlipper1_pivot = App->physics->CreateCircle(393, 489, 3, b2_staticBody, false);

	b2RevoluteJointDef revoluteJointDef1;

	revoluteJointDef1.bodyA = rightFlipper1->body;
	revoluteJointDef1.bodyB = rightFlipper1_pivot->body;

	rightFlipper1->body->SetGravityScale(9.81f);

	revoluteJointDef1.localAnchorA.Set(PIXEL_TO_METERS(25), 0);
	revoluteJointDef1.localAnchorB.Set(0, 0);
	revoluteJointDef1.collideConnected = false;

	revoluteJointDef1.enableLimit = true;
	revoluteJointDef1.upperAngle = 25 * DEGTORAD;
	revoluteJointDef1.lowerAngle = -25 * DEGTORAD;

	revoluteJointDef1.motorSpeed = -2000.0f * DEGTORAD;
	revoluteJointDef1.maxMotorTorque = 1500.0f;
	revoluteJointDef1.enableMotor = false;

	rightFlipperJoint1 = (b2RevoluteJoint*)App->physics->world->CreateJoint(&revoluteJointDef1);

	// Upper flipper
	rightFlipper2 = App->physics->CreateRectangle(475, 280, 32, 10, b2_dynamicBody);
	rightFlipper2_pivot = App->physics->CreateCircle(499, 295, 3, b2_staticBody, false);

	b2RevoluteJointDef revoluteJointDef2;

	revoluteJointDef2.bodyA = rightFlipper2->body;
	revoluteJointDef2.bodyB = rightFlipper2_pivot->body;

	rightFlipper2->body->SetGravityScale(9.81f);

	revoluteJointDef2.localAnchorA.Set(PIXEL_TO_METERS(25), 0);
	revoluteJointDef2.localAnchorB.Set(0, 0);
	revoluteJointDef2.collideConnected = false;

	revoluteJointDef2.enableLimit = true;
	revoluteJointDef2.upperAngle = 25 * DEGTORAD;
	revoluteJointDef2.lowerAngle = -25 * DEGTORAD;

	revoluteJointDef2.motorSpeed = -2000.0f * DEGTORAD;
	revoluteJointDef2.maxMotorTorque = 1500.0f;
	revoluteJointDef2.enableMotor = false;

	rightFlipperJoint2 = (b2RevoluteJoint*)App->physics->world->CreateJoint(&revoluteJointDef2);
}

void ModulePlayer::putLeftFlipper() {
	leftFlipper = App->physics->CreateRectangle(242, 500, 32, 10, b2_dynamicBody);
	leftFlipper_pivot = App->physics->CreateCircle(255, 489, 3, b2_staticBody, false);

	b2RevoluteJointDef revoluteJointDef;

	revoluteJointDef.bodyA = leftFlipper->body;
	revoluteJointDef.bodyB = leftFlipper_pivot->body;
	leftFlipper->body->SetGravityScale(9.81f);

	revoluteJointDef.localAnchorA.Set(PIXEL_TO_METERS(-25), 0);
	revoluteJointDef.localAnchorB.Set(0, 0);
	revoluteJointDef.collideConnected = false;

	revoluteJointDef.enableLimit = true;
	revoluteJointDef.upperAngle = 25 * DEGTORAD;
	revoluteJointDef.lowerAngle = -25 * DEGTORAD;

	revoluteJointDef.motorSpeed = 2000.0f * DEGTORAD;
	revoluteJointDef.maxMotorTorque = 1500.0f;
	revoluteJointDef.enableMotor = false;

	leftFlipperJoint = (b2RevoluteJoint*)App->physics->world->CreateJoint(&revoluteJointDef);
}



