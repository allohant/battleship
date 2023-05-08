#include "engine.h"

Engine::Engine(int maxDeckSize, int FieldSize) : player(maxDeckSize, FieldSize), ai(maxDeckSize, FieldSize){
	scores = new int[2];
	scores[0] = 0;
	scores[1] = 0;
	winner = 0;
	gameOver = false;
	hitBoat = NULL;
}

Engine::~Engine(){
	delete [] scores;
}

void Engine::play(){
	Char** players = new Char*[2]; 
	players[0] = &ai;
	players[1] = &player;
	// game starts with the player (not AI)
	int currentPlayer = 1;
	Coords nextMove;
	hitState hitRes = undefined;
	render();
	while(!gameOver){
		while ( (hitRes = makeMove(players[(currentPlayer+1)%2], nextMove = getNextMove(currentPlayer))) > missed){
			// If hit or killed enemy
			// for AI only
			players[(currentPlayer+1)%2]->markHit(nextMove, hitRes);
			players[currentPlayer]->setMoveResult(hitBoat, hitRes);
			// if inside loop, hit was successful, score++
			scores[currentPlayer]++;
			render();
			// check if boats left. Else end game
			if(gameOver){
				winner = currentPlayer;
				render();
				break;
			}
			// move results processing
		}
		// when hit failed
		players[(currentPlayer+1)%2]->markHit(nextMove, hitRes);
		players[currentPlayer]->setMoveResult(hitBoat, hitRes);
		render();
		currentPlayer = (currentPlayer+1)%2;
	}
	delete [] players;
}

hitState Engine::makeMove(Char* enemy, Coords nextMove){
	 if(hitBoat = enemy->tryHitBoat(nextMove)){
		 if(hitBoat->getState() == dead){
			 if(!enemy->getBoatsAlive())
				 gameOver = true;
			 return killed;
		 }
		 else
			 return hit;
	 }
	 return missed;
}

Coords Engine::getNextMove(int playerNum){
		if(playerNum){
			// get user input to nextMove or hitCoords
			Coords inp = getInput();
			player.setHitCoords(inp);
			return inp;
		} else {
			// write
			return ai.getNextMove();
		}
}
