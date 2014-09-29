#ifndef BOARD_H
#define BOARD_H
#include "object.h"
#include "list.h"
#include <ncurses.h>
#include <vgakeyboard.h>
#include <string.h>
#include <cstdlib>

/* tutaj sa klasy ktore dziala wprost na plansze */

/**/ const int XPOS = 0; /**/// stale uzywane przy wyswietlanie planszy. sa tylko uzywane przez ncurses.h
/**/ const int YPOS = 0; /**/

/* sciana niezniszalna. na plansie wystepuja wskazniki na tylko 1 okaz, bo i tak w zaden sposob nie jest modifikowana */
struct Wall : public object{
	Wall();
	action request(object* o);
	~Wall(){};
};	

/* klasa ktora przechowuje plansze. plansza jest tablica dwuwymiarowa wskaznikow na obiekty typu 'object' po ktory wszelakie
 * inne objekty dziedzicza ( klasa object jest abstrakcjna). jest takze w tej klasie lista (ktora jest w sumie
 * wektorem) w ktorej sa zapisane te objekty ktore aktywnie cos robia (graczy, stwory, itp.). jedna runda polega na przejsciu
 * przez owa liste i wywolanie dla kazdego objektu jego funkcje move() ktora powoduje, ze dany objekt wykonuje swoj ruch */
class Board{
	object*** board;	// sama tablica
	int n,m,players,baddys,over; // wysokosc, szerokosc planszy; ile zostalo graczy, stworow; czy juz ktos wygral
	Wall wall;		// egzemplarz sciany niezniszczalnej ktora jest na plaszy
	List<object> list;	// lista ( w sumie wektor ) objektow aktywnych
	Board(const Board&){};	// aby nie dalo sie skopiowac tablice
public:
	Board(int n, int m);	
	int round();		// wywoluje funkcje move() dla kazdego objektu listy
	void print();		// wyswietla obecny stan gry
	int add2list(object*);	// dodaje objekt do listy
	object* dellist(int i);	// usuwa i-ty element z listy, ale nie usuwa samego objektu - to musi zrobic sam objekt
	action movebeing(int x,int y,action kier); // probuje przesunac object o wsp. (x,y) o 1 miejsce w kierunku 'kier'
	object* check(int x,int y);	// zwraca wskaznik na objekt pod wsp. (x,y)
	object* place(object*,int x,int y);	// probuje klasc objekt na board[x,y], jezeli sie nie da to go usuwa i zwraca 0
	void remove(int x,int y);	// usuwa objekt pod wsp. (x,y)
	void playerDown();	// dekrementuje zmienna players przy smierci gracza
	void baddyDown();	// to samo dla stworkow
	int checkBaddys();	// zwraca ilosc stworow na plansie
	void end(int x, int y);	// konczy gre na obecnej plansie
	friend class initialiser; // klasa ktora inicjalizuje plansie
	friend class twin;	// umozliwia postawienia 2 objekty na 1 polu planszy
	~Board();
};

/* klasa ktora przechowuje pozycje objektu na plansie i posredniczy miedzy objektem a plansza */
class pos{
protected:
	static int n,m; // wysokosc i dlugosc planszy
	int x,y;	// pozycja objektu na planszy
	signed int id;	// identyfikator objektu ( jezeli jest > niz -1 to jest to pozycja w liscie aktywnych objektow)
	static Board* board; // skaznik na plansze
public:
	pos(int x,int y);
	action move(action);	// probuje wykonacz przekazana akcje (przesunac sie albo umrzecz)
	static void set(Board*,int,int);	// ustawia paramentry planszy
	void getid(object*);	// wstawia objekt do listy aktywnych objektow, ustawiajac przy tym jego nr identyfikacjny
	void setid(int);	// ustawia nr. id., przy czym jezeli jest < niz 0 to wypisuje objekt z list aktywnych objektow	
	void remove();		// uzywana przy smierci stwora by zawiadomic planszy, ze jest jeden stworek mniej
	~pos();
};
#endif
