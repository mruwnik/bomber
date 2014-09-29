#include "fire.h"


spark::spark(float R, float G, float B, float X, float Y, float Z, float Xi, float Yi, float Zi, float Xg, float Yg, float Zg, float f, float ra, bool act, float l) : r(R), b(B), g(G), x(X), y(Y), z(Z), xi(Xi), yi(Yi), zi(Zi), xg(Xg), yg(Yg), zg(Zg), fade(f), rad(ra), active(active), life(l), xo(X), yo(Y), zo(Z){}

spark::spark(float* colour, float* position, float* direction, float* gravity, float f, bool act, float ra, float l) : fade(f), active(act), rad(ra), life(l){
		r = colour[0];
		g = colour[1];
		b = colour[2];
		xo = x = position[0];
		yo = y = position[1];
		zo = z = position[2];
		xi = direction[0];
		yi = direction[1];
		zi = direction[2];
		xg = gravity[0];
		yg = gravity[1];
		zg = gravity[2];
}

spark::	spark(float X, float Y, float Z, float R, float G, float B) : x(X), y(Y), z(Z), xo(X), yo(Y), zo(Z), r(R), g(G), b(B), rad(0){
	active=true;				// Make All The Particles Active
	life=1.0f;				// Give All The Particles Full Life
	fade=float(rand()%100)/1000.0f+0.003f;	// Random Fade Speed
	xi=float((rand()%50)-26.0f)*10.0f;	// Random Speed On X Axis
	yi=float((rand()%50)-25.0f)*10.0f;	// Random Speed On Y Axis
	zi=float((rand()%50)-25.0f)*10.0f;	// Random Speed On Z Axis
	xg=0.0f;				// Set Horizontal Pull To Zero
	yg=0.0f;				// Set Pull On Y Axis To Zer0
	zg=0.8f;				// Set Vertical Pull Downward
}

spark::spark(float ra, float R, float G, float B) : r(R), g(G), b(B), rad(ra){
	active=true;				// Make All The Particles Active
	life=1.0f;				// Give All The Particles Full Life
	fade=float(rand()%100)/100.0f+0.003f;	// Random Fade Speed
	xi=0;float((rand()%50)-26.0f)*10.0f;	// Random Speed On X Axis
	yi=0;float((rand()%50)-25.0f)*10.0f;	// Random Speed On Y Axis
	zi=1/(fade*80);	// Random Speed On Z Axis
	//zi=float((rand()%50)-25.0f);	// Random Speed On Z Axis
	xg=0.0f;				// Set Horizontal Pull To Zero
	yg=0.0f;				// Set Pull On Y Axis To Zer0
	zg=0.8f;				// Set Vertical Pull Downward
	xo = x = float((rand()/((double)RAND_MAX))*rad-((rad)/2));	// Random Speed On X Axis
	ra = (rand()/(double)RAND_MAX)*rad;
	yo = y = sqrt((ra+x)*(ra-x)) - rad/2;	// Random Speed On Y Axis
	//y=float((rand()/((double)RAND_MAX))*rad-((rad)/2));	// Random Speed On Y Axis
	zo = z = 0.0;
	g = fade;
	rad = 0.028;
}
		
spark::spark(float ra): rad(ra){
	active=true;				// Make All The Particles Active
	life=1.0f;				// Give All The Particles Full Life
	fade=float(rand()%100)/1000.0f+0.003f;	// Random Fade Speed
	xi=float((rand()%50)-26.0f);	// Random Speed On X Axis
	yi=float((rand()%50)-25.0f);	// Random Speed On Y Axis
	zi=float((rand()%50)-25.0f);	// Random Speed On Z Axis
	xg=0.0f;				// Set Horizontal Pull To Zero
	yg=0.0f;				// Set Pull On Y Axis To Zer0
	zg=0.8f;				// Set Vertical Pull Downward
	xo = x = float((rand()/((double)RAND_MAX))*rad);	// Random Speed On X Axis
	yo = y = float((rand()/((double)RAND_MAX))*rad);	// Random Speed On Y Axis
	zo = z =float((rand()/((double)RAND_MAX))*rad);	// Random Speed On Z Axis
	int col = rand()%12;
	r=colours[col][0];	// Select Red Rainbow Colour
	g=colours[col][1];	// Select Green Rainbow Colour
	b=colours[col][2];	// Select Blue Rainbow Colour
}

