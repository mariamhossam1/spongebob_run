#include "TextureBuilder.h"
#include "Model_3DS.h"
#include "GLTexture.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <iostream>
#include <glut.h>

#define DEG2RAD(a) (a * 0.0174532925)

int WIDTH = 720;
int HEIGHT = 1280;

float cameraez = 57.5169;
float cameracz = 56.7452;

double hx = 12; //net & spatula z & y
double hy = 0;
double texz = 0; //texture z
double texz1 = 50;

float light = 0.0f;
float light1 = 0.7;

int score = 0;
int lives = 3;
int powerup1 = 35;

double sbz = 45; //spongebob z
double sbx = 10;//spongebob x
double sby = 3; //spongebob y

float by1 = 3; //
float by2 = 5;
float by3 = 4;
float by4 = 6.5;

double x1 = 5; // x coordinates of models
double x2 = 10;
double x3 = 15;

double z1 = 40; //jellyfish and sea urchin z (level 1)
double z2 = 35;
double z3 = 30;
double z4 = 25;
double z5 = 20;
double z6 = 15;
double z7 = 10;
double z8 = 5;
double z9 = 0;
double z10 = -5;
double z11 = -10;
double z12 = -15;
double z13 = -20;
double z14 = -25;
double z15 = -30;
double z16 = -35;
double z17 = -40;
double z18 = -45;
double z19 = -50;

double c1 = 40; //burger and sea urchin z (level 2)
double c2 = 35;
double c3 = 30;
double c4 = 25;
double c5 = 20;
double c6 = 15;
double c7 = 10;
double c8 = 5;
double c9 = 0;
double c10 = -5;
double c11 = -10;
double c12 = -15;
double c13 = -20;
double c14 = -25;
double c15 = -30;
double c16 = -35;
double c17 = -40;
double c18 = -45;
double c19 = -50;

double s1 = 1;
double s2 = 1;
double s3 = 1;
double s4 = 1;
double s5 = 1;
double s6 = 1;
double s7 = 1;
double s8 = 1;
double s9 = 1;
double s10 = 1;
double s11 = 1;
double s12 = 1;
double s13 = 1;
double s14 = 1;
double s15 = 1;
double s16 = 1;
double s17 = 1;
double s18 = 1;
double s19 = 1;
double s20 = 1;
double s21 = 1;
double s22 = 1;
double s23 = 1;
double s24 = 1;
double s25 = 1;
double s26 = 1;
double s27 = 1;
double s28 = 1;

double h1 = 2;
double h2 = 2;
double h3 = 2;
double h4 = 2;
double h5 = 2;
double h6 = 2;
double h7 = 2;
double h8 = 2;
double h9 = 2;
double h10 = 2;
double h11 = 2;
double h12 = 2;
double h13 = 2;
double h14 = 2;
double h15 = 2;
double h16 = 2;

double L1 = 1;
double L2 = 1;
double L3 = 1;

bool flag = false;
bool flag1 = false;
//bool flaggame = false;

GLuint gameover;
char title[] = "3D Model Loader Sample";

// 3D Projection Options
GLdouble fovy = 45.0;
GLdouble aspectRatio = (GLdouble)WIDTH / (GLdouble)HEIGHT;
GLdouble zNear = 0.1;
GLdouble zFar = 1000;

class Vector3f {
public:
	float x, y, z;

	Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) {
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3f operator+(Vector3f& v) {
		return Vector3f(x + v.x, y + v.y, z + v.z);
	}

	Vector3f operator-(Vector3f& v) {
		return Vector3f(x - v.x, y - v.y, z - v.z);
	}

	Vector3f operator*(float n) {
		return Vector3f(x * n, y * n, z * n);
	}

	Vector3f operator/(float n) {
		return Vector3f(x / n, y / n, z / n);
	}

	Vector3f unit() {
		return *this / sqrt(x * x + y * y + z * z);
	}

	Vector3f cross(Vector3f v) {
		return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
};

class Camera {
public:
	Vector3f eye, center, up;

	Camera(float eyeX = 9.97877f, float eyeY = 23.1547f, float eyeZ = 57.5169, float centerX = 9.97911f, float centerY = 22.5187f, float centerZ = 56.7452f, float upX = 0.000280989f, float upY = 0.77167f, float upZ = -0.636023f) {
		eye = Vector3f(eyeX, eyeY, eyeZ);
		center = Vector3f(centerX, centerY, centerZ);
		up = Vector3f(upX, upY, upZ);
	}

	void moveX(float d) {
		Vector3f right = up.cross(center - eye).unit();
		eye = eye + right * d;
		center = center + right * d;
	}

	void moveY(float d) {
		eye = eye + up.unit() * d;
		center = center + up.unit() * d;
	}

	void moveZ(float d) {
		Vector3f view = (center - eye).unit();
		eye = eye + view * d;
		center = center + view * d;
	}

	void rotateX(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + up * sin(DEG2RAD(a));
		up = view.cross(right);
		center = eye + view;
	}

	void rotateY(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + right * sin(DEG2RAD(a));
		right = view.cross(up);
		center = eye + view;
	}

	void look() {
		gluLookAt(
			eye.x, eye.y, eye.z,
			center.x, center.y, center.z,
			up.x, up.y, up.z
		);
	}
};

Camera camera;

// Model Variables
//Model_3DS model_house;
//Model_3DS model_tree;
Model_3DS model_spongebob;
Model_3DS model_jellyfish;
Model_3DS model_seaurchin;
Model_3DS model_wood;
Model_3DS model_net;
Model_3DS model_spatula;
Model_3DS model_lives;
Model_3DS model_burger;

// Textures
GLTexture tex_ground;
GLTexture tex_ground1;
GLTexture tex_ground2;
GLTexture tex_ground3;
GLTexture tex_ground4;
GLTexture tex_ground5;
GLTexture tex_ground6;
GLTexture tex_ground7;

//=======================================================================
// Lighting Configuration Function
//=======================================================================
void InitLightSource()
{
	// Enable Lighting for this OpenGL Program
	glEnable(GL_LIGHTING);

	// Enable Light Source number 0
	// OpengL has 8 light sources
	glEnable(GL_LIGHT0);

	// Define Light source 0 ambient light
	GLfloat ambient[] = { 0.1f, 0.1f, 0.1, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	// Define Light source 0 diffuse light
	GLfloat diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

	// Define Light source 0 Specular light
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	// Finally, define light source 0 position in World Space
	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

//=======================================================================
// Material Configuration Function
//======================================================================
void InitMaterial()
{
	// Enable Material Tracking
	glEnable(GL_COLOR_MATERIAL);

	// Sich will be assigneet Material Properties whd by glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Set Material's Specular Color
	// Will be applied to all objects
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

	// Set Material's Shine value (0->128)
	GLfloat shininess[] = { 96.0f };
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}

//=======================================================================
// OpengGL Configuration Function
//=======================================================================
void myInit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(fovy, aspectRatio, zNear, zFar);
	//*******************************************************************************************//
	// fovy:			Angle between the bottom and top of the projectors, in degrees.			 //
	// aspectRatio:		Ratio of width to height of the clipping plane.							 //
	// zNear and zFar:	Specify the front and back clipping planes distances from camera.		 //
	//*******************************************************************************************//

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	gluLookAt(camera.eye.x, camera.eye.y, camera.eye.z, camera.center.x, camera.center.y, camera.center.z, camera.up.x, camera.up.y, camera.up.z);
	//*******************************************************************************************//
	// EYE (ex, ey, ez): defines the location of the camera.									 //
	// AT (ax, ay, az):	 denotes the direction where the camera is aiming at.					 //
	// UP (ux, uy, uz):  denotes the upward orientation of the camera.							 //
	//*******************************************************************************************//

	InitLightSource();

	InitMaterial();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);
}

//=======================================================================
// Render Ground Function
//=======================================================================
void RenderGround()
{
	//glDisable(GL_LIGHTING);	// Disable lighting 

	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	glBindTexture(GL_TEXTURE_2D, tex_ground.texture[0]);	// Bind the ground texture

	//front
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(0, 0, texz);
	glTexCoord2f(1, 0);
	glVertex3f(20, 0, texz);
	glTexCoord2f(1, 1);
	glVertex3f(20, 30, texz);
	glTexCoord2f(0, 1);
	glVertex3f(0, 30, texz);
	glEnd();
	glPopMatrix();

	//right
	glBindTexture(GL_TEXTURE_2D, tex_ground1.texture[0]);
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(20, 0, texz);
	glTexCoord2f(1, 0);
	glVertex3f(20, 0, texz1);
	glTexCoord2f(1, 1);
	glVertex3f(20, 30, texz1);
	glTexCoord2f(0, 1);
	glVertex3f(20, 30, texz);
	glEnd();
	glPopMatrix();

	//left
	glBindTexture(GL_TEXTURE_2D, tex_ground2.texture[0]);
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(0, 0, texz);
	glTexCoord2f(1, 0);
	glVertex3f(0, 0, texz1);
	glTexCoord2f(1, 1);
	glVertex3f(0, 30, texz1);
	glTexCoord2f(0, 1);
	glVertex3f(0, 30, texz);
	glEnd();
	glPopMatrix();

	//ground
	glBindTexture(GL_TEXTURE_2D, tex_ground3.texture[0]);
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(0, 0, -50);
	glTexCoord2f(1, 0);
	glVertex3f(20, 0, -50);
	glTexCoord2f(1, 1);
	glVertex3f(20, 0, 50);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0, 50);
	glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
}

