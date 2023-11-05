/*
By: Carlos Gross-Martinez
Fall 2019 - COP 3530
*/
#include "Sudoku.h"
#include <vector>
#include <iostream>
#include <string>
// The games array holds the numbers for each game. There are 81 numbers for each game. There is only one
// game defined for this definition (more can be easily added). The first 9 numbers in the array (elements 0 to 8) represent 
// the first row of a game. The 2nd 9 numbers in the array (elements 9 to 17) represent the 2nd row of a game.
// The show array represents the initial game conditions. If a number is 0 (NO_ENTRY) then it is missing
// on the game board. The numbers from 1 to 9 in the show array are initially provided to the user on the game board.
// These initial numbers are "fixed" on the game board and cannot be changed by the member functions (by the player of the game).
const int Sudoku::games[][Sudoku::TOTAL_BOXES] = { { 2,1,6,7,5,4,8,9,3,  5,7,9,8,2,3,1,6,4,  8,3,4,9,6,1,7,2,5,  4,6,1,3,7,5,9,8,2,  3,9,2,4,8,6,5,1,7,  7,8,5,1,9,2,4,3,6,  1,5,3,6,4,9,2,7,8,  9,4,7,2,3,8,6,5,1,  6,2,8,5,1,7,3,4,9 } };
const int Sudoku::show[][Sudoku::TOTAL_BOXES] = { { 2,0,0,0,0,4,8,0,0,  5,0,9,0,0,3,0,6,0,  0,3,0,9,0,1,0,0,5,  0,0,1,0,0,0,9,0,2,  3,9,0,0,0,0,0,1,7,  7,0,5,0,0,0,4,0,0,  1,0,0,6,0,9,0,7,0,  0,4,0,2,0,0,6,0,1,  0,0,8,5,0,0,0,0,9 } };

// The default constructor will select a game to play. There is only 1 game defined for this
// definition. The default constructor will initialize the game board using the show array.
// The game board must be implemented using an array of vectors where each vector represents
// one row of the game board.

//--- Definition of class constructor
// Selects game to play
// Precondition:  None.
// Postcondition : a vector array is initilized with values of show array
Sudoku::Sudoku()
{
	//variable declaration and initialization to keep track of elements in show array
	int k = 0; 

	//outer loop that will load show array to vector array
	for(int i = 0; i < MAX_ROW_NUM; i++) 
		{
			//inner loop that will load show array to vector array
			for (int j = 0; j < MAX_COLUMN_NUM; j++)
				{	
					//code that will initialize vector array to the values of show array
					vecArr[i].push_back(show[0][k++]);						
				}//end inner for 			
		}//end outer for
}//end constructor

// The member function addNumber() will attempt to add a number to the game board.
// The row input variable represents the row of the input. Valid row inputs are from MIN_ROW_NUM to MAX_ROW_NUM inclusive.
// The column input variable represents the column of the input. Valid column inputs are from MIN_COLUMN_NUM to MAX_COLUMN_NUM
// inclusive. The number input variable represents the number to be placed at the row and column. 
// Valid number inputs are from MIN_NUM to MAX_NUM inclusive. The return value is the status of the function.
// An OUT_OF_BOUNDS_ERROR is returned if the row, column, or number is invalid. An OUT_OF_BOUNDS_ERROR is also returned if the
// the valid row/column is a fixed number (initially shown to the user at the game start).
// In the case of an OUT_OF_BOUNDS_ERROR error, the number is not inserted to the game board.
// If there is no OUT_OF_BOUNDS_ERROR, then check for a GAME_ERROR. 
// A GAME_ERROR is returned if a valid number to be placed at a valid row/column position breaks the sudoku game play rules.
// In the case of a GAME_ERROR, the number is inserted to the game board.
// For example, for game 1 (the only gamefor this definition), addNumber(1, 2, 9) would return a GAME_ERROR
// and insert a 9 to row/column position 1/2 on the game board.
// If an OUT_OF_BOUNDS_ERROR and GAME_ERROR are not detected, then return a NO_ERROR.
// In the case of NO_ERROR, the number is placed on the game board.

