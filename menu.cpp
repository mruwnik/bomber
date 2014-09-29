#include "menu.h"
#ifdef USE_FTGL
Menu::Menu(initialiser& i) : in(i), mousePressed(false), font("textures/subfont.ttf"), menuElement(0), s(0.5,70,10,0.1){
	if(font.Error())
		std::cerr << "error loading font\n";
	font.FaceSize(7);
	font.Depth(2);
#else
Menu::Menu(initialiser& i) : in(i), mousePressed(false),  menuElement(0), s(0.5,70,10,0.1){
#endif
	static bool pressed = false;
}


void Menu::setMenu(bool pressed, float nr){
	mousePressed = pressed;
	menuElement = nr;
}

void Menu::viewMenu(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0,-0.0, 100,	// punkt z ktorego sie patrzy
		  0.0,0.0,0.0,		// punkt (dowolny) lezacy na linie wzroku
		  0.0f,1.0f,0.0f);	// wektor ktory wskazuje gore
}

void Menu::renderBitmapString(float x, float y, float z, void *font, char *string) {  
	char *c;
	glRasterPos3f(x, y,z);
	for (c=string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

/* wyswietla menu gry */
int Menu::menu(){
	static int selected = 0;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();


	if((menuElement-5 != selected) && menuElement > 4 && menuElement < 9)
		selected = menuElement - 5;

	if(!pressed && selected > 0 && keys::keyPressed(UP)){
		selected--;
		pressed = true;
	}
	if(!pressed && selected < 3 && keys::keyPressed(DOWN)){
		selected++;
		pressed = true;
	}
	if(pressed && !keys::keyPressed(13) && !keys::keyPressed(UP) && !keys::keyPressed(DOWN)){
		pressed = false;
	}
	if(!pressed && keys::keyPressed(13) || (menuElement > 4 && menuElement < 9 && mousePressed) ){
		switch(selected){
		pressed = true;
		case 0 : in.nuke(); 
			 in.setPlayers(1);
			 in.setGameType(coOp);
		       	 return 2;	//gra jedno osobowa
		case 1 : in.nuke();
			 if(in.getPlayers() == 1)
				 in.setPlayers(2);
		       	 return 5;	//gra jedno osobowa
		case 2 : glPopMatrix();
			 return options(); 
		case 3 : return 0;
		}
	}



#ifdef USE_FTGL
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f); // Black text
	glRotatef(0,0,90,0);
	glTranslatef(-37,-4.8,0);
	font.Render("Nowa Gra Jedno-osobowa");
	glTranslatef(0,-10,0);
	font.Render("Nowa Gra Wielo-osobowa");
	glTranslatef(0,-10,0);
	font.Render("Opcje");
	glTranslatef(0,-10,0);
	font.Render("Wyjscie");
#else
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f); // Black text
	renderBitmapString(-37, -4.8, 0, GLUT_BITMAP_9_BY_15, "Nowa Gra Jedno-osobowa");
	renderBitmapString(-37, -14.8, 0, GLUT_BITMAP_9_BY_15, "Nowa Gra Wielo-osobowa");
	renderBitmapString(-37, -24.8, 0, GLUT_BITMAP_9_BY_15, "Opcje");
	renderBitmapString(-37, -34.8, 0, GLUT_BITMAP_9_BY_15, "Wyjscie");
	glTranslatef(-37,-34.8,0);
#endif
	if(selected >= 0 && selected < 5){
		glTranslatef(-4, 30 - selected*10 + 2 ,0);

		glColor3f(0.1,0.1,0.1);
		glTranslatef(0,0,r);
		glutSolidSphere(r,40,40);

		glColor3f(0.5,0.5,0.5);
		glRotatef(45,-r/6,-r/6,0);
		glTranslatef(0,0,r);
		GLUquadric* quad = gluNewQuadric();
		gluCylinder(quad, r/4,r/4,r/8,40,40);
		quad = gluNewQuadric();
		glTranslatef(0,0,r/7);
		gluDisk(quad, 0, r/4, 10,10);

//	Ponizszy kawalek kodu rysuje lont. fajnie by bylo gdyby szlo domontowac
//	iskiernice na koniec co by sie przesuwala w dol wraz z lontem
//
//		glColor3f(1.0,0.45,0);
//		glLineWidth(4);
//		glBegin(GL_LINE_LOOP);
//			double x,y=0;
//			for(int i = 0; i< 13; i++){
//				x-=r/28;
//				y=-x;
//				glVertex3f(x,y,y);
//			}
//		glEnd();
//		glTranslatef(x,y,0);
	
		s.print();	// tworzy iskiernice
	}

	glPopMatrix();
	glutSwapBuffers();
	return 3;
}

