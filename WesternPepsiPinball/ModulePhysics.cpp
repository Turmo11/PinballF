#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"
#include "p2Point.h"
#include "math.h"

#ifdef _DEBUG
#pragma comment( lib, "Box2D/libx86/Debug/Box2D.lib" )
#else
#pragma comment( lib, "Box2D/libx86/Release/Box2D.lib" )
#endif

int background[132] = {
	0, 521,
	231, 521,
	241, 508,
	243, 500,
	243, 478,
	237, 465,
	220, 454,
	163, 429,
	135, 411,
	84, 366,
	62, 334,
	45, 285,
	50, 271,
	64, 263,
	174, 218,
	202, 231,
	410, 121,
	420, 100,
	445, 86,
	484, 79,
	504, 80,
	515, 85,
	526, 100,
	569, 100,
	585, 107,
	600, 117,
	621, 141,
	630, 154,
	638, 173,
	646, 205,
	654, 248,
	654, 289,
	660, 389,
	669, 515,
	545, 515,
	557, 427,
	600, 400,
	618, 390,
	620, 377,
	621, 275,
	603, 183,
	590, 156,
	573, 140,
	543, 135,
	537, 142,
	538, 160,
	544, 185,
	544, 231,
	560, 266,
	573, 278,
	590, 307,
	600, 366,
	596, 389,
	588, 404,
	579, 412,
	557, 421,
	494, 423,
	444, 439,
	422, 455,
	408, 475,
	405, 487,
	407, 495,
	400, 521,
	687, 521,
	687, 0,
	0, 0,

};

int background2[18] = {
	516, 270,
	508, 339,
	497, 385,
	505, 392,
	524, 395,
	550, 390,
	565, 379,
	567, 360,

};

int Barrels1[10] = {
	150, 350,
	205, 347,
	237, 410,
	218, 415,
	145, 374,
};

int Barrels2[8] = {
	390, 425,
	465, 385,
	465, 345,
	380, 395,
};

int fence[8] = {
	80, 305,
	150, 265,
	155, 270,
	85, 310,
};

int pillar1[6] = {
	495, 120,
	495, 130,
	504, 123,
};

int pillar2[6] = {
	457, 118,
	465, 116,
	456, 125
};

int bumper[16] = {
	400, 170,
	400, 160,
	405, 155,
	430, 155,
	435, 160,
	435, 170,
	430, 175,
	405, 175,
};

int cowboy[8] = {
	330, 157,
	330, 182,
	344, 175,
	344, 150,
};
ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	world = NULL;
	mouse_joint = NULL;
	debug = false;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");

	world = new b2World(b2Vec2(GRAVITY_X, -GRAVITY_Y));
	world->SetContactListener(this);

	// Needed to create joints like mouse joint
	b2BodyDef bd;
	ground = world->CreateBody(&bd);

	int x = SCREEN_WIDTH / 2;
	int y = SCREEN_HEIGHT / 1.5f;
	int width = 200;
	int height = 200;
	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	CreateChain(0, 0, background, 132, b2_staticBody, 0);

	CreateChain(0, 0, background2, 16, b2_staticBody, 0);

	CreateChain(0, 0, Barrels1, 10, b2_staticBody, 2);

	CreateChain(20, 0, Barrels2, 8, b2_staticBody, 2);

	CreateChain(0, 0, fence, 8, b2_staticBody, 0);

	CreateChain(0, 0, pillar1, 6, b2_staticBody, 0);

	CreateChain(0, 0, pillar2, 6, b2_staticBody, 0);

	//bumpers

	CreateChain(0, 0, bumper, 16, b2_staticBody, 2);

	CreateChain(4, 40, bumper, 16, b2_staticBody, 2);

	CreateChain(55, 15, bumper, 16, b2_staticBody, 2);

	//cowboys

	CreateChain(0, 0, cowboy, 8, b2_staticBody, 0);

	CreateChain(-20, 13, cowboy, 8, b2_staticBody, 0);

	CreateChain(-40, 26, cowboy, 8, b2_staticBody, 0);

	CreateChain(-60, 39, cowboy, 8, b2_staticBody, 0);

	CreateChain(-80, 52, cowboy, 8, b2_staticBody, 0);

	CreateChain(-100, 65, cowboy, 8, b2_staticBody, 0);

	CreateChain(12, 31, cowboy, 8, b2_staticBody, 0);

	CreateChain(-6, 44, cowboy, 8, b2_staticBody, 0);

	CreateChain(-23, 57, cowboy, 8, b2_staticBody, 0);

	CreateChain(-43, 70, cowboy, 8, b2_staticBody, 0);

	CreateChain(-63, 80, cowboy, 8, b2_staticBody, 0);

	//b->CreateFixture(&fixture);

	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	world->Step(1.0f / 60.0f, 6, 2);

	for (b2Contact* c = world->GetContactList(); c; c = c->GetNext())
	{
		if (c->GetFixtureA()->IsSensor() && c->IsTouching())
		{
			PhysBody* pb1 = (PhysBody*)c->GetFixtureA()->GetBody()->GetUserData();
			PhysBody* pb2 = (PhysBody*)c->GetFixtureB()->GetBody()->GetUserData();
			if (pb1 && pb2 && pb1->listener)
				pb1->listener->OnCollision(pb1, pb2);
		}
	}

	return UPDATE_CONTINUE;
}

