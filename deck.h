#ifndef DECK_H_SENTRY
#define DECK_H_SENTRY
#include "coords.h"
class Deck{
	private:
		bool hit;
		Coords location;
	public:
		Deck();
		Deck(Coords);
		Deck(const Deck&);
		~Deck();
		bool wasHit() const;
		void setHit();
		void setLocation(Coords);
		Coords getLocation() const;
		const Deck& operator=(const Deck&);
#ifdef DEBUG
		void printDeck();
#endif
};
#endif
