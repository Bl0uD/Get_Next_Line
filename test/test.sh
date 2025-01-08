#!/bin/bash

green=$(tput bold; tput setaf 2)
green2=$(tput bold; tput setaf 052)
red=$(tput bold; tput setaf 1)
magenta=$(tput bold; tput setaf 5)
jaune=$(tput bold; tput setaf 221)
violet=$(tput bold; tput setaf 12)
reset=$(tput sgr 0)
test_size=(1 10 42 9999 10000000)

if [ ! -d "outputs" ]; then
	mkdir outputs
fi

for test_size in "${test_size[@]}"; do
	echo -e "$green2""\nRunning tests with test_size = ""$jaune""$test_size\n""$reset"
	
	cat header_conf.h | sed 's/$TEST_SIZE/'"$test_size/" > get_next_line.h
	cp ../get_next_line.c ./
	cc main.c ./get_next_line.c ../get_next_line_utils.c -o test_gnl -I ./

	for filename in ./inputs/*; do
		testname=$(basename $filename)
		output_file_name=./outputs/result_test_${test_size}_$testname
		echo -ne "$magenta""Starting test "$violet"\"$testname\" : ""$reset"
		./test_gnl $filename > $output_file_name
		diff -q $filename $output_file_name > /dev/null
		if [ $? -eq 0 ];then
			echo -e "$green""OK""$reset"
			rm $output_file_name
		else
			echo -e "$red""KO""$reset"
		fi
	done
	rm test_gnl
done

if [ -z "$(ls -A outputs)" ]; then
	echo -e "$green2""\nALL TESTS PASSED !! CONGRATS !!\n" 
    rmdir outputs
fi