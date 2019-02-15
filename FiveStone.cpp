//Name: Rosalind Ng - 100286169
//Program Name : FiveStone.cpp
//Course: CPSC 1160
//A game of fivestones that gets the userinputs. whoever places 5 consecutive
//stones in a row, wins. 

#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <cstdlib>

using namespace std;

//make a constant for the array
const int SIZE = 9;

//making the function prototypes
void fiveStone();
void drawBoard(char[][SIZE]);
void fillArr(char[][SIZE]);
void getAPlay(char[][SIZE], bool&, int&, int&);
void printWelcomeMessage();
void generateAPlay(char[][SIZE], int, int);
bool playerTurn;
bool isPlayValid(string, char[][SIZE]);
bool isInsideBoard(int, int);
bool isFreeSquare(string, char[][SIZE]);
bool isFreeSquare(int, int, char[][SIZE]);
int getRowsIndex(char);
int getColIndex(char);
bool isAWin(char[][SIZE]);
bool isAWin(char, char[][SIZE]);
bool checkStatus(char[][SIZE]);
bool isATie(char[][SIZE]);
char checkHorizontalWin(char[][SIZE]);
char checkVerticalWin(char[][SIZE]);
char checkLeftDiagonalWin(char[][SIZE]);
char checkRightDiagonalWin(char[][SIZE]);

void fiveStone() {
	//store the winner here
	string winner;
	//stores if it is the end of the game
	bool isEnd = false;
	bool playerTurn = true;
	
	//stores the user input
	int row;
	int col; 
	
	//this is the array that will hold the data for the game
	char places[SIZE][SIZE];
	
	//call a function that will fill the array with empty spaces.
	fillArr(places);
	
	//prints the message/ instruction
	printWelcomeMessage();
	//draw the board
	drawBoard(places);
	
	//as long as there is no winner continue to get the player's
	//or the computer's input
	while(!isEnd) {
		
		
		//if it is the player's turn, call the function getAPlay
		//then change playerTurn into false, vice versa for if
		//it is comp's turn
		if(playerTurn) { 
			getAPlay(places, isEnd, row, col); 
			playerTurn = false;
		} else { 
			generateAPlay(places, row, col); 
			playerTurn = true;
			//only draw the board after the computer places a move
			drawBoard(places);
		}
		
		//always check if it is the end of the game only if isEnd 
		//is not already true
		if(!isEnd) { isEnd = checkStatus(places); }

	}
	
	cout << "Thank you for playing!" << endl;
}

//check if there are any wins
bool checkStatus(char places[][SIZE]) {
	
	//call isAWin and isATie to see if there is a win or a tie
	//if there isAWin, end the game
	//if there isATie, end the game 
	return isAWin(places) || isATie(places);
}

//return true if there is a win, if not return false
bool isAWin(char places[][SIZE]) {
	char check;
	
	//check if there is a win at the horizontal
	check = checkHorizontalWin(places);
	if(isAWin(check, places)) {
		return true;
	}
	//if there is no win on the horizontal, check the vertical win
	check = checkVerticalWin(places);
	if(isAWin(check, places)) {
		return true;
	}	
	//if there is not win on the horizontal, check the left diagonal
	check = checkLeftDiagonalWin(places);
	if(isAWin(check, places)) {
		return true;
	}
	//lastly check the Right DiagonalWin
	check = checkRightDiagonalWin(places);
	if(isAWin(check, places)) {
		return true;
	}
	
	return false;
}

//prints out a win message and return true if there is a win
//if not then return false
bool isAWin(char check, char places[][SIZE]) {
		
	//if the winner is  X then it is the computer and the player
	//has lost
	if(check == 'X') {
		//draw the board one last time 
		drawBoard(places);
		
		cout << "You lose" << endl;
		return true;
	//if the winner is O, then the player has won
	} else if(check == 'O') {
		//draw the board one last time 
		drawBoard(places);
		
		cout << "YOU WIN" << endl;
		return true;
	}
	//if not then no one has won
	else {
		return false;
	}
}

//check to see if there is a tie
bool isATie(char places[][SIZE]) {
	//if the array is full, and there is no winner, it is a tie
	for(int i = 0; i < SIZE; i++) {
		for(int j = 0; j < SIZE; j++) {
			//once it gets an element that is a space, return false right away,
			//no need to go through the rest of the array
			if(places[i][j] == ' ') {
				return false;
			}
		}
	}
	//if it comes out of the for loops, then it is full 
	cout << "It is a tie" << endl;
	return true;
}