//--- Definition of addNumber()
// Adds numbers to the vector array and checks for bound and game errors
// Precondition:  function will receive 3 integer numbers, passed by value which represent
//				  the number that will be inserted and the row and column where it will be inserted
// Postcondition: if location or number is invalid, an out of bounds error will be returned.
//                Otherwise, number will be inserted into game board. If the number is repated
//                in any row or column a game error will be returned. Otherwise, a no error value
//                will be returned to main
int Sudoku::addNumber(int row, int column, int number)
{
	//variable declaration and initialization with the position of show array element 
	//for comparison
	int arrLoc = ((row - 1) * 9) + (column - 1);	

	//conditions that check to ensure number, row, and column passed to function are valid entries 
	if (number < MIN_NUM || number > MAX_NUM ||		
		row < MIN_ROW_NUM || row > MAX_ROW_NUM ||
		column < MIN_COLUMN_NUM || column > MAX_COLUMN_NUM)
		{
			//code that returns error if number, row, or column values are invalid
			return OUT_OF_BOUNDS_ERROR;
		}//end if

	//condition that returns error if there is a fixed number where the insertion (row/column) 
	//is trying to occur
	if (show[0][arrLoc] != 0)
		{
			//code that returns error if location of insertion is a fixed number
			return OUT_OF_BOUNDS_ERROR;
		}//end if

	//code that inserts given number to given row and column in vector array
	vecArr[row - 1][column - 1] = number;

	//loop that will compare given number to row in specified position to avoid duplicates
	for (int i = 0; i < MAX_ROW_NUM; i++)
		{
			//condition that checks that number is not repeated in row
			if (vecArr[i][column - 1] == number)
				{
					//error that is return if number is repeated in provided row
					return GAME_ERROR;
				}//end if
		}//end for

	//loop that will compare given number to column in specified position to avoid duplicates
	for (int j = 0; j < MAX_COLUMN_NUM; j++)
		{
			//condition that checks that number is not repeated in column
			if (vecArr[row - 1][j] == number)
				{
					//error that is return if number is repeated in provided column
					return GAME_ERROR;
				}//end if
		}//end for

	//code that returns no error if there are no rules violations in entries
	return NO_ERROR;
}//end addNumber()

// The member function remove() will attempt to remove a number to the game board.
// The row input variable represents the row of the input. Valid row inputs are from MIN_ROW_NUM to MAX_ROW_NUM inclusive.
// The column input variable represents the column of the input. Valid column inputs are from MIN_COLUMN_NUM to MAX_COLUMN_NUM
// inclusive. The return value is the status of the function.
// An OUT_OF_BOUNDS_ERROR is returned if the row or column is invalid. An OUT_OF_BOUNDS_ERROR is also returned if the
// the valid row/column is a fixed number (initially shown to the user at the game start). If there are no errors encountered, then
// the number at the corresponding row/column will be removed.

//--- Definition of remove()
// removes numbers to the vector array and checks for boundary errors
// Precondition:  function will receive 2 integer numbers, passed by value which represent
//				  the row and column where number will be deleted
// Postcondition: if location is invalid or number being deleted is fixed, an out of bounds error
//                will be returned. Otherwise, the specified location will be set to 0               
int Sudoku::remove(int row, int column)
{
	//variable declaration and initialization with the position of show array element 
	//for comparison
	int arrLoc = ((row - 1) * 9) + (column - 1);

	//conditions that check to ensure row and column passed to function are valid entries 
	if (row < MIN_ROW_NUM || row > MAX_ROW_NUM ||
		column < MIN_COLUMN_NUM || column > MAX_COLUMN_NUM)
		{
			//code that returns error if row or column values are invalid
			return OUT_OF_BOUNDS_ERROR;
		}//end if

	//condition that returns error if there is a fixed number where the deletion (row/column) 
	//is trying to occur
	if (show[0][arrLoc] != 0)
		{
			//code that returns error if location of deletion is a fixed number
			return OUT_OF_BOUNDS_ERROR;
		}//end if

	//code that deletes number by setting the specified location to 0 in vector array
	vecArr[row - 1][column - 1] = 0;

	//return statement
	return 0;
}//end remove

