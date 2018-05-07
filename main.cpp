#include "functions.h"
#include <iostream>

void print_usage(char* argv[]);

int main(int argc, char* argv[]){
	if(argc < 2 || argc > 3){
		print_usage(argv);
		return -1;
	}
	bool compress = true;

	if(argc == 3 && (argv[2] != "decompress" || argv[2] != "compress")){
		print_usage(argv);
		return -1;
	}else{
		if(argv[1] == "decompress"){
			std::cout << "Decompressing " << argv[1] << "\n";
			compress = false;
		}else{
			std::cout << "Compressing " << argv[1] << "\n";
		}
	}
	auto file_path = argv[1];

	


	std::string str = load_from_file(file_path);
	std::cout << "Input is: " << str << "\n";

	return 0;
}

void print_usage(char* argv[]){
	std::cerr << "Usage: first arg: " << " Path to the file." << std::endl;
	std::cerr << "Usage: second arg: " << " Selected behaviour 'compress' or 'decompress'. Default 'compress'." << std::endl;
}