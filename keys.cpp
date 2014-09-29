#include "keys.h"
#include <iostream>
bool keys::key[keysAmount]={false};

keys::keys(){
	up = right = down = left = bomb = 0;
}

keys::keys(int a, int b, int c, int d, int e): up(a), right(b), down(c), left(d), bomb(e){}

void keys::keypress(unsigned char c, int,int){
//	std::cout << (int)c << "\n";
	key[c]=true;
}

keys& keys::operator=(const keys& kn){
	up = kn.up;
	right = kn.right;
	down = kn.down;
	left = kn.left;
	bomb = kn.bomb;
}

void keys::init(){
	for(int i=0; i<keysAmount; i++)
		key[i]=false;
}

void keys::specialKeypress(int c, int,int){
	switch(c){
	case GLUT_KEY_F1 : key[258]=true; break;
	case GLUT_KEY_F2 : key[258+1]=true; break;
	case GLUT_KEY_F3 : key[258+2]=true; break;
	case GLUT_KEY_F4 : key[258+3]=true; break;
	case GLUT_KEY_F5 : key[258+4]=true; break;
	case GLUT_KEY_F6 : key[258+5]=true; break;
	case GLUT_KEY_F7 : key[258+6]=true; break;
	case GLUT_KEY_F8 : key[258+7]=true; break;
	case GLUT_KEY_F9 : key[258+8]=true; break;
	case GLUT_KEY_F10 : key[258+9]=true; break;
	case GLUT_KEY_F11 : key[258+10]=true; break;
	case GLUT_KEY_F12 : key[258+11]=true; break;
	case GLUT_KEY_LEFT : key[258+12]=true; break;
	case GLUT_KEY_UP : key[258+13]=true; break;
	case GLUT_KEY_RIGHT : key[258+14]=true; break;
	case GLUT_KEY_DOWN : key[258+15]=true; break;
	case GLUT_KEY_PAGE_UP : key[258+16]=true; break;
	case GLUT_KEY_PAGE_DOWN : key[258+17]=true; break;
	case GLUT_KEY_HOME : key[258+18]=true; break;
	case GLUT_KEY_END : key[258+19]=true; break;
	case GLUT_KEY_INSERT  : key[258+20]=true; break;
	}
}

bool keys::keyPressed(unsigned int k){
	if(k < keysAmount && k > 0)
		return key[k];
	else
		return false;
}

void keys::keyrelease(unsigned char c, int,int){
	key[c]=false;
}

void keys::specialKeyRelease(int c, int,int){
	switch(c){
	case GLUT_KEY_F1 : key[258]=false; break;
	case GLUT_KEY_F2 : key[258+1]=false; break;
	case GLUT_KEY_F3 : key[258+2]=false; break;
	case GLUT_KEY_F4 : key[258+3]=false; break;
	case GLUT_KEY_F5 : key[258+4]=false; break;
	case GLUT_KEY_F6 : key[258+5]=false; break;
	case GLUT_KEY_F7 : key[258+6]=false; break;
	case GLUT_KEY_F8 : key[258+7]=false; break;
	case GLUT_KEY_F9 : key[258+8]=false; break;
	case GLUT_KEY_F10 : key[258+9]=false; break;
	case GLUT_KEY_F11 : key[258+10]=false; break;
	case GLUT_KEY_F12 : key[258+11]=false; break;
	case GLUT_KEY_LEFT : key[258+12]=false; break;
	case GLUT_KEY_UP : key[258+13]=false; break;
	case GLUT_KEY_RIGHT : key[258+14]=false; break;
	case GLUT_KEY_DOWN : key[258+15]=false; break;
	case GLUT_KEY_PAGE_UP : key[258+16]=false; break;
	case GLUT_KEY_PAGE_DOWN : key[258+17]=false; break;
	case GLUT_KEY_HOME : key[258+18]=false; break;
	case GLUT_KEY_END : key[258+19]=false; break;
	case GLUT_KEY_INSERT  : key[258+20]=false; break;
	}
}


