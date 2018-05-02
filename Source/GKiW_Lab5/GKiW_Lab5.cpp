#include "stdafx.h"
#include "OBJLoader.h"
#include "FileParser.h"

#define debug true

#pragma region Zmienne globalne
SCameraState player;
std::vector<Point3D> points;

// Game
bool captureMouse = true;
bool free3DMovement = true;

int mouseX = 0;
int mouseY = 0;

float mouseSensitivity = .15f;

#pragma endregion

void drawText(float x, float y, std::string st);
void BetterDraw(float x, float y, std::string message, color color);

// https://stackoverflow.com/questions/686353/c-random-float-number-generation
float GetRandomFloat() {
	return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

ParsedData *shapeConfig;
Shape *outter;
int main(int argc, char* argv[])
{
	//try {
	// load file
	string filePath;
	cout << "Please enter path to file with shape specification:\n";
	if (!debug)
		cin >> filePath;
	else
		filePath = "./testFile.txt";

	ParsedData sc = FileParser::parse(filePath); // tej funkcji (pacz linia nizej)
	shapeConfig = &sc; // nie wiem czemu ale odrazu z funkcji nie dzialalo (shapes.size() bylo rowne 0)

	Shape sssss = sc.shapes[0].getCubeAround();
	outter = &sssss;

	if (debug) {
		int i = 0;
		for (Shape shape : shapeConfig->shapes) {
			cout << "\nShape: " << ++i << " = " << shape.getPoints().size() - 1 << " lines.\nPoints:" << "\n";
			int j = 0;
			for (Point3D point3D : shape.getPoints())
				cout << "point: " << ++j << " = " << point3D.getX() << "x" << point3D.getY() << "x" << point3D.getZ() << "\n";
		}
	}
	
	for (float i = 0; i <= 1; i += 0.1) {
		points.push_back(Point3D(i, i, i));
		points.push_back(Point3D(1 - i, 0, 1 - i));
		points.push_back(Point3D(1 - i, 1, i));
		//points.push_back(Point3D(0, i, 1-i));
	}

	/*for (int i = 0; i < 30; i++) {
		points.push_back(Point3D(GetRandomFloat(), GetRandomFloat(), GetRandomFloat()));
	}*/


	glutInit(&argc, argv);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 360);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	//TODO zmieniæ nazwê gry!
	glutCreateWindow("Calkowanie figur?? xDxD");

	glutDisplayFunc(OnRender);
	glutReshapeFunc(OnReshape);
	glutKeyboardFunc(OnKeyPress);
	glutKeyboardUpFunc(OnKeyUp);
	glutPassiveMotionFunc(OnMouseMove);
	glutMotionFunc(OnMouseMove);
	glutTimerFunc(17, OnTimer, 0);
	
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	
	float gl_amb[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gl_amb);

	player.pos.x = 0.0f;
	player.pos.y = 1.0f;
	player.pos.z = 4.0f;

	player.dir.x = 0.0f;
	player.dir.y = 0.0f;
	player.dir.z = -1.0f;

	player.speed = .4f;

	glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
	mouseX = glutGet(GLUT_WINDOW_WIDTH) / 2;
	mouseY = glutGet(GLUT_WINDOW_HEIGHT) / 2;
	glutSetCursor(GLUT_CURSOR_NONE);
	
	glutMainLoop();

	return 0;
	/*
	}catch (const std::exception exceptional_result) {
		std::cout << exceptional_result.what() << '\n';
		string x;
		cin >> x;
		return -1;
	}
	*/
}

#pragma region Obsluga wejscia

bool keystate[255];

void OnKeyPress(unsigned char key, int x, int y) {
	if (!keystate[key]) {
		keystate[key] = true;
		OnKeyDown(key, x, y);
	}
}
bool enterPressed = false;
string consoleComandString = "";