PhysBody* ModulePhysics::CreateCircle(int x, int y, int radius, b2BodyType type)
{
	b2BodyDef body;
	body.type = type;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2CircleShape shape;
	shape.m_radius = PIXEL_TO_METERS(radius);
	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = 1.0f;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = radius;

	return pbody;
}

PhysBody* ModulePhysics::CreateRectangle(int x, int y, int width, int height, b2BodyType type)
{
	b2BodyDef body;
	body.type = type;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);
	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(width), PIXEL_TO_METERS(height));

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;
	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = width;
	pbody->height = height;

	return pbody;
}

PhysBody* ModulePhysics::CreateRectangleSensor(int x, int y, int width, int height)
{
	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(width) * 0.5f, PIXEL_TO_METERS(height) * 0.5f);

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;
	fixture.isSensor = true;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = width;
	pbody->height = height;

	return pbody;
}

PhysBody* ModulePhysics::CreateChain(int x, int y, int* points, int size, b2BodyType type, int res)
{
	b2BodyDef body;
	body.type = type;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2ChainShape shape;
	b2Vec2* p = new b2Vec2[size / 2];

	for (uint i = 0; i < size / 2; ++i)
	{
		p[i].x = PIXEL_TO_METERS(points[i * 2 + 0]);
		p[i].y = PIXEL_TO_METERS(points[i * 2 + 1]);
	}

	shape.CreateLoop(p, size / 2);

	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.restitution = res;


	b->CreateFixture(&fixture);

	delete p;

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = 0;

	return pbody;
}


