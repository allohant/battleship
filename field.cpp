#include "field.h"
#ifdef DEBUG
#include <iostream>
#endif

Field::Field(int fieldSizeIn){
	fieldSize = fieldSizeIn;
	field = new int*[fieldSize];
	for(int i = 0; i < fieldSize; i++){
		field[i] = new int[fieldSize];
	}
	// Initialize array
	for(int i = 0; i < fieldSize; i++){
		for(int j = 0; j < fieldSize; j++){
			field[i][j] = 0;
		}
	}
}

Field::Field(int fieldSizeIn, int** fieldArr){
	fieldSize = fieldSizeIn;
	field = new int*[fieldSize];
	for(int i = 0; i < fieldSize; i++){
		field[i] = new int[fieldSize];
	}
	// Initialize array
	for(int i = 0; i < fieldSize; i++){
		for(int j = 0; j < fieldSize; j++){
			field[i][j] = fieldArr[i][j];
		}
	}
}

Field::~Field(){
	for(int i = 0; i < fieldSize; i++){
		delete [] field[i];
	}
	delete [] field;
}


// having a boat object, reflect its coordinated in the field and its surrounding with -1
void Field::addBoatWithLimits(const Boat& b){
	int deckSize = b.getSize();
	List<Deck>::Node* decks = b.decks.head;
	while(decks){
		Coords deckC = decks->value.getLocation();
		field[deckC.getH()][deckC.getW()] = deckSize;
		setDeckLimits(deckC);
		decks = decks->prev;
	}
}

void Field::addBoat(const Boat& b){
	int deckSize = b.getSize();
	List<Deck>::Node* decks = b.decks.head;
	while(decks){
		Coords deckC = decks->value.getLocation();
		field[deckC.getH()][deckC.getW()] = deckSize;
		decks = decks->prev;
	}
}

// mark -1 all cell, surrounding the deck (one point)
void Field::setDeckLimits(const Coords& c){
	Coords currentPoint = c - 1;
	int w = 0, h = 0;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(pointIsWithinFieldLimits(currentPoint)){
				w = currentPoint.getW();
				h = currentPoint.getH();
				if(!field[h][w])
					field[h][w] = -1;
			}
			currentPoint = currentPoint + Coords(0, 1); 
		}
		currentPoint = currentPoint + Coords(1, -3);
	}
}

bool Field::pointsAreAvailable(int boatSize, Coords* boatCoords){
	for(int i = 0; i < boatSize; i++)
		if(!pointIsAvailable(boatCoords[i]))
			return false;
	return true;
}

// point is available if there is 0 at its coordinates
bool Field::pointIsAvailable(const Coords& c) const{
	if(pointIsWithinFieldLimits(c))
		if(field[c.getH()][c.getW()] == 0)
			return true;
	return false;
}

Coords Field::getBoatDirection(Coords cIn) const{
	Coords dirVec, nearCoords;
	for(int i = 0; i < 4; i++){
		dirVec = DirVectors::getDir(i);
		nearCoords = cIn + dirVec;
		if(pointIsWithinFieldLimits(nearCoords) && field[nearCoords.getH()][nearCoords.getW()] == field[cIn.getH()][cIn.getW()])
			return dirVec;
	}
	return Coords(-1, -1);
}

// point is within 10x10 field
bool Field::pointIsWithinFieldLimits(const Coords& c) const {
	if( (c.getH() >= 0 && c.getH() < fieldSize) && (c.getW() >= 0 && c.getW() < 10) )
		return true;
	return false;
}

#ifdef DEBUG
void Field::printFlatField(){
	std::cout << " ";
	for(int i = 0; i < fieldSize; i++){
			std::cout << (char)(i+65);
	}
	std::cout << std::endl;
	for(int i = 0; i < fieldSize; i++){
		std::cout << i;
		for(int j = 0; j < fieldSize; j++){
			std::cout << ((field[i][j] == -1) ? 0 : field[i][j]) ;
		}
		std::cout << std::endl;
	}
}
#endif

int Field::getSize() const { return fieldSize; }

int& Field::operator()(int i, int j){
	return field[i][j];
}

int& Field::operator()(Coords cIn){
	return field[cIn.getH()][cIn.getW()];
}

void Field::removeBoat(const Boat& b){
	List<Deck>::Node* decks = b.decks.head;
	while(decks){
		Coords deckC = decks->value.getLocation();
		field[deckC.getH()][deckC.getW()] = 0;
		decks = decks->prev;
	}
}