void RenderGround1()
{
	//glDisable(GL_LIGHTING);	// Disable lighting 

	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	glBindTexture(GL_TEXTURE_2D, tex_ground4.texture[0]);	// Bind the ground texture

	//front
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(0, 0, texz);
	glTexCoord2f(1, 0);
	glVertex3f(20, 0, texz);
	glTexCoord2f(1, 1);
	glVertex3f(20, 30, texz);
	glTexCoord2f(0, 1);
	glVertex3f(0, 30, texz);
	glEnd();
	glPopMatrix();

	//right
	glBindTexture(GL_TEXTURE_2D, tex_ground5.texture[0]);
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(20, 0, texz);
	glTexCoord2f(1, 0);
	glVertex3f(20, 0, texz1);
	glTexCoord2f(1, 1);
	glVertex3f(20, 30, texz1);
	glTexCoord2f(0, 1);
	glVertex3f(20, 30, texz);
	glEnd();
	glPopMatrix();

	//left
	glBindTexture(GL_TEXTURE_2D, tex_ground6.texture[0]);
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(0, 0, texz);
	glTexCoord2f(1, 0);
	glVertex3f(0, 0, texz1);
	glTexCoord2f(1, 1);
	glVertex3f(0, 30, texz1);
	glTexCoord2f(0, 1);
	glVertex3f(0, 30, texz);
	glEnd();
	glPopMatrix();

	//ground
	glBindTexture(GL_TEXTURE_2D, tex_ground7.texture[0]);
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(0, 0, -50);
	glTexCoord2f(1, 0);
	glVertex3f(20, 0, -50);
	glTexCoord2f(1, 1);
	glVertex3f(20, 0, 50);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0, 50);
	glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
}

void setupLights() {
	GLfloat ambient[] = { 0.7f, 0.7f, 0.7, 1.0f };
	GLfloat diffuse[] = { 0.6f, 0.6f, 0.6, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0, 1.0f };
	GLfloat shininess[] = { 50 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	GLfloat lightIntensity[] = { 0.7f, 0.7f, 1, 1.0f };
	GLfloat lightPosition[] = { -7.0f, 15.0f, 3.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightIntensity);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
}
void setupCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 640 / 480, 0.001, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.look();
}

void cameraeye(double ex, double ey, double ez, double cx, double cy, double cz) {
	camera.eye = Vector3f(ex, ey, ez);
	camera.center = Vector3f(cx, cy, cz);
}

void drawJellyfish(double x, double z, double sx, double sy, double sz) {
	glPushMatrix();
	glColor3f(0.8, 0.4, 0.5);
	glTranslated(x, 2, z);
	glScaled(sx, sy, sz);
	model_jellyfish.Draw();
	glPopMatrix();
}

void drawPowerUps(double x, double z, double sx, double sy, double sz) {
	glPushMatrix();
	glColor3f(0, 0.3, 0.6);
	glTranslated(x, 2, z);
	glScaled(sx, sy, sz);
	model_jellyfish.Draw();
	glPopMatrix();
}

void drawSeaUrchin(double x, double z) {
	glPushMatrix();
	glTranslated(x, 2, z);
	glScaled(20, 20, 20);
	model_seaurchin.Draw();
	glPopMatrix();
}

