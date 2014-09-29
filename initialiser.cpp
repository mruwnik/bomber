#include "initialiser.h"
//
//
//

int loadGLTextures(texType t, Texture* texture){	/* Load Bitmaps And Convert To Textures */

	int Stat = 0;					/* Status Indicator */
	int loop;					/* Loop index */
	int amount = 1;
	char check = 0;

	// Load The Bitmap, Check For Errors. 
	switch(t){
	case warehousePillar : 	check = ((LoadTGA(&texture[0], "textures/metal_walls/side1.tga") &&
					LoadTGA(&texture[1], "textures/metal_walls/top.tga")));
				amount = 2;
				break;
	case crate : 	check = (LoadTGA(&texture[0], "textures/crates/crate1.tga") &&
				       LoadTGA(&texture[1], "textures/crates/crate1.tga"));
				amount = 2;
				break;
	case stoneWall : 	check = ((LoadTGA(&texture[0], "textures/stone_walls/stoneside1.tga") &&
					LoadTGA(&texture[1], "textures/stone_walls/stonetop.tga")));
				amount = 2;
				break;
	case brickWall : 	check = ((LoadTGA(&texture[0], "textures/stone_walls/brickside.tga") &&
					LoadTGA(&texture[1], "textures/stone_walls/bricktop.tga")));
				amount = 2;
				break;
	case metalDoor : 	check = (LoadTGA(&texture[0], "textures/bonuses/door.tga") &&
				       LoadTGA(&texture[1], "textures/bonuses/metal_door_top.tga"));
				amount = 2;
				break;
	case warehouseFloor :	check = LoadTGA(&texture[0], "textures/floor/stonefloor1.tga"); break;
	case grass :	check = LoadTGA(&texture[0], "textures/floor/grass2.tga"); break;
	case extraBombs	 :	check = LoadTGA(&texture[0], "textures/bonuses/extraBombs.tga"); break;
	case stim	 :	check = LoadTGA(&texture[0], "textures/bonuses/stim.tga"); break;
	case extraRange	 :	check = LoadTGA(&texture[0], "textures/bonuses/range.tga"); break;
	case fire1	 :	check = LoadTGA(&texture[0], "textures/fire/fire.tga"); break;
	}	
	if(check){
		for(loop = 0;loop < amount;loop++,Stat++){			/* Loop Through Both Textures */
	/* Typical Texture Generation Using Data From The TGA */
			glGenTextures(1, &texture[loop].texID);	
			/* Create The Texture */
			glBindTexture(GL_TEXTURE_2D, texture[loop].texID);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, texture[loop].width, texture[loop].height, 0, GL_RGB,
			       	GL_UNSIGNED_BYTE, texture[loop].imageData);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
			if (texture[loop].imageData){		/* If Texture Image Exists */					
				free(texture[loop].imageData);				/* Free The Texture Image Memory */
			}
			std::cout << "Texture nr." << loop << " loaded\n";
		}
	}
	return Stat;		/* Return The Status */
}


//
//needs an algorythm to put bonuses on the board

/* konstruktor wypelniajacy plansze scianami ktore mozna rozwalic. zmienna 'fill' okresla z jaka gestoscia. 'fill' moze miec 
 * dowolna wartosc, przyczym wartosci <= 0 oznaczaja, ze nie maja byc sciany, a im wieksza wartosc tym mniej jest scian. 
 * praktycznie rzecz biorac nie ma sensu dawac liczby wieksze od 9 bo to wiekszej roznicy nie zrobi, jako ze sciany sa 
 * postawiane z prawdopodobienstwem 1/fill */
initialiser::initialiser(Board& bo): b(bo), players(3), gameType(deathmatch), theme(warehouse), n(bo.n), m(bo.m), f(4), bonuses(3) {
	p[0] = p[1] = p[2] = p[3] = 0;	// na poczatku nie ma graczy
	for(int i = 0; i < baddyTypes; i++)
		baddys[i] = 0;
	baddys[0] = 5;
	playerKeys[0] = keys('w','d','s','a','q');
	playerKeys[1] = keys(UP,RIGHT,DOWN,LEFT,' ');
	playerKeys[2] = keys('8','6','5','4','0');
	playerKeys[3] = keys(); // na razie nie ma ukladu klawiatury dla tego gracza
	twin::set(&bo);			// klasa twin dostaje adres planszy
	keys::init();
	fire::getTex();
	rounds = 1;
	roundsleft = rounds;

}

