#include "playerchar.h"
#include <iostream>
#include <stdio.h>

// Player Char is created with empty field at first
PlayerChar::PlayerChar(int maxDeckSize, int fieldSize) : Char::Char(maxDeckSize, fieldSize){}

PlayerChar::~PlayerChar(){};
// The field is generated on the basis of the array
void PlayerChar::genField(int** playerFieldArr){
	int fieldSize = Char::fd.getSize();
	Field tempField(fieldSize, playerFieldArr);
	for(int i = 0; i < fieldSize; i++){
		for(int j = 0; j < fieldSize; j++){
			if(tempField(i, j) > 0){
				Boat b = getBoatFromStartingPoint(Coords(i, j), tempField);
				tempField.removeBoat(b);
#ifdef DEBUG2
				tempField.printFlatField();
				std::cout << " **** SEPARATOR **** \n";	
#endif
				fd.addBoat(b);
#ifdef DEBUG2
				fd.printFlatField();
				std::cout << " **** SEPARATOR **** \n";	
#endif
				boats[b.getSize()-1].push(b);
			}
		}
	}
}

Boat PlayerChar::getBoatFromStartingPoint(Coords start, Field& fIn){
	int decksNum = fIn(start);
	Coords *deckCoords = new Coords[decksNum];
	getBoatCoords(start, deckCoords, fIn);
	Boat b(decksNum, deckCoords);
	delete [] deckCoords;
	return b;
}

void PlayerChar::getBoatCoords(Coords startIn, Coords* deckCoords, Field& tempFd){
	int decksNum = tempFd(startIn);
	Coords start = startIn;
	// add first deck to the array
	deckCoords[0] = start;
	if(decksNum > 1){
		// get direction
		Coords vec = tempFd.getBoatDirection(start);
		// get coordinates for the rest of the decks
		for(int i = 1; i < decksNum; i++){
			deckCoords[i] = start + vec;
			start = deckCoords[i];
		}
	}
}

void PlayerChar::setHitCoords(Coords cIn){
	hitCoords = cIn;
}

void PlayerChar::setMoveResult(Boat* bp, hitState hs){
	switch(hs){
		case killed:
			efd.addBoatWithLimits(*bp);
			break;
		case hit:
			// get player hit coords
			efd(hitCoords) = -3;
			break;
		case missed:
			efd(hitCoords) = -1;
			break;
	}
}
