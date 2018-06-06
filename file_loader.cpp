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

void save_encoded_to_file(std::vector<Triple> encoded, std::string path){
	auto out = std::ofstream(path);

	for(int i = 0; i < encoded.size(); i++) {
		out << encoded[i].P << '\037' << encoded[i].C << '\037' << encoded[i].S << '\035';
	}
	out.flush();
	out.close();
}

size_t split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    size_t pos = txt.find( ch );
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while( pos != std::string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos ) );
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    // Add the last one
    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );

    return strs.size();
}

std::vector<Triple> load_encoded_from_file(std::string path){
	//each line looks like this
	//(P,C,S)
	std::ifstream file(path);
	std::string line;
	std::vector<Triple> triples;
	std::vector<std::string> v;
	while(std::getline(file, line, '\035')) {
		split(line, v, '\037');
		Triple triple = Triple {
				std::stoi(v[0]),
				std::stoi(v[1]),
				v[2][0] 
			};

		triples.push_back(triple);
	}
	return triples;
}

void save_to_file(std::string content, std::string path) {
	auto out = std::ofstream(path);
	out << content;
	out.close();
}