char* itoa(std::string& str, int n){
	char buf[6] = {0};
	int i = 5;
	while(n > 10){
		buf[i--] = (n % 10) + '0';
	        n /=10;
	}
	buf[i] = n + '0';
	str += buf+i;
}

/* wyswietla menu gry */
int Menu::options(){
	static int selected = 0;
	const int amount = 8;	
	std::string str;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();


	if((menuElement - (9 - amount) != selected) && menuElement >= 9 - amount && menuElement < 9)
		selected = menuElement - amount+1;

	if(!pressed && selected > 0 && keys::keyPressed(UP)){
		selected--;
		pressed = true;
	}
	if(!pressed && selected < amount && keys::keyPressed(DOWN)){
		selected++;
		pressed = true;
	}
	if(pressed && !keys::keyPressed(UP) && !keys::keyPressed(DOWN) && !keys::keyPressed(13) && !keys::keyPressed(RIGHT) && !keys::keyPressed(LEFT)){
		pressed = false;
	}
	if(!pressed && keys::keyPressed(13) || (menuElement >= 9 - amount -1 && menuElement < 9 && mousePressed) ){
		pressed = true;
		switch(selected){
		case 5 : return 6;
		case 7 : selected = 0; 
			 return 3;
		}
	}
	if(!pressed && keys::keyPressed(RIGHT)){
		pressed = true;
		switch(selected){
		case 0 : in.setWidth(in.getWidth()+1); break;
		case 1 : in.setHeight(in.getHeight()+1); break;
		case 2 : in.setFill(in.getFill()+1); break;
		case 3 : in.setTheme(1); break;
		case 4 : in.setBaddys(0,(in.getBaddys(0)+1)); break;
		case 5 : return 6;
		case 6 : in.setBonuses(in.getBonuses()+1); break;
		}
	}

	if(!pressed && keys::keyPressed(LEFT)){
		pressed = true;
		switch(selected){
		case 0 : in.setWidth(in.getWidth()-1); break;
		case 1 : in.setHeight(in.getHeight()-1); break;
		case 2 : in.setFill(in.getFill()-1); break;
		case 3 : in.setTheme(1); break;
		case 4 : in.setBaddys(0,(in.getBaddys(0)-1)); break;
		case 6 : in.setBonuses(in.getBonuses()-1); break;
		}
	}


#ifdef USE_FTGL
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f); // Black text
	glRotatef(0,0,90,0);
	glTranslatef(-37,30.8,0);
	str = "Szerokosc planszy: ";
	itoa(str,in.getWidth());
	font.Render(str.c_str());
	glTranslatef(0,-10,0);
	str = "Wysokosc planszy: ";
	itoa(str,in.getHeight());
	font.Render(str.c_str());
	glTranslatef(0,-10,0);
	str = "Wypelnienie: 1/";
	itoa(str,in.getFill());
	font.Render(str.c_str());
	glTranslatef(0,-10,0);
	str = "Mapa: ";
	str += in.getTheme();
	font.Render(str.c_str());
	glTranslatef(0,-10,0);
	str = "Ilosc stworkow: ";
	itoa(str,in.getBaddys(0));
	font.Render(str.c_str());
	glTranslatef(0,-10,0);
	font.Render("Zmiana klawiszy");
	glTranslatef(0,-10,0);
	str = "Ilosc bonusow: ";
	itoa(str,in.getBonuses());
	font.Render(str.c_str());
	glTranslatef(0,-10,0);
	font.Render("Powrot");
