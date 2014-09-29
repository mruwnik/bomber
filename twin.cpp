#include "twin.h"

Board* twin::board = 0;

/* konstruktor ten najpierw usuwa objekt pod wspol. (x,y) z planszy i siebie tam postawia. nastepnie usuwa swoj drugi argument
 * ( ktory chce sie przeniesc na wspol. (x,y)) z listy aktywnych objektow i na koniec dodaje siebie do owej listy. w ten sposob
 * powstaje objekt ktory z pozoru sie nie rozni od innych ale ktory naprawde sie sklada z 2 objektow, gdzie pierwszy nie jest
 * aktywny, a drugi jest. co prawda bomby sa elementami aktywnymi, ale z punktu widzenia planszy, gdy gracz dopiero co ja 
 * postawi, to jest nieaktywna bo gracz nia steruje. */
#ifdef NCURSES
twin::twin(object* o, object* t, int X, int Y): object(' '), one(o), two(t), x(X), y(Y), f(0){
/**/	two->changeMask(A_STANDOUT,Or); // nie potrzebne - uzywany do upiekszania wypisywania znakow
#else
twin::twin(object* o, object* t, int X, int Y): object(1), one(o), two(t), x(X), y(Y), f(0){
#endif
	board->board[y][x]=this;
	two->setid(-1);
	id=board->add2list(this);
}

void twin::set(Board* b){ board=b;}

action twin::request(object* o){return none;}// klasa twin, dla innych objektow zachowuje sie jak mur niezniszczalny

void twin::setid(int i){id =i;}

/* przy porzadnej grafice nalezaloby tutaj sie postarac, ale przy znakach ascii nie ma co sie bardziej meczyc, wiec zostaje
 * wyswietlane znak drugiego objektu, czyli ten ktory jest aktywny (przyczym, co prawda, jest on podswietlany wiec widac czy
 * ma pod soba bombe czy nie) */
void twin::print(){
#ifndef NCURSES	
	glPushMatrix();
#endif
	one->print();
#ifndef NCURSES	
	glPopMatrix();
#endif
	two->print();
}

/* poniwaz zarowno gdy objekt spotka ognia jak i gdy ogien spotka obiektu zostaje wywolane objekt->die() nalezalo jakos
 * rozroznic miedzy tymi dwoma sytuacjami poniewaz obie musialy miec inne skutki. w pierwszy przypadku obiekt 2 sie przesuwal, a
 * wiec objekt 2 powinien zostac usuniety. w drugim przypadku obiekt 1 dostal ogniem a wiec tylko ten obiekt powinnien zostac
 * zniszczony. do tego sluzy zmienna f. jezeli objekt klasy 'twin' dostanie sygnal die() to sprawdza zawartosc zmiennej f. 
 * jezeli bedzie = 0 to nalezy zabic obiekt 1. jezeli f=1 to nalezy zabic objekt 2. gdy objekt 2 wykonuje swoj ruch (jezeli sie
 * uda oczewiscie) to przesuwa nie siebie, lecz objekt klasy 'twin' w ktorej sie znajduje. dlatego nalezy po wykonaniu ruchu 
 * wziasc na to poprawke i postawic objekt 2 w wlasciwym miejscu */
int twin::move(){
	int a=0;
//	if(one->move() >= 0){
//		delete this;
//		return 1;
//	}
	f++;
//	board->board[y][x] = two;
	if((a=two->move()) > 1){
		switch(a){
			case up: board->board[y-1][x] = two; break;
			case right: board->board[y][x+1] = two; break;
			case down: board->board[y+1][x] = two; break;
			case left: board->board[y][x-1] = two; break;
			case kill: return 0;
		}
		two->getid();	// drugi objekt musi byc potem wpisany spowrotem do listy aktywnych objektow
		two=NULL;
		delete this;	// jako, ze juz nie ma potrzeby na tego objektu nalezy go usunac
		return 0;
	}
//	board->board[y][x] = one;
	f=0;
	return 1;
}

void twin::die(){delete this;}

twin::~twin(){	// usuwa odpowiedni objekt a pozostala kladzie spowrotem na plansze
	if(f){
		//delete two;
		if(two)
			delete two;
		board->board[y][x]=one;
	}
	else{
		board->board[y][x]=two;
		two->getid();
		delete one;
	}
	one=two=NULL;
	board->dellist(id);
}



