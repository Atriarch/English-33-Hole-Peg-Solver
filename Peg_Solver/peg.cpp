//Nathan McGaughy
//Peg Solver

#include <time.h>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace std;

struct board{                  //Holds a board.
public:
	long long board[7][7];
};

class barray{                  //Holds many boards.
public:
	board barray[20000];
	bool equal(int num, board &equ);
};

bool barray::equal(int num, board &equ){ //This is used to compare the board layouts between the struct 'board' and the class 'barray'.
	for(int y = 0; y < 7; y++){
		for(int x = 0; x < 7; x++){
			if(barray[num].board[x][y] != equ.board[x][y]){
				return false;
			}
		}
	}
	return true;
}

double diffclock(clock_t clock1,clock_t clock2)
{
	double diffticks=clock1-clock2;
	double diffms=(diffticks*10)/CLOCKS_PER_SEC;
	return diffms;
}

int pegs = 0; //Global variable used to keep an eye on the #of pegs in play.
board boardmove(board &set, ifstream& input); //Sets up the board.
bool hashsolver(board &set/*, barray &copy*/);    //Solves the board.
bool solver(board &set/*, barray &copy*/);
void OpenInputFile(int argc, char* argv[], ifstream& input); //Opens the Input File containing the board.
bool pastcheck(board &set, barray &copy, int num); //Checks to see if a similar move has been made.
int brutefind(int x, int y); //Checks between an x and y array and the numerical order of the board.

barray newboard; //This is used to maintain the past movies of the board.
bool finish = false; //If true, the board has been solved.
int num = 0;         //Number of nodes created.

int main(int argc, char* argv[]){
	ifstream input;
	OpenInputFile(argc, argv, input);
	board game;
	barray copy;
	int peghold;
	game = boardmove(game, input);
	copy.barray[0] = game;

	for(int i = 0; i < 7; i++){       //Displays the board.
		for(int x = 0; x < 7; x++){
			cout << game.board[x][i];
		}
		cout << endl;
	}
	cout << endl;

	newboard.barray[0]=game;

	peghold = pegs;

	cout << "Without Hash Tables:" << endl;
	clock_t begin=clock();
	if(solver(game) == true){
		cout << endl;
		cout << "The puzzle has been solved." << endl;
	}
	else {
		cout << endl;
		cout << "The puzzle can not be solved." << endl;
	}
	clock_t end=clock();
	cout << "Time elapsed: " << double(diffclock(end,begin)) << " ms"<< endl;
	cout << endl;


	pegs = peghold;
	finish = false;
	num = 0;

	cout << "With Hash Tables:" << endl;
	clock_t start=clock();
	if(hashsolver(game) == true){
		cout << endl;
		cout << "The puzzle has been solved." << endl;
	}
	else {
		cout << endl;
		cout << "The puzzle can not be solved." << endl;
	}
	clock_t finish=clock();
	cout << "Time elapsed: " << double(diffclock(finish, start)) << " ms"<< endl;

	input.close();
	return 0;
}


