#!/bin/bash
# Default filenames
input_file="example.py"
output_dot="temp.dot"
output_pdf="ast.pdf"
# If input arguments are provided, override the defaults
if [ "$#" -eq 3 ]; then
    input_file="$1"
    output_dot="$2"
    output_pdf="$3"
fi
# Compile the program using make
make clean
make

# Run the parser program
./parser -input "$input_file" -output "$output_dot" 

# Generate Parse tree
dot -Tpdf "$output_dot" -o "$output_pdf"

# Compile the assembly code
gcc asm.s -o a.out

# Display output separator
echo "-----OUTPUT-----"

# Run the compiled assembly program
./a.out
