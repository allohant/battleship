#ifndef TEXTENGINE_H_SENTRY
#define TEXTENGINE_H_SENTRY
#include "coords.h"
#include "engine.h"

class TextEngine : public Engine{
	private:
		char getPrintCharPlayer(int);
		char getPrintCharAI(int);
		// Block copy and assignment
		TextEngine(const TextEngine&);
		const TextEngine& operator=(const TextEngine&);
	public:
		TextEngine(int, int, const char*);
		virtual ~TextEngine();
		virtual void render();
		virtual Coords getInput();
};
#endif
