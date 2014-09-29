#ifndef OBJECT_H
#define OBJECT_H
#include <ncurses.h>
#include <iostream>

/* action opisuje ruchy. none oznacza zeby nic nie robic, fly jest dla latajacych stworow i oznacza, ze nie mozna tutaj przejsc
 * ale mozna przeleciec. up,right, down i left sa po to by przekazac chec przejscia w danym kierunku. mov oznacza, ze droga jest
 * wolna i ze mozna tutaj przejsc. kill oznacza ze object ktory takowy sygnal dostal musi umrzec */
enum action{none=0,fly,up,right,down,left,mov,kill};
enum {Set,Or,And};	// uzywany przy wypisywaniu znaki. mozna spokojnie usunac jezeli sie uzywa cos innego 

/* klasa bazowa wszystkich objektow na planszy. przechowuje znak objektu (czy obrazek albo co innego - zalezy od 
 * implementacji grafiki) oraz licznik ktory przechowuje ilosc tur zanim mozna wykonac ruch */
class object{
	char symbol; // symbol objektu - tu bedziesz pewnie musial cos innego wsadzic
	unsigned long int mask; // uzywany przez ncurses
public:
	int counter; // zmieniajac ta wartosc mozna ustalac czy obiekt ma cos robic czy nie - aby nie tyralo wszystko choby po amfie - to jest taki dzielnik czestotliwosci
	object(char c, unsigned long int = A_NORMAL, int t=0);
	void changeSymbol(char);
	void changeMask(unsigned long int m = 0, int = Set); // uzywany do ncurses. mozna usunac
	virtual int move();// obsluguje dzialanie objektu
	virtual action request(object*) = 0; // do zapytania czy moze objekt sie przesunac
	virtual void die(); // zabija obiekt ( jezeli to mozliwe )
	virtual void setid(int){} 
	virtual void getid(){} 
	virtual void print();
	virtual ~object();
};


#endif
