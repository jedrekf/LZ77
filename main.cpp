#include "functions.h"
#include <iostream>

Window WINDOW_PARAMS = {4096, 2048, 2048};

int main(int argc, char* argv[]){
	// uncomment below 3 lines to use arguments
	// auto args = get_args(argc, argv);
	// std::string str = load_from_file(std::get<0>(args));
	// std::cout << "Input is: " << str << "\n";

	auto data = "aabbcabbcdddc";
	std::cout << "Encoding string : "<< data <<std::endl;
	auto result = get_compressed_data(data);
	for(int i=0; i<result.size(); i++)
		std::cout << result[i].P << ' ' << result[i].C << ' ' << result[i].S << std::endl;

	auto decompressed_str = decompress(result);
	std::cout << "Decoded string : " << decompressed_str << std::endl;

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