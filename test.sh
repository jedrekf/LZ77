#!/bin/bash

RED='\033[0;31m'
NC='\033[0m' # No Color

echo "rebuilding project..."
make

echo ; echo ; echo ;
#print variable on a screen
echo "Launching tests for LZ77 algorithm..."

declare -a results=()
all_tests_passed=true

for fn in `ls -d -1 ./tests/input_files/*.*`; do
    echo
    echo "running test: "$fn
    file_len=$(wc -c <"$fn")
    echo "File length: "$file_len
    
    temp_enc=fn"_enc"
    temp_dec=fn"_dec"
    
    compression_time=`./main $fn $temp_enc "compress"`
    compression_result=$?
    if [ $compression_result -ne 0 ]
    then
        echo "${RED}ERROR:${NC} file not successfuly encoded: $fn"
        all_tests_passed=false
    else
        echo "compression time: "$compression_time
        results+=($compression_time)
    fi

    decompression_time=`./main $temp_enc $temp_dec "decompress"`
    decompression_result=$?
    if [ $decompression_result -ne 0 ]
    then
        echo -e "${RED}ERROR:${NC} file not successfuly decoded: $fn"
        all_tests_passed=false
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
    fi

    `rm $temp_enc $temp_dec`
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

 