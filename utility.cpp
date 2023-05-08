#include "utility.h"
#include <time.h>
#include <stdlib.h>

// Should be called only once
RandomEngine::RandomEngine(){
	srand(time(NULL));
}
RandomEngine::~RandomEngine(){};

Coords RandomEngine::getRandomCoords(int lowerLimit, int upperLimit){
	// From 0 to 9 (incl)upper
	int width = getRandomInt(lowerLimit, upperLimit);	
	int height = getRandomInt(lowerLimit, upperLimit);	
	return Coords(height, width);
}

int RandomEngine::getRandomInt(int from, int to){
	return rand() % (to + 1 - from) + from;
}

Coords DirVectors::dirs[4] = {Coords(1,0), Coords(0,1), Coords(-1,0), Coords(0,-1)};

Coords DirVectors::getDir(sides sIn){
	return dirs[sIn];
}

Coords DirVectors::getDir(int iIn){
	return dirs[iIn];
}
