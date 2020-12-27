// Coded by OS of The System!

#include<iostream>
#include<iomanip>
#include<Windows.h>
#include<cstring>
#include<fstream>
#include<conio.h>
using namespace std;

enum piece { Empty, Pawn, Rook, Knight, Bishop, Queen, King };
enum player { No, P1, P2 };

void gotoxy(int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void initBoard(piece board[][8], player occupied[][8])
{
	for (int i = 0; i < 8; i++)
	{
		if (i == 0)
		{
			for (int j = 0; j < 8; j++)
			{
				if (j == 0 || j == 7)
					board[i][j] = Rook;
				else if (j == 1 || j == 6)
					board[i][j] = Knight;
				else if (j == 2 || j == 5)
					board[i][j] = Bishop;
				else if (j == 3)
					board[i][j] = Queen;
				else
					board[i][j] = King;
				occupied[i][j] = P2;
			}
		}
		else if (i == 7)
		{
			for (int j = 0; j < 8; j++)
			{
				if (j == 0 || j == 7)
					board[i][j] = Rook;
				else if (j == 1 || j == 6)
					board[i][j] = Knight;
				else if (j == 2 || j == 5)
					board[i][j] = Bishop;
				else if (j == 3)
					board[i][j] = Queen;
				else
					board[i][j] = King;
				occupied[i][j] = P1;
			}
		}
		else if (i == 1)
		{
			for (int j = 0; j < 8; j++)
			{
				board[i][j] = Pawn;
				occupied[i][j] = P2;
			}
		}
		else if (i == 6)
		{
			for (int j = 0; j < 8; j++)
			{
				board[i][j] = Pawn;
				occupied[i][j] = P1;
			}
		}
		else
		{
			for (int j = 0; j < 8; j++)
			{
				board[i][j] = Empty;
				occupied[i][j] = No;
			}
		}
	}
}

int color(player key)
{
	if (key == P1)
		return 15;
	else
		return 8;
}

void printBoard(piece board[][8], player occupied[][8])
{
	cout << setw(50) << "*-*-*-*-*-*-*  CHESS GAME  *-*-*-*-*-*-*\n";
	cout << endl;
	cout << "  ";
	for (int i = 0; i < 16; i++)
	{
		if (i % 2 == 0)
		{
			cout << setw(3) << ' ';
		}
		else
		{
			char key = 'A' + i / 2;
			cout << left << setw(4) << key;
		}
	}
	cout << endl;
	for (int i = 0; i <= 16; i++)
	{
		if (i % 2 == 1)
		{
			cout << 8 - i / 2 << ' ';
			for (int j = 0; j < 8; j++)
			{
				cout << '|';
				int col = color(occupied[i / 2][j]);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), col);
				cout << setw(6) << left;
				if (board[i / 2][j] == Rook)
					cout << "Rook";
				else if (board[i / 2][j] == Knight)
					cout << "Knignt";
				else if (board[i / 2][j] == Bishop)
					cout << "Bishop";
				else if (board[i / 2][j] == Queen)
					cout << "Queen";
				else if (board[i / 2][j] == King)
					cout << "King";
				else if (board[i / 2][j] == Pawn)
					cout << "Pawn";
				else if (board[i / 2][j] == Empty)
					cout << ' ';
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}
			cout << "| " << 8 - i / 2;
		}
		else
		{
			cout << "  ";
			for (int j = 0; j < 8; j++)
			{
				cout << "+------";
			}
			cout << '+';
		}
		cout << endl;
	}

	cout << "  ";
	for (int i = 0; i < 16; i++)
	{
		if (i % 2 == 0)
		{
			cout << setw(3) << ' ';
		}
		else
		{
			char key = 'A' + i / 2;
			cout << left << setw(4) << key;
		}
	}
	cout << endl << endl;
}

void storeMove()
{

}

void validMoves(char ** posMoves[][8], piece board[][8], player occupied[][8])
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			posMoves[i][j] = NULL;
			if (occupied[i][j] == 1)
			{
				if (board[i][j] == King)
				{
					if (i > 0)
					{
						if (occupied[i - 1][j] != 1)
							storeMove();
						if (j > 0 && occupied[i - 1][j - 1] != 1)
							storeMove();
						if (j < 7 && occupied[i - 1][j + 1] != 1)
							storeMove();
					}
					else if (i < 7)
					{
						if (occupied[i + 1][j] != 1)
							storeMove();
						if (j > 0 && occupied[i + 1][j - 1] != 1)
							storeMove();
						if (j < 7 && occupied[i + 1][j + 1] != 1)
							storeMove();
					}
					else
					{
						if (j > 0 && occupied[i][j - 1] != 1)
							storeMove();
						if (j < 7 && occupied[i][j + 1] != 1)
							storeMove();
					}
				}
				else if (board[i][j] == Pawn)
				{
					if (i == 6 && occupied[i - 1][j] == 0 && occupied[i - 2][j] == 0)
						storeMove();
					if (i > 0)
					{
						if (occupied[i - 1][j] == 0)
							storeMove();
						if (j > 0 && occupied[i - 1][j - 1] == 1)
							storeMove();
						else if (j < 7 && occupied[i - 1][j + 1] == 1)
							storeMove();
					}

				}
			}
		}
	}
}