void drawburger(double x, double y, double z, double sx, double sy, double sz) {
	glPushMatrix();
	glColor3f(0.4, 0.3, 0);
	glTranslated(x, y, z);
	glScaled(sx, sy, sz);
	model_burger.Draw();
	glPopMatrix();
}

void drawpowerup(double x, double y, double z, double sx, double sy, double sz) {
	glPushMatrix();
	glColor3f(0.9, 0.4, 0.5);
	glTranslated(x, y, z);
	glScaled(sx, sy, sz);
	model_burger.Draw();
	glPopMatrix();
}

void drawlives(double x, double y, double z, double sx, double sy, double sz) {

	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslated(x, y, z);
	glScaled(sx, sy, sz);
	glRotated(90, 0, 1, 0);
	model_lives.Draw();
	glPopMatrix();
}

void print(int x, int y, int z, char* string)
{
	int len, i;

	//set the position of the text in the window using the x and y coordinates
	glRasterPos3f(x, y, z);

	//get the length of the string to display
	len = (int)strlen(string);

	//loop to display character by character
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

void power1(int val) {
	light1 += 1;
	powerup1 -= 1;
	if (powerup1 > 0) {
		glutTimerFunc(300, power1, 0);
	}
	else {
		light1=0.7;
	}
}
//=======================================================================
// Display Function
//=======================================================================
void Level2(void);
void time2(int val);

void Level1(void)
{
	setupCamera();
	setupLights();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat lightIntensity[] = { 20, light1, 0.7, 1.0f };
	GLfloat lightPosition[] = { 0.0f, 100.0f, 0.0f, light };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);

	// Draw Ground
	RenderGround();

	//draw spongebob
	glPushMatrix();
	glTranslated(10, 3, 45);
	glRotated(180, 0, 1, 0);
	glTranslated(-10, -3, -45);
	glPushMatrix();
	glTranslated(sbx, 3, sbz);
	model_spongebob.Draw();
	glPopMatrix();
	glPopMatrix();

	//draw net
	glPushMatrix();
	glTranslated(12, 0, 45);
	glRotated(180, 0, 1, 0);
	glTranslated(-12, 0, -45);

	glPushMatrix();
	glTranslated(hx, 0, sbz);
	glScaled(0.5, 0.5, 0.5);
	model_wood.Draw();
	glPopMatrix();
	glPopMatrix();

	//draw jellyfish
	drawJellyfish(x3,z1,s1,s1,s1);
	drawJellyfish(x3,z2,s2,s2,s2);
	drawJellyfish(x2, z3, s19, s19, s19);
	drawJellyfish(x1,z3,s3,s3,s3);
	drawJellyfish(x2,z4,s4,s4,s4);
	drawJellyfish(x2,z5,s5,s5,s5);
	drawJellyfish(x3,z6,s16,s16,s16);
	drawPowerUps(x1, z5, s21, s21, s21);
	drawJellyfish(x1, z6, s20, s20, s20);
	drawJellyfish(x3,z7,s6,s6,s6);
	drawJellyfish(x2,z8,s7,s7,s7);
	drawJellyfish(x1, z9, s17, s17, s17);
	drawJellyfish(x1,z10,s8,s8,s8);
	drawJellyfish(x3, z10, s18, s18, s18);
	drawJellyfish(x2,z11,s9,s9,s9);
	drawJellyfish(x3, z12, s27, s27, s27);
	drawJellyfish(x3, z13, s28, s28, s28);
	drawJellyfish(x1,z13,s10,s10,s10);
	drawJellyfish(x1, z14, s22, s22, s22);
	drawJellyfish(x1, z15, s23, s23, s23);
	drawJellyfish(x2,z14,s11,s11,s11);
	drawJellyfish(x3,z16,s12,s12,s12);
	drawJellyfish(x1, z16, s25, s25, s25);
	drawJellyfish(x2,z17,s13,s13,s13);
	drawJellyfish(x3, z18, s26, s26, s26);
	drawJellyfish(x1, z17, s24, s24, s24);
	drawJellyfish(x1,z18,s14,s14,s14);
	drawJellyfish(x3,z19,s15,s15,s15);

	//draw lives
	drawlives(2, 9, 2, L1, L1, L1);
	drawlives(5, 9, 2, L2, L2, L2);
	drawlives(8, 9, 2, L3, L3, L3);


	//draw sea urchin
	drawSeaUrchin(x2, z2);
	drawSeaUrchin(x3, z3);
	drawSeaUrchin(x1, z4);
	drawSeaUrchin(x3, z5);
	drawSeaUrchin(x1, z6);
	drawSeaUrchin(x1, z11);
	drawSeaUrchin(x2, z6);
	drawSeaUrchin(x2, z9);
	drawSeaUrchin(x3, z9);
	drawSeaUrchin(x2, z12);
	drawSeaUrchin(x3, z15);
	drawSeaUrchin(x3, z17);
	drawSeaUrchin(x2, z18);


	if (sbx == 5 && z1 == sbz) {
		score += 1;
		s1 = 0;
		sndPlaySound(TEXT("jellyfish.wav"), SND_ASYNC);
	}
	if (sbx == 5 && z2 == sbz) {
		score += 1;
		s2 = 0;
		//sound
		sndPlaySound(TEXT("jellyfish.wav"), SND_ASYNC);
	}
	if (sbx == 10 && z2 == sbz) {
		//score += 1;
		lives -= 1;
		if (L1 == 1)
			L1 = 0;
		else if (L1 == 0 && L2 == 1)
			L2 = 0;
		else if (L1 == 0 && L2 == 0)
			L3 = 0;
		//sound
		sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
	}
	if (sbx == 5 && z5 == sbz) {
		//score += 1;
		lives -= 1;
		if (L1 == 1)
			L1 = 0;
		else if (L1 == 0 && L2 == 1)
			L2 = 0;
		else if (L1 == 0 && L2 == 0)
			L3 = 0;
		//sound
		sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
	}
	if (sbx == 15 && z3 == sbz) {
		score += 1;
		s3 = 0;
		//sound
		sndPlaySound(TEXT("jellyfish.wav"), SND_ASYNC);
	}
	if (sbx == 5 && z3 == sbz) {
		//score += 1;
		lives -= 1;
		if (L1 == 1)
			L1 = 0;
		else if (L1 == 0 && L2 == 1)
			L2 = 0;
		else if (L1 == 0 && L2 == 0)
			L3 = 0;
		//sound
		sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
	}
	if (sbx == 10 && z3 == sbz) {
		score += 1;
		//lives -= 1;
		//sound
		s19 = 0;
		sndPlaySound(TEXT("jellyfish.wav"), SND_ASYNC);
	}
	if (sbx == 10 && z4 == sbz) {
		score += 1;
		s4 = 0;
		sndPlaySound(TEXT("jellyfish.wav"), SND_ASYNC);
	}
	if (sbx == 15 && z4 == sbz) {
		//score += 1;
		lives -= 1;
		if (L1 == 1)
			L1 = 0;
		else if (L1 == 0 && L2 == 1)
			L2 = 0;
		else if (L1 == 0 && L2 == 0)
			L3 = 0;
		//sound
		sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
	}
	if (sbx == 10 && z5 == sbz) {
		score += 1;
		s5 = 0;
		//sound
		sndPlaySound(TEXT("jellyfish.wav"), SND_ASYNC);
	}
	if (sbx == 15 && z5 == sbz) {
		//score += 1;
		s21 = 0;
		//sound
		light = 0;
		glutTimerFunc(0, power1, 0);
		sndPlaySound(TEXT("powerup.wav"), SND_ASYNC);
	}
	if (sbx == 10 && z6 == sbz) {
		//score += 1;
		lives -= 1;
		if (L1 == 1) {
			L1 = 0;
			sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
		}
		else if (L1 == 0 && L2 == 1) {
			L2 = 0;
			sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
		}
		else if (L1 == 0 && L2 == 0)
			L3 = 0;
	}
	if (sbx == 5 && z6 == sbz) {
		if (s21 == 0 && powerup1 > 0) {
			score += 2;
		}
		else {
			score += 1;
			light1 = 0.7;
		}
		s16 = 0;
		sndPlaySound(TEXT("jellyfish.wav"), SND_ASYNC);
	}
	if (sbx == 5 && z7 == sbz) {
		if (s21 == 0 && powerup1 > 0) {
			score += 2;
		}
		else {
			score += 1;
			light1 = 0.7;
		}
		s6 = 0;
		sndPlaySound(TEXT("jellyfish.wav"), SND_ASYNC);
		//sound
	}
	if (sbx == 15 && z6 == sbz) {
		if (s21 == 0 && powerup1 > 0) {
			score += 2;
		}
		else {
			score += 1;
			light1 = 0.7;
		}
		s20 = 0;
		sndPlaySound(TEXT("jellyfish.wav"), SND_ASYNC);
		//sound
	}
	if (sbx == 10 && z8 == sbz) {
		if (s21 == 0 && powerup1 > 0) {
			score += 2;
		}
		else {
			score += 1;
			light1 = 0.7;
		}
		s7 = 0;
		sndPlaySound(TEXT("jellyfish.wav"), SND_ASYNC);
		//sound
	}
	if (sbx == 10 && z9 == sbz) {
		//score += 1;
		lives -= 1;
		if (L1 == 1) {
			L1 = 0;
			sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
		}
		else if (L1 == 0 && L2 == 1) {
			L2 = 0;
			sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
		}
		else if (L1 == 0 && L2 == 0)
			L3 = 0;
	}
	if (sbx == 15 && z6 == sbz) {
		//score += 1;
		lives -= 1;
		if (L1 == 1) {
			L1 = 0;
			sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
		}
		else if (L1 == 0 && L2 == 1) {
			L2 = 0;
			sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
		}
		else if (L1 == 0 && L2 == 0)
			L3 = 0;
	}
	if (sbx == 5 && z9 == sbz) {
		//score += 1;
		lives -= 1;
		if (L1 == 1) {
			L1 = 0;
			sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
		}
		else if (L1 == 0 && L2 == 1) {
			L2 = 0;
			sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
		}
		else if (L1 == 0 && L2 == 0)
			L3 = 0;
	}
	if (sbx == 15 && z9 == sbz) {
		if (s21 == 0 && powerup1 > 0) {
			score += 2;
		}
		else {
			score += 1;
			light1 = 0.7;
		}
		s17 = 0;
		sndPlaySound(TEXT("jellyfish.wav"), SND_ASYNC);
	}
	if (sbx == 15 && z10 == sbz) {
		if (s21 == 0 && powerup1 > 0) {
			score += 2;
		}
		else {
			score += 1;
			light1 = 0.7;
		}
		s8 = 0;
		sndPlaySound(TEXT("jellyfish.wav"), SND_ASYNC);
		//sound
	}
	if (sbx == 5 && z10 == sbz) {
		if (s21 == 0 && powerup1 > 0) {
			score += 2;
		}
		else {
			score += 1;
			light1 = 0.7;
		}
		s18 = 0;
		sndPlaySound(TEXT("jellyfish.wav"), SND_ASYNC);
		//sound
	}
	if (sbx == 10 && z11 == sbz) {
		if (s21 == 0 && powerup1 > 0) {
			score += 2;
		}
		else {
			score += 1;
			light1 = 0.7;
		}
		s9 = 0;
		sndPlaySound(TEXT("jellyfish.wav"), SND_ASYNC);
		//sound
	}
	if (sbx == 15 && z11 == sbz) {
		lives -= 1;
		if (L1 == 1) {
			L1 = 0;
			sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
		}
		else if (L1 == 0 && L2 == 1) {
			L2 = 0;
			sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
		}
		else if (L1 == 0 && L2 == 0)
			L3 = 0;
		//sound
	}
	if (sbx == 10 && z12 == sbz) {
		//score += 1;
		lives -= 1;
		if (L1 == 1) {
			L1 = 0;
			sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
		}
		else if (L1 == 0 && L2 == 1) {
			L2 = 0;
			sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
		}
		else if (L1 == 0 && L2 == 0)
			L3 = 0;
	}
	if (sbx == 5 && z12 == sbz) {
		if (s21 == 0 && powerup1 > 0) {
			score += 2;
		}
		else {
			score += 1;
			light1 = 0.7;
		}
		s27 = 0;
		sndPlaySound(TEXT("jellyfish.wav"), SND_ASYNC);
		//sound
	}
	if (sbx == 5 && z13 == sbz) {
		if (s21 == 0 && powerup1 > 0) {
			score += 2;
		}
		else {
			score += 1;
			light1 = 0.7;
		}
		s28 = 0;
		sndPlaySound(TEXT("jellyfish.wav"), SND_ASYNC);
		//sound
	}
	if (sbx == 15 && z13 == sbz) {
		if (s21 == 0 && powerup1 > 0) {
			score += 2;
		}
		else {
			score += 1;
			light1 = 0.7;
		}
		s10 = 0;
		sndPlaySound(TEXT("jellyfish.wav"), SND_ASYNC);
		//sound
	}
	if (sbx == 15 && z14 == sbz) {
		if (s21 == 0 && powerup1 > 0) {
			score += 2;
		}
		else {
			score += 1;
			light1 = 0.7;
		}
		s22 = 0;
		sndPlaySound(TEXT("jellyfish.wav"), SND_ASYNC);
		//sound
	}
	if (sbx == 10 && z14 == sbz) {
		if (s21 == 0 && powerup1 > 0) {
			score += 2;
		}
		else {
			score += 1;
			light1 = 0.7;
		}
		s11 = 0;
		sndPlaySound(TEXT("jellyfish.wav"), SND_ASYNC);
		//sound
	}
	if (sbx == 5 && z15 == sbz) {
		//score += 1;
		lives -= 1;
		if (L1 == 1) {
			L1 = 0;
			sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
		}
		else if (L1 == 0 && L2 == 1) {
			L2 = 0;
			sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
		}
		else if (L1 == 0 && L2 == 0)
			L3 = 0;
	}
	if (sbx == 15 && z15 == sbz) {
		if (s21 == 0 && powerup1 > 0) {
			score += 2;
		}
		else {
			score += 1;
			light1 = 0.7;
		}
		s23 = 0;
		sndPlaySound(TEXT("jellyfish.wav"), SND_ASYNC);
		//sound
	}
	if (sbx == 5 && z16 == sbz) {
		if (s21 == 0 && powerup1 > 0) {
			score += 2;
		}
		else {
			score += 1;
			light1 = 0.7;
		}
		s12 = 0;
		sndPlaySound(TEXT("jellyfish.wav"), SND_ASYNC);
		//sound
	}
	if (sbx == 15 && z16 == sbz) {
		if (s21 == 0 && powerup1 > 0) {
			score += 2;
		}
		else {
			score += 1;
			light1 = 0.7;
		}
		s25 = 0;
		sndPlaySound(TEXT("jellyfish.wav"), SND_ASYNC);
		//sound
	}
	if (sbx == 10 && z17 == sbz) {
		if (s21 == 0 && powerup1 > 0) {
			score += 2;
		}
		else {
			score += 1;
			light1 = 0.7;
		}
		s13 = 0;
		sndPlaySound(TEXT("jellyfish.wav"), SND_ASYNC);
		//sound
	}
	if (sbx == 15 && z17 == sbz) {
		if (s21 == 0 && powerup1 > 0) {
			score += 2;
		}
		else {
			score += 1;
			light1 = 0.7;
		}
		s24 = 0;
		sndPlaySound(TEXT("jellyfish.wav"), SND_ASYNC);
		//sound
	}
	if (sbx == 5 && z17 == sbz) {
		//score += 1;
		lives -= 1;
		if (L1 == 1) {
			L1 = 0;
			sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
		}
		else if (L1 == 0 && L2 == 1) {
			L2 = 0;
			sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
		}
		else if (L1 == 0 && L2 == 0)
			L3 = 0;
	}
	if (sbx == 15 && z18 == sbz) {
		if (s21 == 0 && powerup1 > 0) {
			score += 2;
		}
		else {
			score += 1;
			light1 = 0.7;
		}
		s14 = 0;
		sndPlaySound(TEXT("jellyfish.wav"), SND_ASYNC);
		//sound
	}
	if (sbx == 10 && z18 == sbz) {
		//score += 1;
		lives -= 1;
		if (L1 == 1) {
			L1 = 0;
			sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
		}
		else if (L1 == 0 && L2 == 1) {
			L2 = 0;
			sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
		}
		else if (L1 == 0 && L2 == 0)
			L3 = 0;
	}
	if (sbx == 5 && z19 == sbz) {
		if (s21 == 0 && powerup1 > 0) {
			score += 2;
		}
		else {
			score += 1;
			light1 = 0.7;
		}
		s15 = 0;
		//sound
		sndPlaySound(TEXT("jellyfish.wav"), SND_ASYNC);
	}
	if (sbx == 5 && z18 == sbz) {
		if (s21 == 0 && powerup1 > 0) {
			score += 2;
		}
		else {
			score += 1;
			light1 = 0.7;
		}
		s26 = 0;
		sndPlaySound(TEXT("jellyfish.wav"), SND_ASYNC);
		//sound
	}
	if (lives == 0) {
		flag = true;
		lives = -1;
		sndPlaySound(TEXT("gameover.wav"), SND_ASYNC);
	}
	if (lives < 0) {
		glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glColor3f(1, 1, 1);
		char* p0s[20];
		sprintf((char*)p0s, "GAME OVER!");
		print(2, -10, 0, (char*)p0s);
	}
	if (flag == false) {
		glColor3f(1, 1, 1);
		char* p0s[20];
		sprintf((char*)p0s, "Score: %d", score);
		print(12, 7, 2, (char*)p0s);

	}
	if (lives > 0 && z19 >= sbz) {
		powerup1 = 25;
		glutDisplayFunc(Level2);
	}

	glutSwapBuffers();
}