#else
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f); // Black text
	str = "Szerokosc planszy: ";
	itoa(str,in.getWidth());
	renderBitmapString(-37, 30.8, 0, GLUT_BITMAP_9_BY_15, (char*)str.c_str());
	str = "Wysokosc planszy: ";
	itoa(str,in.getHeight());
	renderBitmapString(-37, 20.8, 0, GLUT_BITMAP_9_BY_15, (char*)str.c_str());
	str = "Wypelnienie: 1/";
	itoa(str,in.getFill());
	renderBitmapString(-37, 10.8, 0, GLUT_BITMAP_9_BY_15, (char*)str.c_str());
	str = "Mapa: ";
	str += in.getTheme();
	renderBitmapString(-37, 0.8, 0, GLUT_BITMAP_9_BY_15, (char*)str.c_str());
	str = "Ilosc stworkow: ";
	itoa(str,in.getBaddys(0));
	renderBitmapString(-37, -10.8, 0, GLUT_BITMAP_9_BY_15, (char*)str.c_str());
	renderBitmapString(-37, -20.8, 0, GLUT_BITMAP_9_BY_15, "Zmiana klawiszy");
	str = "Ilosc bonusow: ";
	itoa(str,in.getBonuses());
	renderBitmapString(-37, -30.8, 0, GLUT_BITMAP_9_BY_15, (char*)str.c_str());
	renderBitmapString(-37, -40.8, 0, GLUT_BITMAP_9_BY_15, "Powrot");
	glTranslatef(-37,-40.8,0);
#endif

	if(selected >= 0 && selected < amount){
		glTranslatef(-4, 70 - selected*10 + 2 ,0);

		glColor3f(0.1,0.1,0.1);
		glTranslatef(0,0,r);
		glutSolidSphere(r,40,40);

		glColor3f(0.5,0.5,0.5);
		glRotatef(45,-r/6,-r/6,0);
		glTranslatef(0,0,r);
		GLUquadric* quad = gluNewQuadric();
		gluCylinder(quad, r/4,r/4,r/8,40,40);
		quad = gluNewQuadric();
		glTranslatef(0,0,r/7);
		gluDisk(quad, 0, r/4, 10,10);

//	Ponizszy kawalek kodu rysuje lont. fajnie by bylo gdyby szlo domontowac
//	iskiernice na koniec co by sie przesuwala w dol wraz z lontem
//
//		glColor3f(1.0,0.45,0);
//		glLineWidth(4);
//		glBegin(GL_LINE_LOOP);
//			double x,y=0;
//			for(int i = 0; i< 13; i++){
//				x-=r/28;
//				y=-x;
//				glVertex3f(x,y,y);
//			}
//		glEnd();
//		glTranslatef(x,y,0);
	
		s.print();	// tworzy iskiernice
	}

	glPopMatrix();
	glutSwapBuffers();
	return 4;
}


