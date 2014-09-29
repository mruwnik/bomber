#ifndef OBJECT_H
#define OBJECT_H
#include <iostream>

	#include "Texture.h"
	#include <GL/glut.h>

/* action opisuje ruchy. none oznacza zeby nic nie robic, fly jest dla latajacych stworow i oznacza, ze nie mozna tutaj przejsc
 * ale mozna przeleciec. up,right, down i left sa po to by przekazac chec przejscia w danym kierunku. mov oznacza, ze droga jest
 * wolna i ze mozna tutaj przejsc. kill oznacza ze object ktory takowy sygnal dostal musi umrzec */
enum action{none=0,fly,up,right,down,left,mov,kill};

/* klasa bazowa wszystkich objektow na planszy. przechowuje znak objektu (czy obrazek albo co innego - zalezy od 
 * implementacji grafiki) oraz licznik ktory przechowuje ilosc tur zanim mozna wykonac ruch */
class object{

protected:
	Texture* symbol[2]; // symbol objektu - zrobilem to jko tablica roznych tekstur, bo to mi pasuje do scian. jako, ze stworki itp. i tak beda musialy miec jakies osobne animacje, to powinno wystarczyc. problem moze byc z zapamietaniem dlugosci tej tablicy, ale nie chcialo mi sie tworzyc dla niej klasy
public:
	int counter; // zmieniajac ta wartosc mozna ustalac czy obiekt ma cos robic czy nie - aby nie tyralo wszystko choby po amfie - to jest taki dzielnik czestotliwosci
	object(int t,Texture** c = NULL,  int texlen=2);
	object(Texture* c, int t = 0, int texlen=2);
	void changeSymbol(Texture**);
	void changeSymbol(Texture*,int);
	virtual int move();// obsluguje dzialanie objektu
	virtual action request(object*) = 0; // do zapytania czy moze objekt sie przesunac
	virtual void die(); // zabija obiekt ( jezeli to mozliwe )
	virtual void setid(int){} 
	virtual void getid(){} 
	virtual void print();
	virtual ~object();
};


#endif
