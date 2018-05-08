#include "functions.h"

void init_dictionary(char* window, char c);

std::string decompress(std::vector<Triple> coded) {
    char window [WINDOW_PARAMS.WINDOW_SIZE];
    // initialize dictionary part of window with the first symbol
    init_dictionary(window, coded.at(0).S);

    int pos = 0;
    int curr_dict_len = 1;
    for(int i = 1; i < coded.size(); i++){
        // for each triple check how far to go back in the sequence
        // copy given number of characters to current position
        // append next character
        // if the length can 
        int dict_pos = pos - coded.at(i).P;

        //see how many times to repeat copying out of window substr
        // int substr_repetition_count = coded.at(i).C/(coded.at(i).P);
        // int subst_repetition_rest = coded.at(i).P % 
        // for(int rep_i = 0; rep_i < substr_repetition_count; rep_i++){
            for(int d_i = 0; d_i < coded.at(i).C ; d_i++ ){
                window[pos+d_i] = window[dict_pos+d_i];
            }
        // }
        // if(coded.at(i).C == 0){
        //     pos++;
        // }
        if(coded.at(i).C == 0) pos++; // if no movement, move manually
        pos += coded.at(i).C;
        window[pos] = coded.at(i).S;
        pos++;
    }

    //return part of window with decoded string
    return std::string(&window[0], pos);
}

//init window, which contains dictionary and input buffer with first character
void init_dictionary(char* window, char c){
    for(int i=0; i < WINDOW_PARAMS.DICTIONARY_SIZE; i++){
        window[i] = c;
    }
}