//check horizontally for any wins, return the stone's char of the
//winner if there is one, if not then return a space
char checkHorizontalWin(char places[][SIZE]) {
	char previous;
	int count = 1;
	
	//check each row to see if the there is a char of 5 long
	for(int i = 0; i < SIZE; i++ ) {
		
		//place the first element here
		previous = places[i][0];
		for(int j = 1; j < SIZE; j++ ) {
			//compare the previous element to the current element
			//if there are the same, then increment the count 
			//if not then want to change previous to the current element
			//and set count back to 1
			if(previous == places[i][j] && previous != ' ') {
				count++;
			} else {
				previous = places[i][j];
				count = 1;
			}
			
			//if this row contains 5 of the same element in the a row
			//there is a win and return char
			if(count == 5) {
				cout << "horizontal" << endl;
				return previous;
			}
		}
	}
	//return a space if there is no winner
	return ' ';
}

//check vertically for any wins, return the stone's char of the
//winner if there is one, if not then return a space
char checkVerticalWin(char places[][SIZE]) {
	char previous;
	int count = 1;
	
	//check each column to see if the there is a char of 5 long
	for(int i = 0; i < SIZE; i++ ) {
		
		//place the first element here
		previous = places[0][i];
		for(int j = 1; j < SIZE; j++ ) {
			
			//compare the previous element to the current element
			//if there are the same, then increment the count 
			//if not then want to change previous to the current element
			//and set count back to 1
			if(previous == places[j][i] && previous != ' ') {
				count++;
			} else {
				previous = places[j][i];
				count = 1;
			}
			
			//if this column contains 5 of the same element in the a row
			//there is a win and return char
			if(count == 5) {
				cout << "vertical" << endl;
				return previous;
			}
		}
	}
	//return a space if there is no winner
	return ' ';
}

//check for a win from the bottom left to the top right 
char checkLeftDiagonalWin(char places[][SIZE]) {
	char previous;
	int count;
	
	//have to the check in half, first will be using the 
	//row as the outer loop and second will be the column as the outer
	
	//first case: row will be outer loop
	//want to start only at row = 4, because anything before will not make 
	//enough for 5 elements to even check 
	for(int i = 4; i < SIZE; i++ ) {
		previous = places[i][0];
		count = 1;
		
		//stop the for loop when i - j is less than 0
		for(int j = 1; j <= i; j++ ) {
			
			//if the previous element is the sames as the current element
			//want to increment count, if it's not then reset count and
			//make previuos to be equal to current element, want to make sure
			//previous is not a space... don't want to compare the spaces
			if(previous == places[i-j][j] && previous != ' ') {
           
				count++;
			} else{
				previous = places[i-j][j];
				count = 1;
			}
			
			//check if count is 5, if it is, there is a win
			if(count == 5) {
				
				return previous;
			}
		}
	}
	
	//next case: the lower half of the diagonal
	//no need to check for the middle ones, because top loop has already check
	//for it
	//need another counter, k to know when to stop the inner loop
	for(int i = 1; i < 5; i++) {
		previous = places[8][i];
		count = 1;
		
		for(int j = 7, c = 1; j > i; j--, c++) {

			if(previous == places[j][i+c] && previous != ' ') {
					count++;
			} else{
				previous = places[j][i+c];
				count = 1;
			}
			
			//check if count is 5, if it is, there is a win
			if(count == 5) {
				cout << "ld2" << endl;
				return previous;
			}
		}
	}
	//if no return, then return and empty char
	return ' ';
}

//check for a win from the top left to bottom right
char checkRightDiagonalWin(char places[][SIZE]) {
	
	char previous;
	int count;
	
	//have to the check in half, first will be using the 
	//row as the outer loop and second will be the column as the outer
	
	//first case: row will be outer loop
	//want to end when row = 4, because anything that starts at the row index after will not make 
	//enough for 5 elements to even check 
	for(int i = 0; i < 5; i++ ) {
		previous = places[i][0];
		count = 1;
		
		//stop the for loop when 9 - j =  i is less than 0
		for(int j = 1, k=8;  k >= i; j++, k = 8-j) {
			
			//if the previous element is the sames as the current element
			//want to increment count, if it's not then reset count and
			//make previuos to be equal to current element, want to make sure
			//it doesn't count the element that is a space
			if(previous == places[i+j][j] && previous != ' ') {
           
				count++;
            
			} else if(previous != places[i+j][j]) {
				previous = places[i+j][j];
				count = 1;
            
			}
			
			//check if count is 5, if it is, there is a win
			if(count == 5) {
				return previous;
			}
		}
	}
	
	//first case: row will be outer loop
	//want to start only at row = 4, because anything before will not make 
	//enough for 5 elements to even check 
	for(int i = 1; i < 5; i++) {
		previous = places[0][i];
		count = 1;
		
		//stop the for loop when i - j is less than 0
		for(int j = 1;  j < 8; j++) {
			
			//if the previous element is the sames as the current element
			//want to increment count, if it's not then reset count and
			//make previuos to be equal to current element
			if(previous == places[j][i+j] && previous != ' ') {
            
				count++;
			} else{
				previous = places[j][i+j];
				count = 1;
			}
			
			//check if count is 5, if it is, there is a win
			if(count == 5) {
				return previous;
			}
		}
	}
	//if no return, then return and empty char
	return ' ';
}