void spark::print(){
	// Draw The Particle Using Our RGB Values, Fade The Particle Based On It's Life
	glColor4f(r,g,b,life);

	glBegin(GL_TRIANGLE_STRIP);			// Build Quad From A Triangle Strip
	 	glTexCoord2d(1,1); glVertex3f(x+rad,y+rad,z);	// Top Right
		glTexCoord2d(0,1); glVertex3f(x-rad,y+rad,z);	// Top Left
		glTexCoord2d(1,0); glVertex3f(x+rad,y-rad,z); 	// Bottom Right
		glTexCoord2d(0,0); glVertex3f(x-rad,y-rad,z); 	// Bottom Left
	glEnd();					// Done Building Triangle Strip

	x+=xi/(slowdown);// Move On The X Axis By X Speed
	y+=yi/(slowdown);// Move On The Y Axis By Y Speed
	z+=zi/(slowdown);// Move On The Z Axis By Z Speed

	xi+=xg;	// Take Pull On X Axis Into Account
	yi+=yg;	// Take Pull On Y Axis Into Account
	zi+=zg;	// Take Pull On Z Axis Into Account

	life-=fade;	// Reduce Particles Life By 'Fade'

	if (life<0.0f && active){			// If Particle Is Burned Out
		life=1.0f;				// Give It New Life
		x = xo;
		y = yo;
		z = zo;
	//	double steps = 1.0 / fade;
		//xi -= steps * xg;
	//	yi -= steps * yg;
	//	zi -= steps * zg;
//		fade*= (float(rand()%10)/10) +0.503f;	// Random Fade Value
		//x= rand()/(double)RAND_MAX * rad - rad/2 -0.1;					// Center On X Axis
		//y= rand()/(double)RAND_MAX * rad - rad/2 - 0.1;
		//x -= steps * (xi + xg)/(slowdown); 
		//y -= steps * (yi + yg)/(slowdown); 
		//z -= steps * (zi + zg)/(slowdown); 
	//	xi=0;//float((rand()%60)-32.0f);	// X Axis Speed And Direction
	//	yi=0;//float((rand()%60)-30.0f);	// Y Axis Speed And Direction
	//	zi=1/(fade*80);  // Z Axis Speed And Direction
		//zi=float((rand()%60)-30.0f); // Z Axis Speed And Direction
	//	int col = rand()% coloursAmount;
	//	r=colours[col][0];	// Select Red From Colour Table
	//	g=colours[col][1];	// Select Green From Colour Table
	//	g= fade;	// Select Green From Colour Table
	//	b=colours[col][2];	// Select Blue From Colour Table
	}
}

sparkler::sparkler(float s, int i, float splash, float size) : spray(s), intensity(i){

	sparks = new spark*[intensity];
		if(!sparks){
			std::cerr << "Error! bad memory allocation\n";
			exit(1);
		}
	for (int loop=0; loop < intensity; loop++){
		GLfloat fade=GLfloat(rand()%50)/1000.0f+0.005f;	// Random Fade Speed
		GLfloat colour[3] = {1.0,0.008/fade,0.0};
		float position[3] = {0.0,0.0,0.0};
		float speed[3] = {((rand()%50)-26.0f)*fade*splash*30*s,float((rand()%50)-26.0f)*fade*splash*30*s,float((rand()%100))*fade*splash*80.0f*s};
		//float gravity[3] = 
		sparks[loop] = new spark(colour,position,speed,position,fade,true,size);
		if(!sparks[loop]){
			std::cerr << "Error! bad memory allocation\n";
			exit(1);
		}
	}
}

