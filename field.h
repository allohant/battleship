#ifndef FIELD_H_SENTRY
#define FIELD_H_SENTRY
#include "boat.h"
#include "utility.h"

class Field{
	private:
		// flatField is an array of integers representing pleyer fild and used for the purpose of easier rendering
		int fieldSize;
		int** field;

		// Block copy and assignment
		Field(const Field&);
		const Field& operator=(const Field&);

		// set "delimiters" (-1) for one deck with the center, defined by the argument
		void setDeckLimits(const Coords&);
		bool pointIsWithinFieldLimits(const Coords&) const;

	public:
		// arg: fieldSize
		Field(int);
		// args: fieldSize and fieldArr
		Field(int, int**);
		~Field();
#ifdef DEBUG
		void printFlatField();
#endif
		int getSize() const;
		void addBoatWithLimits(const Boat&);
		void addBoat(const Boat&);
		bool pointIsAvailable(const Coords&) const;
		bool pointsAreAvailable(int, Coords*);
		// For refererence to the coordinates as to array
		int& operator()(int, int);
		int& operator()(Coords);
		void removeBoat(const Boat&);
		Coords getBoatDirection(Coords cIn) const;
};
#endif
