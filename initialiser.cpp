#include "initialiser.h"
//
//needs an algorythm to put bonuses on the board

/* funkcja ktora zmienia ktore przyciski kontroluja gracza. jest on bazowana na vgakeyboard.h wiec przenosne nie jest. przy
 * zmianie obslugi klawiatury funkcja ta musialaby byc calkiem zmieniona */
void changekeys(player* p){
	knefle k; 	// struktura przechowujaca kody klawiszy sterujace graczem
	char* buf;	//lancuch w ktorym sa zapisane stany poszczegolnych przyciskow. jezeli = 1 to wcisniete, jezeli 0 to nie
	int c=0;	// kod klawisza

	/**/ erase(); 	// czysci ekran
	
/*###################### wczytuje klawisz sterowania 'w gore' ################################*/
	
	/**/ keyboard_clearstate(); // czysci bufor klawiszy
	printw("up: ");
	/**/ refresh();		// wypisuje na ekran to co ma byc wypisany 
	while(getchar()<1);
	/**/ keyboard_waitforupdate(); 	// czeka az bedzie zmiany stanu klawiatury
	/**/ buf = keyboard_getstate(); // wczyta do buf lancuch z stanem wszystkich przyciskow
	while (!(buf[++c]) && (((int)c) < 127) );
	k.up = c;	// jezeli (buf[i] != 0) to przycisk o kodzie 'i' jest wcisniety
	/**/ keyboard_clearstate(); /**/
	c=0;

/*###########################################################################################*/

	printw("%d  right: ",k.up);	// w prawo
	refresh();
	while(getchar()<1);
	keyboard_waitforupdate();
	buf = keyboard_getstate();
	while (!(buf[++c]) && (((int)c) < 127) );
	k.right = c;	
	keyboard_clearstate();
	c=0;

	printw("%d   down: ",k.right);	// w dol
	refresh();
	while(getchar()<1);
	keyboard_waitforupdate();
	buf = keyboard_getstate();
	while (!(buf[++c]) && (((int)c) < 127) );
	k.down = c;	
	keyboard_clearstate();
	c=0;

	printw("%d left: ",k.down);	// w lewo
	refresh();
	while(getchar()<1);
	keyboard_waitforupdate();
	buf = keyboard_getstate();
	while (!(buf[++c]) && (((int)c) < 127) );
	k.left = c;	
	keyboard_clearstate();
	c=0;

	printw("%d  set bomb:%d ",k.left,k.bomb);	// postawienia bomby
	refresh();
	while(getchar()<1);
	keyboard_waitforupdate();
	buf = keyboard_getstate();
	while (!(buf[++c]) && (((int)c) < 127) );
	k.bomb = c;	
	keyboard_clearstate();

	p->setkeys(k);	// ustawia nowe wartosci dla gracza 'p'
}

/* konstruktor wypelniajacy plansze scianami ktore mozna rozwalic. zmienna 'fill' okresla z jaka gestoscia. 'fill' moze miec 
 * dowolna wartosc, przyczym wartosci <= 0 oznaczaja, ze nie maja byc sciany, a im wieksza wartosc tym mniej jest scian. 
 * praktycznie rzecz biorac nie ma sensu dawac liczby wieksze od 9 bo to wiekszej roznicy nie zrobi, jako ze sciany sa 
 * postawiane z prawdopodobienstwem 1/fill */
initialiser::initialiser(Board& bo): b(bo){
	p[0] = p[1] = p[2] = p[3] = 0;	// na poczatku nie ma graczy
	twin::set(&bo);			// klasa twin dostaje adres planszy
}

void initialiser::addbonus(){
	/*#####################*/
	/* tutaj powinno byc generator bonusow, ale nie mialem pomyslu jak wyznaczyc ich ilosc wiec kilka bonusow jest 
	 * wpisanych na sztywno aby sprawdzic czy dzialaja */
	delete b.board[0][2];
	delete b.board[0][3];
	delete b.board[0][4];
	delete b.board[0][5];
	b.board[0][2] = (object*) new bonus(2,0,'b',&player::addbomb); 
	b.board[0][3] = (object*) new bonus(3,0,'S',&player::stim); 
	b.board[0][4] = (object*) new bonus(4,0,'R',&player::incrange); 
	b.board[0][5] = (object*) new door(5,0,'D'); 
	/* ################## */
}

void initialiser::fill(int f){	
	/* tutaj jest wypelniana plansza */
	if(f>0){	
		for(int i=0; i<=b.n; i+=2){
			for(int j=0; j<=b.m; j++){
				if(!((int) ((double)f * (rand() / (RAND_MAX + 1.0)))))
					b.board[i][j]= new blok(j,i);
				else b.board[i][j] = 0;
			}
		}
		for(int i=1; i<b.n; i+=2){
			for(int j=0; j<=b.m; j+=2){
				if(!((int) ((double)f * (rand() / (RAND_MAX + 1.0)))))
					b.board[i][j]= new blok(j,i);
				else b.board[i][j] = 0;
			}
		}
	}
}	