/* wyswietla menu gry */
int Menu::multiplayer(){
	static int selected = 1;
	static int amount = 5;	
	std::string str;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();


	if((menuElement - (9 - amount) != selected) && menuElement >= 9 - amount && menuElement < 9)
		selected = menuElement - amount+1;

	if(!pressed && selected > 0 && keys::keyPressed(UP)){
		selected--;
		pressed = true;
	}
	if(!pressed && selected < amount && keys::keyPressed(DOWN)){
		selected++;
		pressed = true;
	}
	if(pressed && !keys::keyPressed(UP) && !keys::keyPressed(DOWN) && !keys::keyPressed(13) && !keys::keyPressed(RIGHT) && !keys::keyPressed(LEFT)){
		pressed = false;
	}
	if(!pressed && keys::keyPressed(13) || (menuElement >= 9 - amount -1 && menuElement < 9 && mousePressed) ){
		pressed = true;
		if(!selected){
			selected = 1;
		       	return 2;	//gra jedno osobowa
		}
		else if(selected == amount -1){
			selected = 1; 
			return 3;
		}
	}
	if(!pressed && keys::keyPressed(RIGHT)){
		pressed = true;
		switch(selected){
		case 1 : in.setPlayers(in.getPlayers()+1); break;
		case 2 : in.setTheme(1); break;
		case 3 : in.setGameType(1); break;
		}
		if(amount == 6 && selected == 4)
			in.setRounds(in.getRounds()+1);
	}

	if(!pressed && keys::keyPressed(LEFT)){
		pressed = true;
		switch(selected){
		case 1 : in.setPlayers(in.getPlayers()-1); break;
		case 2 : in.setTheme(1); break;
		case 3 : in.setGameType(1); break;
		}
		if(amount == 6 && selected == 4)
			in.setRounds(in.getRounds()-1);
	}



#ifdef USE_FTGL
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f); // Black text
	glRotatef(0,0,90,0);
	glTranslatef(-37,10.8,0);
	font.Render("Rozpocznij gre");
	glTranslatef(0,-10,0);
	str = "Ilosc graczy: ";
	itoa(str,in.getPlayers());
	font.Render(str.c_str());
	glTranslatef(0,-10,0);
	str = "Mapa: ";
	str += in.getTheme();
	font.Render(str.c_str());
	glTranslatef(0,-10,0);
	str = "Typ gry: ";
	int type = in.getGameType();
       switch(type){
	       case coOp : str+= "wspolpraca"; break;
	       case deathmatch : str+= "bitwa"; break;
       }
	font.Render(str.c_str());
	if(!type){
		amount = 6;
		glTranslatef(0,-10,0);
		str = "Ilosc rund: ";
		itoa(str,in.getRounds());
		font.Render(str.c_str());
	}else{
		amount = 5;
	}
	glTranslatef(0,-10,0);
	font.Render("Powrot");

#else
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f); // Black text
	renderBitmapString(-37, 10.8, 0, GLUT_BITMAP_9_BY_15, "Rozpocznij gre");
	str = "Ilosc graczy: ";
	itoa(str,in.getPlayers());
	renderBitmapString(-37, 0.8, 0, GLUT_BITMAP_9_BY_15, (char*)str.c_str());
	str = "Mapa: ";
	str += in.getTheme();
	renderBitmapString(-37, -10.8, 0, GLUT_BITMAP_9_BY_15, (char*)str.c_str());
	str = "Typ gry: ";
	int type = in.getGameType();
        switch(type){
	       case coOp : str+= "wspolpraca"; break;
	       case deathmatch : str+= "bitwa"; break;
       }
	renderBitmapString(-37, -20.8, 0, GLUT_BITMAP_9_BY_15, (char*)str.c_str());
	if(!type){
		amount = 6;
		str = "Ilosc rund: ";
		itoa(str,in.getRounds());
		renderBitmapString(-37, -30.8, 0, GLUT_BITMAP_9_BY_15, (char*)str.c_str());
		renderBitmapString(-37, -40.8, 0, GLUT_BITMAP_9_BY_15, "Powrot");
		glTranslatef(-37,-44.8,0);
	}else{
		amount = 5;
		renderBitmapString(-37, -30.8, 0, GLUT_BITMAP_9_BY_15, "Powrot");
		glTranslatef(-37,-34.8,0);
	}
#endif

	if(selected >= 0 && selected < amount){
		glTranslatef(-4, ((amount-1) - selected)*10 + 2 ,0);

		glColor3f(0.1,0.1,0.1);
		glTranslatef(0,0,r);
		glutSolidSphere(r,40,40);

		glColor3f(0.5,0.5,0.5);
		glRotatef(45,-r/6,-r/6,0);
		glTranslatef(0,0,r);
		GLUquadric* quad = gluNewQuadric();
		gluCylinder(quad, r/4,r/4,r/8,40,40);
		quad = gluNewQuadric();
		glTranslatef(0,0,r/7);
		gluDisk(quad, 0, r/4, 10,10);

//	Ponizszy kawalek kodu rysuje lont. fajnie by bylo gdyby szlo domontowac
//	iskiernice na koniec co by sie przesuwala w dol wraz z lontem
//
//		glColor3f(1.0,0.45,0);
//		glLineWidth(4);
//		glBegin(GL_LINE_LOOP);
//			double x,y=0;
//			for(int i = 0; i< 13; i++){
//				x-=r/28;
//				y=-x;
//				glVertex3f(x,y,y);
//			}
//		glEnd();
//		glTranslatef(x,y,0);
	
		s.print();	// tworzy iskiernice
	}

	glPopMatrix();
	glutSwapBuffers();
	return 5;
}

