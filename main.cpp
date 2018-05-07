#include "functions.h"
#include <iostream>

int main(){
	std::string str = load_from_file("./example.txt");
	std::cout << str << "\n";

	return 0;
}