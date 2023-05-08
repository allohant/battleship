#ifndef AICHAR_H_SENTRY
#define AICHAR_H_SENTRY
// for random numbers
#include "field.h"
#include "char.h"
#include "utility.h"
#include "coords.h"
class AIChar : public Char {
	private:
		// Random numbers generator
		RandomEngine re;

		// Game-related fields
		// First and second hit of player boats by the enemy
		Coords firstHit;
		Coords secondHit;
		int hitDir;
		hitState firstHitRes;
		hitState secondHitRes;

		// methods to generate random boats
		void genRandomField();
		Boat genBoat(int);
		void genBoatCoords(int, Coords*);
		void genRandomCoords(int boatSize, Coords* deckCoords);
		// block copy and assignment
		AIChar(const AIChar&);
		const AIChar& operator=(const AIChar&);
		// Game-realated methods
		void resetMoveStates();

	public:
		AIChar(int, int);
		virtual ~AIChar();

		// Game-related functions
		Coords getNextMove();
		virtual void setMoveResult(Boat*, hitState);

};
#endif