bool solver(board &set){

	static barray copy; //Holds all the boards (even the unplayable ones).


	if (pegs == 1){   //Display the final move of a solved board.
		for(int i = 0; i < 7; i++){
			for(int x = 0; x < 7; x++){
				cout << set.board[x][i];
			}
			cout << endl;
		}
		cout << endl;
		return true;
	}
	for(int y = 0; y < 7; y++){
		for(int x = 0; x < 7; x++){
			if(x <= 5 && set.board[x][y] == 1 && set.board[x+1][y] == 1 && set.board[x+2][y] == 0 && finish != true){
				set.board[x][y] = 0;
				set.board[x+1][y] = 0;
				set.board[x+2][y] = 1;

				pegs--;
				num++;
				newboard.barray[num] = set;
				finish = solver(set);
				num--;
				set = newboard.barray[num];
				
				if(finish == true){
					cout << "(" << brutefind(x,y)  << " " <<  brutefind(x+1,y) << " " <<  brutefind(x+2,y) << ")"; //If the board is solved, this will tell us in what order the pegs were moved.
				}
			}
			if(x >= 2 && set.board[x][y] == 1 && set.board[x-1][y] == 1 && set.board[x-2][y] == 0 && finish != true){
				set.board[x][y] = 0;
				set.board[x-1][y] = 0;
				set.board[x-2][y] = 1;

				pegs--;
				num++;
				newboard.barray[num] = set;
				finish = solver(set);
				num--;
				set = newboard.barray[num];
				
				if(finish == true){

					cout << "(" << brutefind(x, y)  << " " <<  brutefind(x-1,y) << " " <<  brutefind(x-2,y) << ")";

				}
			}
			if(y <= 5 && set.board[x][y] == 1 && set.board[x][y+1] == 1 && set.board[x][y+2] == 0 && finish != true){
				set.board[x][y] = 0;
				set.board[x][y+1] = 0;
				set.board[x][y+2] = 1;

				pegs--;
				num++;
				newboard.barray[num] = set;
				finish = solver(set);
				num--;
				set = newboard.barray[num];
		
				if(finish == true){
					cout << "(" << brutefind(x,y)  << " " <<  brutefind(x, y+1) << " " <<  brutefind(x, y+2) << ")";
				}
			}
			if(y >= 2 && set.board[x][y] == 1 && set.board[x][y-1] == 1 && set.board[x][y-2] == 0 && finish != true){
				set.board[x][y] = 0;
				set.board[x][y-1] = 0;
				set.board[x][y-2] = 1;

				pegs--;
				num++;
				newboard.barray[num] = set;
				finish = solver(set);
				num--;
				set = newboard.barray[num];
			
				if(finish == true){
					cout << "(" << brutefind(x,y)  << " " <<  brutefind(x, y-1) << " " <<  brutefind(x, y-2) << ")";
				}
			}
		}
	}
	if(finish == true){
		return true;
	}
	else{

		pegs++;
		return false;
	}
}




