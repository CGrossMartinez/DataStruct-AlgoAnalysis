#ifndef SUDOKU_H
#define SUDOKU_H
#include <vector>

class Sudoku
{
public:
	Sudoku();
	int addNumber(int row, int column, int number);
	int remove(int row, int column);
	void display();
	void getBoard(int array[]);
	bool hasPlayerWonGame();
	static const int OUT_OF_BOUNDS_ERROR = -1;
	static const int GAME_ERROR = -2;
	static const int NO_ERROR = 0;
	static const int NO_ENTRY = 0;

private:
	int gameNum; // used to track the game being played, will be 0 for this implementation
	const int MIN_ROW_NUM = 1;
	const int MAX_ROW_NUM = 9;
	const int MIN_COLUMN_NUM = 1;
	const int MAX_COLUMN_NUM = 9;
	const int MIN_NUM = 1;
	const int MAX_NUM = 9;
	const int BOX_SIZE = 3;
	static const int TOTAL_BOXES = 81;
	static const int games[][TOTAL_BOXES];  // defines the games to play
	static const int show[][TOTAL_BOXES];  // defines the games to play

	std::vector<int> vecArr[9]; // array of vectors declaration;
	
};

#endif