bool checkBlock(char block[])
{
	if (strlen(block) != 2)
		return false;
	else if (tolower(block[0]) < 'a' || tolower(block[0]) > 'h')
		return false;
	else if (block[1] < '1' || block[1] > '8')
		return false;
	return true;
}

void inputBlock(char input[])
{
	bool valid = false;
	while (valid == false)
	{
		cin.getline(input, 100);
		if (checkBlock(input))
			valid = true;
		else
			cout << "Invalid block! Try again: ";
	}
}

void storeBlock(int block[], char input[])
{
	block[1] = tolower(input[0]) - 'a';
	block[0] = 8 - (input[1] - '0');
}

bool checkPath(bool occupied[][8], int s[], int d[])
{
	if (s[0] == d[0])
	{
		if (d[1] > s[1])
		{
			for (int i = s[1] + 1; i < d[1]; i++)
			{
				if (occupied[s[0]][i] == 1)
					return false;
			}
		}
		else
		{
			for (int i = d[1] + 1; i < s[1]; i++)
			{
				if (occupied[s[0]][i] == 1)
					return false;
			}
		}
	}
	else if (s[1] == d[1])
	{
		if (d[0] > s[0])
		{
			for (int i = s[0] + 1; i < d[0]; i++)
			{
				if (occupied[i][s[1]] == 1)
					return false;
			}
		}
		else
		{
			for (int i = d[0] + 1; i < s[0]; i++)
			{
				if (occupied[i][s[1]] == 1)
					return false;
			}
		}
	}
	else if (d[0] > s[0])
	{
		if (d[1] > s[1])
		{
			for (int i = 1; i < (d[0] - s[0]); i++)
			{
				if (occupied[s[0] + i][s[1] + i] == 1)
					return false;
			}
		}
		else
		{
			for (int i = 1; i < (d[0] - s[0]); i++)
			{
				if (occupied[s[0] + i][s[1] - i] == 1)
					return false;
			}
		}
	}
	else if (s[0] > d[0])
	{
		if (d[1] > s[1])
		{
			for (int i = 1; i < (s[0] - d[0]); i++)
			{
				if (occupied[s[0] - i][s[1] + i] == 1)
					return false;
			}
		}
		else
		{
			for (int i = 1; i < (s[0] - d[0]); i++)
			{
				if (occupied[s[0] - i][s[1] - i] == 1)
					return false;
			}
		}
	}
	return true;
}

int checkMove(char board[][8], bool occupied[][8], bool turn, int s[], int d[])
{
	char piece = board[s[0]][s[1]];

	if (occupied[s[0]][s[1]] == 0) // No piece to move
		return 0;
	else if (turn == true) // white player's turn
	{
		if (piece < 97) // Piece belongs to other player
			return -2;
		else if (occupied[d[0]][d[1]] == 1 && board[d[0]][d[1]] > 97) // trying to kill your own piece
			return -1;
		else if (piece == 'k')
		{
			if ((d[0] == s[0] || d[0] == s[0] + 1 || d[0] == s[0] - 1) && (d[1] == s[1] || d[1] == s[1] + 1 || d[1] == s[1] - 1))
				return 1;
			return -1;
		}
		else if (piece == 'q')
		{
			if (s[0] == d[0] || s[1] == d[1] || s[0] - d[0] == s[1] - d[1] || s[0] - d[0] == d[1] - s[1] || d[0] - s[0] == s[1] - d[1] || d[0] - s[0] == d[1] - s[1])
			{
				if (checkPath(occupied, s, d))
					return 1;
			}
			return -1;
		}
		else if (piece == 'b')
		{
			if (s[0] - d[0] == s[1] - d[1] || s[0] - d[0] == d[1] - s[1] || d[0] - s[0] == s[1] - d[1] || d[0] - s[0] == d[1] - s[1])
			{
				if (checkPath(occupied, s, d))
					return 1;
			}
			return -1;
		}
		else if (piece == 'r')
		{
			if (s[0] - d[0] == s[1] - d[1])
			{
				if (checkPath(occupied, s, d))
					return 1;
			}
			return -1;
		}
		else if (piece == 'n')
		{
			if ((d[0] == s[0] + 2 || d[0] == s[0] - 2) && (d[1] == s[1] + 1 || d[1] == s[1] - 1))
				return 1;
			else if ((d[0] == s[0] + 1 || d[0] == s[0] - 1) && (d[1] == s[1] + 2 || d[1] == s[1] - 2))
				return 1;
			return -1;
		}
		else if (piece == 'p')
		{
			if (s[0] == 6 && d[0] == 4 && d[1] == s[1] && occupied[d[0]][d[1]] == 0 && occupied[d[0] - 1][d[1]] == 0)
				return 1;
			else if (d[0] == s[0] - 1 && d[1] == s[1] && occupied[d[0]][d[1]] == 0)
				return 1;
			else if (d[0] == s[0] - 1 && (d[1] == s[1] - 1 || d[1] == s[1] + 1) && occupied[d[0]][d[1]] == 1)
				return 1;
			return -1;
		}
	}
	else // black player's turn
	{
		if (piece > 97)
			return -2;
		else if (occupied[d[0]][d[1]] == 1 && board[d[0]][d[1]] < 97)
			return -1;
		else if (piece == 'K')
		{
			if ((d[0] == s[0] || d[0] == s[0] + 1 || d[0] == s[0] - 1) && (d[1] == s[1] || d[1] == s[1] + 1 || d[1] == s[1] - 1))
				return 1;
			return -1;
		}
		else if (piece == 'Q')
		{
			if (s[0] == d[0] || s[1] == d[1] || s[0] - d[0] == s[1] - d[1] || s[0] - d[0] == d[1] - s[1] || d[0] - s[0] == s[1] - d[1] || d[0] - s[0] == d[1] - s[1])
			{
				if (checkPath(occupied, s, d))
					return 1;
			}
			return -1;
		}
		else if (piece == 'B')
		{
			if (s[0] - d[0] == s[1] - d[1] || s[0] - d[0] == d[1] - s[1] || d[0] - s[0] == s[1] - d[1] || d[0] - s[0] == d[1] - s[1])
			{
				if (checkPath(occupied, s, d))
					return 1;
			}
			return -1;
		}
		else if (piece == 'R')
		{
			if (s[0] - d[0] == s[1] - d[1])
			{
				if (checkPath(occupied, s, d))
					return 1;
			}
			return -1;
		}
		else if (piece == 'N')
		{
			if ((d[0] == s[0] + 2 || d[0] == s[0] - 2) && (d[1] == s[1] + 1 || d[1] == s[1] - 1))
				return 1;
			else if ((d[0] == s[0] + 1 || d[0] == s[0] - 1) && (d[1] == s[1] + 2 || d[1] == s[1] - 2))
				return 1;
			return -1;
		}
		else if (piece == 'P')
		{
			if (s[0] == 1 && d[1] == s[1] && (d[0] <= 3 && d[0] > 1))
				return 1;
			else if (d[0] == s[0] + 1 && d[1] == s[1])
				return 1;
			else if (d[0] == s[0] + 1 && (d[1] == s[1] + 1 || d[1] == s[1] - 1) && occupied[d[0]][d[1]] == 1)
				return 1;
			return -1;
		}
	}
	return 1;
}