bool hashsolver(board &set){

	static barray copy; //Holds all the boards (even the unplayable ones).
	board temp;
	static int cnum = 0; //Used to keep track of 'copy's boards.
	if(cnum >=20000){
		cnum = 0;
	} 

	if (pegs == 1){   //Display the final move of a solved board.
		for(int i = 0; i < 7; i++){
			for(int x = 0; x < 7; x++){
				cout << set.board[x][i];
			}
			cout << endl;
		}
		cout << endl;
		return true;
	}


	for(int y = 0; y < 7; y++){
		for(int x = 0; x < 7; x++){

			if(x <= 5 && set.board[x][y] == 1 && set.board[x+1][y] == 1 && set.board[x+2][y] == 0 && finish != true){
				temp = set;
				set.board[x][y] = 0;
				set.board[x+1][y] = 0;
				set.board[x+2][y] = 1;

				if( pastcheck(set,copy, cnum) == true){ //checks to see if this move has already been made.
					copy.barray[cnum] = temp;
					cnum++;
					pegs--;
					num++;
					newboard.barray[num] = set;
					finish = hashsolver(set);
					num--;
					set = newboard.barray[num];
				}
				else{
					set = temp;
				}
				if(finish == true){
					cout << "(" << brutefind(x,y)  << " " <<  brutefind(x+1,y) << " " <<  brutefind(x+2,y) << ")"; //If the board is solved, this will tell us in what order the pegs were moved.
				}
			}
			if(x >= 2 &&  set.board[x][y] == 1 && set.board[x-1][y] == 1 && set.board[x-2][y] == 0 && finish != true){
				temp = set;
				set.board[x][y] = 0;
				set.board[x-1][y] = 0;
				set.board[x-2][y] = 1;

				if( pastcheck(set,copy, cnum) == true){
					copy.barray[cnum] = temp;
					cnum++;
					pegs--;
					num++;
					newboard.barray[num] = set;
					finish = hashsolver(set);
					num--;
					set = newboard.barray[num];
				}
				else{
					set = temp;
				}
				if(finish == true){
					cout << "(" << brutefind(x, y)  << " " <<  brutefind(x-1,y) << " " <<  brutefind(x-2,y) << ")";
				}
			}
			if(y <= 5 && set.board[x][y] == 1 && set.board[x][y+1] == 1 && set.board[x][y+2] == 0 && finish != true){
				temp = set;
				set.board[x][y] = 0;
				set.board[x][y+1] = 0;
				set.board[x][y+2] = 1;

				if( pastcheck(set,copy, cnum) == true){
					copy.barray[cnum] = temp;
					cnum++;
					pegs--;
					num++;
					newboard.barray[num] = set;
					finish = hashsolver(set);
					num--;
					set = newboard.barray[num];
				}
				else{
					set = temp;
				}
				if(finish == true){
					cout << "(" << brutefind(x,y)  << " " <<  brutefind(x, y+1) << " " <<  brutefind(x, y+2) << ")";
				}
			}
			if(y >= 2 && set.board[x][y] == 1 && set.board[x][y-1] == 1 && set.board[x][y-2] == 0 && finish != true){
				temp = set;
				set.board[x][y] = 0;
				set.board[x][y-1] = 0;
				set.board[x][y-2] = 1;

				if( pastcheck(set,copy, cnum) == true){
					copy.barray[cnum] = temp;
					cnum++;
					pegs--;
					num++;
					newboard.barray[num] = set;
					finish = hashsolver(set);
					num--;
					set = newboard.barray[num];
				}
				else{
					set = temp;
				}
				if(finish == true){
					cout << "(" << brutefind(x,y)  << " " <<  brutefind(x, y-1) << " " <<  brutefind(x, y-2) << ")";
				}
			}
		}
	}

	if(finish == true){
		return true;
	}
	else{

		pegs++;
		return false;
	}
}

int brutefind(int x, int y){
	int point = 0;
	for(int i = 0; i < x; i++){
		point = point + 1;
	} 

	for(int r = 0; r < y; r++){
		point = point + 7;
	}
	return point;

}



bool pastcheck(board &set, barray &copy, int num){ //Checks to see if this is a repeated move.
	for(int i = 0; i < num; i++){
		if(copy.equal(i, set)==true){
			return false;
		}
	}
	return true;
}


board boardmove(board &set, ifstream& input){
	int hold = 0;
	int x = 0;
	int y = 0;
	char brace;
	for(int r = 0; r < 7; r++){
		for(int z = 0; z < 7; z++){
			set.board[r][z] = 0;
		}
	}
	set.board[0][0] = 2;
	set.board[1][0] = 2;
	set.board[0][1] = 2;
	set.board[1][1] = 2;
	set.board[5][0] = 2;
	set.board[6][0] = 2;
	set.board[5][1] = 2;
	set.board[6][1] = 2;
	set.board[0][5] = 2;
	set.board[1][5] = 2;
	set.board[0][6] = 2;
	set.board[1][6] = 2;
	set.board[5][5] = 2;
	set.board[6][5] = 2;
	set.board[5][6] = 2;
	set.board[6][6] = 2;
	input >> brace;
	while(input >> hold){
		for (int i = 1; i <= hold; i++){
			x ++;
			if(x == 7){
				x = 0;
				y++;
			}
		}
		pegs++;
		set.board[x][y] = 1;
		x = 0;
		y = 0;
	}
	return set;
}

void OpenInputFile(int argc, char* argv[], ifstream& input) {
	if (argc != 2) {
		cerr << "Error: you should provide exactly one command-line "
			<< "argument.\n";
		exit(1);
	}
	input.open(argv[1]);
	if (input.fail()) {
		cerr << "Error: " << argv[1] << " could not be opened for reading.\n";
		exit(1);
	}
}
