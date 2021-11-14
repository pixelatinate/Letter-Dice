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
	Node* ahead ;
	Node* behind ;
	Edge* backUp ;
	int original , extra ;
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
	vector <Node*> selectedLetter ;
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
			Node *letter = new Node ;
			
			// Pushes the appropriate value back into the node
			letter->id = counter ;
			letter->type = wordNode ;
			letter->letters.resize(26) ;
			letter->letters.at( words.at(i).at(j) - 'A' ) = 1 ;

			// Pushes each letter back
			selectedLetter.push_back( letter ) ;
		}

		// Letters go to sink, die go to source
		for( int j = 0; j < selectedLetter.size(); j++){
			Edge *diceEdge = new Edge ;
			Edge *backEdge = new Edge ;

			diceEdge->ahead = sink ;
			diceEdge->behind = selectedLetter.at( j ) ;
			diceEdge->original = 1 ;

			backEdge->ahead= selectedLetter.at( j ) ;
			backEdge->behind = sink ;
			backEdge->extra = 1 ;

			diceEdge->backUp = backEdge ;
			backEdge->backUp = diceEdge ;

			selectedLetter.at( j )->adj.push_back( diceEdge ) ;
			sink->adj.push_back( backEdge ) ;
		}

		for( int j = 0 ; j < dice.size() ; j++ ){
			Edge *diceEdge = new Edge ;
			Edge *backEdge = new Edge ;

			diceEdge->ahead = dice.at( j ) ;
			diceEdge->behind = source ;
			diceEdge->original = 1 ;
		
			backEdge->ahead= source ;
			backEdge->behind = dice.at( j ) ;
			backEdge->extra = 1 ;

			diceEdge->backUp = backEdge ;
			backEdge->backUp = diceEdge ;

			source->adj.push_back(diceEdge) ;
			dice.at(j)->adj.push_back(backEdge) ;
		}

		// Compares die to letter nodes and links them
		for( int j = 0 ; j < dice.size() ; j++ ){
			for( int k = 0 ; k < selectedLetter.size() ; k++ ){
				for( int l = 0 ; l < dice.at( j )->letters.size() ; l++ ){
					if( ( selectedLetter.at( k )->letters.at( l ) == 1 ) && ( dice.at( j )->letters.at( l ) == 1 ) ){

						Edge *diceEdge = new Edge ;
						Edge *backEdge = new Edge ;

						diceEdge->ahead = selectedLetter.at( k ) ;
						diceEdge->behind = dice.at(j) ;
						diceEdge->original = 1 ;

						backEdge->ahead = dice.at( j ) ;
						backEdge->behind = selectedLetter.at( k ) ;

						diceEdge->backUp = backEdge ;
						backEdge->backUp = diceEdge ;

						dice.at( j )->adj.push_back( diceEdge ) ;
						selectedLetter.at( k )->adj.push_back( backEdge ) ;
					}
				}
			}
		}

		// Puts the nodes in the graph
		graph.nodes.push_back( source ) ; 

		for( int j = 0 ; j < dice.size() ; j++ ){
			graph.nodes.push_back( dice.at( j ) ) ;
		}
		for( int j = 0 ; j < selectedLetter.size() ; j++ ){
			graph.nodes.push_back( selectedLetter.at( j ) ) ;
		}

		// Saves the sink
		graph.nodes.push_back( sink ) ;

		// Saves the smallest size
		graph.minimum = dice.size() ;

		// Accounts for if the word can't be spelled 
		if( dice.size() < selectedLetter.size() ){
			cout << selectedLetter.size() << "\n" ;
			cout << "Cannot Spell: " << words.at( i ) << "\n" ;
		}

		// Prints it out if it can be spelled
		if( graph.confirm() ){
			for( int j = 0 ; j < graph.usedDie.size() ; j++ ){
				if ( j == 0 ){
					cout << graph.usedDie.at( j ) ;
				}
				else{
					cout << "," << graph.usedDie.at( j ) ;
				}
			}
			cout << ": " << words.at( i ) << "\n" ;
		}
		
		// Other cases
		else{
			cout << "Cannot spell " << words.at( i ) << "\n" ;
		}

		// Clears previous data for the next run 
		graph.clear() ;
		graph.usedDie.clear() ;
		selectedLetter.clear() ;
		counter = ( dice.size() + 1 ) ;
	}
    return 0 ;
}