void Level2(void)
{
	setupCamera();
	setupLights();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat lightIntensity[] = { 0.7, light1, 0.7, 1.0f };
	GLfloat lightPosition[] = { 0.0f, 100.0f, 0.0f, light};
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);

	//sndPlaySound(TEXT("background2.wav"), SND_ASYNC | SND_LOOP);

	//Draw Ground
	RenderGround1();

	//draw spongebob
	glPushMatrix();
	glTranslated(10, 3, 45);
	glRotated(180, 0, 1, 0);
	glTranslated(-10, -3, -45);
	glPushMatrix();
	glTranslated(sbx, sby, sbz);
	model_spongebob.Draw();
	glPopMatrix();
	glPopMatrix();

	//draw spatula
	glPushMatrix();
	glTranslated(12, 0, 45);
	glRotated(180, 0, 1, 0);
	glTranslated(-12, 0, -45);
	glPushMatrix();
	glTranslated(hx, hy, sbz);
	glScaled(0.4, 0.4, 0.4);
	glRotated(90, 0, 0, 1);
	glRotated(90, 1, 0, 0);
	model_spatula.Draw();
	glPopMatrix();
	glPopMatrix();

	drawlives(2, 9, 2, L1, L1, L1);
	drawlives(5, 9, 2, L2, L2, L2);
	drawlives(8, 9, 2, L3, L3, L3);

	drawpowerup(x3, 2, c5, h16, h16, h16);

	if (sbx == 5 && c5 == sbz) {
		score += 5;
		h16 = 0;
		//sound
		light = 0;
		sndPlaySound(TEXT("powerup.wav"), SND_ASYNC);
		glutTimerFunc(0, power1, 0);
	}

	drawburger(x3, by1, c1, h1, h1, h1);
	drawburger(x1, by2, c2, h2, h2, h2);
	drawburger(x3, by3, c3, h3, h3, h3);
	drawburger(x2, by4, c4, h4, h4, h4);
	drawburger(x3, by1, c7, h5, h5, h5);
	drawburger(x1, by2, c7, h6, h6, h6);
	drawburger(x2, by3, c8, h7, h7, h7);
	drawburger(x3, by4, c10, h8, h8, h8);
	drawburger(x2, by4, c11, h9, h9, h9);
	drawburger(x3, by3, c13, h10, h10, h10);
	drawburger(x2, by2, c14, h11, h11, h11);
	drawburger(x1, by1, c16, h12, h12, h12);
	drawburger(x2, by1, c17, h13, h13, h13);
	drawburger(x3, by3, c18, h14, h14, h14);
	drawburger(x1, by4, c19, h15, h15, h15);

	if ((sbx == 5) && (c1 == sbz)) {
		h1 = 0;
		score += 1;
		sndPlaySound(TEXT("jellyfish.wav"), SND_ASYNC);

	}
	if ((sbx == 15) && (c2 == sbz)) {
		h2 = 0;
		score += 1;
		sndPlaySound(TEXT("jellyfish.wav"), SND_ASYNC);

	}
	if ((sbx == 5) && (c3 == sbz)) {
		h3 = 0;
		score += 1;
		sndPlaySound(TEXT("jellyfish.wav"), SND_ASYNC);

	}
	if ((sbx == 10) && (c4 == sbz)) {
		h4 = 0;
		score += 1;
		sndPlaySound(TEXT("jellyfish.wav"), SND_ASYNC);

	}
	if ((sbx == 5) && (c7 == sbz)) {
		h5 = 0;
		score += 1;
		sndPlaySound(TEXT("jellyfish.wav"), SND_ASYNC);

	}
	if ((sbx == 15) && (c7 == sbz)) {
		h6 = 0;
		score += 1;
		sndPlaySound(TEXT("jellyfish.wav"), SND_ASYNC);

	}
	if ((sbx == 10) && (c8 == sbz)) {
		h7 = 0;
		score += 1;
		sndPlaySound(TEXT("jellyfish.wav"), SND_ASYNC);

	}
	if ((sbx == 5) && (c10 == sbz)) {
		h8 = 0;
		score += 1;
		sndPlaySound(TEXT("jellyfish.wav"), SND_ASYNC);

	}
	if ((sbx == 10) && (c11 == sbz)) {
		h9 = 0;
		score += 1;
		sndPlaySound(TEXT("jellyfish.wav"), SND_ASYNC);

	}
	if ((sbx == 5) && (c13 == sbz)) {
		h10 = 0;
		score += 1;
		sndPlaySound(TEXT("jellyfish.wav"), SND_ASYNC);

	}
	if ((sbx == 10) && (c14 == sbz)) {
		h11 = 0;
		score += 1;
		sndPlaySound(TEXT("jellyfish.wav"), SND_ASYNC);

	}
	if ((sbx == 15) && (c16 == sbz)) {
		h12 = 0;
		score += 1;
		sndPlaySound(TEXT("jellyfish.wav"), SND_ASYNC);

	}
	if ((sbx == 10) && (c17 == sbz)) {
		h13 = 0;
		score += 1;
		sndPlaySound(TEXT("jellyfish.wav"), SND_ASYNC);

	}
	if ((sbx == 5) && (c18 == sbz)) {
		h14 = 0;
		score += 1;
		sndPlaySound(TEXT("jellyfish.wav"), SND_ASYNC);

	}
	if ((sbx == 15) && (c19 == sbz)) {
		h15 = 0;
		score += 1;
		sndPlaySound(TEXT("jellyfish.wav"), SND_ASYNC);
	}

	//draw sea urchin
	drawSeaUrchin(x2, c2);
	drawSeaUrchin(x1, c3);
	drawSeaUrchin(x3, c4);
	drawSeaUrchin(x1, c5);
	drawSeaUrchin(x3, c6);
	drawSeaUrchin(x3, c11);
	drawSeaUrchin(x2, c6);
	drawSeaUrchin(x2, c9);
	drawSeaUrchin(x1, c9);
	drawSeaUrchin(x2, c12);
	drawSeaUrchin(x1, c15);
	drawSeaUrchin(x1, c17);
	drawSeaUrchin(x2, c18);


	if (sbx == 10 && c2 == sbz) {
		//score += 1;
		lives -= 1;
		//sound
		if (L1 == 1) {
			L1 = 0;
			sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
		}
		else if (L1 == 0 && L2 == 1) {
			L2 = 0;
			sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
		}
		else if (L1 == 0 && L2 == 0)
			L3 = 0;
	}

	if (sbx == 15 && c3 == sbz) {
		lives -= 1;
		//sound
		if (L1 == 1) {
			L1 = 0;
			sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
		}
		else if (L1 == 0 && L2 == 1) {
			L2 = 0;
			sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
		}
		else if (L1 == 0 && L2 == 0)
			L3 = 0;
	}

	if (sbx == 5 && c4 == sbz) {
		lives -= 1;
		//sound
		if (L1 == 1) {
			L1 = 0;
			sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
		}
		else if (L1 == 0 && L2 == 1) {
			L2 = 0;
			sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
		}
		else if (L1 == 0 && L2 == 0)
			L3 = 0;
	}

	if (sbx == 15 && c5 == sbz) {
		if ((powerup1 > 0 && h16!=0) || (powerup1 <= 0 && h16==0)) {
			lives -= 1;
			//sound
			if (L1 == 1) {
				L1 = 0;
				sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
			}
			else if (L1 == 0 && L2 == 1) {
				L2 = 0;
				sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
			}
			else if (L1 == 0 && L2 == 0)
				L3 = 0;
		}
	}
	if (sbx == 5 && c6 == sbz) {
		if ((powerup1 > 0 && h16 != 0) || (powerup1 <= 0 && h16 == 0)) {
			lives -= 1;
			//sound
			if (L1 == 1) {
				L1 = 0;
				sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
			}
			else if (L1 == 0 && L2 == 1) {
				L2 = 0;
				sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
			}
			else if (L1 == 0 && L2 == 0)
				L3 = 0;
		}
	}
	if (sbx == 5 && c11 == sbz) {
		if ((powerup1 > 0 && h16 != 0) || (powerup1 <= 0 && h16 == 0)) {
			lives -= 1;
			//sound
			if (L1 == 1) {
				L1 = 0;
				sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
			}
			else if (L1 == 0 && L2 == 1) {
				L2 = 0;
				sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
			}
			else if (L1 == 0 && L2 == 0)
				L3 = 0;
		}
	}

	if (sbx == 10 && c6 == sbz) {
		if ((powerup1 > 0 && h16 != 0) || (powerup1 <= 0 && h16 == 0)) {
			lives -= 1;
			//sound
			if (L1 == 1) {
				L1 = 0;
				sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
			}
			else if (L1 == 0 && L2 == 1) {
				L2 = 0;
				sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
			}
			else if (L1 == 0 && L2 == 0)
				L3 = 0;
		}
	}
	if (sbx == 10 && c9 == sbz) {
		if ((powerup1 > 0 && h16 != 0) || (powerup1 <= 0 && h16 == 0)) {
			lives -= 1;
			//sound
			if (L1 == 1) {
				L1 = 0;
				sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
			}
			else if (L1 == 0 && L2 == 1) {
				L2 = 0;
				sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
			}
			else if (L1 == 0 && L2 == 0)
				L3 = 0;
		}
	}

	if (sbx == 15 && c9 == sbz) {
		if ((powerup1 > 0 && h16 != 0) || (powerup1 <= 0 && h16 == 0)) {
			lives -= 1;
			//sound
			if (L1 == 1) {
				L1 = 0;
				sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
			}
			else if (L1 == 0 && L2 == 1) {
				L2 = 0;
				sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
			}
			else if (L1 == 0 && L2 == 0)
				L3 = 0;
		}
	}

	if (sbx == 10 && c12 == sbz) {
		if ((powerup1 > 0 && h16 != 0) || (powerup1 <= 0 && h16 == 0)) {
			lives -= 1;
			//sound
			if (L1 == 1) {
				L1 = 0;
				sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
			}
			else if (L1 == 0 && L2 == 1) {
				L2 = 0;
				sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
			}
			else if (L1 == 0 && L2 == 0)
				L3 = 0;
		}

	}
	if (sbx == 15 && c15 == sbz) {
		if ((powerup1 > 0 && h16 != 0) || (powerup1 <= 0 && h16 == 0)) {
			lives -= 1;
			//sound
			if (L1 == 1) {
				L1 = 0;
				sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
			}
			else if (L1 == 0 && L2 == 1) {
				L2 = 0;
				sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
			}
			else if (L1 == 0 && L2 == 0)
				L3 = 0;
		}

	}
	if (sbx == 15 && c17 == sbz) {
		if ((powerup1 > 0 && h16 != 0) || (powerup1 <= 0 && h16 == 0)) {
			lives -= 1;
			//sound
			if (L1 == 1) {
				L1 = 0;
				sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
			}
			else if (L1 == 0 && L2 == 1) {
				L2 = 0;
				sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
			}
			else if (L1 == 0 && L2 == 0)
				L3 = 0;
		}

	}

	if (sbx == 10 && c18 == sbz) {
		if ((powerup1 > 0 && h16 != 0) || (powerup1 <= 0 && h16 == 0)) {
			lives -= 1;
			//sound
			if (L1 == 1) {
				L1 = 0;
				sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
			}
			else if (L1 == 0 && L2 == 1) {
				L2 = 0;
				sndPlaySound(TEXT("seaurchin.wav"), SND_ASYNC);
			}
			else if (L1 == 0 && L2 == 0)
				L3 = 0;
		}
	}

	if (lives == 0) {
		flag = true;
		lives = -1;
		sndPlaySound(TEXT("gameover.wav"), SND_ASYNC);
	}

	if (lives < 0) {
		glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glColor3f(1, 1, 1);
		char* p0s[20];
		sprintf((char*)p0s, "GAME OVER!");
		print(2, -10, 0, (char*)p0s);
	}
	if (flag == false) {
		glColor3f(1, 1, 1);
		char* p0s[20];
		sprintf((char*)p0s, "Score: %d", score);
		print(12, 7, 2, (char*)p0s);
	}

	if (lives > 0 && c19 >= sbz) {
		glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glColor3f(1, 1, 1);
		char* p0s[20];
		sprintf((char*)p0s, "You Win!");
		print(2, -10, 0, (char*)p0s);
		sndPlaySound(TEXT("end.wav"), SND_ASYNC);
	}


	glutSwapBuffers();
}

