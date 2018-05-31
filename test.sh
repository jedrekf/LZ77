#!/bin/bash

RED='\033[0;31m'
NC='\033[0m' # No Color

echo "rebuilding project..."
make

echo ; echo ; echo ;
#print variable on a screen
echo "Launching tests for LZ77 algorithm..."


for fn in `ls -d -1 ./tests/input_files/*.*`; do
    echo "the next file is $fn"
    file_len=$(wc -c <"$fn")
    echo "File length: "$file_len
    
    temp_enc=fn"_enc"
    temp_dec=fn"_dec"
    
    echo "Running compression..."
    ./main $fn $temp_enc "compress"
    if [ $? -ne 0 ]
    then
        echo "${RED}ERROR:{$NC} file not successfuly encoded: $fn"
    fi
    ./main $temp_enc $temp_dec "decompress"
    if [ $? -ne 0 ]
    then
        echo -e "${RED}ERROR:{$NC} file not successfuly decoded: $fn"
    fi

    #compare initial file with the compressed -> decompressed one
    diff $fn $temp_dec
    if [ $? -ne 0 ]
    then
        echo -e "${RED}ERROR:${NC} Decoded file is not the same as the input file $fn. Something went wrong. :("
    fi

    `rm $temp_enc $temp_dec`
done

