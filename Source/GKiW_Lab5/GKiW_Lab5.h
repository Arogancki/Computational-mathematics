#pragma once

#define PI 3.14159265
#define WHITE color(1,1,1)

// Deklaracje funkcji u¿ywanych jako obs³uga zdarzeñ GLUT-a.
void OnRender();
void OnReshape(int, int);
void OnKeyPress(unsigned char, int, int);
void OnKeyDown(unsigned char, int, int);
void OnKeyUp(unsigned char, int, int);
void OnMouseMove(int, int);
void MouseButton(int button, int state, int x, int y);
void OnTimer(int);
void MonsterSpawner(int);
void TimePassed(int);
void BulletFireLogic(int);

struct vec3 {
	float x, y, z;

	vec3()
	{}

	vec3(float x, float y, float z)
		: x(x), y(y), z(z)
	{}
	vec3(const vec3 &v) 
		: x(v.x), y(v.y), z(v.z)
	{}
};

struct color {
	float r, g, b;

	color(float r, float g, float b)
		: r(r), g(g), b(b)
	{}
	color(const color &v)
		: r(v.r), g(v.g), b(v.b)
	{}
};

struct SCameraState {
	vec3 pos;
	vec3 dir;
	float speed;
	float velRX, velRY, velM, velS;
};

struct Monster {
	vec3 pos;
	vec3 dir;
	int hitpoints = 20;
	int time_waited = 0;
	float speed = 0.04f;
	bool attack = false;

	float height = 2.0f;

	Monster(vec3 pos, vec3 dir)
		:pos(pos), dir(dir)
	{}
};

struct Bullet {
	vec3 pos;
	vec3 dir;
	int Distance_To_Travel = 1000;
	int damage = 20;
	// lepiej nie modyfikowaæ prêdkoœci pocisków
	// wiêcej == szybciej == bêdzie omijaæ potwory
	// mniej == wolniej == potwory bêd¹ omijaæ pocisk
	float speed = 0.4f;

	Bullet(vec3 pos, vec3 dir)
		: pos(pos), dir(dir)
	{}
};