#include "player.h"

//works, but could do with improvement

knefle::knefle(int a, int b, int c, int d, int e): up(a), right(b), down(c), left(d), bomb(e){}

knefle::knefle(){
	up = right = down = left = bomb = 0;
}

knefle& knefle::operator=(const knefle& kn){
	up = kn.up;
	right = kn.right;
	down = kn.down;
	left = kn.left;
	bomb = kn.bomb;
}

/* playerpos to pozycja gracza + metoda ktora postawia bombe */
playerpos::playerpos(int x, int y): pos(x,y){}

playerpos::~playerpos(){}

void playerpos::remove(){ board->playerDown();}

bomba* playerpos::spawnbomb(object* o, int range){//postawia bombe w danym kierunku
	if(o == board->check(x,y)){
		bomba* b = new bomba(x,y,range);
		new twin(b,o,x,y); // klasa twin pozwala postawic 2 objekty na jednym polu planszy
		return b;
	}
	return 0;
}

player::player(int x, int y, knefle k,int t): object('@',COLOR_PAIR(2),t), face(none), p(x,y), k(k), list(), range(4), bombs(3), speed(t){
	p.getid(this);
	x=y=0;
}

void player::die(){//funkcja ktora odrazu zabija gracza (ogien ja uzywa by sie nie przejmowac sprawdzaniem warunkow)
	p.move(kill);
}

int player::move(){// obsluguje klawiature by sprawdzic co gracz chce zrobic
	bomba* b=0;
	int i=0;
	action a=none;

	if(!object::counter--){
		object::counter=speed;
/*	switch(getchar()){
		case 'w': a=p.move(up); face=down; break;
		case 'd': a=p.move(right); face=left; break;
		case 's': a=p.move(down); face=up; break;
		case 'a': a=p.move(left); face=right; break;
		case 'q': if(bombs && (b=p.spawnbomb(this,range))){
				  bombs--;
				  b->setid(list.add(b));
			  }
			  break;
	}*/
/**/		if(keyboard_keypressed(k.bomb) && bombs && (b=p.spawnbomb(this,range))){
			bombs--;
			b->setid(list.add(b)); // dodaje bombe do swojej listy bomb
/**/			mvprintw(40,90,"d");
			return none;
		 }
	}
		//else{
	/**/	mvprintw(40+x,90+y," ");
/**/			if(keyboard_keypressed(k.up)){
				if ( (--y) <= -speed ){ 
					a=p.move(up);
					y = speed;
				}
			}
/**/			else if(keyboard_keypressed(k.right)){
				if ( (++x) >= speed ){
					a=p.move(right);
					x = -speed;
				}
			}
/**/			else if(keyboard_keypressed(k.down)){
				if ( (++y) >= speed ){ 
					a=p.move(down);
					y = -speed;
				}
/**/			}
			else if(keyboard_keypressed(k.left)){
				if ( (--x) <= -speed ){
					a=p.move(left);
					x = speed;
				}
			}
	/**/	mvprintw(40+x,90+y,"*");

		if(a==kill)
			return kill;

	//}
//przelatuje cala liste bomb i sprawdza czy powinne juz wybuchnac, jezeli tak to ja wysadza
	while(b =list[i++]){
		if(!b->count()){ 
			b->setid(-1);
			list.remove(i-1);
			bombs++;
		}
		b->move();
	}
	if(a)
/**/	mvprintw(40,90,"%d",a);
	return (int)a;
}

/* this could be done using signals instead of RTTI. if it recieved an action it could discern what to do on the 
 * basis of that; eg. baddys send a kill, players send a mov. if that was used then pos.move() would have to kill 
 * players by invoking player.die(), or it could return a kill and let the player do it - but it's probably better 
 * if pos.move() did it */
action player::request(object* o){// obsluguje zapytania o usuniecia sie z drogi
	if(typeid(*o)==typeid(baddy)){
		die();
		return mov;
	}
	return none;
}

void player::setkeys(const knefle& kn){
	k = kn;
}

/*################*/
/* funkje modyfikujace gracz - sa wywolane przez bonusy. moze byc ich dowolna ilosc, byle mialy format 'void func()' */
void player::addbomb(){ bombs++;}

void player::stim(){ if(speed) speed--;}

void player::incrange(){ range++; }

/*################*/

void player::getid(){
	p.getid(this);
}

void player::setid(int i){
	p.setid(i);
}

player::~player(){
	int i=0;
	while(bomba* o =list[i++]) //jezeli jeszcze ma jakies bomby na planszie to trzebe je dolozyc do listy aktywnych objektow
		o->getid();
	p.remove();
}

