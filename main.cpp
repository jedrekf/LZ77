#include "functions.h"
#include <iostream>
#include <ctime>
#include <chrono>

Window WINDOW_PARAMS = {4096, 2048, 2048};

int main(int argc, char* argv[]) {
	auto args = get_args(argc, argv);
	auto output_file_path = std::get<1>(args);
	
	double elapsed_time;

	bool compress = std::get<2>(args);
	try{
		if(compress) {
			auto data = load_from_file(std::get<0>(args));

			std::clock_t c_start = std::clock();
			auto result = get_compressed_data(data);
			std::clock_t c_end = std::clock();
			elapsed_time = 1000.0 * (c_end-c_start) / CLOCKS_PER_SEC;
			std::cout << elapsed_time*1000000 << std::endl;

			save_encoded_to_file(result, output_file_path);
		} else {
			auto data = load_encoded_from_file(std::get<0>(args));
			std::clock_t c_start = std::clock();
			auto decompressed_str = decompress(data);
			std::clock_t c_end = std::clock();
			elapsed_time = 1000.0 * (c_end-c_start) / CLOCKS_PER_SEC;
			std::cout<< elapsed_time*1000000 <<std::endl;

			save_to_file(decompressed_str, output_file_path);
		}
	}catch(const std::exception& e){
		std::cout << e.what() << std::endl;
		exit(-1);
	}

	return 0;	
}

void print_usage(char* argv[]) {
	std::cerr << "Usage: first arg: " << " Path to the file." << std::endl;
	std::cerr << "Usage: second arg: " << " Path to the output file. (it will be created or overwritten)" << std::endl;
	std::cerr << "Usage: third arg: " << " Selected behaviour 'compress' or 'decompress'" << std::endl;
}

std::tuple<std::string, std::string, bool> get_args(int argc, char* argv[]) {
	if(argc != 4) {
		print_usage(argv);
		exit(-1);
	}
	std::string purpose = argv[3];
	bool compress;
	if(purpose == "decompress") {
		compress = false;
	}
	else if(purpose == "compress") {
		compress = true;
	} else {
		print_usage(argv);
		exit(-1);
	}

	auto file_path = argv[1];
	auto output_file_path = argv[2];
	return std::make_tuple(file_path, output_file_path, compress);
}