#include "board.h"

action Wall::request(object* o){return none;} // wszelakie proby przejscia przez taka sciane sa odrzucone

#ifdef NCURSES
	Wall::Wall() : object('#'){};
#else
	Wall::Wall() : object(NULL,1){};

	void Wall::changeSymbol(Texture* t){
		object::symbol[0] = new Texture();
			if(!object::symbol[0]){
				std::cerr << "Error! bad memory allocation.\n";
				exit(1);
			}
		*object::symbol[0] = t[0];
		object::symbol[1] = new Texture();
			if(!object::symbol[1]){
				std::cerr << "Error! bad memory allocation.\n";
				exit(1);
			}
		*object::symbol[1] = t[1];
	}
	/* Ustawia teksture scian niezniszczalnych */
	void Board::setWall(Texture* t){
		wall.changeSymbol(t);
	}

	Wall::~Wall(){ 
		delete object::symbol[0];
		object::symbol[0] = NULL;
		delete object::symbol[1];
		object::symbol[1] = NULL;
		//delete[] object::symbol;
	}
#endif

/* konstruktor planszy ktora odrazu ustawia mury ktorych nie mozna rozwalic. takiego muru jest tylko jeden egzemplarz, bo i tak
 * nie moze zostac rozwalony i szkoda czasu i miejsca by stworzyc N*M/4 takich murow, tym bardziej, ze jest to tylko wskaznik */
Board::Board(int N, int M) : list(), wall(), players(0),baddys(0), over(0), gameType(0){
	n = 2*(N/2) +1; 	// powoduje, ze n i m sa zawsze nieparzyste aby plansza byla odpowiedniej wielkosci
	m = 2*(M/2) +1;  
	pos::set(this,n,m);	// ustawia dla wszystkich wystapien klasy pos wskaznik na siebie
	alive[0] = alive [1] = alive[2] = alive[3] = false;
	
	board = new object**[n];// tworzy sama plansze
			if(!board){
				std::cerr << "Error! bad memory allocation.\n";
				exit(1);
			}
	for(int i = 0; i<=n; i+=2){ // tworzy nieparzyste wiersze i je zeruje
		board[i] = new object*[m];
			if(!board[i]){
				std::cerr << "Error! bad memory allocation.\n";
				exit(1);
			}
	//	for(int j=0; j<m;j++)
	//		board[i][j]=NULL;
		memset(board[i],0,sizeof(object*)*m);
	}
	for(int i = 1; i<n; i+=2){// tworzy parzyste wiersze i wstawia na zmiane '\0' i sciane
		board[i] = new object*[m];
			if(!board[i]){
				std::cerr << "Error! bad memory allocation.\n";
				exit(1);
			}
		board[i][0] = 0;
		for(int j=1; j<m;){
			board[i][j++] = &wall;
			board[i][j++] = NULL;
		}
	}
	srand((long)board * (long)this);	// inicjalizuje generator liczb losowych. nie jest to zbyt dobry sposob, ale powinno
					// dac wystarczajace wyniki 
}

void Board::newBoard(int N, int M){
	int nn = 2*(N/2) +1; 	// powoduje, ze n i m sa zawsze nieparzyste aby plansza byla odpowiedniej wielkosci
	int nm = 2*(M/2) +1;  
	over = 0;
	pos::set(this,nn,nm);	// ustawia dla wszystkich wystapien klasy pos wskaznik na siebie
	list.clear();

	clear();
//	if( n != nn || m != nm){
	if(board){
		for(int i = 0; i < n; i++){
			delete[] board[i];
			board[i] = NULL;
		}
		delete[] board;
	}
		n = nn;
		m = nm;
		board = new object**[n];// tworzy sama plansze
			if(!board){
				std::cerr << "Error! bad memory allocation.\n";
				exit(1);
			}
		for(int i = 0; i<=n; i+=2){ // tworzy nieparzyste wiersze i je zeruje
				board[i] = new object*[m];
				if(!board[i]){
					std::cerr << "Error! bad memory allocation.\n";
					exit(1);
				}
				memset(board[i],0,sizeof(object*)*m);
		}
		for(int i = 1; i<n; i+=2){// tworzy parzyste wiersze i wstawia na zmiane '\0' i sciane
			board[i] = new object*[m];
			if(!board[i]){
				std::cerr << "Error! bad memory allocation.\n";
				exit(1);
			}
			board[i][0] = 0;
			for(int j=1; j<m;){
				board[i][j++] = &wall;
				board[i][j++] = NULL;
			}
		}
//	}
	std::cout << "new board: players:" << players << std::endl;
}

