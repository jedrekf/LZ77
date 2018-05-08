#include "functions.h"
#include <iostream>

Window WINDOW_PARAMS = {4096, 2048, 2048};

int main(int argc, char* argv[]){
	// uncomment below 3 lines to use arguments
	// auto args = get_args(argc, argv);
	// std::string str = load_from_file(std::get<0>(args));
	// std::cout << "Input is: " << str << "\n";

	std::vector<Triple> encoded;
	encoded.push_back(Triple{0,0,'a'});
	encoded.push_back(Triple{0,0,'b'});
	encoded.push_back(Triple{2,2,'c'});
	
	std::cout << "Encoded string is: aab" << '\n';

	auto decompressed_str = decompress(encoded);

	std::cout << "Decoded string is: " <<  decompressed_str << '\n';

	return 0;
}

void print_usage(char* argv[]){
	std::cerr << "Usage: first arg: " << " Path to the file." << std::endl;
	std::cerr << "Usage: second arg: " << " Selected behaviour 'compress' or 'decompress'. Default 'compress'." << std::endl;
}

std::tuple<std::string, bool> get_args(int argc, char* argv[]){
	if(argc < 2 || argc > 3){
		print_usage(argv);
		exit(-1);
	}
	bool compress = true;

	if(argc == 3 && (argv[2] != "decompress" || argv[2] != "compress")){
		print_usage(argv);
		exit(-1);
	}else{
		if(argv[1] == "decompress"){
			std::cout << "Decompressing " << argv[1] << "\n";
			compress = false;
		}else{
			std::cout << "Compressing " << argv[1] << "\n";
		}
	}
	auto file_path = argv[1];

	return std::make_tuple(file_path, compress);
}