void time(int val) {
	z1 += 1;
	z2 += 1;
	z3 += 1;
	z4 += 1;
	z5 += 1;
	z6 += 1;
	z7 += 1;
	z8 += 1;
	z9 += 1;
	z10 += 1;
	z11 += 1;
	z12 += 1;
	z13 += 1;
	z14 += 1;
	z15 += 1;
	z16 += 1;
	z17 += 1;
	z18 += 1;
	z19 += 1;

	glutPostRedisplay();
	if (z19 < sbz && lives > 0) {
		glutTimerFunc(300, time, 0);
	}
	else{
		z19 = 50;
		glutTimerFunc(0, time2, 0);
	}
}

void time2(int val) {
	c1 += 1;
	c2 += 1;
	c3 += 1;
	c4 += 1;
	c5 += 1;
	c6 += 1;
	c7 += 1;
	c8 += 1;
	c9 += 1;
	c10 += 1;
	c11 += 1;
	c12 += 1;
	c13 += 1;
	c14 += 1;
	c15 += 1;
	c16 += 1;
	c17 += 1;
	c18 += 1;
	c19 += 1;

	if (by1 < 8)
		by1 += 1;
	else
		by1 -= 5;

	if (by4 < 11)
		by4 += 1;
	else
		by4 -= 5.5;

	glutPostRedisplay();
	if (c19 < sbz && lives > 0) {
		glutTimerFunc(300, time2, 0);
	}
}

