#include "aichar.h"
#include <iostream>

AIChar::AIChar(int maxDeckSize, int fieldSize) : Char::Char(maxDeckSize, fieldSize) {
	genRandomField();
	#ifdef DEBUG
	std::cout<< "DEBUG: AIField:\n";
	fd.printFlatField();
	printBoatsList();
	#endif
	hitDir = 0;
}

AIChar::~AIChar(){};

// generate an array with randomly placed boats on it
void AIChar::genRandomField(){
	for(int i = 0; i < maxDeckSize; i++){
		for(int j = 0; j < maxDeckSize-i; j++){
			// maxDeckSize - i times create i+1 sized boat
			Boat b = genBoat(i+1);
			// for 0 to b.size reflect points at flatField and  mark surrounding points as -1
			fd.addBoatWithLimits(b);
			boats[i].push(b);
			// set respective cell
		}
	}
}

Boat AIChar::genBoat(int decksNum){
	Coords *deckCoords = new Coords[decksNum];
	genBoatCoords(decksNum, deckCoords);
	Boat b(decksNum, deckCoords);
	delete [] deckCoords;
	return b;
}	

void AIChar::genBoatCoords(int boatSize, Coords* deckCoords){
	do{
		genRandomCoords(boatSize, deckCoords);
	} while (!fd.pointsAreAvailable(boatSize, deckCoords));
}

void AIChar::genRandomCoords(int boatSize, Coords* deckCoords){
	// TODO create random engine
	// get random start
	Coords start = re.getRandomCoords(0, fd.getSize()-1);
	// add first deck to the array
	deckCoords[0] = start;
	// get random direction
	Coords vec = DirVectors::getDir(re.getRandomInt(0, 3));
	// get coordinates for the rest of the decks
	for(int i = 1; i < boatSize; i++){
		deckCoords[i] = start + vec;
		start = deckCoords[i];
	}
}

// Game-related functions
Coords AIChar::getNextMove(){
	if(firstHitRes < hit){
		// find random coordinate available from enemy field, assign it to firstHit
		while(!efd.pointIsAvailable(firstHit = re.getRandomCoords(0, efd.getSize()-1)));
		return firstHit;
	} else if(secondHitRes < hit){
		// find next coordinate adjacent to the first one and available (not going out of DirVectors boundaries since it is guaranteed such a coordinate exist
		while(!efd.pointIsAvailable(secondHit = firstHit + DirVectors::getDir(hitDir)))
			hitDir = (hitDir+1)%4;
		// increment side for the next iteration if this fails
		return secondHit;
	} else {
		// continue with the same direction
		return secondHit = secondHit + DirVectors::getDir(hitDir);
	}
}

void AIChar::setMoveResult(Boat* bp, hitState hs){
	if(hs == killed){
		// that means boat is not null
		// reflect killed boat on enemy field
		efd.addBoatWithLimits(*bp);
		// reset all move vars to start with random point
		resetMoveStates();
	// if hit was successful
	} else if (hs == hit) { 
		// and this is first hit
		if(firstHitRes < hit)
			// note it to make second hit
			firstHitRes = hs;
		// and this is second hit
		else if(secondHitRes < hit)
			// note it to start trying directions
			secondHitRes = hs;
	// hit was unsuccessful
	} else {
		// and this is first hit - do nothing
		if(firstHitRes < hit){
			firstHitRes = hs;
		// and this is second hit - meaning first was successful, second - missed
		} else if(secondHitRes < hit){
			// direction should be changed
			hitDir = (hitDir+1)%4;
			secondHitRes = hs;
		// next hits were successful, but direction should be changes, since new unsuccessful place found
		} else {
			hitDir = (hitDir+1)%4;
			secondHitRes = hs;
		}
	}
}

void AIChar::resetMoveStates(){
		hitDir = 0;
		firstHitRes = undefined;
		secondHitRes = undefined;
}
