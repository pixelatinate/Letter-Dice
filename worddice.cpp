// Project 05: Letter Dice
// You can read about this challenge here: https://web.eecs.utk.edu/~semrich/cs302-21/assignments/proj05.html 
// This lab takes input from imaginary dice with letters on each side and checks if 
//      you can form certain words with the dice provided
// COSC 302
// Katie Nuchols and Swasti Mishra

# include <map>
# include <list>
# include <vector>
# include <fstream>
# include <iostream>

using namespace std ;

enum customNodes{   wordNode ,
                    sinkNode ,
                    diceNode ,
                    sourceNode , 
                } ;  

struct Node{
	customNodes type ;		// Type of node being used
	int id ;				// ID of the variable
	int visited ;			// If the variable has been visited then this will change
	vector<bool> letters ;	// All of the letters if used will change bool value
	vector<class Edge*> adj;// Use a vector of the Edge struct 
	class Edge* backEdge ;
};

struct Edge{

};

struct Graph{
	bool BFS() ;
	void clear() ;
	bool confirm() ;

	int minimum ;
	vector<Node*> nodes ;
	vector<int> usedDie ;	
};

int main( int argc , char* argv[] ){
    
	// Variables
	string temp ;
	ifstream inputFile ;
	vector <Node*> dice ;
	vector <Node*> letters ;
	vector <string> words ;
	int counter ;
	Graph graph;

	// Opens the file and pushes back the information
    counter = 1 ;
	inputFile.open( argv[1] ) ;
	while( getline( inputFile, temp ) ){
		Node * die = new Node ;
		die->type = diceNode ;
		die->id = counter ;
		die->letters.resize( 26 ) ;
		for( int j = 0 ; j < temp.length() ; j++ ){
			die->letters.at( temp.at(j) - 'A' ) = 1 ;
		}
		dice.push_back( die ) ;
		counter++ ;
	}

	// Closes the first file and opens the next 
	inputFile.close() ;
	inputFile.open( argv[2] ) ;

	// Pushes back the words
	while( getline( inputFile, temp ) ){
		words.push_back( temp ) ;
	}
    
	for( int i = 0; i < words.size(); i++){
		
		// Builds the sink
		Node* sink = new Node ;
		sink->type = sinkNode ;
		sink->id = ( words.at( i ).length() + dice.size() ) ;

		// Builds the source
		Node* source = new Node ;
		source->type = sourceNode ;

		// Pushes each letter back as its own node
		for( int j = 0 ; j < words.at( i ).length() ; j++ ){
			
			// Creates the new node
			Node letter* = new Node ;
			
			// Pushes the appropriate value back into the node
			letter->id = counter ;
			letter->type = wordNode ;
			letter->letters.resize(26) ;
			letter->letters.at( words.at(i).at(j) - 'A' ) = 1 ;

			// Pushes each letter back
			currentLetters.push_back( letter ) ;
		}
	}

    return 0 ;
}