void initialiser::addbonus(){
	/*#####################*/
	/* tutaj powinno byc generator bonusow, ale nie mialem pomyslu jak wyznaczyc ich ilosc wiec kilka bonusow jest 
	 * wpisanych na sztywno aby sprawdzic czy dzialaja */
	delete b.board[0][2];
	delete b.board[0][3];
	delete b.board[0][4];
	//delete b.board[0][5];
	Texture* tex = new Texture;
		if(!tex){
			std::cerr << "Error! memory allocation error\n";
			exit(1);
		}
       	loadGLTextures(stim, tex);
	b.board[0][3] = (object*) new bonus(3,0,tex,&player::stim); 
		if(!b.board[0][3]){
			std::cerr << "Error! memory allocation error\n";
			exit(1);
		}
	tex = new Texture;
		if(!tex){
			std::cerr << "Error! memory allocation error\n";
			exit(1);
		}
       	loadGLTextures(extraRange, tex);
	b.board[0][4] = (object*) new bonus(4,0,tex,&player::incrange); 
		if(!b.board[0][4]){
			std::cerr << "Error! memory allocation error\n";
			exit(1);
		}
	tex = new Texture;
		if(!tex){
			std::cerr << "Error! memory allocation error\n";
			exit(1);
		}
       	loadGLTextures(extraBombs, tex);
	b.board[0][2] = (object*) new bonus(2,0,tex,&player::addbomb); 
		if(!b.board[0][2]){
			std::cerr << "Error! memory allocation error\n";
			exit(1);
		}
	Texture texes[2];
	/* ################## */
       	
	// tu tez by trza bylo to jakos porzadnie zrobic, bo tak to jest bajzel
	if(gameType == coOp){	
		int x = (int) ((double)b.m * (rand() / (RAND_MAX + 1.0)));	// losuje wspolrzedne stworka
		int y = (int) ((double)b.n * (rand() / (RAND_MAX + 1.0)));
		if(x < 1 && y<1 )
			x=2;
		if( x == 0  && y == n )
			y=n-3;
		if(x == m && y == 0 )
			x = m-3;
		if( x > m-3  && y > n-3 )
			y=n-3;

		if( x%2 && y%2 )	// zapewnia, ze nie zostanie postawiony w miejsce murow niezniszalnych
			x++;
		if(b.board[y][x])	// jezeli cos jest w tym miejscu to probuje tego usunac
			b.board[y][x]->die();
		if(b.board[y][x]){	// jezeli jest juz puste miejsce to postawia stworka
			delete b.board[y][x];
		}

		loadGLTextures(metalDoor, texes);
		b.board[y][x] = (object*) new door(x,y,texes); 
		if(!b.board[y][x]){
			std::cerr << "Error! memory allocation error\n";
			exit(1);
		}
	}
}