void OnKeyDown(unsigned char key, int x, int y) {
	if (key == 27) { // 27 == ESC
		glutLeaveMainLoop();
	}
	
	if (key == 13) { // 13 == Enter
		// Start Gry
		glutMouseFunc(MouseButton);

		// Console that allows to write etc. 
		if (consoleComandString != "")
		{
			switch (consoleComandString[0])
			{
			case 'M':
			case 'm':
				//sim.set_m(stod(consoleComandString.substr(1, consoleComandString.length())));
				break;
			default:
				break;
			}
			consoleComandString.erase();
		}
		enterPressed = !enterPressed;
	}

	//backspace
	if (enterPressed && key == 8)
	{
		consoleComandString = consoleComandString.substr(0, consoleComandString.length() - 1);
	}

	//dodawanie znakow
	if (enterPressed && key != 13 && key != 8)
		consoleComandString += key;

	if (key == 'm' || key == 'M') {
		if (captureMouse) {
			captureMouse = false;
			glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
		}
		else {
			captureMouse = true;
			glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
			glutSetCursor(GLUT_CURSOR_NONE);
		}
	}
}

void OnKeyUp(unsigned char key, int x, int y) {
	keystate[key] = false;
}

void OnMouseMove(int x, int y) {
	mouseX = x;
	mouseY = y;
}

void MouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		/*if (state == GLUT_DOWN && Player_Ammo_Amount > 0)
		{
			shooting = true;
		}

		if (state == GLUT_UP)
		{
			shooting = false;
		}

		if (shooting)
		{
			glutTimerFunc(17, BulletFireLogic, 0);
		}*/
	}
}

#pragma endregion

void OnTimer(int id) {

	glutTimerFunc(17, OnTimer, 0);

	#pragma region Ruch kamery

	if (captureMouse) {
		player.velRY = -mouseSensitivity * (glutGet(GLUT_WINDOW_WIDTH) / 2 - mouseX);
		player.velRX = mouseSensitivity * (glutGet(GLUT_WINDOW_HEIGHT) / 2 - mouseY);
		glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
	}
	if (!enterPressed) {
		if (keystate['w']) {
			player.velM = player.speed;
		}
		if (keystate['s']) {
			player.velM = -player.speed;
		}
		if (keystate['a']) {
			player.velS = -player.speed;
		}
		if (keystate['d']) {
			player.velS = player.speed;
		}
		if (keystate['q']) {
			player.velRY = -player.speed;
		}
		if (keystate['e']) {
			player.velRY = player.speed;
		}
		if (keystate['f']) {
			player.velRX = -player.speed;
		}
		if (keystate['c']) {
			player.velRX = player.speed;
		}
	}

	float T = acos(player.dir.y);
	float G = atan2(player.dir.z, player.dir.x);
	T -= player.velRX * .03f;
	G += player.velRY * .03f;
	player.dir.x = sin(T) * cos(G);
	player.dir.y = cos(T);
	player.dir.z = sin(T) * sin(G);

	vec3 per(-player.dir.z, 0, player.dir.x);

	player.pos.x += player.dir.x * player.velM * .1f;
	if (free3DMovement) {
		player.pos.y += player.dir.y * player.velM * .1f;
	}
	else {
		player.pos.y = 1.0f;
	}
	player.pos.z += player.dir.z * player.velM * .1f;

	player.pos.x += per.x * player.velS * .1f;
	if (free3DMovement) {
		player.pos.y += player.dir.y * player.velM * .1f;
	}
	else {
		player.pos.y = 1.0f;
	}
	player.pos.z += per.z * player.velS * .1f;

	player.velRX /= 1.2;
	player.velRY /= 1.2;
	player.velM /= 1.2;
	player.velS /= 1.2;

	#pragma endregion

}

void DrawGUI() 
{
	std::stringstream s;

#pragma region Credentials
	int x = 23;
	int y = -45;
	s << "Krzysztof Kolodziejczak";
	BetterDraw(x, y, s.str(), WHITE);
	s.str("");
	s << "Artur Ziemba";
	y -= 7;
	BetterDraw(x, y, s.str(), WHITE);
	s.str("");
	s << "Grupa 14 lato 2018";
	y -= 7;
	BetterDraw(x, y, s.str(), WHITE);
	s.str("");

#pragma endregion

#pragma region Console
	if (enterPressed)
	{
		s << "->" << consoleComandString;
		BetterDraw(-60, -60, s.str(), WHITE);
	}
#pragma endregion
}

