#ifndef PLAYER_H
#define PLAYER_H
#include "bomb.h"
#include "list.h"
#include "twin.h"
#include "baddy.h"
#include <vgakeyboard.h>
#include <typeinfo>

/* prosta klasa ktora przechowuje kody klawiszowe poszczegolnych przyciskow sterujacych */
struct knefle{
	knefle(int,int,int,int,int);
	knefle();
	knefle& operator=(const knefle&);
	int up;
	int right;
	int down;
	int left;
	int bomb;
};

/* pozycja gracza - takze pozwala postwic bomby i przy smierci gracza powiadomia planszy, ze jest 1 gracza mniej */
struct playerpos : public pos{
	playerpos(int x, int y);
	bomba* spawnbomb(object*,int);	// postawia bombe pod graczem
	void remove();			// powiadomia plansze o smierci gracza
	~playerpos();
};

/* klasa gracza. posiada liste swoich postawionych bomb i jest odpowiedzialny za to by je wysadzic. jezeli umrze ale zostawi
 * bomby na plansze to przekazuje je do listy objektow aktywnych aby sie wysadzily w odpowiednim momencie. jest to tak zrobione
 * by mozna bylo latwo sledzic stan wszystkich bomb danego gracza, a tak ze po to by umozliwic dolozenia bonusa ktory by
 * pozwalal bomby wysadzac zdalnie zamiast na czas*/
class player : public object{
	action face;// kierunek w ktora gracz patrzy - nieuzywany, ale moze byc przydatny przy porzadnej grafiki 
	playerpos p;
	List<bomba> list;// tablica bomb - jak postawi sie bombe to zostaje on przechowany w owej tablicy
	int range,bombs,speed;	// zasieg bomby, ilosc bomb oraz predkosc gracza
	knefle k;		// kody klawiszowe poszczegolnych przyciskow uzywane do sterowania graczem
	signed int x,y;
public:
	player(int x, int y, knefle k, int t=6);
	void addbomb();		// bonusowa bomba
	void incrange();	// bonus dajacy +1 do zasiegu
	void stim();		// bonus przyspieszajacy gracza
	void die();		// zabija gracza ( moznaby wykorzystac jako 'bonus' :D )
	int move();		// obsluguje ruchy gracza
	void setid(int);
	void getid();
	void setkeys(const knefle&); // za pomoca tej funkcji mozna zmienic klawisze sterujace
	action request(object*);// do pytania sie o usuniecia sie z drogi	
	~player();
};
#endif
