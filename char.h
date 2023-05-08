#ifndef CHAR_H_SENTRY
#define CHAR_H_SENTRY
#include "coords.h"
#include "boat.h"
#include "utility.h"
#include "field.h"

class Char{
	protected:
		// char field
		Field fd;
		// enemy field
		Field efd;
		// Boats array to easier control state of each boat and operations with them
		int maxDeckSize;
		int boatsAlive;
		// a list instead of an array to avoid creating boats without decks 
		List<Boat>* boats;

		Boat* getBoatByDeckCoords(Coords);
		void addBoatToBoatsList(const Boat& b);
		
		// Block copy and assignment
		Char(const Char&);
		const Char& operator=(const Char&);

	public:
		Char(int, int);
		virtual ~Char();
#ifdef DEBUG
		void printFlatField();
		void printBoatsList();
#endif
		int getBoatsAlive();
		Boat* tryHitBoat(Coords);
		// Game-related functions
		void markHit(Coords, hitState);
		virtual void setMoveResult(Boat*, hitState) = 0;
		Field& getCharField();
		Field& getEnemyField();
};
#endif