void sparkler::print(){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, fire::getTex());
	glPushMatrix();

	glDisable(GL_DEPTH_TEST);		// Disable Depth Testing
//	glEnable(GL_BLEND);			// Enable Blending
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);	// Type Of Blending To Perform
	for (int loop=0; loop < intensity; loop++){	// Loop Through All The Particles
		if (sparks[loop]!= NULL && sparks[loop]->active){// If The Particle Is Active
			if(sparks[loop]->life < 0.03){
				sparks[loop]->fade = GLfloat(rand()%50)/1000.0f+0.008f;	// Random Fade Speed
				sparks[loop]->g = 0.008/(sparks[loop]->fade) + 0.2;
				sparks[loop]->xi = float((rand()%50)-26.0f)*sparks[loop]->fade*30*spray;
				sparks[loop]->yi = float((rand()%50)-26.0f)*sparks[loop]->fade*30*spray;
				sparks[loop]->zi = float((rand()%100))*sparks[loop]->fade*80.0f*spray;
				sparks[loop]->life = 1.0;
				sparks[loop]->x = 0.0;
				sparks[loop]->y = 0.0;
				sparks[loop]->z = 0.0;
			}
			sparks[loop]->print();	
		}
	}

	glPopMatrix();
//	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
	glColor4f(0.1,0.1,0.1,1);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);				// Type Of Blending To Perform
}


sparkler::~sparkler(){
	for (int loop=0; loop < intensity; loop++)
		delete sparks[loop];
	delete[] sparks;
}

wierdo::wierdo(int n, GLuint t, float s, int i, float rad) : tex(t), spray(s), amount(i) {

	bits = new spark*[amount];
		if(!bits){
			std::cerr << "Error! bad memory allocation\n";
			exit(1);
		}
	for (int loop=0; loop < amount; loop++){
		float fade=float(rand()%40)/5000.0f+0.003f;	// Random Fade Speed
		GLfloat colour[3] = {0};
		switch(n){
		case 0 : colour[0] = 0;	colour[1] = 0.6; colour[2] = 1; break;
		case 1 : colour[0] = 0.25; colour[1] = 1; colour[2] = 0.75; break;
		case 2 : colour[0] = 0.5;  colour[1] = 0.5; colour[2] = 0.5; break;
		case 3 : colour[0] = 0.75; colour[1] = 0.3; colour[2] = 0.25; break;
		}
		float position[3] = {0.0,0.0,0.0};
//		position[0] = float((rand()/((double)RAND_MAX))*rad-((rad)/2));
//		float ra = (rand()/(double)RAND_MAX)*rad;
//		position[1] = sqrt((ra+position[0])*(ra-position[0])) - rad/2;
		float speed[3] = {float((rand()%50)-26.0f)*fade*s,float((rand()%50)-26.0f)*fade*s,float((rand()%50)-26.0f)*fade*s};
		//float gravity[3] = 
		bits[loop] = new spark(colour,position,speed,position,fade,true,0.025);
		if(!bits[loop]){
			std::cerr << "Error! bad memory allocation\n";
			exit(1);
		}
	}
}

void wierdo::print(){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex);
	glPushMatrix();

	glDisable(GL_DEPTH_TEST);		// Disable Depth Testing
//	glEnable(GL_BLEND);			// Enable Blending
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);	// Type Of Blending To Perform
	for (int loop=0; loop < amount; loop++){	// Loop Through All The Particles
		if (bits[loop]!= NULL)// If The Particle Is Active
			bits[loop]->print();	
	}

	glPopMatrix();
//	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
	glColor4f(0.1,0.1,0.1,1);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);				// Type Of Blending To Perform
}

wierdo::~wierdo(){
	for (int loop=0; loop < amount; loop++)
		delete bits[loop];
	delete[] bits;
}


