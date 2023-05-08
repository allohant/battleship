#include "deck.h"
#ifdef DEBUG
#include <iostream>
#endif

Deck::Deck() : hit(0), location(0, 0){}

Deck::Deck(Coords cIn) : hit(0), location(cIn){}

Deck::Deck(const Deck& dIn){
	hit = dIn.hit;
	location = dIn.location;
}

Deck::~Deck(){}

bool Deck::wasHit() const { return hit; }

void Deck::setHit(){ hit = true; }

void Deck::setLocation(Coords cIn){ location = cIn; }

Coords Deck::getLocation() const { return location; }

const Deck& Deck::operator=(const Deck& dIn){
	hit = dIn.hit;
	location = dIn.location;
	return *this;
}

#ifdef DEBUG
void Deck::printDeck(){
	std::cout << "h: " << location.getH() << "; w: " << location.getW();
}
#endif