//this prints the welcome message and the instructions
void printWelcomeMessage() {
	cout << "Welcome to Five Stones!" << endl;
	cout << "Your id will be O" << endl;
   cout << "Enter your move (ie. 1a), or q to QUIT" <<endl;
}

//gets the computer to generate a move
//TODO
void generateAPlay(char places[][SIZE], int row, int col) {
	
	//place the X right below
	if(row < 8 && isFreeSquare(row + 1, col, places)) {
		places[row+1][col] = 'X';
	//place the X right above
	} else if(row > 0 && isFreeSquare(row-1, col, places)) {
		places[row-1][col] = 'X';
	//place the X to the left
	} else if(col> 0 && isFreeSquare(row, col -1, places)) {
		places[row][col-1] = 'X';
	//place the X to the right
	} else if(col < 8 && isFreeSquare(row, col+1, places)) {
		places[row][col+1] = 'X';
	//place it diagonally left up 
	} else if(row > 0 && col > 0 && isFreeSquare(row-1, col-1, places)){
		places[row-1][col-1] = 'X';
	//place it diagonally left down
	} else if(row < 8 && col > 0 && isFreeSquare(row+1, col-1, places)) {
		places[row+1][col-1] = 'X';
	//place it diagonally right up
	} else if(row > 0 && col <8 && isFreeSquare(row-1, col+1, places)) {
		places[row-1][col+1] = 'X';
	//place it diagonally right down 
	} else if(row <8 && col < 8 && isFreeSquare(row+1, col+1, places)) {
		places[row+1][col+1] = 'X';
	//if all full, then will have to place at a random spot
	} else {
		int row1 = 0;
		int col1 = 0;
		for(int i = 0; i < SIZE; i++) {
			for(int j = 0; j < SIZE; j++) {
				if(isFreeSquare(i, j, places)) {
					row1 = i;
					col1 = i;
				}
			}
		}
		places[row1][col1] = 'X';
	}	
}

//asks for user input, user always start first
void getAPlay(char places[][SIZE], bool& isEnd, int& row, int& col) {
	bool validMove = true;
	string userInput;
	
	//if the move is not valid, want to keep asking the player to enter a move
	do {
		if(validMove) {
			cout << "Time to make a move: " << endl;
		} else {
			cout << "That wasn't a valid option, please try again" << endl;
			cout << "Enter a new move: " << endl;
		}
		
		//place user input here
		cin >> userInput;
		if(userInput == "q") {
			isEnd = true;
			validMove = true;
		
		//check to see if user made a valid move
		} else { validMove = isPlayValid(userInput, places); }
	} while(!validMove);
	
	row = getRowsIndex(userInput[0]);
	col = getColIndex(userInput[1]);
	//if goes out of the loop then there is a valid move, want to update the array
	places[row][col] = 'O';

}

//get the integer form of the first index
int getRowsIndex(char c) {
	//the first char of the string will be a 
	return c - 49;
}

//get the integer form of the second index
int getColIndex(char c) {
	return c - 'a';
}

//check to see the move is a valid move
bool isPlayValid(string input, char places[][SIZE]) {
	return isFreeSquare(input, places);
}

//check to see if the input is in the square
bool isInsideBoard(int row, int col) {
	//if the first char is 0 to 9 and thhe second char is
	//a to l, then the input is in the board
	return(row >= 0 && row <= 8 &&
		col >= 0 && col <= 8 );
}

//check to see if the user or computer is trying to place
//their stone on a free space, if it is free, then update
//the array
bool isFreeSquare(string in, char places[][SIZE]) {
	int row = getRowsIndex(in[0]);
	// has to convert the second index to an int
	int col = getColIndex(in[1]);
	
	//check to see that is in the board first
	if(!isInsideBoard(row, col)) { return false; }
	return (places[row][col] == ' ');	
}

bool isFreeSquare(int row, int col,char places[][SIZE]) {
	return (places[row][col] == ' ');
}
//fills the 2d array with empty chars
void fillArr(char places[][SIZE]){
	for(int i = 0; i < SIZE; i++) {
		for(int j = 0; j < SIZE; j++) {
			places[i][j] = ' ';
		}
	}
}

//draw the current board and its contents
void drawBoard(char places[][SIZE]) {
		char header = 'a';
      //draw the top header
      for(int i = 0; i < SIZE; i++ ) {
         cout << setw(4) << header++;
      }
      cout << endl;
		//draw the top bounding line
		cout << "  ....................................." << endl;
	for(int i =0, k = 1; i < SIZE; i ++, k++) {
		//draw the left-most bounding wall 
		cout << k << " |";
		for(int j = 0; j < SIZE; j++) {
			cout << setw(3) << places[i][j] << "|";	
		}
		//make a new line
		cout << endl;
		//draw the bottom bounding box
		cout << "  ....................................." << endl;
	}
		
}


int main() {
	fiveStone();
	return 0;

}