void initialiser::operator()(const Board& bo){
	b = bo;
}

/* dzieki tej funkcji mozna dowolny obiekt postawic na plansze, oczkolwiek nie jest to najlepszy sposob, bo jezeli to jest
 * stworek albo gracz to moga byc potem problemy z zakonczeniem ( bedzie wiecej zyjatek na planszy niz powinno) */
object* initialiser::add(object* o, int x, int y){
	return(b.place(o,x,y));
}

/* postawia gracza na plansze. maksymalnie moga byc 4 gracze; jezeli jest juz tyle to funkcja zwraca 0, w przeciwnym przypadku
 * zwraca ile w sumie jest graczy. kazdy gracz ma z gory ustalona pozycje na planszy i domyslny uklad sterowania. uklad 
 * klawiatury mozna potem zmienic. nalezalo by takze okreslic czy gracz jest czlowiekiem czy komputerem, ale jako ze jeszcze
 * nie ma sztucznej inteligencji to mozna tego pominac */
int initialiser::play(int type){
	int n = b.n-1;
	int m = b.m-1;
	if(b.players>=4)
		return 0;
	switch(b.players){	
		case 0: if(b.board[0][0])	// pierwszy gracz - gorny lewy rog
				b.board[0][0]->die();
			 if(b.board[0][1])
				b.board[0][1]->die();
			 if(b.board[1][0])
				b.board[1][0]->die();
			 p[0] = new player(0,0,knefle(SCANCODE_W,SCANCODE_D,SCANCODE_S,SCANCODE_A,SCANCODE_Q));
			 b.board[0][0] = (object*) p[0];
			 break;
		case 1: if(b.board[n][m])	// drugi gracz - dolny prawy rog
				b.board[n][m]->die();
			 if(b.board[n][m-1])
				b.board[n][m-1]->die();
			 if(b.board[n-1][m])
				b.board[n-1][m]->die();
			 p[1] = new player(m,n,knefle(SCANCODE_CURSORBLOCKUP,SCANCODE_CURSORBLOCKRIGHT,SCANCODE_CURSORBLOCKDOWN,SCANCODE_CURSORBLOCKLEFT,SCANCODE_SPACE));
			 b.board[n][m] = (object*) p[1];
			 break;
		case 2: if(b.board[0][m])	// trzeci gracz - gorny prawy rog
				b.board[0][m]->die();
			 if(b.board[0][m-1])
				b.board[0][m-1]->die();
			 if(b.board[1][m])
				b.board[1][m]->die();
			 p[2] = new player(m,0,knefle(SCANCODE_KEYPAD8,SCANCODE_KEYPAD6,SCANCODE_KEYPAD5,SCANCODE_KEYPAD4,SCANCODE_KEYPAD0));
			 b.board[0][m] = (object*) p[2];
			 break;
		case 3: if(b.board[n][0])	// czwarty gracz - dolny lewy rog
				b.board[n][0]->die();
			 if(b.board[n][1])
				b.board[n][1]->die();
			 if(b.board[n-1][0])
				b.board[n-1][0]->die();
			 p[3] = new player(0,n,knefle()); // na razie nie ma ukladu klawiatury dla tego gracza
			 b.board[n][0] = (object*) p[3];
			 break;
		}
	return ++b.players;
}

/* kladzie 'amount' stworkow typu 'type' na plansze w losowe miejsce, przyczym jezeli tam cos bylo to probuje go usunac i 
 * dopiero zostaje tam postawiony stworek jezeli sie uda. jezeli sie nie uda to bedzie 1 stworek mniej. obecnie jest tylko
 * jeden typ stworka, ale rozbudowac gre o wiecej nie jest problemem. chociaz w przypadku usuniecia obiektu z planszy nie jest
 * sprawdzono jakiego typu byl poprzednik, to moga niepowinny wystapic roznicy miedzy liczba stworkow zapisanych a naprawde 
 * istniejacych, bo rzeczy sa usuwane z planszy poprzez wysylanie do nich sygnal die(). moga jednak wystapic bonusy ktore sa
 * odkryte juz na poczatku gry, ale jest to na tyle malo wazne wydarzenie, ze mozna by to potraktowac jako urozmaicenia gry */
int initialiser::baddys(int type, int amount){
	int i,x,y;
	for(i=0; i<amount; i++){
		x = (int) ((double)b.m * (rand() / (RAND_MAX + 1.0)));	// losuje wspolrzedne stworka
		y = (int) ((double)b.n * (rand() / (RAND_MAX + 1.0)));
		if( x%2 && y%2 )	// zapewnia, ze nie zostanie postawiony w miejsce murow niezniszalnych
			x++;
		if(b.board[y][x])	// jezeli cos jest w tym miejscu to probuje tego usunac
			b.board[y][x]->die();
		if(!b.board[y][x]){	// jezeli jest juz puste miejsce to postawia stworka
			switch(type){
				case 0:b.board[y][x]= (object*) new baddy(x,y,'B'); break;
			}
			b.baddys++;	// jako, ze jest o 1 stworek wiecej inkrementuje ich licznik
		}
	}
	return i;
}