// 
update_status ModulePhysics::PostUpdate()
{
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if (!debug)
		return UPDATE_CONTINUE;

	b2Body* body_clicked = nullptr;
	b2Vec2 mouse_position;
	mouse_position.x = PIXEL_TO_METERS(App->input->GetMouseX());
	mouse_position.y = PIXEL_TO_METERS(App->input->GetMouseY());

	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch (f->GetType())
			{
				// Draw circles ------------------------------------------------
			case b2Shape::e_circle:
			{
				b2CircleShape* shape = (b2CircleShape*)f->GetShape();
				b2Vec2 pos = f->GetBody()->GetPosition();
				App->renderer->DrawCircle(METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), METERS_TO_PIXELS(shape->m_radius), 255, 255, 255);
			}
			break;

			// Draw polygons ------------------------------------------------
			case b2Shape::e_polygon:
			{
				b2PolygonShape* polygonShape = (b2PolygonShape*)f->GetShape();
				int32 count = polygonShape->GetVertexCount();
				b2Vec2 prev, v;

				for (int32 i = 0; i < count; ++i)
				{
					v = b->GetWorldPoint(polygonShape->GetVertex(i));
					if (i > 0)
						App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);

					prev = v;
				}

				v = b->GetWorldPoint(polygonShape->GetVertex(0));
				App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);
			}
			break;

			// Draw chains contour -------------------------------------------
			case b2Shape::e_chain:
			{
				b2ChainShape* shape = (b2ChainShape*)f->GetShape();
				b2Vec2 prev, v;

				for (int32 i = 0; i < shape->m_count; ++i)
				{
					v = b->GetWorldPoint(shape->m_vertices[i]);
					if (i > 0)
						App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
					prev = v;
				}
			}
			break;

			// Draw a single segment(edge) ----------------------------------
			case b2Shape::e_edge:
			{
				b2EdgeShape* shape = (b2EdgeShape*)f->GetShape();
				b2Vec2 v1, v2;

				v1 = b->GetWorldPoint(shape->m_vertex0);
				v1 = b->GetWorldPoint(shape->m_vertex1);
				App->renderer->DrawLine(METERS_TO_PIXELS(v1.x), METERS_TO_PIXELS(v1.y), METERS_TO_PIXELS(v2.x), METERS_TO_PIXELS(v2.y), 100, 100, 255);
			}
			break;
			}

			// TODO 1: If mouse button 1 is pressed ...
			if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN)
			{
				if (f->TestPoint(mouse_position))
					body_clicked = b;
			}
			// test if the current body contains mouse position
		}
	}

	// If a body was selected we will attach a mouse joint to it
	// so we can pull it around
	// TODO 2: If a body was selected, create a mouse joint
	// using mouse_joint class property
	if (body_clicked != nullptr)
	{
		b2MouseJointDef def;
		def.bodyA = ground;
		def.bodyB = body_clicked;
		def.target = mouse_position;
		def.dampingRatio = 0.5f;
		def.frequencyHz = 2.0f;
		def.maxForce = 100.0f*body_clicked->GetMass();
		mouse_joint = (b2MouseJoint*)world->CreateJoint(&def);
	}


	// TODO 3: If the player keeps pressing the mouse button, update
	// target position and draw a red line between both anchor points
	if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT && mouse_joint != nullptr)
	{
		mouse_joint->SetTarget(mouse_position);
	}

	// TODO 4: If the player releases the mouse button, destroy the joint
	if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_UP && mouse_joint != nullptr)
	{
		world->DestroyJoint(mouse_joint);
		mouse_joint = nullptr;
		body_clicked = nullptr;
	}

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	// Delete the whole physics world!
	delete world;

	return true;
}

void PhysBody::GetPosition(int& x, int &y) const
{
	b2Vec2 pos = body->GetPosition();
	x = METERS_TO_PIXELS(pos.x) - (width);
	y = METERS_TO_PIXELS(pos.y) - (height);
}

float PhysBody::GetRotation() const
{
	return RADTODEG * body->GetAngle();
}

bool PhysBody::Contains(int x, int y) const
{
	b2Vec2 p(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	const b2Fixture* fixture = body->GetFixtureList();

	while (fixture != NULL)
	{
		if (fixture->GetShape()->TestPoint(body->GetTransform(), p) == true)
			return true;
		fixture = fixture->GetNext();
	}

	return false;
}

int PhysBody::RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const
{
	int ret = -1;

	b2RayCastInput input;
	b2RayCastOutput output;

	input.p1.Set(PIXEL_TO_METERS(x1), PIXEL_TO_METERS(y1));
	input.p2.Set(PIXEL_TO_METERS(x2), PIXEL_TO_METERS(y2));
	input.maxFraction = 1.0f;

	const b2Fixture* fixture = body->GetFixtureList();

	while (fixture != NULL)
	{
		if (fixture->GetShape()->RayCast(&output, input, body->GetTransform(), 0) == true)
		{
			// do we want the normal ?

			float fx = x2 - x1;
			float fy = y2 - y1;
			float dist = sqrtf((fx*fx) + (fy*fy));

			normal_x = output.normal.x;
			normal_y = output.normal.y;

			return output.fraction * dist;
		}
		fixture = fixture->GetNext();
	}

	return ret;
}

void ModulePhysics::BeginContact(b2Contact* contact)
{
	PhysBody* physA = (PhysBody*)contact->GetFixtureA()->GetBody()->GetUserData();
	PhysBody* physB = (PhysBody*)contact->GetFixtureB()->GetBody()->GetUserData();

	if (physA && physA->listener != NULL)
		physA->listener->OnCollision(physA, physB);

	if (physB && physB->listener != NULL)
		physB->listener->OnCollision(physB, physA);
}