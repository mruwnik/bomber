#ifndef BLOK_H
#define BLOK_H
#include "board.h"
#include "player.h"

/* klasa ta obsluguje wszelakie bonusy. nalezy ja zadeklarowac z znakiem jakim bedzie mialo na planszy oraz ze funkcja skladowa
 * klasy gracza ktora bedzie odpowiedzialna za modifikacji jego parametrow */
class bonus: public object{
	char c;		//znak wypisywany na ekran po rozwalenie sciany
	void (player::*f)();// wskaznik na funkcje skladowa gracza
protected:
	int dead;	// pamieta czy sciana rozwalona czy nie
	pos p;		// pozycja bonusa na planszy
public:
	bonus(int x, int y, char c, void (player::*f)());
	action request(object *);// obsluguje prosby by sie przesuniac
	void die();		// rozwala sciane, ewentualnie bonusa
};

/* klasa pomocnicza do drzwi - przechowuje ich pozycja na planszy */
struct doorpos: public pos{
	doorpos(int x, int y);
	int checkbaddys();	// sprawdza czy jakies stwory zostaly na planszy
	void victory();		// konczy gre na obecnej planszy, mozna tutaj dawac efekty koncowe
};

/* drzwi. jezeli nie bedzie juz stworkow na planszy i drzwi sa odkryte, to przejscie przez nie oznacza przejscie do nastepnej
 * planszy */
class door: public object{
	int id;		// identyfikator w liscie aktywnych obiektow ( co ture sprawdza czy jeszcze sa stworki )
	int dead;	// czy sciana zakrywajaca drzwi zostala juz rozwalona
	char c;		// symbol drzwi po rozwaleniu sciany ktora je ukrywa
	doorpos p;	// pozycja drzwi na planszy
public:
	door(int x, int y, char c='X');
	int move();		// sprawdza czy jeszcze sa stworki, jezeli nie i drzwi sa zakryte, to daje wskazowke gdzie sa
	action request(object *);// obsluguje obiektu ktore wpady na drzwi
	void die();		// jezeli drzwi jeszcze nie sa odkryte, to je odkrywa
	void setid(int);	// ustawia identyfikator drzwi (uzywane przy sortowaniu liste aktywnych obiektow)
};

/* zwykla sciana. jezeli sie ja rozwali to jest puste pole na planszie */
class blok : public object{
	pos p;		//pozycja na planszie
public:
	blok(int x, int y,char c='X');
	void die();	// rozwala sciane
	action request(object* o); // informuje napotkane obietkom, ze nie ma przejscia (chyba, ze umia latac)
	~blok();
};

#endif