Board* initialiser::newgame(){
	int width=10,height=10,wyp=5,stwor=5,bon=5,pla=3;
	Board* bo=0;
	const int zdania = 7;
	/**/ int attr[zdania]={A_REVERSE,A_NORMAL}; /**/
	char* text[]={"szerokosc","wysokosc","wypelnienie","ilosc stworow","ilosc bonusow","ilosc graczy","potwierdz"};
	int old_pair,i=0;
	/**/ attr_t old_attr; /**/

	/**/attr_get(&old_attr,&old_pair,NULL);/**/
	/**/keyboard_clearstate();	/**/
	
	while(!(keyboard_keypressed(SCANCODE_ESCAPE))){
		/**/keyboard_update();	/**/
		
		/**/erase();	/**/
		for(int j =0; j<zdania; j++){
			/**/attrset(attr[j]);	/**/
			printw("%s",text[j]);
			switch (j){
				case 0: printw(": %d\n",width);
				case 1: printw(": %d\n",height);
				case 2: printw(": %d\n",wyp);
				case 3: printw(": %d\n",stwor);
				case 4: printw(": %d\n",bon);
				case 5: printw(": %d\n",pla);
				case 6: printw("\n");
			}
		}
		/**/refresh();	/**/

		/**/if(keyboard_keypressed(SCANCODE_CURSORBLOCKUP) && i>0){/**/
			attr[i--]=A_NORMAL;
			attr[i]=A_REVERSE;
			/**/keyboard_clearstate();	/**/
		/**/}else if(keyboard_keypressed(SCANCODE_CURSORBLOCKDOWN) && i<zdania-1){/**/
			attr[i++]=A_NORMAL;
			attr[i]=A_REVERSE;
			/**/keyboard_clearstate();	/**/
		/**/}else if(keyboard_keypressed(SCANCODE_ENTER)){/**/
			/**/keyboard_clearstate();	/**/
			switch(i){
				case 0 : std::cin >> width; break;
				case 1 : std::cin >> height; break;
				case 2 : std::cin >> wyp; break;
				case 3 : std::cin >> stwor; break;
				case 4 : std::cin >> bon; break;
				case 5 : std::cin >> pla; break;
				case 6 : bo= new Board(width,height); 
					 if(!bo) return 0;
					 b = *bo; 
					 fill(wyp); baddys(0,stwor); 
					 for (int k=0; k<pla; k++)
						 play();
					 return bo;
			}
		/**/}else if(keyboard_keypressed(SCANCODE_ESCAPE)){/**/
			/**/attr_set(old_attr,old_pair,NULL);	/**/
			/**/keyboard_clearstate();	/**/
			delete bo;
			return 0;
		}
	}
	/**/attr_set(old_attr,old_pair,NULL);/**/
	return 0;

}


/* wyswietla menu gry */
Board* initialiser::menu(){
	const int zdania = 6;
	/**/ int attr[zdania]={A_REVERSE,A_NORMAL}; /**/
	char* text[]={"player 1 keys","player 2 keys","player 3 keys","player 4 keys","new game","exit"};
	int old_pair,i=0;
	/**/ attr_t old_attr; /**/

	/**/attr_get(&old_attr,&old_pair,NULL);/**/
	/**/keyboard_clearstate();	/**/
	
	while(!(keyboard_keypressed(SCANCODE_ESCAPE))){
		/**/keyboard_update();	/**/
		
		/**/erase();	/**/
		for(int j =0; j<zdania; j++){
			/**/attrset(attr[j]);	/**/
			printw("%s\n",text[j]);
		}
		/**/refresh();	/**/

		/**/if(keyboard_keypressed(SCANCODE_CURSORBLOCKUP) && i>0){/**/
			attr[i--]=A_NORMAL;
			attr[i]=A_REVERSE;
			/**/keyboard_clearstate();	/**/
		/**/}else if(keyboard_keypressed(SCANCODE_CURSORBLOCKDOWN) && i<zdania-1){/**/
			attr[i++]=A_NORMAL;
			attr[i]=A_REVERSE;
			/**/keyboard_clearstate();	/**/
		/**/}else if(keyboard_keypressed(SCANCODE_ENTER)){/**/
			/**/keyboard_clearstate();	/**/
			switch(i){
				case 0 : changekeys(p[0]); break;
				case 1 : changekeys(p[1]); break;
				case 2 : changekeys(p[2]); break;
				case 3 : changekeys(p[3]); break;
				case 4 : return newgame(); 
				case 5 : keyboard_close(); endwin(); exit(0);	
			}
		/**/}else if(keyboard_keypressed(SCANCODE_ESCAPE)){/**/
			/**/attr_set(old_attr,old_pair,NULL);	/**/
			/**/keyboard_clearstate();	/**/
			return 0;
		}
	}
	/**/attr_set(old_attr,old_pair,NULL);/**/
	return 0;
}
