#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

class Board
{
public:
	void Play()		//This function handles the game loop
	{
		std::cout << "Start!" << '\n' << '\n';
		PrintBoard();

		while (CheckBoard() == 0)
		{
			MakeMove();
			PrintBoard();
		}

		if (CheckBoard() == 1) //Check whether a player has won, else show "Draw"
		{
			if (turnCount % 2 == 0)
			{
				std::cout << "Game Over - Player O has won!" << '\n';
			}
			else
			{
				std::cout << "Game Over - Player X has won!" << '\n';
			}
		}
		else
		{
			std::cout << "Draw" << '\n';
		}
	}
	
	
	void PrintBoard()
	{
		std::cout << "Current Board:" << '\n';
		
		for (int i = 0; i < maxSize; i++)	//Loop through the board and draw it to the console
		{
			if (brd.at(i) == 0)
			{
				std::cout << " " << i << " ";
			}
			else if (brd.at(i) == 1)
			{
				std::cout << " X ";
			}
			else
			{
				std::cout << " O ";
			}

			if (((maxSize % (i + 1)) == rowSize || (maxSize % (i + 1) == 0)) &&		//Draw a horizontal divider between rows after drawing the 3rd and 6th cells
				((i != 0) && ((i + 1) != maxSize)))
			{
				std::cout << '\n' << "-----------" << '\n';
			}
			else if (i != maxSize - 1)		//Draw a divider for each cell except when moving to a lower row or at the last cell
			{
				std::cout << '|';
			}
		}

		std::cout << '\n' << '\n';
	}


	bool IsValidMove(int pos)
	{
		if (pos >= 0 && pos < 9)	//Sanity check
		{
			if (brd.at(pos) != 0)	//If the position is already taken, return false
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		else
		{
			return false;
		}
	}


	void MakeMove()
	{
		std::string pos = "";
		int intPos = 9;
		bool validMove = false;

		while (!validMove) //If the int value of the first character given by the user is greater than 8/less than 0, get more input
		{
			if (turnCount % 2 == 0) //Print Player X or O depending on the turn counter
			{
				std::cout << "Player X: Enter the position of your move: ";
			}
			else
			{
				std::cout << "Player O: Enter the position of your move: ";
			}

			std::cin >> pos;

			//If the first char entered is not between 0 and 8 (inclusive), set pos to "9"...
			//...so that the loop will continue until a valid number is entered
			if (pos[0] < '0' || pos[0] > '8')
			{
				pos = "9";
			}

			intPos = std::stoi(pos); //Convert the char in pos to an int

			if (intPos < 9)
			{
				validMove = IsValidMove(intPos);
			}

			std::cin.ignore(INT_MAX, '\n'); //Ignore any other characters the user entered
		}

		std::cout << '\n';

		if (turnCount % 2 == 0) //Place an X or O according to the turn counter
		{
			brd.at(intPos) = 1;
		}
		else
		{
			brd.at(intPos) = 2;
		}

		turnCount++;
	}


	int CheckBoard() //0 = ongoing, 1 = win, 2 = draw
	{
		bool fullbrd = false;
		bool rowsequal = true;
		bool colsequal = true;
		bool dia1equal = true;
		bool dia2equal = true;

		//Check for full board/potential draw
		if (std::find(brd.begin(), brd.end(), 0) == brd.end())
		{
			fullbrd = true;
		}

		//Check rows, columns, and diagonals by copying the board cells of interest
		std::vector<int> rows = std::vector<int>(rowSize, 0);
		std::vector<int> cols = std::vector<int>(rowSize, 0);
		std::vector<int> diag1 = std::vector<int>(rowSize, 0);
		std::vector<int> diag2 = std::vector<int>(rowSize, 0);
		
		for (int i = 0; i < rowSize; i++)
		{
			rowsequal = true;
			colsequal = true;

			//Loop through each row and column and check if they all have Xs or Os
			for (int j = 0; j < rowSize; j++)
			{
				rows.at(j) = brd.at((i * rowSize) + j);
				cols.at(j) = brd.at((j * rowSize) + i);

				if (rows.at(j) == 0)
				{
					rowsequal = false;
				}
				if (cols.at(j) == 0)
				{
					colsequal = false;
				}
			}

			//Use equal() to check if all cells in a row/col are the same (checks cells 2 and 1, then 3 and 2)
			if (!(std::equal(rows.begin() + 1, rows.end(), rows.begin())))
			{
				rowsequal = false;
			}
			if (!(std::equal(cols.begin() + 1, cols.end(), cols.begin())))
			{
				colsequal = false;
			}

			if (rowsequal || colsequal)
			{
				return 1;
			}

			//Get the two diagonals [(0, 4, 8) and (2, 4, 6)] and check if they have all Xs or Os
			diag1.at(i) = brd.at((i * rowSize) + i);
			diag2.at(i) = brd.at((i * rowSize) + (rowSize - (1 + i)));

			if (diag1.at(i) == 0)
			{
				dia1equal = false;
			}
			if (diag2.at(i) == 0)
			{
				dia2equal = false;
			}
		}

		if (!(std::equal(diag1.begin() + 1, diag1.end(), diag1.begin())))
		{
			dia1equal = false;
		}
		if (!(std::equal(diag2.begin() + 1, diag2.end(), diag2.begin())))
		{
			dia2equal = false;
		}

		if (dia1equal || dia2equal)
		{
			return 1;
		}

		if (fullbrd)
		{
			return 2;
		}
		else
		{
			return 0;
		}
	}

private:
	int maxSize = 9;
	int rowSize = 3;
	int turnCount = 0;
	int brdState = 0;	//For potential future use in choosing when to draw the board
	std::vector<int> brd = std::vector<int>(maxSize, 0); //0 = open, 1 = X, 2 = O
};



int main()
{
	Board b;
	b.Play();

	return 0;
}