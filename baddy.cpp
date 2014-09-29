#include "baddy.h"

/* inicjalizuje stwora znakiem c (domyslnie 'B'), ustala jego kolor, szybkosc, oraz pozycje poczatkowa*/
baddy::baddy(int x, int y, char c, int s) : object(c,COLOR_PAIR(1),s), p(x,y), speed(s){
	x=y=0;
	p.getid(this); // wpisuje stwora do listy aktywnych obiektow (tzn. takie ktore maja co ture cos robic)
}

/* bezwzglednie zabija stwora ( ogien takie sygnal wysyla) */
void baddy::die(){ 
	p.move(kill);
}

/* funkcja ta jest odpowiedzalna za przemieszczenia stworka po planszy - dla prostoty poprostu losuje kierunek i probuje
 * sie tam przemieszcic. aby szlo wprowadzic rozne szybkosci graczy i stworkow wprowadzono licznik ktory sie co tura 
 * dekrementuje i obiekt moze dokonac ruch dopiero gdy jego licznik dojdzie do zera. a jak juz sie wyzeruje to zostaje zas
 * wpisay oryginalna wartosc ktora sie znajduje w zmiennej speed. */
int baddy::move(){
	if(!object::counter--){
		action a;
		switch(rand()%5){
			case 0: a=none; break;
			case 1: a=up; break;
			case 2:	a=right; break;
			case 3:	a=down; break;
			case 4: a=left; break;
		}
		p.move(a);
		object::counter=speed;
	}
	return 0;
}

/* ustawia nr identifikacyjna stworka ( w praktyce jest to jego pozycja w tablicy aktywnych obiektow) */
void baddy::setid(int i){
	p.setid(i);
}

/* jezeli jakis inny obiekt napotka sie na drugi, to ten pierwszy wysyla temu drugiego wskaznik na siebie aby ten drugi sie 
 * zdecydowal co z soba zrobic. wiec jezeli np. stworek trafi na gracza, to gracz umiera a stworek zajmuje jego miejsce, a 
 * jezeli by stworek spotkal sciane, to nie moze sie tam przeniesc ( chyba, ze umie latac). jako, ze nalezalo uzywac elementy
 * z laborek, to zastosowalem tutaj RTTI, aczkolwiek daloby sie to rownie dobrze i pewnie nieco optymalniej uzywajac zwykle 
 * sygnaly. funkcja ta zwraca dzialanie jakie moze wykonac pierwszy obiekt (ten ktory prosil) */
action baddy::request(object* o){
	if(typeid(*this) != typeid(*o))
		return kill;
	return none;
}

baddy::~baddy(){p.remove();} // informuje planszy, ze jest 1 stworek mniej
