#ifndef MENU_H
#define MENU_H

#include "fire.h"
#include "keys.h"
#include "initialiser.h"
#include <string>

#include <GL/glut.h>
#include <GL/gl.h>
#ifdef USE_FTGL
#include <FTGL/ftgl.h>
#endif

const float r = 2.5;		// promien bomby co jest wyswietlona

class Menu{ 
	initialiser& in;
	sparkler s;				// do menu
#ifdef USE_FTGL
	FTExtrudeFont font;
#endif
	bool mousePressed;
	int menuElement;
	bool pressed;
	bool playerkeys(int);
public:
	Menu(initialiser& i);
	void setMenu(bool pressed, float nr);
	void viewMenu();
	void renderBitmapString(float x, float y, float z, void *font, char *string);   
	void print();
	int menu();
	int options();
	int multiplayer();
	int changekeys();
};
#endif //MENU_H
