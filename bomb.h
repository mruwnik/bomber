#ifndef BOMB_H
#define BOMB_H
#include "board.h"

/* oginiki z wybuchu bomby. zamiast szybkosc przechowuja licznik ktory okresla ile jeszcze czasu maja do zycia. gdy licznik 
 * dojdzie do 0, to zamiast wykonacz ruch poprostu znikaja. jezeli ktos napotka sie na ognia to umiera, a ogien rozwala wszystko
 * oprocz sciana niezniszczalne */
class fire : public object{
	pos p;	// pozycja ognie na planszy
public:
	fire(int x, int y,int t=8);
	int move();		 // sprawdza czy powinnien juz zniknac
	action request(object*); // gdy ktos sie na niego napotka to go zabija
	void setid(int);	
	~fire();
};

/* klasa bomba ma swoja klase typu pos poniewaz ma nieco inne szialanie niz typowy objekt. w tej klasie sa tworzone ogniki przy
 * wybuchu (w funkcji move() ). przy wybuchu ognien sie rozprzestrzenia na 'range' pole w kazda strone, chyba ze predzej napotka
 * przeszkode. jezeli cos napotka to wysyla do tego czego sygnal die() i na tym konczy swoje dzielo. jezeli ten rzecz moze 
 * zostac zniszczony to znika i zostaje puste pole, bonus albo ewentualnie drzwi */
class bombpos : public pos{ 
	int range;	// zasieg bomby ( ile ognikow stworzy)
public:
	bombpos(int x,int y, int r);
	int move(action);	// jezeli bomba ma wybucnac to ta funkcja jest odpowiedzialna za tworzenie ogniki
	void setid(int);
};

/* bomba. przy stworzeniu jest na tym samym polu co gracz, wybucha po 'r' turach. jedyny rzecz na co odpowiada to ognien przy
 * czym wybucha */
class bomba : public object{
	bombpos p;	// pozycja bomby na planszy
public:
	bomba(int x, int y, int r);
	int move();	// sprawdza czy wybucnac juz
	void setid(int);	
	void getid();
	int count(){return object::counter;} //	zwraca ile zostalo do wybuchu
	action request(object * o);
	void die();	// wysadza bombe
	~bomba();
};
#endif
