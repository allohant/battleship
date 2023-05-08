#include "textengine.h"
#include <iostream>
TextEngine::TextEngine(int dNum, int fieldSize, const char* nameOfFile) : Engine::Engine(dNum, fieldSize) {
	int** flatField = new int*[fieldSize];
	for(int i = 0; i < fieldSize; i++){
		flatField[i] = new int[fieldSize];
	}
	// Initialize array
	for(int i = 0; i < fieldSize; i++){
		for(int j = 0; j < fieldSize; j++){
			flatField[i][j] = 0;
		}
	}

	#ifdef DEBUG
	std::cout<< "DEBUG: PlayerField:\n";
	player.getCharField().printFlatField();
	#endif

	FILE *inFile;
	inFile = fopen(nameOfFile, "r");	
	while(!inFile){
		inFile = fopen(nameOfFile, "r");	
		if(!inFile){
			std::cout << "Can't open the file '"<< nameOfFile << "'. Enter correct filename:" << std::endl;
			char newFilename[50];
			std::cin >> newFilename;
			nameOfFile = newFilename;
		}
	}
	char ch = 0;
	int i = 0, j = 0;
	while((ch = fgetc(inFile)) != EOF){

		if(i>fieldSize){
			i=0;
		}
		if(j>fieldSize){
			j=0;
		}
		switch(ch){
			case 32:
				if(j > 0 && i > 0)
					flatField[i-1][j-1] = 0;
				j++;
				break;
			case 10:
				i++;
				j = 0;
				break;
			default:
				if(j > 0 && i > 0)
					flatField[i-1][j-1] = ch - '0';
				j++;
				break;
		}
	}
	fclose(inFile);
	player.genField(flatField);
	for(int i = 0; i < fieldSize; i++){
		delete [] flatField[i];
	}
	delete [] flatField;
};

TextEngine::~TextEngine(){};

void TextEngine::render(){
	Field& pf = player.getCharField();
	Field& ef = player.getEnemyField();
	int size = pf.getSize();
	int symb = 0;
	std::cout << "Your field:" << std::endl;
	std::cout << " ";
	for(int i = 0; i < size; i++){
			std::cout << (char)(i+65);
	}
	std::cout << std::endl;
	for(int i = 0; i < size; i++){
		std::cout << i;
		for(int j = 0; j < size; j++){
			symb = getPrintCharPlayer(pf(i, j));
			std::cout << (char)symb;
		}
		std::cout << std::endl;
	}
	std::cout << "Enemy field:" << std::endl;
	std::cout << " ";
	for(int i = 0; i < size; i++){
			std::cout << (char)(i+65);
	}
	std::cout << std::endl;
	for(int i = 0; i < size; i++){
		std::cout << i;
		for(int j = 0; j < size; j++){
			symb = getPrintCharAI(ef(i, j));
			std::cout << (char)symb;
		}
		std::cout << std::endl;
	}
	std::cout << "Your score: " << scores[1] << "\t Computer score: " << scores[0] << std::endl;
	if(gameOver)
		std::cout << "GAME OVER, " << (winner ? "YOU" : "COMPUTER") << " WON WITH THE SCORE: " << scores[winner] << ":" << scores[(winner+1)%2] << std::endl;
}

Coords TextEngine::getInput(){
	char x;
	int intX;
	int y;
	int size = player.getCharField().getSize();
	std::cout << "Yout next move (x, y): " << std::endl;
	std::cin >> x >> y;
	intX = x - 65;
	while(intX < 0 || intX >= size || y < 0 || y >= size){
		std::cout << "Coordinates are out of playfield" << std::endl;
		std::cout << "Yout next move (x, y): " << std::endl;
		std::cin >> x >> y;
		intX = x - 65;
	}
	return Coords(y, intX);
}


// When player field is rendered
char TextEngine::getPrintCharPlayer(int symbIn){
	switch ( symbIn ){
		case -4:
			return 'x';
			break;
		case -3:
			return 'x';
			break;
		case -2:
			return '*';
			break;
		case -1:
			return 'x';
			break;
		case 0:
			return ' ';
			break;
		default:
			return '#';
			break;
	}
}


char TextEngine::getPrintCharAI(int symbIn){
	switch ( symbIn ){
		case -3:
			return 'x';
			break;
		case -2:
			return '*';
			break;
		case -1:
			return '*';
			break;
		case 0:
			return ' ';
			break;
		default:
			return 'o';
			break;
	}
}
