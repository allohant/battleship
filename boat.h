#ifndef BOAT_H_SENTRY
#define BOAT_H_SENTRY
#include "deck.h"
#include "coords.h"
#include "utility.h"

class Boat{
	private:
		int size;
		int decksHitNum;
		boatState state;
		List<Deck> decks;
	public:
		Boat();
		// args: number of decks, array of decks coordinates
		Boat(int, Coords*);
		Boat(const Boat&);
		~Boat();

		int getSize() const;
		boatState getState() const;
		void addDeck(Coords);
		bool hitDeck(Coords);
		bool hasDeck(Coords) const;
		void setSize(int);
		const Boat& operator=(const Boat&);
#ifdef DEBUG
		void printBoat();
#endif
		friend class Field;
};

#endif
