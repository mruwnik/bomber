#include "player.h"

/* playerpos to pozycja gracza + metoda ktora postawia bombe */
playerpos::playerpos(int x, int y,int n): pos(x,y), nr(n){}

void playerpos::printpos(){ std::cout << "players position:[" << pos::x << "," << pos::y << "]\n";}

void playerpos::getpos(int* t){
	t[0] = x;
	t[1] = y;
}		

void playerpos::setpos(int x2, int y2){
	pos::x = x2;
	pos::y = y2;
}

playerpos::~playerpos(){}

void playerpos::remove(){ board->playerDown(nr);}

bomba* playerpos::spawnbomb(object* o, int range){//postawia bombe w danym kierunku
	if(o == board->check(x,y)){
		bomba* b = new bomba(x,y,range);
		if(!b){
			std::cerr << "Error! bad memory allocation\n";
			exit(1);
		}
		twin* tw = new twin(b,o,x,y); // klasa twin pozwala postawic 2 objekty na jednym polu planszy
		if(!tw){
			std::cerr << "Error! bad memory allocation\n";
			exit(1);
		}
		return b;
	}
	return 0;
}

player::player(int x, int y, keys k, int n, int t): object(NULL,t), face(none), p(x,y,n), k(k), list(), range(4), bombs(3), speed(t), x(0.1), y(0.1), playerNo(n), w(n,fire::getTex(),30){
	r=0.5;
	p.getid(this);
}

void player::die(){//funkcja ktora odrazu zabija gracza (ogien ja uzywa by sie nie przejmowac sprawdzaniem warunkow)
	p.move(kill);
}

void player::print(){
//	glEnable(GL_BLEND);
//	glDisable(GL_COLOR_MATERIAL);
//	GLfloat mat[] = {0.29225,0.29225,0.29225,0.6};
//	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat);
//	mat[0] = 0.50754;
//	mat[1] = 0.50754;
//	mat[2] = 0.50754;
//	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat);
//	mat[0] = 0.508273;
//	mat[1] = 0.508273;
//	mat[2] = 0.508273;
//	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat);
//	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 51.2);  

//	glBlendFunc(GL_SRC_ALPHA,GL_DST_ALPHA);

	switch(playerNo){
		case 0 : glColor4f(0.0,0.0,1.0,0.7); break;
		case 1 : glColor4f(0.0,1.0,0.0,0.7); break;
		case 2 : glColor4f(1.0,0.0,0.0,0.7); break;
		case 3 : glColor4f(0.4,0.5,0.2,0.7); break;
	}
	glTranslatef(x,y,r);
	glutSolidSphere(r,40,40);
	w.print();
	glColor3f(1.0,1.0,1.0);
//	glDisable(GL_BLEND);
//	glEnable(GL_COLOR_MATERIAL);
	
//	p.printpos();
	//std::cout << "player printing[" << x << "," << y << "]\n";
}

int player::move(){// obsluguje klawiature by sprawdzic co gracz chce zrobic
	bomba* b=0;
	int i=0;
	action a=none;
	action check=none;

	if(!object::counter--){
		object::counter=speed;
	}
	if(keys::keyPressed(k.bomb) && !(object::counter%4) &&  bombs && (b=p.spawnbomb(this,range))){
		bombs--;
		b->setid(list.add(b)); // dodaje bombe do swojej listy bomb
		return none;
	}
	
	if(keys::keyPressed(k.up)){
		if ( x > (r - 0.5)){ 
			x -= 1.0/speed;
		}else if ( x >= (r - 0.5 - 1.0/speed) ){
			if((check=p.check(up)) == up){
				x -= 1.0/speed;
			}else if (check == kill){
				return kill;
			}
		}else{
			if ( (x-=1.0/speed) <= -0.5 ){ 
				a=p.move(up);
				x = 0.5;
			}
		}
	}
       	if(keys::keyPressed(k.right)){
		if ( y < ( 0.5 - r )){ 
			y += 1.0/speed;
		}else if ( y <= ( 0.5 - r + 1.0/speed) ){
			if((check=p.check(right)) == right){
				y += 1.0/speed;
			}else if (check == kill){
				return kill;
			}
		}else{
			if ( (y+=1.0/speed) >= 0.5 ){ 
				a=p.move(right);
				y = -0.5;
			}
		}
	}

	if(keys::keyPressed(k.down)){
		if ( x < ( 0.5 - r)){ 
			x += 1.0/speed;
		}else if ( x <= ( 0.5 - r + 1.0/speed) ){
			if((check=p.check(down)) == down){
				x += 1.0/speed;
			}else if (check == kill){
				return kill;
			}
		}else{
			if ( (x+=1.0/speed) >= 0.5 ){ 
				a=p.move(down);
				x = -0.5;
			}
		}
	}
	if(keys::keyPressed(k.left)){
		if ( y > (r - 0.5)){ 
			y -= 1.0/speed;
		}else if ( y >= (r - 0.5 - 1.0/speed) ){
			if((check=p.check(left)) == left){
				y -= 1.0/speed;
			}else if (check == kill){
				return kill;
			}
		}else{
			if ( (y-=1.0/speed) <= -0.5 ){ 
				a=p.move(left);
				y = 0.5;
			}
		}
	}

	if(a==kill)
		return kill;


//przelatuje cala liste bomb i sprawdza czy powinne juz wybuchnac, jezeli tak to ja wysadza
	while(b =list[i++]){
		if(!b->count()){ 
			b->setid(-1);
			list.remove(i-1);
			bombs++;
		}
		b->move();
	}

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

void player::setkeys(const keys& kn){
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

void player::getpos(int* t){ return p.getpos(t);}

void player::setpos(int x2, int y2){ p.setpos(x2,y2);}

void player::clearBombs(){
	int i=0;
	while(bomba* o =list[i++]){ //jezeli jeszcze ma jakies bomby na planszie to trzebe je dolozyc do listy aktywnych objektow
		o->defuse();
		o->die();
	}
	list.clear();
}

player::~player(){
	int i=0;
	p.setid(-1);
	while(bomba* o = list.remove(0)) //jezeli jeszcze ma jakies bomby na planszie to trzebe je dolozyc do listy aktywnych objektow
		o->getid();
	p.remove();
}

