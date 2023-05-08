#ifndef UTILITY_H_SENTRY
#define UTILITY_H_SENTRY
#include "coords.h"
#include <cstddef>

enum sides { UP, RIGHT, DOWN, LEFT };
enum hitState{ undefined, missed, hit, killed };
enum boatState { dead, demaged, perfect };

class RandomEngine{
	private:
		RandomEngine(const RandomEngine&);
		const RandomEngine& operator=(const RandomEngine&);
	public:
		RandomEngine();
		~RandomEngine();
		Coords getRandomCoords(int, int);
		int getRandomInt(int, int);
};

template<class T>
class List{
	// public type declaration to use pointers to the type outside of the class
	public:
		struct Node{
			T value;
			Node* prev;
		};
		Node* head;
	public:
		List();
		List(const List&);
		~List();
		void push(const T&);
		const List& operator=(const List&);
};

class DirVectors{
	private:
	static Coords dirs[4];
	public:
	DirVectors();
	~DirVectors();
	static Coords getDir(int);
	static Coords getDir(sides);
};

template<class T>
List<T>::List(){
	head = NULL; 
}

template<class T>
List<T>::~List(){
	while(head){
		Node* tmp = head;
		head = head->prev;
		delete tmp;
	}
}

template<class T>
List<T>::List(const List& listIn){
	Node* h = listIn.head;
	while(h){
		Node* tmp = new Node;
		tmp->value = h.value;
		tmp->prev = head;
		head = tmp;
		h = h->prev;
	}
}

template<class T>
const List<T>& List<T>::operator=(const List& listIn){
	Node* h = listIn.head;
	while(h){
		Node* tmp = new Node;
		tmp->value = h->value;
		tmp->prev = head;
		head = tmp;
		h = h->prev;
	}
	return *this;
}

template<class T>
void List<T>::push(const T& el){
	Node* tmp = new Node;
	tmp->value = el;
	tmp->prev = head;
	head = tmp;
}

#endif
