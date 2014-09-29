#include "blok.h"

/* inicjalizuje klase bazowa znakiem sciany oraz odpowiedni kolor i ustala pozycje bonusu na planszy. nastepnie do c
 * wpisuje znak samego bonusu ktoru sie pojawia dopiero gdy sciana zostanie rozwalona, dead przechowuje czy sciana jest juz
 * rozwalona, a f to wskaznik na funkcje skladowa gracza ktora zostanie wywolana gdy gracz napotka bonusa */
bonus::bonus(int x, int y, char c, void (player::*fu)()): object('X',COLOR_PAIR(4)), p(x,y), c(c), dead(0), f(fu){}

/* wywolana przy spotkaniu z ogniem. jezeli bonus jest jescze sciana, to sciana sie rozwala i zostaje bounus. jezeli jest
 * tylko bonus to bonus sie rozwala */
void bonus::die(){
	if(dead)
		p.move(kill);
	else{
		dead++;
		object::changeSymbol(c);
	}
}

/* jezeli ktos chce zajac miesce bonusa gdy jeszcze jest sciana, to tylko pozwala nad soba przeleciec. w przeciwnym przypadku
 * znika, a jezeli to gracz byl, to wywoluje odpowienia funkcja modifikujaca jego parametry */
action bonus::request(object* o){
	if(dead){
		if(typeid(*o) == typeid(player)){
			player* pl = (player*)o;
			(pl->*f)();
		}
		p.move(kill);
		return mov;
	}
	return fly;
}

/* inicjalizuje drzwi ( jako sciana oczewiscie) */
door::door(int x, int y,char c) : object('X',COLOR_PAIR(4)), p(x,y), c(c){
	p.getid(this);	
}

/* jezeli drzwi sa ukryte i ktos je wysadzi to sie odkrywaja, w przeciwnym razie nic sie nie dzieje */
void door::die(){
	if(!dead){
		dead++;
		c = 'D';
		object::changeSymbol(c);
		object::changeMask(0);
	}
}

/* jezeli ktos napotka na drzwi to dzialaja tak samo jak zwykla sciana, chyba ze nie ma stworow to konczy plansze */
action door::request(object* o){
	if(dead && !(p.checkbaddys()) && typeid(*o) == typeid(player)){
		p.victory();
		return kill;
	}
	return fly;
}

/* jezeli nie ma juz stworow i drzwi sa dalej ukryte, to sciana z ktorym sa zmienia kolor by bylo wiadomo gdzie jest */
int door::move(){
	if(!(dead || p.checkbaddys())){
/**/		object::changeSymbol('X');		// zamiast te 2 funkcja trza wczepac jakas animacje
/**/		object::changeMask(A_REVERSE,Or);
	}
	return 0;
}

void door::setid(int i){ p.setid(i); }

doorpos::doorpos(int x, int y): pos(x,y){}

/* zwraca ile stworow zostalo na planszy */
int doorpos::checkbaddys(){ return board->checkBaddys();}

/* funkcja przeznaczona do wszelakich efektow specjalnych przy wygranej zanim sie skonczy gra */
void doorpos::victory(){
	// tutaj nalezy wstawic efekty
	board->end(x,y);
}

blok::blok(int x, int y,char c) : object(c,COLOR_PAIR(4)), p(x,y){}

action blok::request(object* o){return fly;}

void blok::die(){
	p.move(kill);
}

blok::~blok(){}
