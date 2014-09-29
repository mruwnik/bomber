#include "bomb.h"

fire::fire(int x, int y, int t): object('*',COLOR_PAIR(3),t), p(x,y){ // t to czas zycia ognia
	p.getid(this);
}

int fire::move(){ // poki licznik jest > od 0 to ogien dalej jest na planszie. jak bedzie = 0 to znika
	if(!(object::counter--))
		p.move(kill);
	return -1;
}

action fire::request(object* o){// jezeli ktos napotka ognia to odrazu umiera
	o->die();
	return none;
}

void fire::setid(int i){ // ustawia ID ognia. uzywane przy sortowaniu listy aktywnych objektow
	p.setid(i);
}

fire::~fire(){}

// pos dla bomby
bombpos::bombpos(int x, int y,int r): pos(x,y), range(r){}

int bombpos::move(action a){
	if(a!=kill)// jezeli bomba nie ma wybuchnac to nie ma co robic wiec konczy ruch
		return 0;
int x=pos::x;// w przeciwnym przypadku tworzy oginie wokol siebie
int y=pos::y;
int id=pos::id;

	for(int i = 1; i <= range && y-i>=0; i++){//tworzy ogniki w gore az do skonczenia zasiegu badz spotkania czegos (czego usuwa)
		if(board->check(x,y-i)){
			(board->check(x,y-i))->die();
			break;
		}
		if(!(board->place(new fire(x,y-i),x,y-i)))
			break;
	}
	for(int i = 1; i <= range && x+i<m; i++){ //w prawo
		if(board->check(x+i,y)){
			(board->check(x+i,y))->die();
			break;
		}
		if(!(board->place(new fire(x+i,y),x+i,y)))
			break;
	}
	for(int i = 1; i <= range && y+i<n; i++){ //w dol
		if(board->check(x,y+i)){
			(board->check(x,y+i))->die();
			break;
		}
		if(!(board->place(new fire(x,y+i),x,y+i)))
			break;
	}
	for(int i = 1; i <= range && x-i>=0; i++){ //w lewo
		if(board->check(x-i,y)){
			(board->check(x-i,y))->die();
			break;
		}
		if(!(board->place(new fire(x-i,y),x-i,y)))
			break;
	}
	board->remove(x,y); // bomba usuwa siebie
	fire* f = new fire(x,y); 
	board->remove(x,y); // potrzebny jezeli bomba jest pod graczem; w przeciwnym przypadku nic nie robi 
	board->place(f,x,y); // kladzie ogien na swoim miejscu
	return id;
}

void bombpos::setid(int i){ id=i;}

bomba::bomba(int x, int y, int r): object('o',COLOR_PAIR(5),190),p(x,y,r){} // ta 9 to czasi do wybuchu, r to zasieg

int bomba::move(){// bomba odlicza do zera potem wybucha
	if(!(object::counter--))
		return p.move(kill);
	return -1;
}

action bomba::request(object* o){return none;} // nie odpowiada na proby by sie przesunac

void bomba::setid(int i){
	p.setid(i);
}

void bomba::getid(){
	p.getid(this);
}

void bomba::die(){ // jezeli ogien na bombe trafi to ja wysadza
	object::counter=0;
}

bomba::~bomba(){}