void initialiser::fill(int f, texType t){	
	static texType type = empty;	// zapamietuje wczesniejszy wyglad, co by nie trza bylo 20 razy
						// to samo ladowac

	if(type != t){	
				std::cout << "1set warehouse theme" << std::endl;		
		Texture wall[2]; 
		switch(t){
		case warehouse:	
				std::cout << "2set warehouse theme" << std::endl;		
			loadGLTextures(warehousePillar,wall);	/* Load Bitmaps And Convert To Textures */
				if(!wall){
					std::cerr << "Error: no pillar textures! using old pillar texture \n";
					return;
				}
				b.setWall(wall);		// ustawia teksture dla scian niezniszczalnych
			loadGLTextures(warehouseFloor,wall);	/* Load Bitmaps And Convert To Textures */
				if(!wall){
					std::cerr << "Error: no floor textures! using old pillar texture \n";
					return;
				}
				b.floor = wall[0];		// ustawia teksture dla scian niezniszczalnych

			        loadGLTextures(crate,wall);	/* Load Bitmaps And Convert To Textures */
				if(!wall){
					std::cerr << "Error: no wall textures! using old wall texture\n";
					return;
				}
				blok::setTex(wall);		// ustawia teksture dla scian zniszczalnych
				std::cout << "set warehouse theme" << std::endl;		
				break;
		case garden :	
				std::cout << "set mansion theme" << std::endl;		
			loadGLTextures(stoneWall,wall);	/* Load Bitmaps And Convert To Textures */
				if(!wall){
					std::cerr << "Error: no pillar textures! using old pillar texture \n";
					return;
				}
				b.setWall(wall);		// ustawia teksture dla scian niezniszczalnych
			loadGLTextures(grass,wall);	/* Load Bitmaps And Convert To Textures */
				if(!wall){
					std::cerr << "Error: no pillar textures! using old pillar texture \n";
					return;
				}
				b.floor = wall[0];		// ustawia teksture dla scian niezniszczalnych

			        loadGLTextures(brickWall,wall);	/* Load Bitmaps And Convert To Textures */
				if(!wall){
					std::cerr << "Error: no wall textures! using old wall texture\n";
					return;
				}
				blok::setTex(wall);		// ustawia teksture dla scian zniszczalnych
				std::cout << "set warehouse theme" << std::endl;		
				break;

		default: std::cerr << "Error: no such theme! keeping old theme\n"; return;		
		}
		type = t;
	}


	/* tutaj jest wypelniana plansza */

	if(f>0){	
		for(int i=0; i<=b.n; i+=2){
			for(int j=0; j<=b.m; j++){
				if(!b.board[i][j]){
					if(!((int) ((double)f * (rand() / (RAND_MAX + 1.0))))){
						b.board[i][j]= new blok(j,i);
						if(!b.board[i][j]){
							std::cerr << "Error! memory allocation error\n";
							exit(1);
						}
					}else b.board[i][j] = 0;
				}
			}
		}
		for(int i=1; i<b.n; i+=2){
			for(int j=0; j<=b.m; j+=2){
				if(!b.board[i][j]){
					if(!((int) ((double)f * (rand() / (RAND_MAX + 1.0))))){
						b.board[i][j]= new blok(j,i);
						if(!b.board[i][j]){
							std::cerr << "Error! memory allocation error\n";
							exit(1);
						}
					}else b.board[i][j] = 0;
				}
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
int initialiser::addPlayer(int nr,int type){
	int n = b.n-1;
	int m = b.m-1;
//	if( nr < 0 || nr > 3)
//		nr = b.players;
	if(b.players>=4)
		return 0;

	if( nr >= 0 && nr < 3){
	       if ( p[nr] && !b.alive[nr]){
		p[nr] = NULL;
	       }
	}else {		
		nr = 0;
		if(p[nr] && p[++nr] && p[++nr] && p[++nr]){
			for(nr = 0; nr < 3; nr++){
				if(p[nr] && !b.alive[nr]){
					p[nr] = NULL;
					break;
				}
			}
		}
	}




	switch(nr){	
		case 0: if(b.board[0][0])	// pierwszy gracz - gorny lewy rog
				b.board[0][0]->die();
			 if(b.board[0][1])
				b.board[0][1]->die();
			 if(b.board[1][0])
				b.board[1][0]->die();
			 if(!p[0]){
				 p[0] = new player(0,0,playerKeys[0],0);
				//(p[0])->playerNo = 0;
				b.alive[0] = true;
				b.players++;
			 }else{
				p[0]->setpos(0,0);
				p[0]->getid();
			 }
			 b.board[0][0] = (object*) p[0];
			 std::cout << "first player placed" << std::endl;
			 break;
		case 1: if(b.board[n][m])	// drugi gracz - dolny prawy rog
				b.board[n][m]->die();
			 if(b.board[n][m-1])
				b.board[n][m-1]->die();
			 if(b.board[n-1][m])
				b.board[n-1][m]->die();
			 if(!p[1]){
				p[1] = new player(n,m,playerKeys[1],1);
					if(!p[1]){
						std::cerr << "Error! memory allocation error\n";
						exit(1);
					}
			 	//(p[1])->playerNo = 1;
				b.alive[1] = true;
				b.players++;
			 }else{
				p[1]->setpos(m,n);
				p[1]->getid();
			 }
			 b.board[n][m] = (object*) p[1];
			 std::cout << "second player placed" << std::endl;
			 break;
		case 2: if(b.board[0][m])	// trzeci gracz - gorny prawy rog
				b.board[0][m]->die();
			 if(b.board[0][m-1])
				b.board[0][m-1]->die();
			 if(b.board[1][m])
				b.board[1][m]->die();
			 if(!p[2]){
				p[2] = new player(m,0,playerKeys[2],2);
					if(!p[2]){
						std::cerr << "Error! memory allocation error\n";
						exit(1);
					}
			 	//(p[2])->playerNo = 2;
				b.alive[2] = true;
				b.players++;
			 }else{
				p[2]->setpos(m,0);
				p[2]->getid();
			 }
			 b.board[0][m] = (object*) p[2];
			 std::cout << "third player placed" << std::endl;
			 break;
		case 3: if(b.board[n][0])	// czwarty gracz - dolny lewy rog
				b.board[n][0]->die();
			 if(b.board[n][1])
				b.board[n][1]->die();
			 if(b.board[n-1][0])
				b.board[n-1][0]->die();
			 if(!p[3]){
			 	p[3] = new player(0,n,playerKeys[3],3); // na razie nie ma ukladu klawiatury dla tego gracza
					if(!p[3]){
						std::cerr << "Error! memory allocation error\n";
						exit(1);
					}
			 	//(p[3])->playerNo = 3;
				b.alive[3] = true;
				b.players++;
			 }else{
				p[3]->setpos(0,n);
				p[3]->getid();
			 }
			 b.board[n][0] = (object*) p[3];
			 break;
		}
	return b.players;
}

/* kladzie 'amount' stworkow typu 'type' na plansze w losowe miejsce, przyczym jezeli tam cos bylo to probuje go usunac i 
 * dopiero zostaje tam postawiony stworek jezeli sie uda. jezeli sie nie uda to bedzie 1 stworek mniej. obecnie jest tylko
 * jeden typ stworka, ale rozbudowac gre o wiecej nie jest problemem. chociaz w przypadku usuniecia obiektu z planszy nie jest
 * sprawdzono jakiego typu byl poprzednik, to moga niepowinny wystapic roznicy miedzy liczba stworkow zapisanych a naprawde 
 * istniejacych, bo rzeczy sa usuwane z planszy poprzez wysylanie do nich sygnal die(). moga jednak wystapic bonusy ktore sa
 * odkryte juz na poczatku gry, ale jest to na tyle malo wazne wydarzenie, ze mozna by to potraktowac jako urozmaicenia gry */
int initialiser::addBaddys(int type, int amount){
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
				case 0:b.board[y][x]= (object*) new baddy(x,y,16); break;
					if(!b.board[y][x]){
						std::cerr << "Error! memory allocation error\n";
						exit(1);
					}
			}
			std::cout << "baddy at:[" << x << "," << y << "]\n";
			b.baddys++;	// jako, ze jest o 1 stworek wiecej inkrementuje ich licznik
		}
	}
	return i;
}

Board* initialiser::newgame(){
	for(int i = 0; i < 4; i++){
		if(i >= players || !b.alive[i] || gameType == deathmatch || b.gameType == deathmatch ){
			p[i] = NULL;
		}else{
			if(gameType == coOp){
				p[i]->clearBombs();
				int tab[2];
				p[i]->getpos(tab);
				b.board[tab[1]][tab[0]] = NULL;
			}
		}
	}

	b.newBoard(n,m);
	if(gameType == deathmatch || b.gameType == deathmatch)
		b.players = 0;
	b.gameType = gameType;
	b.over = 0;
	fill(f,theme);				// wypelnia plansze zgodnie z podanym schematem
	addbonus();
	for(int i = 0; i < baddyTypes; i++){	// przelatuje przez liste wszystkich mozliwych stworkow
		if(baddys[i])			// i jezeli ktores sa wybrane, to dodaje na plansze
			addBaddys(i,baddys[i]);
	}
	


	for(int i = 0; i < 4; i++){
		if(!b.alive[i]){
			p[i] = NULL;
		}else{
			std::cout << "player " << i << " still alive\n";
			addPlayer(i);
		}
	}


	if( players > b.players){
		int amount = players - b.players;
		for(int i = 0; i < amount; i++)
			addPlayer();
	}
			std::cout << "amount of players: " << b.players << "\n";

	if(!roundsleft)
		roundsleft = rounds;
	glLoadIdentity();
	gluLookAt(0.0,-0.0, ( m>n ? m : n)+6, 		// punkt z ktorego sie patrzy
		  0.0,0.0,0.0,		// punkt (dowolny) lezacy na linie wzroku
		  -1.0f,0.0f,0.0f);	// wektor ktory wskazuje gore
	std::cout << "new game initialised\n";
}

void initialiser::viewBoard(){
	glLoadIdentity();
	gluLookAt(0.0,-0.0, ( m>n ? m : n)+6, 		// punkt z ktorego sie patrzy
		  0.0,0.0,0.0,		// punkt (dowolny) lezacy na linie wzroku
		  -1.0f,0.0f,0.0f);	// wektor ktory wskazuje gore
}

/* funkcja ktora zmienia ktore przyciski kontroluja gracza. jest on bazowana na vgakeyboard.h wiec przenosne nie jest. przy
 * zmianie obslugi klawiatury funkcja ta musialaby byc calkiem zmieniona */
void initialiser::changekeys(int i, keys k){
	playerKeys[i] = k;
	if(p[i])
		p[i]->setkeys(k);
}

void initialiser::setWidth(int i){ n=i;}
void initialiser::setHeight(int i){ m=i;}
void initialiser::setBonuses(int i){ bonuses=i;}

void initialiser::setRounds(int i){ 
	if(i < 1)
		rounds = 1;
	else rounds = i;
	if(rounds < roundsleft)
		roundsleft = rounds;
}
void initialiser::setFill(int i){ if(i>=0 && i <10)f=i;}

void initialiser::setTheme(int i){ 
	if(theme == warehouse)
		theme = garden;
	else
		theme = warehouse;
}

void initialiser::setGameType(int i){ 
	if(gameType == coOp)
		gameType = deathmatch;
	else
		gameType = coOp;
}

void initialiser::setBaddys(int type, int nr){
       	if(type >= 0 && type < baddyTypes){
	       baddys[type] = nr;
	}
}

int initialiser::getWidth(){ return n;}
int initialiser::getHeight(){ return m;}
int initialiser::getFill(){ return f;}
int initialiser::getRounds(){ return rounds;}

int initialiser::getRoundsleft(){
       if(roundsleft > 0)
       	       return --roundsleft;
	else
		return 0;
}

int initialiser::getPlayers(){ return players;}
int initialiser::getBonuses(){ return bonuses;}

int initialiser::getBaddys(int type){ 
	if(type >= 0 && type < baddyTypes)
		return baddys[type];
	else
		return 0;
}

char* initialiser::getTheme(){
       switch(theme){
	       case warehouse : return "warehouse";
	       case garden : return "garden";
       }
}

int initialiser::getGameType(){
	return gameType;
}

void initialiser::setPlayers(int i){
	if(i>0 && i <5)
		players = i;
}

void initialiser::nuke(){
	std::cout << "nuking... ";
	b.list.clear();
	std::cout << "cleared list, ";
	if(b.board){
		std::cout << "clearing board: ";
		b.clear();
		std::cout << "cleared board, deleting board: ";
		for(int i = 0; i < b.n; i++){
			memset(b.board[i],0,sizeof(object*)*b.m);
			delete[] b.board[i];
			b.board[i] = NULL;
			std::cout << "deleted row:" << i << "\n";
		}
	}
	delete[] b.board;
	std::cout << "deleted board.\n";
	b.board = NULL;
	b.players = 0;
	b.baddys = 0;
	b.over = 0;
	b.alive[0] = false;
	b.alive[1] = false;
	b.alive[2] = false;
	b.alive[3] = false;

	p[0] = NULL;
	p[1] = NULL;
	p[2] = NULL;
	p[3] = NULL;
	std::cout << "nuking finished.\n";
}
