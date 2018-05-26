#include "stdafx.h"
#include "FileParser.h"

#define debug true

#pragma region Zmienne globalne
SCameraState player;
std::vector<Point3D> points;

// Game
bool captureMouse = true;
bool free3DMovement = true;
double volume = 0.0;

int mouseX = 0;
int mouseY = 0;

float mouseSensitivity = .15f;

int prezentacjaFigurNaStarcieIndex = 0;
int prezentacjaFigurNaStarcieEtap = 0;
GLuint Points;
GLuint Squares;

bool axisViewSwtich = true;
bool methodResultsView = true;
bool methodResultsExtra = true;
bool CHECK_FEATURE_SWITCH = true;

#pragma endregion

void drawText(float x, float y, std::string st);
void BetterDraw(float x, float y, std::string message, color color);

void RegenerateViews();
void DrawShapes(std::vector<Shape> shapes, double r, double g, double b);
void DrawShapes(std::vector<Shape> shapes, double r, double g, double b, bool negative);

void DrawPoint(Point3D p1, double r, double g, double b) {
	glPushMatrix();

	float m_amb[] = { r, g, b, 1.0f };
	float m_dif[] = { r, g, b, 1.0f };
	float m_spe[] = { r, g, b, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_spe);

	glTranslatef(p1.getX(), p1.getY(), p1.getZ());
	glutSolidCube(0.05);
	glPopMatrix();
}

void CalculateVolume();

// https://stackoverflow.com/questions/686353/c-random-float-number-generation
float GetRandomFloat(float min = 0, float max = 1) {
	return min + static_cast <float> (rand()) / static_cast <float> (RAND_MAX / (max - min));
}

ParsedData *shapeConfig;
std::vector<Shape> outters = std::vector<Shape>();
std::vector<rectangleMethodResults> resultsR = std::vector<rectangleMethodResults>();
std::vector<monteCarloMethodResults> resultsM = std::vector<monteCarloMethodResults>();
int main(int argc, char* argv[])
{
#pragma region OpenGL stuff

	glutInit(&argc, argv);
	srand(time(NULL));
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 360);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow("Obliczanie objetosci figur");

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

	player.speed = .5f;

	glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
	mouseX = glutGet(GLUT_WINDOW_WIDTH) / 2;
	mouseY = glutGet(GLUT_WINDOW_HEIGHT) / 2;
	glutSetCursor(GLUT_CURSOR_NONE);

