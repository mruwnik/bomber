#include "object.h"


object::object(char c, unsigned long int m, int t): symbol(c), counter(t), mask(m){}

void object::changeSymbol(char c){// funkcja w sumie nie potrzebna, ale przydatna dla obecnej obslugi grafiki
	symbol = c;
}

/* funkcja czysto estetyczny dla ncurses.h */
void object::changeMask(unsigned long int m, int i){
	switch(i){
		case Set : mask = m; break;
		case Or : mask = mask | m; break;
		case And : mask = mask & m; break;
	}
}

/* funkcja ta jest wywolana dla wszystkich objektow znajdujacych sie na liscie objektow aktywnych. sluzy ona by przemiescac 
 * zyjatka albo wysadzic bomby itp. */
int object::move(){return 0;}	// domyslnie nic nie robi 

/* funkcja ta jest podstawa komunikacji miedzy objektami. jezeli objekt chce sie gdziesz przemiescic, ale jakis objekt stoi
 * mu na drodze, to posyla temu objektowi wskaznik na siebie przez ta funkcje. nastepnie objekt zapytany sprawdza co nalezy
 * zrobi i mu zwraca odpowiednia dzialanie jaka moze pierwszy objekt wykonac. np. jezeli gracz spotka gracza to zaden z nich sie
 * nie przesunie wiec zwroca sygnal 'none'. nastomiast jezeli stworek byl napotknal gracza, to gracz umiera i odpowiada
 * stworkowi sygnalem 'mov' mowiacy, ze ustapil mu miejsce i moze sie tak przemiescic stworek. domyslnie objektu nic nie robia*/
action object::request(object* o){ return none;}// nikomu nie ustepuje

/* funkcja ktora pozwala ogniowi bezposrednio zabic objektom. normalnie by musial poslac objektowi komunikat request() proszac
 * tamtego by sprawdzil co ma zrobic. ale jako, ze wiekszosc rzeczy odrazu umiera, a reszta nic nie robi, lepiej jest dolozyc
 * druga funkcje ktora by obslugiwala wszelakie zabojstwa planowane. */
void object::die(){}		// nie umiera

/* funkcja dla grafiki. mozna tu cokolwiek innego dac. chodzi o to, ze funkcja print() w klasie board wywoluje ta funkcje dla
 * kazdego objektu na planszie wiec tutaj nalezy odpowiednie kroki podjac aby wyswietlic obecny stan tego obiektu */
void object::print(){		
/**/	addch(symbol | mask);/**/
}

object::~object(){}
