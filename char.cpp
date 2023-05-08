#include "char.h"
#include "utility.h"
#ifdef DEBUG
#include <iostream>
#endif

Char::Char(int maxDeckSizeIn, int fieldSizeIn) : fd(fieldSizeIn), efd(fieldSizeIn){
	maxDeckSize = maxDeckSizeIn;
	boatsAlive = 0;
	for(int i = 0; i < maxDeckSizeIn; i++)
		boatsAlive += maxDeckSize - i;
	// Initialize array
	boats = new List<Boat>[maxDeckSize];
}

Char::~Char(){ delete [] boats; }

#ifdef DEBUG
void Char::printFlatField(){
	int fieldSize = fd.getSize();
	std::cout << " ";
	for(int i = 0; i < fieldSize; i++){
			std::cout << (char)(i+65);
	}
	std::cout << std::endl;
	for(int i = 0; i < fieldSize; i++){
		std::cout << i;
		for(int j = 0; j < fieldSize; j++){
			std::cout << ((fd(i,j) == -1) ? 0 : fd(i,j)) ;
		}
		std::cout << std::endl;
	}
}

void Char::printBoatsList(){
	std::cout << "Inside boats list" << std::endl;	
	for(int i = 0; i < maxDeckSize; i++){
		List<Boat>::Node* currNode = boats[i].head;
		while(currNode){
			std::cout << i+1 << ":" << std::endl;
			currNode->value.printBoat();
			currNode = currNode->prev;
			std::cout << " _______________ " << std::endl;
		}
		std::cout << std::endl;
	}
}
#endif

Boat* Char::getBoatByDeckCoords(Coords c){
	for(int i = 0; i < maxDeckSize; i++){
		List<Boat>::Node* currNode = boats[i].head;
		while(currNode){
			if(currNode->value.hasDeck(c))
				return &(currNode->value);
			currNode = currNode->prev;
		}
	}
	return NULL;
}

Boat* Char::tryHitBoat(Coords c){
	for(int i = 0; i < maxDeckSize; i++){
		List<Boat>::Node* currNode = boats[i].head;
		while(currNode ){
			if(currNode->value.getState()!=dead && currNode->value.hitDeck(c)){
				if(currNode->value.getState()==dead)
					boatsAlive--;
				return &(currNode->value);
			}
			currNode = currNode->prev;
		}
	}
	return NULL;
}

// Game Functions 
int Char::getBoatsAlive(){ return boatsAlive; }

Field& Char::getCharField(){ return fd; }

Field& Char::getEnemyField(){ return efd; }

void Char::markHit(Coords cIn, hitState stIn){
		switch (stIn) {
			case hit:
				fd(cIn) = -3;
				break;
			case missed:
				fd(cIn) = -2;
				break;
			case killed:
				fd(cIn) = -4;
				break;
		}
}
