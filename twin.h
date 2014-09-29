#ifndef TWIN_H
#define TWIN_H
#include "board.h"

/* jest to klasa ktora pozwala postawic 2 objekty na jednym polu planszy */
class twin : public object{
	static Board* board;
	int x,y,id,f;	// wspol. (x,y), identyfikator w liscie objektow aktywnych, znacznik ktorego objektu nalezy usunac
	object* one;	// wskaznik na objekt nieaktywny, lezacy na dole (np. sciana albo bomba)
	object* two;	// wskaznik na objekt aktywny, lezacy na gorze (np. latajacy stworek albo gracz)
public:
	twin(object* o, object* t, int x, int y);
	static void set(Board*);	// ustawia wskaznik na plansze
	action request(object* o);	// przyjmuje prosby o przesuniecia sie
	int move();			// kaze drugiemu objektowi zrobic ruch
	void print();			
	void die();			// usuwa odpowiedni objekt ( f==0 ? one->die() : two->die() )
	void setid(int i);		
	~twin();
};
#endif
