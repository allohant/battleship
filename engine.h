#ifndef ENGINE_H_SENTRY
#define ENGINE_H_SENTRY
#include "playerchar.h"
#include "aichar.h"
#include "coords.h"
// for hitState
#include "utility.h"

class Engine{
	protected:
		PlayerChar player;
		AIChar ai;
		int *scores;

		int winner;
		bool gameOver;

		Boat* hitBoat;

		Coords getNextMove(int);

		hitState makeMove(Char*, Coords);
		// Block copy and assignment
		Engine(const Engine&);
		const Engine& operator=(const Engine&);

	public:
		// maxDeckSize, fieldSize 
		Engine(int, int);
		virtual ~Engine();
		void play();

		virtual Coords getInput() = 0;
		virtual void render() = 0;
};
#endif
