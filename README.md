# Letter-Dice

The write up for this project is here: https://web.eecs.utk.edu/~semrich/cs302-21/assignments/proj05.html

**Authors:** Katie Nuchols (@knuchols) and Swasti Mishra (@pixelatinate)

## Files
**worddice.cpp :**
Contains the driver function for our project.

**worddice.h:**
Contains the various structures we used and their accompanying functions.

**gradescript:**
The file we used to compile. 

These are the commands you can use: 
- make:       compiles the program
- make test:  compiles the program and runs the gradeall
- make clean: deletes the compiled program

**gradeall:**
Checks our output against the correct outputs. 

## Directories
**Dice:**
Contains the "dice" that we use to spell each word. 

**Word:**
Contains the words that our program needs to try and spell. 


## Complexity of Our Implementation
So for the complexity we used a BFS, list, map and nodes. A BFS is O(V) where V is the number of nodes. Though in some cases it will be O(V^2). The BFS allows us to store nodes with multiple sources of input and use graphs to see all possibilites. The BFS is a fast way to find all of this information and transverse through options quickly.