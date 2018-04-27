#include "stdafx.h"
#include "OBJLoader.h"

#pragma region Zmienne globalne
// Player
int Player_Ammo_Amount = 30;
int Monsters_Killed = 0;
SCameraState player;
vector<Bullet> bullets;
bool shooting = false;

// Game
int Time_Passed = 0;
int Monster_Spawn_Rate = 500; // less == faster 
bool Game_Started = false;
bool Game_Over = false; 
bool fog = true;
bool Random_Fog_Color = true;
bool captureMouse = true;
bool free3DMovement = false;
vector<Monster> Monsters;
vector<vec3> Monster_Spawn_Points;
vec3 End_Field;
int Half_Square = 15; // Size of the square to spawn monster, center at vec3(0,0,0)

int mouseX = 0;
int mouseY = 0;

float mouseSensitivity = .15f;

//TODO dodawnie zmiennych modelu tutaj
// Wczytane modele
OBJLoader *AK47;

//TODO ewentualne tekstury tutaj
// Zmienne przechowuj¹ce identyfikatory tekstur
GLuint Temp;

#pragma endregion

// Funkcja odczytuj¹ca bitmapê i tworz¹ca na jej podstawie teksturê z zadanym rodzajem filtracji
GLuint LoadTexture(char * file, int magFilter, int minFilter) {
	
	// Odczytanie bitmapy
	Bitmap *tex = new Bitmap();
	if (!tex->loadBMP(file)) {
		printf("ERROR: Cannot read texture file \"%s\".\n", file);
		return -1;
	}

	// Utworzenie nowego id wolnej tekstury
	GLuint texId;
	glGenTextures(1, &texId);

	// "Bindowanie" tekstury o nowoutworzonym id
	glBindTexture(GL_TEXTURE_2D, texId);

	// Okreœlenie parametrów filtracji dla tekstury
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter); // Filtracja, gdy tekstura jest powiêkszana
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter); // Filtracja, gdy tekstura jest pomniejszana

	// Wys³anie tekstury do pamiêci karty graficznej zale¿nie od tego, czy chcemy korzystaæ z mipmap czy nie
	if (minFilter == GL_LINEAR_MIPMAP_LINEAR || minFilter == GL_LINEAR_MIPMAP_NEAREST) {
		// Automatyczne zbudowanie mipmap i wys³anie tekstury do pamiêci karty graficznej
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, tex->width, tex->height, GL_RGB, GL_UNSIGNED_BYTE, tex->data);
	}
	else {
		// Wys³anie tekstury do pamiêci karty graficznej 
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->width, tex->height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex->data);
	}
	
	// Zwolnienie pamiêci, usuniêcie bitmapy z pamiêci - bitmapa jest ju¿ w pamiêci karty graficznej
	delete tex;
	
	// Zwrócenie id tekstury
	return texId;
}

void Init() {
	// TODO: Dodawanie modeli tutaj
	// Init modeli
	AK47 = new OBJLoader("AK47");

	// Inicjalizacja punktu docelowego.
	End_Field = vec3(1, 0, 1);

	// Genertowanie punktów startowych potworów 

	// Tworzymy vektor przechowuj¹cy wszytkie mo¿liwe spawnpointy w tym przypadku bêdzie to kwadrat. 
	for (int i = -Half_Square; i < Half_Square; i++) {
		Monster_Spawn_Points.push_back(vec3(-Half_Square, 0, i));
		Monster_Spawn_Points.push_back(vec3(Half_Square, 0, i));
		Monster_Spawn_Points.push_back(vec3(i, 0, -Half_Square));
		Monster_Spawn_Points.push_back(vec3(i, 0, Half_Square));
	}

}

void drawText(float x, float y, std::string st);
void BetterDraw(float x, float y, std::string message, color color);

