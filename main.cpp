#include "player.h"
#include "baddy.h"
#include "blok.h"
#include "twin.h"
#include "initialiser.h"
#include "keys.h"
#include "menu.h"

#include <GL/glut.h>
#include <math.h>

static int n = 16;
static int m = 16;
static Board b(n,m);
static initialiser t(b);
static Menu me(t);


void renderScene(void) {
//	glMatrixMode(GL_MODELVIEW);
//	a->print();
}


void setlight(){
//	GLfloat spot_direction[] = { 0.0, 0.0, 1.0};
//	GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 0.4 };
//	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	GLfloat light_position[] = {0.0,0.0,365,0};
	GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 0.1};
	GLfloat light_specular[] = { 0.2, 0.2, 0.2, 0.0 };
	GLfloat light_diffuse[] = { 0.2,0.2, 0.2, 1.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
//	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
//	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);


	GLfloat light1_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat light1_diffuse[] = { 0.1, 0.1, 0.1, 0.0 };
	GLfloat light1_specular[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat light1_position[] = { 0, 0, 290, 1.0 };
	GLfloat spot_direction[] = { 0, 0, -1};

	
	glPushMatrix();
	glLoadIdentity();
//	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
//	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
//	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.5);
//	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
//	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);

//	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 15.0);
//	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 6.0);

	glEnable(GL_LIGHT1);
	glPopMatrix();
	glEnable(GL_LIGHT0);

	std::cout << "Initalised lights\n";

	GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = {50.0};
//	GLfloat high_shininess[] = { 100.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
//	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

//	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

}

void mouse(int button,int state,int x, int y){
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		std::cout << x << "; "<< y << " proportionaly:" << x/(float)glutGet(GLUT_WINDOW_WIDTH) << "; " << y/(float)glutGet(GLUT_WINDOW_HEIGHT) << "\n";
		me.setMenu(true,(y/(float)glutGet(GLUT_WINDOW_HEIGHT))*10);
	}else{
		me.setMenu(false,(y/(float)glutGet(GLUT_WINDOW_HEIGHT))*10);
	}

}
void changeSize(int w, int h){
	/* Prevent a divide by zero, when window is too short
	 (you cant make a window of zero width). */
	if(h == 0)
		h = 1;

	float ratio = 1.0* w / h;
	//float angle = atan( (m>n ? m: n)/

	/* Reset the coordinate system before modifying*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	/* Set the viewport to be the entire window*/
	glViewport(0, 0, w, h);

	/* Set the correct perspective.*/
	gluPerspective(45,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	double g = 16;
	gluLookAt(0.0,-0.0, 100,//( m>n ? m : n)+6, 		// punkt z ktorego sie patrzy
		  0.0,0.0,0.0,		// punkt (dowolny) lezacy na linie wzroku
		  0.0f,1.0f,0.0f);	// wektor ktory wskazuje gore
	setlight();

}

void init(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(820,820);
	glutCreateWindow("Bomberman");
	glutDisplayFunc(renderScene);
	glutIdleFunc(NULL);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(keys::keypress);
	glutSpecialFunc(keys::specialKeypress);
	glutKeyboardUpFunc(keys::keyrelease);
	glutIgnoreKeyRepeat(1);
	glutSpecialUpFunc(keys::specialKeyRelease);
	std::cout << "Initalised the window\n";

//	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_DST_ALPHA);
	glShadeModel(GL_SMOOTH);
	//glCullFace(GL_FRONT);
	//glFrontFace(GL_CCW);
	glClearColor(0.0, 0.0, 0.0, 0.0); 
	glClear(GL_COLOR_BUFFER_BIT);

//	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

//	GLfloat mat_amb_diff[] = { 0, 0, 0, 1.0 };
//	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, 
//			            mat_amb_diff);

	std::cout << "Initalised colours\n";

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
	glutFullScreen();

}

void mainLoop(int i){
	static bool paused = false;
	static bool pressed = false;
	switch(i){
		case 0: t.nuke();
			exit(EXIT_SUCCESS);
		case 1:	b.print();	// wyswietla obecny stan gry
			switch(b.round()){
			case 1 : t.nuke();
				 exit(EXIT_SUCCESS);
			case 2 : t.newgame();	// gra typu wspolpraca, wiec nowa plansza
				 break;
			case 3 : if(b.end(0,0)){
					 if(t.getRoundsleft())
						 t.newgame();	// gra typu wybij wszystkich
					 else{
						t.nuke();
				       		i = 3;
						me.viewMenu();
					}
			 	}		 
				 break;
			}
			break;
		case 2:	paused = false;
			t.newgame();		
			i = 1;
			break;
		case 3: i = me.menu();
			break;
		case 4: i = me.options();
			break;
		case 5: i = me.multiplayer();
			break;
		case 6: i = me.changekeys();
			break;
	}
	if(!pressed && keys::keyPressed(27)){	// nacisnieto ESC
		pressed = true;
		if(paused){
			paused = false;	
			i = 1;
			t.viewBoard();
		} else {
			paused = true;	
			i = 3;
			me.viewMenu();
		}
	}else if(pressed && !keys::keyPressed(27)){
		pressed = false;
	}

	glutTimerFunc(1000/60, mainLoop, i);
}

int main(int argc,char** argv){

//	initncurses();
	init(argc, argv);
	glutMouseFunc(mouse);
	keys k;

int r=0,i=0;
//	t.fill(5,garden);
//	t.addPlayer();		// dodaje 3 graczy
//	t.addPlayer();		// dodaje 3 graczy
//	t.addPlayer();		// dodaje 3 graczy
//	t.addbonus();
//	t.addBaddys(0,5);		// dodaje 2 stworki typu 0 (czyli jedyny typ jaki jest)
//	gluLookAt(0.0,-0.0,50 ,//m>n ? m : n)+6, 		// punkt z ktorego sie patrzy
//		  0.0,0.0,0.0,		// punkt (dowolny) lezacy na linie wzroku
//		  -1.0f,0.0f,0.0f);	// wektor ktory wskazuje gore

//	bomba* u = new bomba(4,4,3);
//	b.remove(4,4);
//	b.place(u,4,4);
//	u->getid();


//	bomba* w = new bomba(2,2,5);
//	b.place(w,2,2);
//	w->getid();

//	player* p = new player(0,0);
//	b.place(p,0,0);

//	baddy* z = new baddy(6,6,'B');
//	b.place(z,6,6);

//**/	keyboard_init(); /**/// inicjalizuje klawiature
	//a=&b;
	std::cout << "Initalised the board\n";
	glutTimerFunc(1000/60, mainLoop, 3);
	glutMainLoop();
	
	
	b.print();		// wyswietla wstepna konfiguracja gry
	
	while(!r){		// petla gry - dopoki wynik z rundy = 0 to znaczy, ze gra sie dalej toczy
//**/		mvprintw(25,25,"%d",i);	// licznik czasoprzestrzenny. nic nie robi ale ciekawie wyglada :^)
		i++;			
//**/		refresh(); /**/// wypisuje wszystko co ma byc wypisane na ekran
		r=b.round();	// jedna tura gry
		b.print();	// wyswietla obecny stan gry
//**/		usleep(7500); /**/// czeka 7,5ms
//**/		if(keyboard_keypressed(SCANCODE_ESCAPE)){/**/
//			Board* ba=0;
//			if(ba=t.menu())
//				b=*ba;
//		}
	}
//	if(r==1)
//		printw("\n\nprzegrales");
//	if(r==2)
//		printw("\n\ngratulacje za wygrana");
//**/	refresh();	/**/
	
//**/	keyboard_close();/**/

//**/	endwin();	/**/

}
