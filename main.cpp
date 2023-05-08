#include <iostream>
#include "textengine.h"
using namespace std;
int main(){
	TextEngine te(4, 10, "./input.txt");
	te.play();
	return 0;
}