bool Menu::playerkeys(int i){
	static bool pressed = true;
	static keys k;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	glColor4f(0.0f, 0.0f, 1.0f, 1.0f); // Black text
	glRotatef(0,0,90,0);
	if(pressed && k.keyPressed(RIGHT))
		return true;
	else 
		pressed = false;

#ifdef USE_FTGL
	glTranslatef(-37,10.8,0);
	font.Render("Gora: ");
#else
	renderBitmapString(-37, 10.8, 0, GLUT_BITMAP_9_BY_15, "Gora:");
#endif
	if(!k.up){
		for(unsigned int i = 0; i < keysAmount; i++){
			if(k.keyPressed(i)){
					k.up = i;
			}
		}
		return true;
	}
	if(k.keyPressed(k.up))
		return true;
#ifdef USE_FTGL
	glTranslatef(0,-10,0);
	font.Render("Prawo: ");
#else
	renderBitmapString(-37, 0.8, 0, GLUT_BITMAP_9_BY_15, "Prawo:");
#endif
	if(!k.right){
		for(unsigned int i = 0; i < keysAmount; i++){
			if(k.keyPressed(i)){
					k.right = i;
			}
		}
		return true;
	}
	if(k.keyPressed(k.right))
		return true;

#ifdef USE_FTGL
	glTranslatef(0,-10,0);
	font.Render("Dol: ");
#else
	renderBitmapString(-37, -10.8, 0, GLUT_BITMAP_9_BY_15, "Dol:");
#endif
	if(!k.down){
		for(unsigned int i = 0; i < keysAmount; i++){
			if(k.keyPressed(i)){
					k.down = i;
			}
		}
		return true;
	}
	if(k.keyPressed(k.down))
		return true;
#ifdef USE_FTGL
	glTranslatef(0,-10,0);
	font.Render("Lewo: ");
#else
	renderBitmapString(-37, -20.8, 0, GLUT_BITMAP_9_BY_15, "Lewo:");
#endif
	if(!k.left){
		for(unsigned int i = 0; i < keysAmount; i++){
			if(k.keyPressed(i)){
					k.left = i;
			}
		}
		return true;
	}
	if(k.keyPressed(k.left))
		return true;
#ifdef USE_FTGL
	glTranslatef(0,-10,0);
	font.Render("Bomba: ");
#else
	renderBitmapString(-37, -30.8, 0, GLUT_BITMAP_9_BY_15, "Bomba:");
#endif
	if(!k.bomb){
		for(unsigned int i = 0; i < keysAmount; i++){
			if(k.keyPressed(i)){
					k.bomb = i;
			}
		}
		return true;
	}
	if(k.keyPressed(k.bomb))
		return true;
	in.changekeys(i,k);
	std::cout << "changed keys for player " << i << std::endl;
	pressed = true;
	k = keys();
	glPopMatrix();
	return false;
}


