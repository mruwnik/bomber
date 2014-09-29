#include <ncurses.h>
#include <vgakeyboard.h>
#include "player.h"
#include "baddy.h"
#include "blok.h"
#include "twin.h"
#include "initialiser.h"

/* ustawia odpowiednie kolory. jak nazwa wskazuje, jest to tylko dla ncurses.h, wiec przy zmianie sposobu wyswietlania mozna 
 * spokojnie ( a nawet nalezy) ta funkcje usunac */
void initncurses(){
/**/	initscr();
/**/	start_color();
/**/	init_color(COLOR_RED,910,400,530);
/**/	init_color(COLOR_BLUE,0,490,921);
/**/	init_color(COLOR_YELLOW,999,650,0);
/**/	init_color(COLOR_CYAN,810,360,0);
/**/	init_color(COLOR_GREEN,60,320,70);
/**/	init_pair(1,COLOR_RED,COLOR_GREEN); 	// kolor stworka
/**/	init_pair(2,COLOR_BLUE,COLOR_GREEN); 	// kolor gracza
/**/	init_pair(3,COLOR_YELLOW,COLOR_GREEN); 	// kolor ognia
/**/	init_pair(4,COLOR_CYAN,COLOR_GREEN); 	// kolor sciany (zniszczalne) 
/**/	init_pair(5,COLOR_BLACK,COLOR_GREEN);	// kolor tla
/**/	init_pair(6,COLOR_WHITE,COLOR_GREEN);	// domyslny kolor
/**/	attron(COLOR_PAIR(6));
}


int main(int argc,char** argv){

	initncurses();

	int r=0,i=0;
	Board b(23,24);		// tworzy nowa plansze 13x18 (praktycznie bedzie 13x19 bo musza byc nieparzyste liczby)
	initialiser t(b);	// inicjalizuje plansze z wypelnieniem 1/5
	t.fill(6);
	t.baddys(0,5);		// dodaje 2 stworki typu 0 (czyli jedyny typ jaki jest)
	t.play();		// dodaje 3 graczy
	t.play();		// dodaje 3 graczy
	t.play();		// dodaje 3 graczy
	t.addbonus();
	t.addbonus();
	t.addbonus();
	t.addbonus();

//	bomba* u = new bomba(4,4,3);
//	b.place(u,4,4);
//	u->getid();

//	bomba* w = new bomba(2,2,5);
//	b.place(w,2,2);
//	w->getid();

//	player* p = new player(0,0);
//	b.place(p,0,0);

//	baddy* z = new baddy(6,6,'B');
//	b.place(z,6,6);

/**/	keyboard_init(); /**/// inicjalizuje klawiature

	b.print();		// wyswietla wstepna konfiguracja gry
	
	while(!r){		// petla gry - dopoki wynik z rundy = 0 to znaczy, ze gra sie dalej toczy
		mvprintw(25,25,"%d",i);	// licznik czasoprzestrzenny. nic nie robi ale ciekawie wyglada :^)
		i++;			
/**/		refresh(); /**/// wypisuje wszystko co ma byc wypisane na ekran
		r=b.round();	// jedna tura gry
		b.print();	// wyswietla obecny stan gry
/**/		usleep(7500); /**/// czeka 7,5ms
/**/		if(keyboard_keypressed(SCANCODE_ESCAPE)){/**/
			Board* ba=0;
			if(ba=t.menu())
				b=*ba;
		}
	}
	if(r==1)
		printw("\n\nprzegrales");
	if(r==2)
		printw("\n\ngratulacje za wygrana");
/**/	refresh();	/**/
	
/**/	keyboard_close();/**/

/**/	endwin();	/**/

}