// The member function hasPlayerWonGame() will determine if the player has correctly solved the puzzle.
// The return value of true is returned if the player has correctly solved the puzzle, otherwise false is returned.
// To win the game, all entries in the game board must be entered and match the solution provided in the games array.

//--- Definition of hasPlayerWon()
// checks to see if player has properly solved the puzzle
// Precondition:  None
// Postcondition: function will return true if player won the game. Otherwise, it will return false  
bool Sudoku::hasPlayerWonGame()
{
	//variable declaration and initialization to keep track of elements in games array
	int k = 0;

	//outter loop that will traverse through all rows in vector array for comparison
	for (int i = 0; i < MAX_ROW_NUM; i++)
		{
			//inner loop that will traverse through all columns in vector array for comparison
			for (int j = 0; j < MAX_COLUMN_NUM; j++)
				{
					//condition that checks vector array to games array
					if (games[0][k++] != vecArr[i][j])
						{
							//return statement if games array does not equal vector array
							return false;
						}//end if
				}//end inner loop
		}//end outer loop
	
	//condition that returns to main if game array equals vector array
	return true;
}//end hasPlayerWon()

// The member function display() will display the current state of the game board.
// See an image example provided for the homework.

//--- Definition of display()
// displays current state of the game board
// Precondition:  None
// Postcondition: function will print to the screen the state of the game board 
void Sudoku::display()
{	
	//outer loop that will print all row values to screen
	for (int i = 0; i <= MAX_ROW_NUM; i++)
		{
			//condition that will print the dashed vertical lines at position 0, 3, 6 ,9 in the loop
			//these dash lines will be printed at the top, bottom, and twice in middle
			if (i == 0 || i == 3 || i == 6 || i == 9)
				{
					//code that prints the dashed lines
					std::cout << " ----------------------------------- " << std::endl;;
				}//end if

			//inner loop that will print all columns values to screen
			for (int j = 0; j <= MAX_COLUMN_NUM; j++)
				{
					//condition that will print horizontal lines before a number in the specified locations
					if ((j == 0 || j == 3 || j == 6) && i < MAX_ROW_NUM)
						{
							//code that prints the horizontal lines
							std::cout << "|  ";
						}//end if

					//condition that will print horizontal lines after a number in the specified location
					else if (j == 9 && i < MAX_ROW_NUM)
						{
							//code that prints the horizontal lines
							std::cout << "|";
						}//end else-if

					//condition that ensures the values for row and column are 0 through 8
					if (i < MAX_ROW_NUM && j < MAX_COLUMN_NUM)
						{
							//condition that prints the values of all fixed numbers to screen as long as they are not 0s
							if (vecArr[i][j] != 0)
								{
									//code that prints the value of the fixed number to screen
									std::cout << vecArr[i][j] << "  ";
								}//end if

							//if the fixed number in the show array is 0 a blank space will be printed
							else
								{
									//code that prints blank space to the scree where 0s are located
									std::cout << "   ";
								}	//end else					
						}//end if									
				}//end inner for

			//code that moves cursor to new line for values of next row to be printed
			std::cout << std::endl;	
		}//end outer for
}//end display()

// The member function getBoard() will populate the array input variable with the current game board values.
// The first row of the game board is entered to the first 9 elements of array (elements 0 to 8).
// The second row of the game board is entered to the next 9 elements of array (elements 9 to 17).
// For enteries that do not exist (not entered yet), they should be represented by NO_ENTRY.
// For example, for the game provided, at the beginning of the game before any new numbers are entered,
// the first 9 elements of array should be 2,0,0,0,0,4,8,0,0.

//--- Definition of getBoard()
// will transfer information from vector array to the given array for comparison
// Precondition:  None
// Postcondition: function will transfer all information contained in vector array to the given array
void Sudoku::getBoard(int array[])
{	
	//variable declaration and initialization to keep track of elements in given array
	int k = 0;

	//outer loop that will load vector array to given array
	for (int i = 0; i < MAX_ROW_NUM; i++)
		{
			//Inner loop that will load vector array to given array
			for (int j = 0; j < MAX_COLUMN_NUM; j++)
				{
					//code that will save information form the vector array to the given array
					array[k++] = vecArr[i][j];
				}//end inner loop
		}//end outer loop
}//end getBoard()