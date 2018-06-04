#!/bin/bash

RED='\033[0;31m'
NC='\033[0m' # No Color

echo "rebuilding project..."
make

echo ; echo ; echo ;
#print variable on a screen
echo "Launching tests for LZ77 algorithm..."


all_tests_passed=true
TESTS_DIR="./tests/"
FULL_TESTS_DIR=$TESTS_DIR"input_files/*.*"
mkdir -p $TESTS_DIR"temp"

declare -a results=()
for fn in `ls -d -1 $FULL_TESTS_DIR`; do
    temp_file=$TESTS_DIR"temp/"`echo $fn | cut -f4 -d"/"`
    echo "some shit:  "$temp_file

    test_passed=true
    echo
    echo "running test: "$fn
    file_len=$(wc -c <"$fn")
    echo "File length: "$file_len
    
    temp_enc=$temp_file"_enc"
    temp_dec=$temp_file"_dec"
    
    compression_time=`./main $fn $temp_enc "compress"`
    compression_result=$?
    if [ $compression_result -ne 0 ]
    then
        echo "${RED}ERROR:${NC} failed compression on: $fn"
        all_tests_passed=false
        test_passed=false
    else
        echo "compression time: "$compression_time
        results+=($compression_time)
    fi

    decompression_time=`./main $temp_enc $temp_dec "decompress"`
    decompression_result=$?
    if [ $decompression_result -ne 0 ]
    then
        echo -e "${RED}ERROR:${NC} failed decompression on: $fn"
        all_tests_passed=false
        test_passed=false
    else
        echo "Decompression time: "$decompression_time
        results+=($decompression_time)
    fi

    #compare initial file with the compressed -> decompressed one
    diff $fn $temp_dec
    if [ $? -ne 0 ]
    then
        echo -e "${RED}ERROR:${NC} Decoded file is not the same as the input file $fn. Something went wrong. :("
        all_tests_passed=false
        test_passed=false
    fi

    if $test_passed; then
        `rm $temp_enc $temp_dec`
    fi
done

echo

if $all_tests_passed;then
    #save results to csv file
    echo "compression, decompression" > test_results.csv
    i=0
    for result in "${results[@]}"; do
        if [ $(($i%2)) -eq 0 ]; then
            echo -n "$result," >> test_results.csv
        else
            echo "$result," >> test_results.csv
        fi
        i=$((i+1))
    done
    echo "Tests finished successfuly, time elapsed results saved in test_results.csv"
else
    echo "Not All tests finished successfuly."
fi

 