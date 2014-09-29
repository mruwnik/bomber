#ifndef INITIAL
#define INITIAL
#include "player.h"
#include "baddy.h"
#include "blok.h"
#include "twin.h"

//	#include "Texture.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include "Tga.h"
#include <iostream>



enum { deathmatch = 0, coOp = 1};

/* klasa ta jest odpowiedzialna za wlasciwa inicjalizacje planszy oraz za obsluge menu gry */
class initialiser{
	Board& b;				// referencja na plansze
	player* p[4];				// tablica wskaznikow na graczy
	int players;				// ile ma byc graczy
	int baddys[baddyTypes];			// ile stworkow danego rodzaju
	int n,m;				// rozmiary planszy
	texType theme;				// wyglad planszy
	int gameType;				// typ gry ( kogo trza rozwalic - graczy czy stworkow)
	int f;					// wypelnienie planszy
	int bonuses,rounds,roundsleft;
	keys playerKeys[4];			// knefle gracza

public:
	initialiser(Board& bo);
	void addbonus();			// dodaje bonusy
	void operator()(const Board& bo);	// zmienia plansze
	object* add(object* o, int x, int y);	// dodaje dowolny element do tablicy pod wspl. (x,y)
	int menu();				// menu gry
	Board* newgame();
	void fill(int f=0, texType = warehouse);	// wypelnia plansze, texType mowi jak ma wygladac plansza (las, dom iyp.)
	int addPlayer(int nr = -1,int type=0);		// dodaje gracza nr nr. domyslnie gracz jest czlowiekiem (w sumie tylko to dziala)
	int addBaddys(int type, int amount=1);	// dodaje 'amount' stworkow typu ' type'. obecnie jest tylko 1 typ stworka
	void changekeys(int player, keys k);
	void setPlayers(int i);
	void setGameType(int i);
	void setWidth(int i);
	void setHeight(int i);
	void setFill(int i);
	void setTheme(int i);
	void setBonuses(int i);
	void setRounds(int i);
	void setBaddys(int type,int amount);

	int getWidth();
	int getHeight();
	int getFill();
	int getRounds();
	int getRoundsleft();
	int getPlayers();
	int getBonuses();
	int getBaddys(int type);
	char* getTheme();
	int getGameType();

	void viewBoard();
	void nuke();
};
#endif