//jedzie przez cala liste aktywnych obiektow (gracze, stwory, bomby itp.) i kaze im cos zrobic
int Board::round(){
	int i=0;
	while(object* o = list[i++]){
	//	/**/ keyboard_update(); // jest to funkcja do klawiatury pod linuxem. aby program przeniesc na inna platforme
					// nalezy cos z nia zrobic. funkcja ta sprawdza czy jakis przycisk jest nacisniety
		o->move();
	}
	if(over)
		return (gameType ? 2: 3);
	if(!players)
		return 1;// jezeli nie ma juz graczy to takze nalezy skonczyc
	return 0;
}

/* drukuje wyniki. tutaj nalezy wstawiac wszelakie sprawy zwiazane z wyswietlaniem planszy. funkcja ta jest wywolana co runde*/ 
void Board::print(){
	float n2 = -(n/2.0);
	float m2 = -(m/2.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
//	GLfloat mat_amb_diff[] = { 0,1.0,0, 1.0 };
//	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, 
//			            mat_amb_diff);
//	glColor3f(0,1.0,0);
//	glRectf(-(n2),-(m2),n2,m2);
//	glColor3f(1.0,1.0,1.0);
//	mat_amb_diff[0]= 1.0;
//	mat_amb_diff[2]= 1.0;
//	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, 
//			            mat_amb_diff);

			glEnable(GL_TEXTURE_2D);
			//glEnable(GL_BLEND);		// Enable Blending
	for(int i=0; i<n; i++){
		for(int j =0; j<m; j++){
			glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
//			glBlendFunc(GL_ONE_MINUS_DST_ALPHA,GL_DST_ALPHA);
			glBindTexture(GL_TEXTURE_2D, floor.texID);
			glBegin (GL_QUADS);
			//	glColor4f(0.5,0.316,0.164,0);
				glColor4f(0.1,0.1,0.1,1);
				glNormal3f(0.0,0.0,1.0);
				glTexCoord2f(0.0, 0.0); glVertex3f (n2+i, m2+j, 0);
			      	glTexCoord2f(0.0, 1.0); glVertex3f (n2+i, m2+1+j, 0);
				glTexCoord2f(1.0, 1.0); glVertex3f (n2+1+i, m2+1+j, 0.0); 
				glTexCoord2f(1.0, 0.0); glVertex3f (n2+1+i, m2+j, 0.0);
			glEnd();
		}
	}
		//	glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
	for(int i=0; i<n; i++){
		for(int j =0; j<m; j++){
			if(board[i][j]){
				glPushMatrix();
				glTranslatef(n2+0.5+i,m2+0.5+j,0);
				board[i][j]->print();
				glPopMatrix();
			}
	//		m2+=1;
		}
	//	n2+=1;
	}
	glPopMatrix();
	if(!over)
		glutSwapBuffers();
}

//te 2 funkcje odpowiednio dodawaja i odejmuja stwory do/z listy aktywnych stworow, tzn. te ktore sa sprawdzane w kazdej kolejce
int Board::add2list(object* ob){
	return list.add(ob);  // zwraca pozycje objektu w liscie
}

object* Board::dellist(int i){ // usuwa stwor z listy aktywnych obiektow, ale nie z pamieci
	return list.remove(i); // zwraca wskaznik na usuwany objekt. 
}

action Board::movebeing(int x,int y,action dir){ // jezeli nie przekracza poza tablice, to przesuwa objekt o 1 w dany kierunek
	switch(dir){
		case up: return( y>0 ? ((board[y-1][x] = board[y][x]),board[y][x]=0,mov) : none);
		case right: return( x+1<m ? ((board[y][x+1] = board[y][x]),board[y][x]=0,mov) : none);
		case down: return( y+1<n ? ((board[y+1][x] = board[y][x]),board[y][x]=0,mov) : none);
		case left: return( x>0 ? ((board[y][x-1] = board[y][x]),board[y][x]=0,mov) : none);
	}
	return none;	// zwraca ruch jaka sie udalo wykonac
}

object* Board::check(int x, int y){//do komunikacji miedzy objektami - zwraca wskaznik na obiekt znajdujacy sie pod danymi wspolrzednymi
	if( x>=0 && x<m && y>=0 && y<n)
		return board[y][x];
	return &wall;
}

//sprawdza czy mozna wstawic do tabeli jakiegos stwora i jesli moze to wstawia. jezeli sie nie da, to nie ma sensu
//by owy stwor istnial a wiec go usuwa. 
object* Board::place(object* ob, int x, int y){
	if(x>=0 && x<m && y>=0 && y<n){
		if((board[y][x]) && (board[y][x]->request(ob) != mov)){
			delete ob;
			return 0;
		}
		return (board[y][x] = ob);
	}
	return 0;
}

void Board::playerDown(int nr){ 
	if(nr >= 0 && nr < 4)
		alive[nr] = false;
	if(--players <=1  && !gameType){
		end(-1,-1);
		std::cout << "player " << nr << " down, " << players << " players left (end)\n";
		return;
	}
	if(!(players)){
		over = 1;
		std::cout << "noone left, over = " << over <<"\n";
	}
	std::cout << "player " << nr << " down, " << players << " players left\n";
}	// przy smierci gracza - aby bylo wiadomo kiedy skonczyc gre

void Board::baddyDown(){ baddys--;}	// przy smierci stwora - takze do wyznaczania konca gry

int Board::checkBaddys(){ return baddys;} // zwraca ile stworow zostalo na plansie

int Board::end(int x, int y){	// wywolana przy zakonczeniu gry (wygrana)
	// tutaj mozna dac ewentualne efekty, czy komunikaty czy cokolwiek
	static int timer = 50;
#ifdef USE_FTGL
	static FTExtrudeFont font("textures/subfont.ttf");
	if(font.Error())
		std::cerr << "error loading font\n";
	font.FaceSize(1);
	font.Depth(1);
#endif
	over=1;
	if(!timer--){
		timer = 50;
		return 1;
	}
	if(!gameType){
		print();
		glPushMatrix();
		glTranslatef(-2,-4,4);
		glColor4f(0.0f, 1.0f, 1.0f, 1.0f); // Black text
#ifdef USE_FTGL
		glRotatef(90,0,0,1);
		if(alive[0]){
			font.Render("Wygral gracz pierwszy");
		}
		else if(alive[1])
			font.Render("Wygral gracz drugi");
		else if(alive[2])
			font.Render("Wygral gracz trzeci");
		else if(alive[3])
			font.Render("Wygral gracz czwarty");
#else
		if(alive[0])
			renderBitmapString(-3.7, 1.8, 5, GLUT_BITMAP_9_BY_15,"Wygral gracz pierwszy");
		else if(alive[1])
			renderBitmapString(-3.7, 1.8, 5, GLUT_BITMAP_9_BY_15,"Wygral gracz drugi");
		else if(alive[2])
			renderBitmapString(-3.7, 1.8, 5, GLUT_BITMAP_9_BY_15,"Wygral gracz trzeci");
		else if(alive[3])
			renderBitmapString(-3.7, 1.8, 5, GLUT_BITMAP_9_BY_15,"Wygral gracz czwarty");

#endif
		glPopMatrix();
		glutSwapBuffers();
	}
	return 0;
}

/* usuwa z planszy. przyjmowane jest, ze wspolrzedne sa poprawne wiec zakres nie jest sprawzany (w praktyce ta funkcja jest
 * uzywana by siebie usunac, wiec nie powinny wystapic problemy */ 
void Board::remove(int x, int y){
	object* o = board[y][x];	// to mi sie nie podoba, ale alternatywa by bylo
	board[y][x] = NULL;		// stworzenia nowego objektu typu twin w przypadku
	delete o;			// gdy gracz postawia bombe i zaraz wpada na stworka
}					

void Board::clear(){
	if(board){
		for(int i = 0; i<=n; i+=2){ // usuwa nieparzyste wiersze
			for(int j=0; j<m;j++){
				if(board[i][j])
				 	delete board[i][j];	// list needs to be cleaned out, too
			 		board[i][j] = NULL;	
			}
		}
		for(int i = 1; i<n; i+=2){// usuwa parzyste wiersze - nie moze usuwac te sciany ktorych nie mozna wysadzac bo naprawde
			for(int j=0; j<=m; j+=2){  // jest tylko jeden wiec nalezy je przeskoczyc
				if(board[i][j])
				 	delete board[i][j];
			 		board[i][j] = NULL;	
			}
		}
	}
}
Board::~Board(){
	if(board){
		clear();	
		for(int i = 0; i < n; i++){
			delete[] board[i];
			board[i] = NULL;
		}
		delete[] board;
		board = NULL;
	}
}

/* wszystkie dzialanie na planszy sa wykonywane przez obiekt 'pos'. Pos przechowuje wspolrzedne obiektu oraz wskaznik na plansze
 * Jest swojego rodzaju posrednikiem miedzy danym obiektem i otoczeniem. obiekt mowi pos co ma zrobic i pos to za niego robi-
 * najpierw sprawdza czy w danym kierunku jest miejsce, a jak nie ma to pyta sie tego obiektu co mu zawadza czy moze sie
 * usunac, po czym odpowiednio reaguje*/

/* statyczne zmienne klasy pos ktore przechowuja informacje o samej plansie */
int pos::n=0;		// dlugosc
int pos::m=0;		// szerokosc
Board* pos::board=0;	

pos::pos(int X, int Y): x(X), y(Y), id(-1){}// domyslnie ID obiektu = -1, czyli nie jest aktywny

void pos::set(Board* b,int N, int M){// ustala na jaka plansze wskazuja pozycje
	n=N;
	m=M;
	board = b;
}

void pos::getid(object* o){ //w pozycji obiektu jest takze przechowywany jego nr identifikacjny w liscie aktywnych objektow
	if(o)
		id = board->add2list(o);
}

action pos::check(action a){
	object* ob;
	switch(a){//sprawdza czy w danym kierunku cos jest
		case up: ob = board->check(x,y-1); break;
		case right: ob = board->check(x+1,y); break;
		case down: ob = board->check(x,y+1); break;
		case left: ob = board->check(x-1,y); break;
		case kill: board->remove(x,y); return kill;//moze sie zdarzyc, ze trefi na ogien co go odrazu spali
		default: return none;
	}
	if(ob){// jezeli cos bylo, to sie pyta czy moze sie tam przemiescic
		switch(ob->request(board->check(x,y))){
			case kill: board->remove(x,y); return kill;// if signals used instead of RTTI this needs to be changed
			case none: return none;
			case fly: return fly;
		}
	}// jezeli moze, to sie przesuwa
	return a;
}

action pos::move(action a){// przesuwa obiekt po planszy, zwraca co mu sie udalo zrobic
	object* ob;
	switch(a){//sprawdza czy w danym kierunku cos jest
		case up: ob = board->check(x,y-1); break;
		case right: ob = board->check(x+1,y); break;
		case down: ob = board->check(x,y+1); break;
		case left: ob = board->check(x-1,y); break;
		case none: return none;
		case kill: board->remove(x,y); return kill;//moze sie zdarzyc, ze trefi na ogien co go odrazu spali
		default: return none;
	}
	if(ob){// jezeli cos bylo, to sie pyta czy moze sie tam przemiescic
		switch(ob->request(board->check(x,y))){
			case kill: board->remove(x,y); return kill;// if signals used instead of RTTI this needs to be changed
			case none: return none;
			case fly: return fly;
		}
	}// jezeli moze, to sie przesuwa
	if(board->movebeing(x,y,a) == mov){
		switch(a){	
			case up: y--; return up;
			case right: x++; return right;
			case down: y++; return down;
			case left: x--; return left;
		}
	}
	return none;
}

/* ustawia identifikator objektu, przy czym jezeli zostanie przekazy -1, to oznacza, ze obiekt ma byc wypisany z listy aktywnych
 * obiektow, a wiec nalezy go najpierw z tej listy usunac */
void pos::setid(int i){
	if(i < 0 && id >=0 )
		board->dellist(id);
	id=i;
}

void pos::remove(){ board->baddyDown(); } // to mozna by dac do osobne klasy pos dla stworow, ale za duzo by tego bylo :D
// jezeli id obiektu >= 0 to jest on na liscie aktywnych obiektow, z ktorej musi byc najpierw usuniety
pos::~pos(){
	if(id >= 0)
		board->dellist(id);
}