// https://stackoverflow.com/questions/686353/c-random-float-number-generation
float GetRandomFloat() {
	return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 360);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	//TODO zmieniæ nazwê gry!
	glutCreateWindow("Gra");

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
	
	Init(); // Ka¿d¹ teksturê ³adujemy *raz* (nie w ka¿dej klatce!), np. przed wejœciem do pêtli g³ównej

	glutMainLoop();

	//TODO usuniêcie modeli!
	delete AK47;

	return 0;
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
		//Game_Started = true;
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
	if (key == 'l' || key == 'L') {
		free3DMovement = !free3DMovement;
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

void MonsterSpawner(int id) {

	// losujemy pozycjê startow¹ z wczeœniej przygotowanych koordynatów
	vec3 Monster_Pos = Monster_Spawn_Points[rand() % Monster_Spawn_Points.size()];
	
	// kierunke w którym ma siê poruszaæ 
	vec3 Monster_Dir;

	//Z neta ! logika nakierowania kierunku potwora na cel -> czyli end_field
	Monster_Dir.x = End_Field.x - Monster_Pos.x;
	Monster_Dir.y = 0;
	Monster_Dir.z = End_Field.z - Monster_Pos.z;
	float hyp = sqrt(Monster_Dir.x * Monster_Dir.x + Monster_Dir.z * Monster_Dir.z);
	Monster_Dir.x /= hyp;
	Monster_Dir.z /= hyp;

	// Dodajemy do listy ¿ywych potworów
	Monsters.push_back(Monster(Monster_Pos, Monster_Dir));

	glutTimerFunc(Monster_Spawn_Rate, MonsterSpawner, 0);
}

void BulletFireLogic(int id) {
	
	if (shooting) {
		glutTimerFunc(500, BulletFireLogic, 0);
	
		if (Player_Ammo_Amount > 0) {
			bullets.push_back(Bullet(player.pos,player.dir));
			Player_Ammo_Amount--;
		}
	}
	
}

void TimePassed(int id) {

	Time_Passed++;
	glutTimerFunc(1000, TimePassed, 0);

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

void DrawMonster(Monster m) {
	
	srand(time(NULL));
	// Ustawienie materia³u
	float r = GetRandomFloat();
	float g = GetRandomFloat();
	float b = GetRandomFloat();
	float m_amb[] = { 0, 0, 0, 1.0f};
	float m_dif[] = { r, g, b, 1.0f};
	float m_spe[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_spe);

	glPushMatrix();
		glTranslatef(m.pos.x, m.pos.y + 1, m.pos.z);
		float angle = atan2(m.pos.x - End_Field.x, m.pos.z - End_Field.z);
		glRotatef(angle*(180 / 3.14), 0.0f, 1.0f, 0.0f);
		// TODO: tutaj mo¿na wyœwitliæ model jak w przypadku broni.
		// AK47->render();
		glScalef(1.0f, m.height, 1.0f);
		glutSolidCube(1);
		///////////////////////////////////////////////////////////
	glPopMatrix();

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
	
		float l0_amb[] = { 0.2f, 0.2f, 0.2f, 1.0f };
		float l0_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float l0_spe[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float l0_pos[] = { 0.0f, 10.0f, 0.0f, 1.0f };
		glLightfv(GL_LIGHT0, GL_AMBIENT, l0_amb);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, l0_dif);
		glLightfv(GL_LIGHT0, GL_SPECULAR, l0_spe);
		glLightfv(GL_LIGHT0, GL_POSITION, l0_pos);

	#pragma endregion

	#pragma region Rysowanie scian

		glBegin(GL_QUADS);

			#pragma region Przednia sciana
			{
				float m_amb[] = { 1.0f, 1.0f, 0.0f, 1.0f };
				float m_dif[] = { 1.0f, 1.0f, 0.0f, 1.0f };
				float m_spe[] = { 0.0f, 0.0f, 0.0f, 1.0f };
				glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, m_dif);
				glMaterialfv(GL_FRONT, GL_SPECULAR, m_spe);
			
				glNormal3f( 0.0f,  0.0f,  1.0f);
				glVertex3f(-Half_Square, Half_Square, -Half_Square);

				glNormal3f( 0.0f,  0.0f,  1.0f);
				glVertex3f(-Half_Square,  0.0f, -Half_Square);

				glNormal3f( 0.0f,  0.0f,  1.0f);
				glVertex3f(Half_Square,  0.0f, -Half_Square);

				glNormal3f( 0.0f,  0.0f,  1.0f);
				glVertex3f(Half_Square, Half_Square, -Half_Square);
			}
			#pragma endregion

			#pragma region Lewa sciana
			{
				float m_amb[] = { 1.0f, 0.0f, 0.0f, 1.0f };
				float m_dif[] = { 1.0f, 0.0f, 0.0f, 1.0f };
				float m_spe[] = { 0.0f, 0.0f, 0.0f, 1.0f };
				glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, m_dif);
				glMaterialfv(GL_FRONT, GL_SPECULAR, m_spe);
			
				glNormal3f( 1.0f,  0.0f,  0.0f);
				glVertex3f(-Half_Square,  0.0f, -Half_Square);

				glNormal3f( 1.0f,  0.0f,  0.0f);
				glVertex3f(-Half_Square,  Half_Square, -Half_Square);

				glNormal3f( 1.0f,  0.0f,  0.0f);
				glVertex3f(-Half_Square,  Half_Square,  Half_Square);

				glNormal3f( 1.0f,  0.0f,  0.0f);
				glVertex3f(-Half_Square,  0.0f,  Half_Square);
			}
			#pragma endregion

			#pragma region Prawa sciana
			{
				float m_amb[] = { 0.0f, 1.0f, 0.0f, 1.0f };
				float m_dif[] = { 0.0f, 1.0f, 0.0f, 1.0f };
				float m_spe[] = { 0.0f, 0.0f, 0.0f, 1.0f };
				glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, m_dif);
				glMaterialfv(GL_FRONT, GL_SPECULAR, m_spe);
			
				glNormal3f(-1.0f,  0.0f,  0.0f);
				glVertex3f( Half_Square,  Half_Square, -Half_Square);
		
				glNormal3f(-1.0f,  0.0f,  0.0f);
				glVertex3f( Half_Square,  0.0f, -Half_Square);

				glNormal3f(-1.0f,  0.0f,  0.0f);
				glVertex3f( Half_Square,  0.0f,  Half_Square);

				glNormal3f(-1.0f,  0.0f,  0.0f);
				glVertex3f( Half_Square,  Half_Square,  Half_Square);
			}
			#pragma endregion

			#pragma region Tylna sciana
			{
				float m_amb[] = { 1.0f, 1.0f, 1.0f, 1.0f };
				float m_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
				float m_spe[] = { 0.0f, 0.0f, 0.0f, 1.0f };
				glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, m_dif);
				glMaterialfv(GL_FRONT, GL_SPECULAR, m_spe);
			
				glNormal3f( 0.0f,  0.0f, -1.0f);
				glVertex3f(-Half_Square,  0.0f,  Half_Square);

				glNormal3f( 0.0f,  0.0f, -1.0f);
				glVertex3f(-Half_Square,  Half_Square,  Half_Square);

				glNormal3f( 0.0f,  0.0f, -1.0f);
				glVertex3f( Half_Square,  Half_Square,  Half_Square);

				glNormal3f( 0.0f,  0.0f, -1.0f);
				glVertex3f( Half_Square,  0.0f,  Half_Square);
			}
			#pragma endregion

			#pragma region Podloga
			{
				float m_amb[] = { 1.0f, 0.0f, 1.0f, 1.0f };
				float m_dif[] = { 1.0f, 0.0f, 1.0f, 1.0f };
				float m_spe[] = { 0.0f, 0.0f, 0.0f, 1.0f };
				glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, m_dif);
				glMaterialfv(GL_FRONT, GL_SPECULAR, m_spe);
			
				glNormal3f( 0.0f,  1.0f,  0.0f);
				glVertex3f(-Half_Square,  0.0f, -Half_Square);

				glNormal3f( 0.0f,  1.0f,  0.0f);
				glVertex3f(-Half_Square,  0.0f,  Half_Square);

				glNormal3f( 0.0f,  1.0f,  0.0f);
				glVertex3f( Half_Square,  0.0f,  Half_Square);

				glNormal3f( 0.0f,  1.0f,  0.0f);
				glVertex3f( Half_Square,  0.0f, -Half_Square);
			}
			#pragma endregion

			#pragma region Sufit
			{
				float m_amb[] = { 1.0f, 1.0f, 1.0f, 1.0f };
				float m_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
				float m_spe[] = { 0.0f, 0.0f, 0.0f, 1.0f };
				glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, m_dif);
				glMaterialfv(GL_FRONT, GL_SPECULAR, m_spe);
			
				glNormal3f( 0.0f, -1.0f,  0.0f);
				glVertex3f(-Half_Square,  Half_Square,  Half_Square);

				glNormal3f( 0.0f, -1.0f,  0.0f);
				glVertex3f(-Half_Square,  Half_Square, -Half_Square);

				glNormal3f( 0.0f, -1.0f,  0.0f);
				glVertex3f( Half_Square,  Half_Square, -Half_Square);

				glNormal3f( 0.0f, -1.0f,  0.0f);
				glVertex3f( Half_Square,  Half_Square,  Half_Square);
			}
			#pragma endregion

		glEnd();

	#pragma endregion
	
		// Rysowanie linii, mo¿e rysowaæ ca³¹ figure z linii anie jako obiekt bo i 
		//   tak bêdziemy musieli jakiegoœ wireframe zrobic, aby by³o strza³y widaæ
	glLineWidth(1.5);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 2.0, 0.0);
	glVertex3f(0, 2, 7);
	glEnd();


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