void makeMove(char board[][8], bool occupied[][8], bool turn, int s[], int d[])
{
	board[d[0]][d[1]] = board[s[0]][s[1]];
	occupied[d[0]][d[1]] = 1;
	board[s[0]][s[1]] = NULL;
	occupied[s[0]][s[1]] = 0;
}

void load(char board[][8], bool occupied[][8])
{
	ifstream fin("board.txt");
	char ch;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			fin.get(ch);
			if (ch == '\n')
				j--;
			else if (ch == ' ')
			{
				board[i][j] = NULL;
				occupied[i][j] = 0;
			}
			else
			{
				board[i][j] = ch;
				occupied[i][j] = 1;
			}
		}
	}
	fin.close();
}

void save(char board[][8])
{
	ofstream fout("board.txt");
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j] == NULL)
				fout << ' ';
			else
				fout << board[i][j];
		}
		fout << endl;
	}
	fout.close();
}

int main()
{
	piece board[8][8];
	player occupied[8][8];
	bool turn = true;
	/*
	cout << setw(50) << "*-*-*-*-*-*-*  CHESS GAME  *-*-*-*-*-*-*\n";
	cout << endl;

	char key = NULL;
	cout << "Press 1 for new game\n";
	cout << "Press 2 to Load save\n";

	while (key != '1' && key != '2')
	{
		key = _getch();
	}

	if (key == '1')
	{
		initBoard(board, occupied);
		save(board);
	}
	else
	{
		load(board, occupied);
	}

	gotoxy(0, 0);
	*/

	initBoard(board, occupied);

	while (true)
	{
		char ** posMoves[8][8];
		char input[100];
		int source[2];
		int des[2];
		bool valid = false;

		printBoard(board, occupied);
		validMoves(posMoves, board, occupied);

		if (turn == false)
			cout << "Black Player's Turn\n";
		else
			cout << "White Player's Turn\n";
		cout << endl;
		while (valid == false)
		{
			cout << "Enter source(eg. e4): ";
			inputBlock(input);
			storeBlock(source, input);

			cout << "Enter destination(eg. e5): ";
			inputBlock(input);
			storeBlock(des, input);

			//int move = checkMove(board, occupied, turn, source, des);
			/*
			if (move == 0)
				cout << "Invalid Move! No piece to move\n";
			else if (move == -1)
				cout << "Invalid Move! Piece can not move like this\n";
			else if (move == -2)
				cout << "Invalid Move! Piece does not belong to player!\n";
			else
				valid = true;
			cout << endl;
			*/
		}
		//makeMove(board, occupied, turn, source, des);

		turn = !turn;
		system("CLS");
	}

	system("pause");
	return 0;
}