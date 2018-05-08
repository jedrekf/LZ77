#ifndef STRUCTS_H
#define STRUCTS_H
// structure for compression
struct Triple {
    int     P; // number of backwards steps to reach the repeating substring
    int     C; // length of substring
    char    S; // symbol
};

// both for compression and decompression these parameters should remain the same
// I guess dictionary and input buffor sizes should be equal so both are half of window size.
// int WINDOW_SIZE = 4096;
// int DICTIONARY_SIZE = 2048;
// int INPUT_BUFFOR_SIZE = 2048;

struct Window {
    int WINDOW_SIZE;
    int DICTIONARY_SIZE;
    int INPUT_BUFFOR_SIZE;
};

extern Window WINDOW_PARAMS;

#endif