/* wyswietla menu gry */
int Menu::changekeys(){
	static bool changing = false;
	static int selected = 1;
	static int amount = 5;	
	std::string str;

	if(changing){
	       if(changing = playerkeys(selected)){
			glPopMatrix();
			glutSwapBuffers();
			return 6;
		}
	       else
		       changing = false;
	}


	if((menuElement - (9 - amount) != selected) && menuElement >= 9 - amount && menuElement < 9)
		selected = menuElement - amount+1;

	if(!pressed && selected > 0 && keys::keyPressed(UP)){
		selected--;
		pressed = true;
	}
	if(!pressed && selected < amount && keys::keyPressed(DOWN)){
		selected++;
		pressed = true;
	}
	if(pressed && !keys::keyPressed(UP) && !keys::keyPressed(DOWN) && !keys::keyPressed(13) && !keys::keyPressed(RIGHT) && !keys::keyPressed(LEFT)){
		pressed = false;
	}
	if(!pressed && (keys::keyPressed(13) || keys::keyPressed(RIGHT)) || (menuElement >= 9 - amount -1 && menuElement < 9 && mousePressed) ){
		pressed = true;
		switch(selected){
		case 0 : changing = playerkeys(selected); break;
		case 1 : changing = playerkeys(selected); break;
		case 2 : changing = playerkeys(selected); break;
		case 3 : changing = playerkeys(selected); break;
		}
		if(selected == amount -1){
			selected = 1; 
			return 4;
		}
	}
/*	if(!pressed && keys::keyPressed(RIGHT)){
		pressed = true;
		switch(selected){
		case 0 : changing = playerkeys(selected); break;
		case 1 : changing = playerkeys(selected); break;
		case 2 : changing = playerkeys(selected); break;
		case 3 : changing = playerkeys(selected); break;
		}
	}*/
/*
	if(!pressed && keys::keyPressed(LEFT)){
		pressed = true;
		switch(selected){
		case 1 : in.setPlayers(in.getPlayers()-1); break;
		case 2 : in.setTheme(1); break;
		case 3 : in.setGameType(1); break;
		}
		if(amount == 6 && selected == 4)
			in.setRounds(in.getRounds()-1);
	}
*/

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

#ifdef USE_FTGL
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f); // Black text
	glRotatef(0,0,90,0);
	glTranslatef(-37,10.8,0);
	font.Render("Gracz pierwszy");
	glTranslatef(0,-10,0);
	font.Render("Gracz drugi");
	glTranslatef(0,-10,0);
	font.Render("Gracz trzeci");
	glTranslatef(0,-10,0);
	font.Render("Gracz czwarty");
	glTranslatef(0,-10,0);
	font.Render("Powrot");

#else
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f); // Black text
	renderBitmapString(-37, 10.8, 0, GLUT_BITMAP_9_BY_15, "Gracz pierwszy");
	renderBitmapString(-37, 0.8, 0, GLUT_BITMAP_9_BY_15, "Gracz drugi");
	renderBitmapString(-37, -10.8, 0, GLUT_BITMAP_9_BY_15, "Gracz trzeci");
	renderBitmapString(-37, -20.8, 0, GLUT_BITMAP_9_BY_15, "Gracz czwarty");
	renderBitmapString(-37, -30.8, 0, GLUT_BITMAP_9_BY_15, "Powrot");
	glTranslatef(-37,-34.8,0);
	
#endif

	if(selected >= 0 && selected < amount){
		glTranslatef(-4, ((amount-1) - selected)*10 + 2 ,0);

		glColor3f(0.1,0.1,0.1);
		glTranslatef(0,0,r);
		glutSolidSphere(r,40,40);

		glColor3f(0.5,0.5,0.5);
		glRotatef(45,-r/6,-r/6,0);
		glTranslatef(0,0,r);
		GLUquadric* quad = gluNewQuadric();
		gluCylinder(quad, r/4,r/4,r/8,40,40);
		quad = gluNewQuadric();
		glTranslatef(0,0,r/7);
		gluDisk(quad, 0, r/4, 10,10);

//	Ponizszy kawalek kodu rysuje lont. fajnie by bylo gdyby szlo domontowac
//	iskiernice na koniec co by sie przesuwala w dol wraz z lontem
//
//		glColor3f(1.0,0.45,0);
//		glLineWidth(4);
//		glBegin(GL_LINE_LOOP);
//			double x,y=0;
//			for(int i = 0; i< 13; i++){
//				x-=r/28;
//				y=-x;
//				glVertex3f(x,y,y);
//			}
//		glEnd();
//		glTranslatef(x,y,0);
	
		s.print();	// tworzy iskiernice
	}

	glPopMatrix();
	glutSwapBuffers();
	return 6;
}