void time1(int val) {
	if (light < 6.0) {
		light += 1;
	}
	else {
		light = 0.0;
	}
	if (z19 < sbx) {
		glutTimerFunc(500, time1, 0);
	}
}

//=======================================================================
// Keyboard Function
//=======================================================================
void myKeyboard(unsigned char key, int x, int y)
{
	float d = 0.1;
	switch (key)
	{
	case 'w':
		camera.moveY(d);
		break;
	case 's':
		camera.moveY(-d);
		break;
	case 'a':
		camera.moveX(d);
		break;
	case 'd':
		camera.moveX(-d);
		break;
	case 'q':
		camera.moveZ(d);
		break;
	case 'e':
		camera.moveZ(-d);
		break;
	default:
		break;
	}
	if (key == 'z') {
		camera.center.y = 9.3621;
		camera.center.x = 9.97783;
		camera.center.z = 59.5835;
		camera.up.x = 0.000103445;
		camera.up.y = 0.972394;
		camera.up.z = -0.233343;
		camera.eye.x = 9.97741;
		camera.eye.y = 9.59544;
		camera.eye.z = 60.5559;
	}
	if (key == 'y') {
		camera.center.y = 29.312;
		camera.center.x = 9.98794;
		camera.center.z = 36.5027;
		camera.up.x = 0.000439768;
		camera.up.y = 0.0611531;
		camera.up.z = -0.998128;
		camera.eye.x = 9.98792;
		camera.eye.y = 30.3102;
		camera.eye.z = 36.5639;
	}
	if (key == 'x') {
		camera.center.y = 18.6601;
		camera.center.x = 1.02983;
		camera.center.z = 32.5318;
		camera.up.x = -0.0426777;
		camera.up.y = 0.074847;
		camera.up.z = -0.996281;
		camera.eye.x = 0.0592853;
		camera.eye.y = 18.8937;
		camera.eye.z = 32.5909;
	}
	if (key == 'm') { //first person view
		flag1 = true;
		camera.center.y = 4.69843;
		camera.center.x = 9.9847;
		camera.center.z = 44.0934;
		camera.up.x = 1.18619e-05;
		camera.up.y = 0.99966;
		camera.up.z = -0.0260717;
		camera.eye.x = 9.98426;
		camera.eye.y = 4.7245;
		camera.eye.z = 45.0931;
		sbx = 10;
		hx = 10;
	}
	if (key == 'n') { //third person view
		flag1 = false;
		camera.center.y = 22.5187;
		camera.center.x = 9.97911;
		camera.center.z = 56.7452;
		camera.up.x = 0.000280989;
		camera.up.y = 0.77167;
		camera.up.z = -0.636023;
		camera.eye.x = 9.97877;
		camera.eye.y = 23.1547;
		camera.eye.z = 57.5169;
	}
	if (key == 'j' && (sbx + 5) < 20 && flag1 == true ) { 
		sbx += 5;
		hx += 5;
		camera.eye.x -= 5;
		camera.center.x -= 5;
		flag1 = true;
	}
	if (key == 'l' && (sbx - 5) > 0 && flag1 == true) { 
		sbx -= 5;
		hx -= 5;
		camera.eye.x += 5;
		camera.center.x += 5;
		flag1 = true;
	}
	if (key == 'j' && (sbx + 5) < 20 && flag1 == false) {
		sbx += 5;
		hx += 5;
		camera.eye.x -= 0.5;
		camera.center.x -= 0.5;
	}
	if (key == 'l' && (sbx - 5) > 0 && flag1 == false) {
		sbx -= 5;
		hx -= 5;
		camera.eye.x += 0.5;
		camera.center.x += 0.5;
	}

	glutPostRedisplay();
}