cloud::cloud(GLuint t, float s, int i, float rad) : tex(t), spray(s), amount(i) {

	bits = new spark*[amount];
		if(!bits){
			std::cerr << "Error! bad memory allocation\n";
			exit(1);
		}
	for (int loop=0; loop < amount; loop++){
		float fade=float(rand()%20)/100.0f+0.033f;	// Random Fade Speed
		GLfloat colour[3] = {0,0,0.3};
		float position[3] = {0.0,0.0,0.0};
		position[0] = float((rand()/((double)RAND_MAX))*rad-((rad)/2));
		float ra = (rand()/(double)RAND_MAX)*rad;
		position[1] = sqrt((ra+position[0])*(ra-position[0])) - rad/2;
//		float speed[3] = {float((rand()%50)-26.0f)*10.0f*s,float((rand()%50)-26.0f)*10.0f*s,float((rand()%50)-26.0f)*10.0f*s};
		float speed[3] = {position[0] * 90, position[1] *90, position[2] * 0.09};
		//float gravity[3] = 
		bits[loop] = new spark(colour,position,speed,position,fade,false,0.04);
		if(!bits[loop]){
			std::cerr << "Error! bad memory allocation\n";
			exit(1);
		}
	}
}

void cloud::print(){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex);
	glPushMatrix();

	glDisable(GL_DEPTH_TEST);		// Disable Depth Testing
//	glEnable(GL_BLEND);			// Enable Blending
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);	// Type Of Blending To Perform
	for (int loop=0; loop < amount; loop++){	// Loop Through All The Particles
		if (bits[loop]!= NULL)// If The Particle Is Active
			bits[loop]->print();	
	}

	glPopMatrix();
//	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
	glColor4f(0.1,0.1,0.1,1);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);				// Type Of Blending To Perform
}

cloud::~cloud(){
	for (int loop=0; loop < amount; loop++)
		delete bits[loop];
	delete[] bits;
}

GLuint fire::tex[1]={0};

int fire::setTex(){ 
	int Status;
	GLubyte* texture = new GLubyte[32 * 32 * 3];
	FILE *tf;

	tf = fopen ( "textures/fire/Particle.raw", "rb" );
	fread ( texture, 1, 32 * 32 * 3, tf );
	fclose ( tf );

	// do stuff
	Status=1;						// Set The Status To TRUE
	glGenTextures(1, &tex[0]);				// Create One Texture

	glBindTexture(GL_TEXTURE_2D, tex[0]);
//	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 32, 32,
		0, GL_RGB, GL_UNSIGNED_BYTE, texture);

	delete [] texture;

        return Status;
}

GLuint fire::getTex(){ return tex[0];//symbol = t;}
}

fire::fire(int x, int y, int t, float r, int i): object(NULL,t), p(x,y), rad(r), intensity(i){ // t to czas zycia ognia
	sparks = new spark*[intensity];
		if(!sparks){
			std::cerr << "Error! bad memory allocation\n";
			exit(1);
		}
	for (int loop=0; loop < intensity; loop++){				// Initials All The Textures
		sparks[loop] = new spark(rad,1.0);
		if(!sparks[loop]){
			std::cerr << "Error! bad memory allocation\n";
			exit(1);
		}
	}
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

void fire::print(){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex[0]);
	glPushMatrix();

	glDisable(GL_DEPTH_TEST);					// Disable Depth Testing
//	glEnable(GL_BLEND);						// Enable Blending
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);				// Type Of Blending To Perform
	for (int loop=0; loop < intensity; loop++){			// Loop Through All The Particles
		if (sparks[loop]!= NULL && sparks[loop]->active)	// If The Particle Is Active
			sparks[loop]->print();	
	}

	glPopMatrix();
//	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
	glColor4f(0.1,0.1,0.1,1);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);				// Type Of Blending To Perform
}

fire::~fire(){
	for (int loop=0; loop < intensity; loop++)
		delete sparks[loop];
	delete[] sparks;
}


