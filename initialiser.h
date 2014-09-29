#ifndef INITIAL
#define INITIAL
#include "player.h"
#include "baddy.h"
#include "blok.h"
#include "twin.h"
#include <vga.h>

/* klasa ta jest odpowiedzialna za wlasciwa inicjalizacje planszy oraz za obsluge menu gry */
class initialiser{
	Board& b;	// referencja na plansze
	player* p[4];	// tablica wskaznikow na graczy
public:
	initialiser(Board& bo);
	void addbonus();				// dodaje bonusy
	void operator()(const Board& bo);	// zmienia plansze
	object* add(object* o, int x, int y);	// dodaje dowolny element do tablicy pod wspl. (x,y)
	Board* menu();				// menu gry
	Board* newgame();
	void fill(int f=0);			// wypelnia plansze
	int play(int type=0);			// dodaje gracza. domyslnie gracz jest czlowiekiem (w sumie tylko to dziala)
	int baddys(int type, int amount=1);	// dodaje 'amount' stworkow typu ' type'. obecnie jest tylko 1 typ stworka
};
#endif
