# CS335_project

## Description
In this project we have to make a python compiler using tools like bison,flex and many more.

## Installation
Install Bison , Flex and Graphviz according to your OS.

For Ubuntu, run the following commands:\
```sudo apt-get install bison flex```\
```sudo apt-get install graphviz```

Clone the repository using HTTPs:\
```git clone https://git.cse.iitk.ac.in/monill/cs335_project.git```

or using SSH:\
```git clone git@git.cse.iitk.ac.in:monill/cs335_project.git```

## Usage
To run the repo first you have to run the makefile using the command: \
```make```

It will create an executable ```parser``` , now to make the ```.dot``` script run the following command:\
```./parser -input <path_to_python_file> -output <name_of_new_dot_file>``` 

To create a default DOT file ```parser_tree.dot``` just run the following command: \
```./parser -input <path_to_python_file>```

A ```-verbose``` and ```--help``` functionality is also provided which we can access using:\
```./parser -input <path_to_python_file> -verbose```\
```./parser --help```

After getting the DOT file, a pdf has to be generated for that run the following command : \
```dot -Tpdf <path_to_dot_file> -o <name_of_output_file>``` 

For example a sample command can look like:\
```dot -Tpdf parse_tree.dot -o output.pdf```

The output PDF will contain AST of the given python code. 

## Additional files
We have added 5 test cases in the folder named tests, also, for the given
public test cases we have added their AST in PDF format in the folder named
publictestcases_AST

## Authors and acknowledgment
Monil Lodha (210630) \
Akshat Rajani (210812) \
Kalika (210482) 


