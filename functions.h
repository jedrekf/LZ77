#include <string>
#include <vector>
#include <tuple>
#include "structs.h"

//prints usage info
void print_usage(char* argv[]);

//gets arguments from command line
std::tuple<std::string, bool> get_args(int argc, char* argv[]);

// save string to file
void save_to_file(std::string content, std::string path);

//load file content and return as string
std::string load_from_file(std::string path);

//decompresses to string from a vector of Triples
std::string decompress(std::vector<Triple> coded);

