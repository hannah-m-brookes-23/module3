#!/bin/bash

# iterates through all binary files with the format test*.bin (in
# Makfile, ensure that all tests are made in this format)
for FILE in test*.bin
do
		# passes valgrind error output (which contains the infor whether
		# no leaks are possible or whether there are 0 errors) to a file
		# and pass output to separate file
		valgrind --leak-check=full $FILE 2> valgrind_err > valgrind_out
		# checks whether the two required outputs are found in the error
		# file; print to terminal whether the given file passed the check
		# or whether it failed
		if [[ $(grep 'no leaks are possible' valgrind_err | wc -l) -eq 1 && $(grep '0 errors' valgrind_err | wc -l) -eq 1 ]]
		then
				echo "$FILE passed valgrind check"
		else
				echo "$FILE FAILED valgrind check"
		fi
done

# removes the output files
rm -r valgrind_err
rm -r valgrind_out
