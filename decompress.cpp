#include "functions.h"

void init_dictionary(char* window, char c);

std::string decompress(std::vector<Triple> coded) {
    char window [WINDOW_PARAMS.WINDOW_SIZE];
    // initialize dictionary part of window with the first symbol
    init_dictionary(window, coded.at(0).S);



    for(int i = 0; i < coded.size(); i++){

    }


    return "a";
}


//init window, which contains dictionary and input buffer with first character
void init_dictionary(char* window, char c){
    for(int i=0; i < WINDOW_PARAMS.DICTIONARY_SIZE; i++){
        window[i] = c;
    }
}

