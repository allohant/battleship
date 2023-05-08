#ifndef PLAYERCHAR_H_SENTRY
#define PLAYERCHAR_H_SENTRY
#include "char.h"
#include "field.h"
class PlayerChar : public Char {
	private:
		Coords hitCoords;
		Boat getBoatFromStartingPoint(Coords, Field&);
		void getBoatCoords(Coords startIn, Coords* deckCoords, Field& tempFd);
		// Block copy and assignment
		PlayerChar(const PlayerChar&);
		const PlayerChar& operator=(const PlayerChar&);

	public:
		PlayerChar(int, int);
		void genField(int**);
		virtual ~PlayerChar();
		void setHitCoords(Coords);
		virtual void setMoveResult(Boat*, hitState);
};
#endif
