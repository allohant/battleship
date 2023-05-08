#include "coords.h"

Coords::Coords(){
	w = 0;
	h = 0;
}

Coords::Coords(int hIn, int wIn){
	w = wIn;
	h = hIn;
}

Coords::Coords(const Coords& coordsIn){
	w = coordsIn.getW();
	h = coordsIn.getH();
}

Coords::Coords(int num){
	w = num;
	h = num;
}

Coords::~Coords(){};

void Coords::setW(int wIn){
	w = wIn;
}

void Coords::setH(int hIn){
	h = hIn;
}

void Coords::set(int hIn, int wIn){
	w = wIn;
	h = hIn;
}

void Coords::set(const Coords& coordsIn){
	w = coordsIn.getW();
	h = coordsIn.getH();
}

int Coords::getW() const { return w; }

int Coords::getH() const { return h; }

Coords& Coords::operator=(const Coords& coordsIn){
	w = coordsIn.getW();
	h = coordsIn.getH();
	return *this;
}

Coords operator+(const Coords& a, const Coords& b){
	return Coords(a.h + b.h, a.w + b.w);
}
 
Coords operator-(const Coords& a, const Coords& b){
	return Coords(a.h - b.h, a.w - b.w);
}

Coords operator*(const Coords& a, const Coords& b){
	return Coords(a.h * b.h, a.w * b.w);
}

bool operator==(const Coords& a, const Coords& b){
	return (a.h == b.h) && (a.w == b.w);
}

bool operator!=(const Coords& a, const Coords& b){
	return !((a.h == b.h) && (a.w == b.w));
}

