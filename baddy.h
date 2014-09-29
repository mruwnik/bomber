#ifndef BADDY_H
#define BADDY_H
#include "board.h"
#include <typeinfo>

/* klasa bazowa wszystkich potworow. wystarczy dzedziczyc po niej i zmienic znak i predkosc w konstruktorze oraz predefiniowac
 * funkcje move(). mozna takze zrobic latajace stwory, ale to jest o ciut trudniej. aby rozwiazac problem 2 obiektow na tym
 * samym polu zrobiono klase twin. mozna zobaczyc jak ja uzywac na podstawie klasy bomba, przyczym nalezalo by zamisat bomby
 * wstawic mur, a zamiast gracza latajacy stworek */
class baddy : public object{
	int speed;  // predkosc stworka
	pos p;	    // pozycja stworka na planszy
public:
	baddy(int x,int y,char c,int s=18);// x,y - wspol. stwora, c - jak on wyglada na planszy, s - predkosc stwora
	void die();	// bezwzglednie zabija stwora
	int move();	// funkcja odpowiedzialna z ruch stwora
	void setid(int);// ustala identifikator stwora
	action request(object* o); // przyjmuje prosby o usuniecia sie z drogi
	~baddy();
};
#endif