void DrawPoint(Point3D p1, double r, double g, double b) {
	float m_amb[] = { r, g, b, 1.0f };
	float m_dif[] = { r, g, b, 1.0f };
	float m_spe[] = { r, g, b, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_spe);

	glPushMatrix();
	glTranslatef(p1.getX(), p1.getY(), p1.getZ());
	glutSolidCube(0.01);
	glPopMatrix();
}

void DrawLine(Point3D p1, Point3D p2, double r, double g, double b) {
	glLineWidth(2.0);
	float m_amb[] = { r, g, b, 1.0f };
	float m_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float m_spe[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_spe);
	glBegin(GL_LINES);
	glVertex3f(p1.getX(), p1.getY(), p1.getZ());
	glVertex3f(p2.getX(), p2.getY(), p2.getZ());
	glEnd();
}

void DrawShape(Shape shape, double r, double g, double b) {
	// zakladamy ze kazdy shape ma conajmniej dlugosc == 3
	std::vector<Point3D> points = shape.getPoints();
	for (int i = 0; i < points.size() - 1; i++) {
		DrawLine(points[i], points[i + 1], r, g, b);
	}
}

void DrawShapes(std::vector<Shape> shapes, double r, double g, double b) {
	for (Shape shape : shapes)
		DrawShape(shape, r, g, b);
}

void OnRender() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(
		player.pos.x, player.pos.y, player.pos.z,
		player.pos.x + player.dir.x, player.pos.y + player.dir.y, player.pos.z + player.dir.z,
		0.0f, 1.0f, 0.0f
	);

	#pragma region Swiatlo
	
		float l0_amb[] = { 0.8f, 0.8f, 0.8f, 1.0f };
		float l0_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float l0_spe[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float l0_pos[] = { 0.0f, 10.0f, 0.0f, 1.0f };
		glLightfv(GL_LIGHT0, GL_AMBIENT, l0_amb);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, l0_dif);
		glLightfv(GL_LIGHT0, GL_SPECULAR, l0_spe);
		glLightfv(GL_LIGHT0, GL_POSITION, l0_pos);

	#pragma endregion

	//Rysowanie figury
	DrawShapes(shapeConfig->shapes, 0.0, 0.0, 1.0);
	DrawShape(*outter, 1.0, 0.0, 1.0);

	for (auto point : points) {
		if (shapeConfig->shapes.front().isInside(point)) {
			DrawPoint(point, 0, 1, 0);
		}
		else {
			DrawPoint(point, 1, 0, 0);
		}
	}

	DrawGUI();

	glutSwapBuffers();
	glFlush();
	glutPostRedisplay();

}

void OnReshape(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(60.0f, (float) width / height, .01f, 100.0f);
}

// rysowanie tekstu z neta!
void drawText(float x, float y, std::string st)
{
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);  // Tell opengl that we are doing project matrix work
	double *matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();  // Clear the matrix
	glOrtho(-64.0, 64.0, -64.0, 64.0, 0.0, 30.0);  // Setup an Ortho view
	glMatrixMode(GL_MODELVIEW);  // Tell opengl that we are doing model matrix work. (drawing)
	glLoadIdentity(); // Clear the model matrix
	glDisable(GL_BLEND);
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2f(x, y); // location to start printing text
	for (int i = 0; i < st.size(); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, st[i]);
	glPopMatrix();
	glEnable(GL_BLEND);
	glMatrixMode(GL_PROJECTION);  // Tell opengl that we are doing project matrix work
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_LIGHTING);
}

void BetterDraw(float x, float y, std::string message, color color) {
	glColor3f(color.r, color.g, color.b);
	drawText(x, y, message);
	
	// Shadow Color 0 0 0 -> Black
	glColor3f(0, 0, 0);
	drawText(x - 0.25f, y, message);
	drawText(x + 0.25f, y, message);
	drawText(x, y - 0.5f, message);
	drawText(x, y + 0.5f, message);
	drawText(x + 0.25f, y + 0.25f, message);
	drawText(x + 0.25f, y - 0.5f, message);
	drawText(x - 0.25f, y + 0.25f, message);
	drawText(x - 0.25f, y - 0.5f, message);

}
