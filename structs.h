
// structure for compression
struct Triple {
    int     P; // index
    int     C; // length of substring
    char    S; // symbol
};

// I guess dictionary and input buffor sizes should be equal so both are half of window size.
int WINDOW_SIZE = 4096;
int DICTIONARY_SIZE = 2048;
int INPUT_BUFFOR_SIZE = 2048;