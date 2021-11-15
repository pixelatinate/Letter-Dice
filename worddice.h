// Project 05: Letter Dice
// You can read about this challenge here: https://web.eecs.utk.edu/~semrich/cs302-21/assignments/proj05.html 
// This lab takes input from imaginary dice with letters on each side and checks if 
//      you can form certain words with the dice provided
// COSC 302
// Katie Nuchols and Swasti Mishra

// worddice.h

// Libraries 
# include <map>
# include <list>
# include <vector>
# include <fstream>
# include <iostream>

using namespace std ;

// Nodes we'll used to determine dice used
enum customNodes{   wordNode ,
                    sinkNode ,
                    diceNode ,
                    sourceNode , 
                } ;  

// This is what each of the custom nodes will contain 
struct Node{
	customNodes type ;		// Type of node being used
	int id ;				// ID of the variable
	int visited ;			// If the variable has been visited then this will change
	vector<bool> letters ;	// All of the letters if used will change bool value
	vector<class Edge*> adj;// Use a vector of the Edge struct 
	class Edge* backEdge ; 	// The top edge that's connected behind everything else

} ;

// Connects nodes to nodes
struct Edge{
	Node* ahead ;
	Node* behind ;
	Edge* backUp ;
	int original , extra ;
};

// Will collect all the information we finally need to print 
struct Graph{
	bool BFS() ;
	void clear() ;
	bool confirm() ;

	int minimum ;
	vector<Node*> nodes ;
	vector<int> usedDie ;	
} ;

// Empties all information (kind of like a destructor?)
void Graph::clear(){

	// Clears nodes
	for( int i = ( nodes.size() - 1 ) ; i > minimum ; i-- ){
		nodes.pop_back() ;
	}

	// Clears the original value
	for( long unsigned int i = 0 ; i < ( nodes.at( 0 )->adj.size() ) ; i++ ){
		nodes.at( 0 ) -> adj.at( i ) -> original = 1 ;
	}
}

// Uses breadth-first search to look for letters
bool Graph::BFS(){

	Node *currentNode ;
	list<Node*> queue ;

	// Resets fields 
	for( long unsigned int i = 0 ; i < nodes.size() ; i++ ){
		nodes.at( i ) -> visited = 0 ;
	}

	// Go back to 1
	nodes.at( 0 ) -> visited = 1 ;
	queue.push_back( nodes.at( 0 ) ) ;

	while( !queue.empty() ){
		
		// Restarts
		currentNode = queue.front() ;
		queue.pop_front() ;

		// Adds child nodes to the queue
		for( long unsigned int i = 0 ; i < currentNode->adj.size() ; i++ ){
			if( ( currentNode->adj.at( i ) -> ahead -> visited == false ) && ( currentNode -> adj.at( i ) -> original == 1 ) ){
				currentNode->adj.at( i ) -> ahead -> visited = true ;
				currentNode->adj.at( i ) -> ahead -> backEdge = currentNode -> adj.at( i ) ;
				queue.push_back( currentNode->adj.at( i )->ahead ) ;
			}
		}

		// Path found!
		if( currentNode -> type == sinkNode ){
			return true ;
		}

	}

	// Anything else means a path wasn't found. 
	return false;
}

// Confirms that the letter dice were selected properly 
bool Graph::confirm(){
	
	// Confirms that a path was found in the first place
	while( BFS() == true ){

		Node *currentNode ;
		Edge *currentEdge ;
		vector<Node*>::iterator vectorIterator ;

		// Start from the root and then progress to the sink
		vectorIterator = nodes.end() ;
		vectorIterator-- ;
		currentNode = *vectorIterator ;

		// Reverse it (we started from the back)
		while( sourceNode != ( currentNode -> type ) ){
			
			currentEdge = currentNode -> backEdge;

			if( currentEdge -> original == 1 ){
				currentEdge -> original = 0 ;
				currentEdge -> extra = 1 ;
				currentEdge -> backUp->original = 1 ;
			}
			else if( currentEdge -> original == 0 ){
				currentEdge -> original = 1 ;
				currentEdge -> backUp -> extra = 1 ;
			}

			currentNode = currentEdge -> behind ;
		}
	}

	// Finally, tells us if it's possible to spell a word or not
	for( long unsigned int i = minimum ; i < ( nodes.size() - 1 ) ; i++ ){
		for( long unsigned int j = 0 ; j < ( nodes.at( i )->adj.size() ) ; j++ ){

			// If it is possible to spell the word, pushes back the ID we need
			if( ( nodes.at( i ) -> adj.at( j ) -> ahead -> type == diceNode ) && ( nodes.at( i ) -> type != sourceNode ) ){
				if ( ( nodes.at( i ) -> adj.at( j ) -> original == 1 ) ){
					usedDie.push_back( ( nodes.at( i ) -> adj.at( j ) -> ahead -> id ) - 1 ) ;
				}
			}

			// Returns false if it's not possible
			if( ( nodes.at(i)->adj.at(j)->extra == 0 ) && ( nodes.at(i)->adj.at(j)->ahead->type == sinkNode ) ){
				return false ;
			}

		}
	}

	// True in all other cases
	return true ;
}
