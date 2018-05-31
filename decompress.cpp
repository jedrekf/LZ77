#include "functions.h"

void init_dictionary(char* window, char c);

std::string decompress(std::vector<Triple> coded) {
    char window [WINDOW_PARAMS.WINDOW_SIZE];
    // initialize dictionary part of window with the first symbol
    init_dictionary(window, coded.at(0).S);


    int head = 1;
    int curr_dict_len = 1;
    for(int i = 1; i < coded.size(); i++){
        // for each triple check how far to go back in the sequence
        // copy given number of characters to current position
        // append next character
        // if the length can 
        int dict_pos = head - coded.at(i).P;

        for(int d_i = 0; d_i < coded.at(i).C ; d_i++ ){
            window[head + d_i] = window[dict_pos + d_i];
        }

        head += coded.at(i).C;
        if(coded.at(i).C == 0) head++; // move head manually if we don't copy anything
        window[head] = coded.at(i).S;
        head++;
    }

    //return part of window with decoded string
    return std::string(&window[0], head);
}

//init window, which contains dictionary and input buffer with first character
void init_dictionary(char* window, char c){
    for(int i=0; i < WINDOW_PARAMS.DICTIONARY_SIZE; i++){
        window[i] = c;
    }
}

