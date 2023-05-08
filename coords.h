#ifndef COORDS_H_SENTRY
#define COORDS_H_SENTRY
class Coords{
	private:
		// Width (x)
		int w;
		// Height (y); Coordinates are counted from the top left with y as first coordinate and x as second
		int h;
	public:
		Coords();
		// w (x), h (y)
		Coords(int, int);
		// Create new object on the basis of existing one 
		Coords(const Coords&);
		// Create new object with the same int value assignend to both elements;
		Coords(int);
		~Coords();
		void setW(int);
		void setH(int);
		void set(int, int);
		// Set coordinates of one object to another one
		void set(const Coords&);
		int getW() const;
		int getH() const;
		// Assign coordinates of one object to another one
		Coords& operator=(const Coords&);
		// Basic arithmetic operations for the class
		friend Coords operator+(const Coords&, const Coords&);
		friend Coords operator-(const Coords&, const Coords&);
		friend Coords operator*(const Coords&, const Coords&);
		friend bool operator==(const Coords&, const Coords&);
		friend bool operator!=(const Coords&, const Coords&);
};

Coords operator+(const Coords&, const Coords&);
Coords operator-(const Coords&, const Coords&);
Coords operator*(const Coords&, const Coords&);
bool operator==(const Coords&, const Coords&);
bool operator!=(const Coords&, const Coords&);
#endif
