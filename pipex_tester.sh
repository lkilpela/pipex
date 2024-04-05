#!/bin/bash

# Define a function to run a test
run_test() {
    infile=$1
    cmd1=$2
    cmd2=$3
    outfile=$4

    # Run the actual Unix pipeline
    eval "$cmd1 < $infile | $cmd2 > outfile_shell"

    # Run your pipex program
    ./pipex $infile "$cmd1" "$cmd2" $outfile

    # Compare the outputs
    echo "Testing with $infile, $cmd1, $cmd2, $outfile"
    diff outfile_shell $outfile && echo "No differences" || echo "Test failed"
    echo
}

# Run tests
run_test "infile" "ls" "wc" "outfile1"
run_test "infile" "cat" "grep hello" "outfile2"
