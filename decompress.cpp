#include "functions.h"

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
    init_dictionary(window, coded[0].S);

    int head = 1;
    for(int i = 1; i < coded.size(); i++){
        
        int dict_pos = head - coded[i].P;

        //copy
        for(int d_i = 0; d_i < coded[i].C ; d_i++ ){
            window[head + d_i] = window[dict_pos + d_i];
        }

        head += coded[i].C;
        window[head] = coded[i].S;
        head++;
    }

    //return part of window with decoded string
    return std::string(&window[0], head);
}

// initialize Window with given symbol
void init_dictionary(char* window, char c){
    for(int i=0; i < WINDOW_PARAMS.WINDOW_SIZE; i++){
        window[i] = c;
    }
}

