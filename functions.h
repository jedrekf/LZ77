#include <string>
#include <vector>
#include <tuple>
#include "structs.h"

//save encoded 
void save_encoded_to_file(std::vector<Triple> encoded, std::string path);

// save string to file
void save_to_file(std::string content, std::string path);

//load file content and return as string
std::string load_from_file(std::string path);

//decompresses to string from a vector of Triples
std::string decompress(std::vector<Triple> coded);

std::vector<Triple> get_compressed_data(std::string input);

void compress_input(std::string input, std::string path);

std::tuple<std::string, std::string, bool> get_args(int argc, char* argv[]);

std::vector<Triple> load_encoded_from_file(std::string path);