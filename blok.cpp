#include "blok.h"

/* inicjalizuje klase bazowa znakiem sciany oraz odpowiedni kolor i ustala pozycje bonusu na planszy. nastepnie do c
 * wpisuje znak samego bonusu ktoru sie pojawia dopiero gdy sciana zostanie rozwalona, dead przechowuje czy sciana jest juz
 * rozwalona, a f to wskaznik na funkcje skladowa gracza ktora zostanie wywolana gdy gracz napotka bonusa */
bonus::bonus(int x, int y, Texture* T, void (player::*fu)()): object(blok::getTex()), p(x,y), dead(0), f(fu), t(T), debris(NULL){
}

void bonus::print(){
	if(dead && object::counter){
		object::counter--;
		debris->print();
	}
	object::print();
}


/* wywolana przy spotkaniu z ogniem. jezeli bonus jest jescze sciana, to sciana sie rozwala i zostaje bounus. jezeli jest
 * tylko bonus to bonus sie rozwala */
void bonus::die(){
	if(dead)
		p.move(kill);
	else{
		if(!debris){
			debris = new cloud(object::symbol[0]->texID,0.5);
			if(!debris){
				std::cerr << "Error! bad memory allocation.\n";
				exit(1);
			}
		}
		dead++;
		Texture** tex = new Texture*[2];
			if(!tex){
				std::cerr << "Error! bad memory allocation.\n";
				exit(1);
			}
		tex[0]=t;
		tex[1]=t;
		object::changeSymbol(tex);
		tex[0]= NULL;
		tex[1]= NULL;
		delete[] tex;
		tex = NULL;
	}
}

bonus::~bonus(){
	delete debris;
	debris = NULL;
	delete t;
	t = NULL;
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
door::door(int x, int y,Texture* C) : object(blok::getTex()), p(x,y), dead(0){
	c = new Texture*[2];
			if(!c){
				std::cerr << "Error! bad memory allocation.\n";
				exit(1);
			}
	c[0] = new Texture;
			if(!c[0]){
				std::cerr << "Error! bad memory allocation.\n";
				exit(1);
			}
	*c[0] = C[0];
	c[1] = new Texture;
			if(!c[1]){
				std::cerr << "Error! bad memory allocation.\n";
				exit(1);
			}
	*c[1] = C[1];
	p.getid(this);	
}

/* jezeli drzwi sa ukryte i ktos je wysadzi to sie odkrywaja, w przeciwnym razie nic sie nie dzieje */
void door::die(){
	if(!dead){
		dead++;
		object::changeSymbol(c);
	}
}


door::~door(){
	delete c[0];
	c[0] = NULL;
	delete c[1];
	c[1] = NULL;
	delete[] c;
	c = NULL;
}




/* jezeli ktos napotka na drzwi to dzialaja tak samo jak zwykla sciana, chyba ze nie ma stworow to konczy plansze */
action door::request(object* o){
	if(dead && !(p.checkbaddys()) && typeid(*o) == typeid(player)){
		p.victory();
		return none;
	}
	return fly;
}

/* jezeli nie ma juz stworow i drzwi sa dalej ukryte, to sciana z ktorym sa zmienia kolor by bylo wiadomo gdzie jest */
int door::move(){
	static bool on = false;
	if(!(dead || p.checkbaddys())){
	if(!object::counter--){
		if(on){
			object::changeSymbol(blok::getTex(),0);
			on = false;
		}else{
			object::changeSymbol(c);
			on = true;
		}
		object::counter = 35;
	}
	}
	return 0;
}

void door::setid(int i){ p.setid(i);} 

doorpos::doorpos(int x, int y): pos(x,y){}

/* zwraca ile stworow zostalo na planszy */
int doorpos::checkbaddys(){ return board->checkBaddys();}

/* funkcja przeznaczona do wszelakich efektow specjalnych przy wygranej zanim sie skonczy gra */
void doorpos::victory(){
	// tutaj nalezy wstawic efekty
	board->end(x,y);
}

void blok::print(){
	if(debris){
		if(!object::counter--)
			p.move(kill);
		else
			debris->print();
	}else
		object::print();
}

Texture blok::symbol[2];

blok::blok(int x, int y) : object(blok::getTex(),12), p(x,y){
	debris = NULL;
}

Texture* blok::getTex(){ return symbol;}

Texture* blok::setTex(Texture* t){ 
	symbol[0] = t[0];
       	symbol[1] = t[1];
}

action blok::request(object* o){return fly;}

void blok::die(){
	if(!debris){
		debris = new cloud(symbol[0].texID,0.5);
			if(!debris){
				std::cerr << "Error! bad memory allocation.\n";
				exit(1);
			}
	}	//	p.move(kill);
}

blok::~blok(){
	delete debris;
	debris = NULL;
}
