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
The most important element for determining our program's complexity was the breadth-first search algorithm (BFS). A BFS is O(V+E) where V is the number of vertices and E is the number of edges, though in some cases it will be O(V^2). In our case, we think the complexity is O(V^2) because our queue is linked both backwards and forwards. The BFS allows us to store nodes with multiple identifiers and use our other data structures to see all the possibilies. The BFS is a fast way to find all of this information and transverse through options quickly.

We also used several other data structures including vectors and classes. We used vectors because they're quick and easy to implement and push data back into, and classes because all of our data had a lot of identifiers that we needed to parse. Our source nodes told us which die we would be using, and the sink told us which "face" of the die we would use. Storing all this information required the various data structures that we used and (we think) didn't have too much of a negative impact on our complexity. 