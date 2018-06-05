#include "functions.h"
#include <sstream>
#include <iostream>

void init_dictionary(char* window, char c);


/* Decompresses given vector of Triples into a string
*
* IDEA:
* for each triple check how far to go back in the sequence
* copy given number of characters to current position
* append next character
*/
std::string decompress(std::vector<Triple> coded) {
    char window [WINDOW_PARAMS.WINDOW_SIZE];
    std::stringstream outputss;
    
    init_dictionary(window, coded.at(0).S);

    int head = 1;
    int dict_pos;
    for (std::vector<Triple>::iterator it = std::next(coded.begin()) ; it != coded.end(); ++it){
    //for(int i = 1; i < coded.size(); i++){
        Triple triple = *it;
        dict_pos = head - triple.P;
        if(dict_pos < 0){
            // if we have to go back before the first character in window we wrap to window end
            dict_pos = WINDOW_PARAMS.WINDOW_SIZE + dict_pos;
        }

        //copy
        for(int d_i = 0; d_i < triple.C ; d_i++ ){
            window[head] = window[dict_pos];
            head++;
            dict_pos++;
            //making a window array act circular
            if(head >= WINDOW_PARAMS.WINDOW_SIZE){
                outputss << std::string(&window[0], head); 
                head = 0;
            }
            if(dict_pos >= WINDOW_PARAMS.WINDOW_SIZE){
                dict_pos = 0;
            }
        }

        if(triple.S == '\000'){
            //its EOF
            break;
        }
        window[head] = triple.S;
        head++;
        if(head >= WINDOW_PARAMS.WINDOW_SIZE){
            outputss << std::string(&window[0], head); 
            head = 0;
        }
    }
    
    outputss << std::string(&window[0], head); 
    return outputss.str();
}

// initialize Window with given symbol
void init_dictionary(char* window, char c){
    for(int i=0; i < WINDOW_PARAMS.WINDOW_SIZE; i++){
        window[i] = c;
    }
}

