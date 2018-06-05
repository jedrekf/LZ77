#include "functions.h"
#include <sstream>

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
    
    init_dictionary(window, coded[0].S);

    int head = 1;
    for(int i = 1; i < coded.size(); i++){
        
        int dict_pos = head - coded[i].P;
        if(dict_pos < 0){
            // if we have to go back before the first character in window we wrap to window end
            dict_pos = WINDOW_PARAMS.WINDOW_SIZE + dict_pos;
        }

        //copy
        for(int d_i = 0; d_i < coded[i].C ; d_i++ ){
            //making a window array act circular
            if(head == WINDOW_PARAMS.WINDOW_SIZE){
                outputss << std::string(&window[0], head); 
                head = 0;
            }
            if(dict_pos == WINDOW_PARAMS.WINDOW_SIZE){
                dict_pos = 0;
            }

            window[head] = window[dict_pos];
            head++;
            dict_pos++;
        }

        auto next_char = coded[i].S;
        if(next_char == '\000'){
            //its EOF
            break;
        }
        window[head] = coded[i].S;
        head++;
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

