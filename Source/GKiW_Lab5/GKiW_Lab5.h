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
