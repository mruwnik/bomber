#include "baddy.h"

/* inicjalizuje stwora znakiem c (domyslnie 'B'), ustala jego kolor, szybkosc, oraz pozycje poczatkowa*/
#ifdef NCURSES
baddy::baddy(int x, int y, char c, int s) : object(c,COLOR_PAIR(1),s), p(x,y), speed(s){
#else
baddy::baddy(int X, int Y, int s, Texture* c) : object(1), p(X,Y), speed(s){
#endif
	x=y=0;
	a = none;
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
		switch(rand()%5){
			case 0: a=none; break;
			case 1: a=up; x = 1.0; y = 0; break;
			case 2:	a=right; y = -1.0; x = 0; break;
			case 3:	a=down; x = -1.0; y = 0; break;
			case 4: a=left; y = 1.0; x = 0; break;
			default: a = none; break;
		}
//		std::cout << a << " ";
		a=p.move(a);
//		std::cout << a << "\n";
		if(a == none || a == fly)
			x=y=0;
		object::counter=speed;
	}else{	
		switch(a){
		case up: x-=1.0/(speed+1); break;
		case down: x+=1.0/(speed+1); break;
		case right: y+=1.0/(speed+1); break;
		case left: y-=1.0/(speed+1); break;
		}
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

void baddy::print(){
//	GLfloat mat_amb_diff[] = { 1.0, 0, 1.0, 1.0 };
//	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, 
//			            mat_amb_diff);

	glDisable(GL_COLOR_MATERIAL);
	GLfloat mat[] = {0.29225,0.29225,0.29225,1.0};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat);
	mat[0] = 0.50754;
	mat[1] = 0.50754;
	mat[2] = 0.50754;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat);
	mat[0] = 0.508273;
	mat[1] = 0.508273;
	mat[2] = 0.508273;
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 51.2);  
	
	//glColor3f(0.7,0.7,0.7);
	glTranslatef(x,y,0.5);
	float angle = (-y + x) * 180;
	if(a == right || a == left)
		glRotatef(angle,1,0,0);
	else
		glRotatef(angle,0,1,0);
	glutSolidSphere(0.3,10,10);
	glColor3f(0.6,0.6,0.6);

/*	glPushMatrix();
	glRotatef(90,1,0,0);
	glTranslatef(0,0,0.3);
	glutSolidCone(0.05,0.2,10,10);
	glPopMatrix();
	glPushMatrix();
	glRotatef(90,0,1,0);
	glTranslatef(0,0,0.3);
	glutSolidCone(0.05,0.2,10,10);
	glPopMatrix();
	glPushMatrix();
	glRotatef(90,0,0,1);
	glTranslatef(0,0,0.3);
	glutSolidCone(0.05,0.2,10,10);
	glPopMatrix();
	glPushMatrix();
	glRotatef(90,-1,0,0);
	glTranslatef(0,0,0.3);
	glutSolidCone(0.05,0.2,10,10);
	glPopMatrix();
	glPushMatrix();
	glRotatef(90,0,-1,0);
	glTranslatef(0,0,0.3);
	glutSolidCone(0.05,0.2,10,10);
	glPopMatrix();
	glPushMatrix();
	glRotatef(90,0,0,-1);
	glTranslatef(0,0,0.3);
	glutSolidCone(0.05,0.2,10,10);
	glPopMatrix();
	
	glPushMatrix();
	glRotatef(90,1,1,0);
	glTranslatef(0,0,0.3);
	glutSolidCone(0.05,0.2,10,10);
	glPopMatrix();*/
//	glPushMatrix();
//	glRotatef(90,0,1,1);
//	glTranslatef(0,0,0.3);
//	glutSolidCone(0.05,0.2,10,10);
//	glPopMatrix();
//	glPushMatrix();
//	glRotatef(90,1,0,1);
//	glTranslatef(0,0,0.3);
//	glutSolidCone(0.05,0.2,10,10);
//	glPopMatrix();
//	glPushMatrix();
//	glRotatef(90,-1,0,1);
//	glTranslatef(0,0,0.3);
//	glutSolidCone(0.05,0.2,10,10);
//	glPopMatrix();
//	glPushMatrix();
//	glRotatef(90,0,-1,1);
//	glTranslatef(0,0,0.3);
//	glutSolidCone(0.05,0.2,10,10);
//	glPopMatrix();
//	glPushMatrix();
//	glRotatef(90,1,0,-1);
//	glTranslatef(0,0,0.3);
//	glutSolidCone(0.05,0.2,10,10);
//	glPopMatrix();

	glPushMatrix();
	glRotatef(60,1,1,1);
	glTranslatef(0,0,0.3);
	glutSolidCone(0.05,0.2,10,10);
	glPopMatrix();
	glPushMatrix();
	glRotatef(60,1,-1,1);
	glTranslatef(0,0,0.3);
	glutSolidCone(0.05,0.2,10,10);
	glPopMatrix();
	glPushMatrix();
	glRotatef(60,-1,1,1);
	glTranslatef(0,0,0.3);
	glutSolidCone(0.05,0.2,10,10);
	glPopMatrix();
	glPushMatrix();
	glRotatef(60,-1,-1,1);
	glTranslatef(0,0,0.3);
	glutSolidCone(0.05,0.2,10,10);
	glPopMatrix();
	glPushMatrix();
	glRotatef(120,1,1,-1);
	glTranslatef(0,0,0.3);
	glutSolidCone(0.05,0.2,10,10);
	glPopMatrix();
	glPushMatrix();
	glRotatef(120,1,-1,-1);
	glTranslatef(0,0,0.3);
	glutSolidCone(0.05,0.2,10,10);
	glPopMatrix();
	glPushMatrix();
	glRotatef(120,-1,1,-1);
	glTranslatef(0,0,0.3);
	glutSolidCone(0.05,0.2,10,10);
	glPopMatrix();
	glPushMatrix();
	glRotatef(120,-1,-1,-1);
	glTranslatef(0,0,0.3);
	glutSolidCone(0.05,0.2,10,10);
	glPopMatrix();


//	mat_amb_diff[1] = 1.0;
//	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, 
//			            mat_amb_diff);
	glEnable(GL_COLOR_MATERIAL);
}

baddy::~baddy(){p.remove();} // informuje planszy, ze jest 1 stworek mniej