#pragma endregion

	//try {
	// load file
	string filePath;
	cout << "Please enter path to file with shape specification:\n";
	if (!debug)
		cin >> filePath;
	else {
		//filePath = "./figury/szescian.txt";
		//filePath = "./figury/piramida.txt";
		//filePath = "./figury/2szescian.txt";
		filePath = "./testFile.txt";
	}

	ParsedData sc = FileParser::parse(filePath); // tej funkcji (pacz linia nizej)
	shapeConfig = &sc; // nie wiem czemu ale odrazu z funkcji nie dzialalo (shapes.size() bylo rowne 0)



	CalculateVolume();

	if (debug) {
		int i = 0;
		for (Shape shape : shapeConfig->shapes) {
			cout << "\nShape: " << ++i << " = " << shape.getPoints().size() - 1 << " lines.\nPoints:" << "\n";
			int j = 0;
			for (Point3D point3D : shape.getPoints())
				cout << "point: " << ++j << " = " << point3D.getX() << "x" << point3D.getY() << "x" << point3D.getZ() << "\n";
		}
	}

	glutMainLoop();

	glDeleteLists(Points, 1);
	glDeleteLists(Squares, 1);

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

	if (key == 13 && prezentacjaFigurNaStarcieIndex < shapeConfig->shapes.size()) {
		player.pos.x = 0.0f;
		player.pos.y = 1.0f;
		player.pos.z = 4.0f;

		player.dir.x = 0.0f;
		player.dir.y = 0.0f;
		player.dir.z = -1.0f;
		if (++prezentacjaFigurNaStarcieEtap > 3) {
			prezentacjaFigurNaStarcieEtap = 0;
			prezentacjaFigurNaStarcieIndex++;
		}
	}

	if ((key == 'i' || key == 'I') && !enterPressed) {
		axisViewSwtich = !axisViewSwtich;
	}

	if ((key == 'o' || key == 'O') && !enterPressed) {
		methodResultsView = !methodResultsView;
		RegenerateViews();
	}

	if ((key == 'p' || key == 'P') && !enterPressed) {
		methodResultsExtra = !methodResultsExtra;
		RegenerateViews();
	}

	if (key == 'x' || key == 'X') {

		player.pos.x = 0.0f;
		player.pos.y = 1.0f;
		player.pos.z = 4.0f;

		player.dir.x = 0.0f;
		player.dir.y = 0.0f;
		player.dir.z = -1.0f;
	}

	if (key == 'r' || key == 'R') {
		if (player.speed < 5.0)
			player.speed += 0.1;
	}

	if (key == 't' || key == 'T') {
		if (player.speed > 0.1)
			player.speed -= 0.1;
	}
	string mode = "";
	// Console that allows to write etc. 
	if (key == 9) {
		if (consoleComandString != "") {
			switch (consoleComandString[0])
			{
				case 'M':
				case 'm':
					try {
						mode = consoleComandString.substr(1, consoleComandString.length());
						shapeConfig->type = mode[0];
						if (shapeConfig->type >= 97) 
						{
							shapeConfig->type -= 32;
						}
						CalculateVolume();
					}
					catch (...) {
					}
					break;
				case 'V':
				case 'v':
					try {
						shapeConfig->value = stoi(consoleComandString.substr(1, consoleComandString.length()));
						CalculateVolume();
					}
					catch (...){
					}
					break;
				default:
					break;
			}
			consoleComandString.erase();
		}
		enterPressed = !enterPressed;
	}

	//backspace
	if (enterPressed && key == 8) {
		consoleComandString = consoleComandString.substr(0, consoleComandString.length() - 1);
	}
	
	//dodawanie znakow
	if (enterPressed && key != 13 && key != 8 && key != ' ' && key != '\t') {
		consoleComandString += key;
	}

	if ((key == 'm' || key == 'M') && !enterPressed) {
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

void RegenerateViews() {
	if (shapeConfig->type == 'M' && methodResultsView) {
		Points = glGenLists(1);
		glNewList(Points, GL_COMPILE);
		for (auto result : resultsM) {
			if (result.getInclude()) {
				for (auto hitPoint : result.getHitPoints()) {
					DrawPoint(hitPoint, 0, 1, 0);
				}
				for (auto missPoint : result.getMissedPoints()) {
					DrawPoint(missPoint, 1, 0, 0);
				}
			}
			else {
				for (auto hitPoint : result.getHitPoints()) {
					DrawPoint(hitPoint, 1, 0, 0);
				}
				for (auto missPoint : result.getMissedPoints()) {
					DrawPoint(missPoint, 0, 1, 0);
				}
			}
		}
		glEndList();
	}
	if (shapeConfig->type == 'R') {
		Squares = glGenLists(1);
		glNewList(Squares, GL_COMPILE);
		for (rectangleMethodResults &rrrr : resultsR) {
			double negative = !rrrr.getIncludes();
			if (methodResultsExtra) {
				DrawShapes(rrrr.getProjectins(), 0.7, 0.2, 0.2, negative);
			}
			if (methodResultsView) {
				DrawShapes(rrrr.getRectangles(), 0.5, 1.0, 0.5, negative);
			}
		}
		glEndList();
	}
}

void CalculateVolume() {

	outters.clear();
	for (Shape &ssssssssss : shapeConfig->shapes) {
		Shape rmr = ssssssssss.getCubeAround();
		outters.push_back(rmr);
	}
	resultsR.clear();
	if (shapeConfig->type == 'R') {
		for (Shape &ssssssssss : shapeConfig->shapes) {
			rectangleMethodResults rmr = ssssssssss.rectangleMethod(shapeConfig->value);
			resultsR.push_back(rmr);
		}
	}

	resultsM.clear();
	if (shapeConfig->type == 'M') {
		for (Shape &ssssssssss : shapeConfig->shapes) {
			monteCarloMethodResults mcmr = ssssssssss.monteCarloMethod(shapeConfig->value);
			resultsM.push_back(mcmr);
		}
	}

	RegenerateViews();
}



void OnTimer(int id) {

	glutTimerFunc(17, OnTimer, 0);

#pragma region Ruch kamery

	if (captureMouse) {
		player.velRY = -mouseSensitivity * (glutGet(GLUT_WINDOW_WIDTH) / 2 - mouseX);
		player.velRX = mouseSensitivity * (glutGet(GLUT_WINDOW_HEIGHT) / 2 - mouseY);
		glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
	}
	if (!enterPressed) {
		if (keystate['w'] || keystate['W']) {
			player.velM = player.speed;
		}
		if (keystate['s'] || keystate['S']) {
			player.velM = -player.speed;
		}
		if (keystate['a'] || keystate['A']) {
			player.velS = -player.speed;
		}
		if (keystate['d'] || keystate['D']) {
			player.velS = player.speed;
		}
		if (keystate['q'] || keystate['Q']) {
			player.velRY = -player.speed;
		}
		if (keystate['e'] || keystate['E']) {
			player.velRY = player.speed;
		}
		if (keystate['f'] || keystate['F']) {
			player.velRX = -player.speed;
		}
		if (keystate['c'] || keystate['C']) {
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

void DrawCredentials() {
	int x = 23;
	int y = -45;
	std::stringstream s;
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
}

void DrawGUI()
{
	std::stringstream s;

	DrawCredentials();

	int x = -63;
	int y = 58;
	s << "Tab key - open/close console";
	BetterDraw(x, y, s.str(), RED);
	s.str("");
	y -= 7;
	s << "Available commands";
	BetterDraw(x, y, s.str(), WHITE);
	s.str("");
	y -= 7;
	s << "v[number] - number of points/rectangles";
	BetterDraw(x, y, s.str(), WHITE);
	s.str("");
	y -= 7;
	s << "m[m/r] - method";
	BetterDraw(x, y, s.str(), WHITE);
	s.str("");

	x = 6;
	y = 58;
	s << "Method: " << (shapeConfig->type == 'M'? "Monte carlo" : "Rectangles");
	BetterDraw(x, y, s.str(), WHITE);
	s.str("");
	y -= 7;
	s << "Volume: " << volume;
	BetterDraw(x, y, s.str(), WHITE);
	s.str("");
	y -= 7;
	s << (shapeConfig->type == 'M' ? "Points: " : "Rectangles: ") << shapeConfig->value;
	BetterDraw(x, y, s.str(), WHITE);
	s.str("");
#pragma region Console
	if (enterPressed)
	{
		s << "->" << consoleComandString;
		BetterDraw(-62, -60, s.str(), WHITE);
	}
#pragma endregion
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

void DrawShape2D(std::vector<Point2D> _v, double r, double g, double b) {
	// zakladamy ze kazdy shape ma conajmniej dlugosc == 3
	for (int i = 0; i < _v.size(); i++) {
		glPushMatrix();
		glColor4ub(255, 255, 0, 255);
		glRasterPos3f(_v[i].x+0.05, _v[i].y+0.05, 0.0);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, (char)(i + 49));
		glPopMatrix();
		if (i != _v.size() - 1) {
			DrawLine(Point3D(_v[i].x, _v[i].y, 0.0), Point3D(_v[i + 1].x, _v[i + 1].y, 0.0), r, g, b);
		}
	}
	DrawLine(Point3D(_v[_v.size() - 1].x, _v[_v.size() - 1].y, 0.0), Point3D(_v[0].x, _v[0].y, 0.0), r, g, b);
}

void DrawShapes(std::vector<Shape> shapes, double r, double g, double b) {
	for (Shape shape : shapes)
		if (shape.getIncludes())
			DrawShape(shape, r, g, b);
		else
			DrawShape(shape, (r*-1.0) + 1, (g*-1.0) + 1, (b*-1.0) + 1);
}

void DrawShapes(std::vector<Shape> shapes, double r, double g, double b, bool negative) {
	if (negative) {
		r = (r * -1) + 1;
		g = (g * -1) + 1;
		b = (b * -1) + 1;
	}
	DrawShapes(shapes, r, g, b);
}

void showAxis() {
	
	int max = FileParser::getMax_size() + 2;
	DrawLine(Point3D(0, 0, 0), Point3D(max-1, 0, 0), 1, 1, 1);
	for (int i = 1; i < max; i++) {
		glPushMatrix();
		glColor4ub(255, 255, 0, 255);
		glRasterPos3f(i, 0.0f, 0.0f);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'x');
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, (char)(i+48));
		glPopMatrix();
	}

	DrawLine(Point3D(0, 0, 0), Point3D(0, max-1, 0), 1, 1, 1);
	for (int i = 1; i < max; i++) {
		glPushMatrix();
		glColor4ub(255, 255, 0, 255);
		glRasterPos3f(0, i, 0.0f);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'y');
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, (char)(i + 48));
		glPopMatrix();
	}

	DrawLine(Point3D(0, 0, 0), Point3D(0, 0, max-1), 1, 1, 1);
	for (int i = 1; i < max; i++) {
		glPushMatrix();
		glColor4ub(255, 255, 0, 255);
		glRasterPos3f(0, 0, i);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'z');
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, (char)(i + 48));
		glPopMatrix();
	}
	
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

	if (axisViewSwtich)
		showAxis();

	// Rysowanie prezentacjaFigurNaStarcieIndex
	if (CHECK_FEATURE_SWITCH && prezentacjaFigurNaStarcieIndex < shapeConfig->shapes.size()) {
		string info = "Checking shape (" + to_string(prezentacjaFigurNaStarcieIndex + 1) + ") - ";
		if (prezentacjaFigurNaStarcieEtap == 0) {
			info += "(x,z) B - base projection";
			DrawShape2D(shapeConfig->shapes[prezentacjaFigurNaStarcieIndex].getBase(), 0, 1, 0);
		}
		if (prezentacjaFigurNaStarcieEtap == 1) {
			info += "(x, y) F - front projection";
			DrawShape2D(shapeConfig->shapes[prezentacjaFigurNaStarcieIndex].getSide1(), 0, 1, 0);
		}
		if (prezentacjaFigurNaStarcieEtap == 2) {
			info += "(y,z) S - side projection";
			DrawShape2D(shapeConfig->shapes[prezentacjaFigurNaStarcieIndex].getSide2(), 0, 1, 0);
		}
		if (prezentacjaFigurNaStarcieEtap == 3) {
			info += "(x,y,z) 3D shape";
			DrawShape(shapeConfig->shapes[prezentacjaFigurNaStarcieIndex], 1.0, 0.0, 1.0);
		}
		BetterDraw(-64, 58, info, WHITE);
		BetterDraw(-20, -30, "Press Enter, to continue...", WHITE);
		DrawCredentials();
	}
	else {

		//Rysowanie figury
		// glowna figura
		DrawShapes(shapeConfig->shapes, 0.0, 0.0, 1.0);

		int i = -1;
		volume = 0;
		// figura opatulujaca
		if (shapeConfig->type == 'M') {
			i = -1;
			for (Shape &sssss : outters) {
				i++;
				DrawShape(sssss, 1.0, 0.0, 1.0);
				auto &result = resultsM[i];
				if (shapeConfig->shapes[i].getIncludes()) {
					volume += result.getVolume();
				}
				else {
					volume -= result.getVolume();
				}
					
			}
			volume = round(volume * 10000.0) / 10000.0;

				glCallList(Points);
			
		}

		// dla methody kwadratow rysowanie
		if (shapeConfig->type == 'R') {
			for (rectangleMethodResults &rrrr : resultsR) {
				if (rrrr.getIncludes()) {
					volume += rrrr.getVolume();
				}
				else {
					volume -= rrrr.getVolume();
				}
			}
			glCallList(Squares);
			volume = round(volume * 10000.0) / 10000.0;
		}

		DrawGUI();
	}


	glutSwapBuffers();
	glFlush();
	glClearColor(1, 1, 1, 1.0f);
	glutPostRedisplay();

}

void OnReshape(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(60.0f, (float)width / height, .01f, 100.0f);
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
	glColor3f(1, 1, 1);
	drawText(x - 0.25f, y, message);
	drawText(x + 0.25f, y, message);
	drawText(x, y - 0.5f, message);
	drawText(x, y + 0.5f, message);
	drawText(x + 0.25f, y + 0.25f, message);
	drawText(x + 0.25f, y - 0.5f, message);
	drawText(x - 0.25f, y + 0.25f, message);
	drawText(x - 0.25f, y - 0.5f, message);

}
