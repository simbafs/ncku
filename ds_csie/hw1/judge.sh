#!/bin/bash

# Initialize variables
sample_dir="$1"
program="$2"

# Check if the required options are provided
if [[ -z "$sample_dir" || -z "$program" ]]; then
    echo "Usage: $0 <sample_dir> <program>"
    exit 1
fi

if ! gcc "$program" -o main; then
    echo compile fail
    exit 1
fi

inputs=$(find "$sample_dir" -name "*.in" | sort)
fail=0
pass=0

for input_file in $inputs; do
    output_file=$(echo "$input_file" | sed 's/\.in$/.out/')
    if [[ -z "$output_file" ]]; then
        echo "Output file not found for input file: $input_file"
        continue
    fi
    # echo "Running test with input file: $input_file"
    # echo "Expected output file: $output_file"
    ./main <"$input_file" >program_output.txt
    if diff -qEZbB --ignore-blank-lines  program_output.txt "$output_file" >/dev/null; then
        ((pass += 1))
        echo "$input_file: OK"
    else
        ((fail += 1))
        echo "Test failed! Output differs:"
        diff -aEZbB --ignore-blank-lines program_output.txt "$output_file"
    fi
    echo "==========="
    echo
done

echo
echo "Passed: $pass, Failed: $fail"

# Clean up temporary output file
rm program_output.txt main
