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
	nodeType type;//type of node being used
	int id;//id of the variable
	int visited;//if the variable has been visited themn this will change
	vector<bool> letters;//all of the letters if used will change bool value
	vector<class Edge*> adj;//use a vector of the Edge struct 
	class Edge* backEdge;
};

struct Edge{

};

struct Graph{

};

int main( int argc , char* argv[] ){
    string temp;
	ifstream inFile;
	vector<string> words;
	vector<Node*> dice;
	vector<Node*> currentLetters;
	int i, j, k, l, idIterator;
	Graph wordGraph;
    //soime variables that will be used later
    idIterator = 1;
	inFile.open(argv[1]);//open the first file
	while(getline(inFile, temp)){
		Node * die = new Node;
		die->type = DICE;
		die->id = idIterator;
		die->letters.resize(26);
		for(j = 0; j < temp.length(); j++){
			die->letters.at(temp.at(j)-65) = 1;
		}
		dice.push_back(die);
		idIterator++;
	}//get the information and add it to the node to be used later

	inFile.close();//close the file once done
	inFile.open(argv[2]);//open the next file
	while(getline(inFile, temp)){
		words.push_back(temp);//push back the information from the next file to be used later
	}
    
    return 0 ;
}