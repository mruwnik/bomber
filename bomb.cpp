#include "bomb.h"
/*
#ifdef NCURSES
fire::fire(int x, int y, int t): object('*',COLOR_PAIR(3),t), p(x,y){ // t to czas zycia ognia
#else
Texture fire::symbol[2] = {0,0};

Texture* fire::getTex(){ return symbol;}

Texture* fire::setTex(Texture* t){ symbol[0] = t[0]; symbol[1] = t[1];}

fire::fire(int x, int y, int t): object(fire::getTex(),t), p(x,y){ // t to czas zycia ognia
#endif
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

//void fire::print(){
//	glColor3f(193/256,90/256,42/256);
//	glTranslatef(0,0,0.5);
//	glutSolidSphere(0.5,40,40);
//}

fire::~fire(){}
*/
// pos dla bomby
bombpos::bombpos(int x, int y,int r): pos(x,y), range(r){}

int bombpos::move(action a){
	if(a!=kill)// jezeli bomba nie ma wybuchnac to nie ma co robic wiec konczy ruch
		return 0;
int x=pos::x;// w przeciwnym przypadku tworzy oginie wokol siebie
int y=pos::y;
int id=pos::id;
	if(range){
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
		if(!f){
			std::cerr << "Error! bad memory allocation\n";
			exit(1);
		}
		board->remove(x,y); // potrzebny jezeli bomba jest pod graczem; w przeciwnym przypadku nic nie robi 
		board->place(f,x,y); // kladzie ogien na swoim miejscu
	}else{
		board->remove(x,y); // bomba usuwa siebie
	}
	return id;

}

void bombpos::setid(int i){ id=i;}

void bombpos::defuse(){ range = 0;};

bomba::bomba(int x, int y, int R): object(NULL,timer),p(x,y,R), s(0.5,40,1,0.02){ // ta 9 to czasi do wybuchu, r to zasieg
	r = 0.25;
}

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

void bomba::defuse(){ p.defuse(); }

void bomba::die(){ // jezeli ogien na bombe trafi to ja wysadza
	object::counter=0;
}

void bomba::print(){
	glColor4f(0.1,0.1,0.1,1.0);
	glTranslatef(0,0,r);
	glutSolidSphere(r,40,40);
//	mat_amb_diff[0] = 1.0;
//	mat_amb_diff[1] = 1.0;
//	mat_amb_diff[2] = 1.0;
//	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, 
//			            mat_amb_diff);
	glColor4f(0.5,0.5,0.5,1.0);
	glRotatef(45,-r/6,-r/6,0);
	glTranslatef(0,0,r);
	GLUquadric* quad = gluNewQuadric();
	gluCylinder(quad, r/4,r/4,r/8,10,10);
	quad = gluNewQuadric();
	glTranslatef(0,0,r/7);
	gluDisk(quad, 0, r/4, 10,10);

//	Ponizszy kawalek kodu rysuje lont. fajnie by bylo gdyby szlo domontowac
//	iskiernice na koniec co by sie przesuwala w dol wraz z lontem
//
//	glColor3f(1.0,1.0,0);
//	glLineWidth(r/16);
	//glBegin(GL_LINE_LOOP);
	//	double x,y=0;
	//	for(int i = 0; i< object::counter; i++){
	//		x-=r/128;
	//		y=-x;
	//		glVertex3f(x,0,y);
	//	}
	//glEnd();
	//glTranslatef(x,y,0);
	
	s.print();	// tworzy iskiernice
	glColor4f(0.5,0.316,0.164,1);
}


bomba::~bomba(){}
