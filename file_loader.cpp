#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fstream>
#include<streambuf>
#include "functions.h"


std::string load_from_file(std::string path) {
	auto in = std::ifstream(path);
	auto str = std::string((std::istreambuf_iterator<char>(in)),
		std::istreambuf_iterator<char>());
	
	return str;
}

void save_to_file(std::string content, std::string path) {
	auto out = std::ofstream(path);
	out << content;
	out.close();
}
