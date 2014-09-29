#ifndef LIST_H
#define LIST_H

/* kontener ktory w sumie jest wektorem, tyle ze przy usuniecia ze srodka to zamiast przesunac w lewo wszystkie elementy tablicy * lezace na prawo od usuwanej wartosci, to poprostu wstawia w pusta miejsce ostatni element */
template<class T>
class List{
	int quantity; //liczba elementow pamieci
	int next; //nastepny pusty element
	T** storage; //tablica wskaznikow na objekty ktore beda cos robily
	void inflate(int increase = 10); // powieksza tablice o 'increase'
public:
	List() : quantity(0), next(0), storage(0) {};
	int add(T*);			// dodaje element do tablicy i zwraca jego pozycje w tablicy
	T* operator[](int index) const; // pobiera storage[index]
	T* remove(int index); 		// usuwa storage[index] z tablicy, przy czym nie usuwa z pamieci
	~List();
};

template<class T>
void List<T>::inflate(int increase){
	const int size = sizeof(T*);
	T** ob = new T*[quantity + increase];
	memset(ob, 0, (quantity + increase) * size);
	memcpy(ob, storage, quantity * size);
	quantity += increase;
	delete[] storage;
	storage = ob;
}

template<class T>
int List<T>::add(T* ob){
	const int inflateBy = 10;
	if(next >= quantity)
		inflate(inflateBy);
	storage[next++] = ob;
	return (next-1); // numer indeksu dodawanego elementu
}

template<class T>
T* List<T>::operator[](int index) const {
	if( (index >= 0) && (index < next))
		return storage[index];
	return 0;
}

// wyciaga storage[index] i przesuwa ostatni element w powstala luke
template<class T>
T* List<T>::remove(int index){
	T* o = operator[](index);
	if(o){
		storage[index] = storage[--next];
		storage[next] = 0;
		if(storage[index])
			storage[index]->setid(index);	// zmienia nr id. ostatniego elementu na nowa
	}
	return o;
}

template<class T>
List<T>::~List(){// przy usunieciu ma tylko pozbyc sie pamieci zajetej przez tablicy ktore wskazuje zostawic w spokoju
	memset(storage, 0, quantity * sizeof(T*));
	delete storage;
}
#endif
