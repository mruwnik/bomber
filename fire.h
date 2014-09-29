
#ifndef FIRE_H
#define FIRE_H
#include <GL/gl.h>					// Header File For The OpenGL 
#include <GL/glu.h>					// Header File For The GLu
#include "Texture.h"
#include "board.h"
#include "math.h"

const float sqrt2 = 1.41421356237;

const int max_sparks = 1000;
const float slowdown = 2000.0f;
const int coloursAmount = 12;

static GLfloat colours[coloursAmount][3]=				// Rainbow Of Colors
{
	{1.0f,0.5f,0.5f},{1.0f,0.75f,0.5f},{1.0f,1.0f,0.5f},{0.75f,1.0f,0.5f},
	{0.5f,1.0f,0.5f},{0.5f,1.0f,0.75f},{0.5f,1.0f,1.0f},{0.5f,0.75f,1.0f},
	{0.5f,0.5f,1.0f},{0.75f,0.5f,1.0f},{1.0f,0.5f,1.0f},{1.0f,0.5f,0.75f}
};

struct spark{
	float rad;					// size ?
	bool	active;					// Active (Yes/No)
	float	life;					// Particle Life
	float	fade;					// Fade Speed
	GLfloat	r,g,b;					// Colour Value
	float	x,y,z;					// Position
	float	xo,yo,zo;				// original Position
	float	xi,yi,zi;				// Direction
	float	xg,yg,zg;				// Gravity
	spark(GLfloat R, GLfloat G, GLfloat B, float X, float Y, float Z, float Xi, float Yi, float Zi, float Xg, float Yg, float Zg, float f, float r = 0.03, bool act = true, float l = 1.0);
	spark(GLfloat* colour, float* position, float* direction, float* gravity, float f, bool act = true, float ra = 0.03, float l = 1.0);
	spark(float X, float Y, float Z, GLfloat R = 0, GLfloat G = 0, GLfloat B = 0);
	spark(float rad, GLfloat R = 0, GLfloat G = 0, GLfloat B = 0);
	spark(float rad);
	void print();
};

class sparkler{
	static GLuint tex[1];
	spark** sparks;
	int intensity;
	float spray;
public:
	sparkler(float spray, int intensity = 40, float splash = 1.0, float size = 0.02);
	void print();
	~sparkler();
};

class cloud{
	GLuint tex;
	spark** bits;
	int amount;
	float spray;
public:
	cloud(GLuint t, float spray, int intensity = 400, float ra = sqrt2);
	void print();
	~cloud();
};

class wierdo{
	GLuint tex;
	spark** bits;
	int amount;
	float spray;
public:
	wierdo(int n, GLuint t, float spray, int intensity = 40, float ra = sqrt2/3);
	void print();
	~wierdo();
};


/* oginiki z wybuchu bomby. zamiast szybkosc przechowuja licznik ktory okresla ile jeszcze czasu maja do zycia. gdy licznik 
 * dojdzie do 0, to zamiast wykonacz ruch poprostu znikaja. jezeli ktos napotka sie na ognia to umiera, a ogien rozwala wszystko
 * oprocz sciana niezniszczalne */
class fire : public object{
	pos p;	// pozycja ognie na planszy
	static GLuint tex[1];
	spark** sparks;
	int intensity;
	float rad;
public:
	fire(int x, int y,int t=8, float r = sqrt2, int intensity = max_sparks);
	int move();		 // sprawdza czy powinnien juz zniknac
	action request(object*); // gdy ktos sie na niego napotka to go zabija
	static GLuint getTex();
	static int setTex();
	void setid(int);	
	void print();
	~fire();
};




#endif	// FIRE_H
