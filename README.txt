English 33-Hole Peg Board Solver

This program solves the English 33-Hole Peg Board puzzle using a brute force function and a hashtable function. If the board is unsolvable, the program will inform the user and exit. 

How to use:
This is a console based program. When running a compiled version of the peg.cpp file, a .txt file must be included. This file will need to contain a string of numbers with spaces placed inbetween them. The string of numbers needs to be within parentheses. These numbers represent the locations on the peg board that will be occupied by pegs. 

WARNING: do not include numbers that would be occupied by the #. The program does not error check the presence of pegs in those locations and will read them as part of the board. 


#  #  02 03 04  #  #

#  #  09 10 11  #  #

14 15 16 17 18 19 20

21 22 23 24 25 26 27

28 29 30 31 32 33 34

#  #  37 38 39  #  #

#  #  44 45 46  #  #



Example: (3 4 9)

2  2  0  1  1  2  2

2  2  1  0  0  2  2

0  0  0  0  0  0  0

0  0  0  0  0  0  0

0  0  0  0  0  0  0

2  2  0  0  0  2  2

2  2  0  0  0  2  2

