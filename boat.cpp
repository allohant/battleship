#include "boat.h"
#include "utility.h"
#ifdef DEBUG
#include <iostream>
#endif
Boat::Boat(){
	size = 0;
	decksHitNum = 0;
	state = perfect;
}

Boat::Boat(const Boat& bIn){
	size = bIn.size;
	decksHitNum = bIn.decksHitNum;
	decks = bIn.decks;
}
Boat::Boat(int sizeIn, Coords* decksCoords){
	size = sizeIn;
	decksHitNum = 0;
	state = perfect;
	for(int i = 0; i < size; i++){
		decks.push(decksCoords[i]);
	}
}

Boat::~Boat(){}

void Boat::setSize(int sizeIn) {
	if(!size){
		size = sizeIn;
	}
}

int Boat::getSize() const { return size; }

boatState Boat::getState() const { return state;}

void Boat::addDeck(Coords cIn){
	decks.push(Deck(cIn));
	size++;
}

bool Boat::hitDeck(Coords cIn){
	List<Deck>::Node* h = decks.head;
	while(h){
		if(h->value.getLocation() == cIn){
			h->value.setHit();
			state = demaged;
			decksHitNum++;
			if(decksHitNum == size)
				state = dead;
			return true;
		}
		h = h->prev;
	}
	return false;
}

bool Boat::hasDeck(Coords cIn) const {
	List<Deck>::Node* h = decks.head;
	while(h){
		if(h->value.getLocation() == cIn)
			return true;
		h = h->prev;
	}
	return false;
}

const Boat& Boat::operator=(const Boat& bIn){
	size = bIn.size;
	decksHitNum = bIn.decksHitNum;
	decks = bIn.decks;
	return *this;
}
#ifdef DEBUG
void Boat::printBoat(){
	List<Deck>::Node* h = decks.head;
	while(h){
		h->value.printDeck();
		std::cout << std::endl;
		h = h->prev;
	}
}
#endif