void actM(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		sby += 0.5;
		hy += 0.5;
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		sby = 3;
		hy = 0;
	}
	glutPostRedisplay();
}

void Special(int key, int x, int y) {
	float a = 1.0;

	switch (key) {
	case GLUT_KEY_UP:
		camera.rotateX(a);
		break;
	case GLUT_KEY_DOWN:
		camera.rotateX(-a);
		break;
	case GLUT_KEY_LEFT:
		camera.rotateY(a);
		break;
	case GLUT_KEY_RIGHT:
		camera.rotateY(-a);
		break;
	}

	glutPostRedisplay();
}

//=======================================================================
// Reshape Function
//=======================================================================
void myReshape(int w, int h)
{
	if (h == 0) {
		h = 1;
	}

	WIDTH = w;
	HEIGHT = h;

	// set the drawable region of the window
	glViewport(0, 0, w, h);

	// set up the projection matrix 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, (GLdouble)WIDTH / (GLdouble)HEIGHT, zNear, zFar);

	// go back to modelview matrix so we can move the objects about
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera.eye.x, camera.eye.y, camera.eye.z, camera.center.x, camera.center.y, camera.center.z, camera.up.x, camera.up.y, camera.up.z);
}

//=======================================================================
// Assets Loading Function
//=======================================================================
void LoadAssets()
{
	// Loading Model files
	model_spongebob.Load("Models/spongebob.3ds");
	model_jellyfish.Load("Models/Jellyfish.3ds");
	model_seaurchin.Load("Models/seaurchin.3ds");
	model_wood.Load("Models/WOOD.3ds");
	model_net.Load("Models/NET.3ds");
	model_lives.Load("Models/heart.3ds");
	model_spatula.Load("Models/spatula.3ds");
	model_burger.Load("Models/burger.3ds");

	// Loading texture files
	tex_ground.Load("Textures/frontbg1.bmp");
	tex_ground1.Load("Textures/frontbg1.bmp");
	tex_ground2.Load("Textures/frontbg1.bmp");
	tex_ground3.Load("Textures/ground.bmp");
	tex_ground4.Load("Textures/frontbgb2.bmp");
	tex_ground5.Load("Textures/sidesb.bmp");
	tex_ground6.Load("Textures/sidesb.bmp");
	tex_ground7.Load("Textures/groundb.bmp");
}

//=======================================================================
// Main Function
//=======================================================================
void main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(WIDTH, HEIGHT);

	glutInitWindowPosition(100, 150);

	glutCreateWindow("Spongebob Run");

	glutDisplayFunc(Level1);
	sndPlaySound(TEXT("background.wav"), SND_ASYNC | SND_LOOP);

	glutKeyboardFunc(myKeyboard);
	glutMouseFunc(actM);
	glutSpecialFunc(Special);
	glutTimerFunc(0, time, 0);
	glutTimerFunc(0, time1, 0);

	glutReshapeFunc(myReshape);

	myInit();

	LoadAssets();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	glutMainLoop();
}