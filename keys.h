#ifndef KEYS_H
#define KEYS_H
#include <GL/glut.h>
static const int keysAmount = 279;

enum specialKeys{F1 = 258, F2, F3, F4, F5, F6, F7, F8,
		F9, F10, F11, F12, LEFT, UP, RIGHT, DOWN,
		PAGE_UP, PAGE_DOWN, HOME, END, INSERT};

class keys{
static bool key[keysAmount];
public:
	int up;
	int right;
	int down;
	int left;
	int bomb;
	keys(int,int,int,int,int);
	keys();
	keys& operator=(const keys&);
	static void init();
	static void keypress(unsigned char k,int x,int y);
	static void specialKeypress(int k,int x,int y);
	static bool keyPressed(unsigned int);
	static void keyrelease(unsigned char k,int x,int y);
	static void specialKeyRelease(int k,int x, int y);
};

#endif //KEYS_H
