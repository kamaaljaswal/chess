// Coded by OS of The System!

#include<iostream>
#include<iomanip>
#include<Windows.h>
#include<cstring>
#include<fstream>
#include<conio.h>
using namespace std;

#pragma region
void initBoard(char board[][8])
{
	for (int i = 0; i < 8; i++)
	{
		if (i == 0)
		{
			for (int j = 0; j < 8; j++)
			{
				if (j == 0 || j == 7)
					board[i][j] = 'R';
				else if (j == 1 || j == 6)
					board[i][j] = 'N';
				else if (j == 2 || j == 5)
					board[i][j] = 'B';
				else if (j == 3)
					board[i][j] = 'Q';
				else
					board[i][j] = 'K';
			}
		}
		else if (i == 7)
		{
			for (int j = 0; j < 8; j++)
			{
				if (j == 0 || j == 7)
					board[i][j] = 'r';
				else if (j == 1 || j == 6)
					board[i][j] = 'n';
				else if (j == 2 || j == 5)
					board[i][j] = 'b';
				else if (j == 3)
					board[i][j] = 'q';
				else
					board[i][j] = 'k';
			}
		}
		else if (i == 1)
		{
			for (int j = 0; j < 8; j++)
			{
				board[i][j] = 'P';
			}
		}
		else if (i == 6)
		{
			for (int j = 0; j < 8; j++)
			{
				board[i][j] = 'p';
			}
		}
		else
		{
			for (int j = 0; j < 8; j++)
			{
				board[i][j] = NULL;
			}
		}
	}
}
#pragma endregion Initializion

#pragma region
void gotoxy(int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int color(char key)
{
	int col;
	if (key > 'a')
		col = 15;
	else
		col = 8;
	return col;
}

void printBoard(char board[][8])
{
	cout << right;
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
				int col = color(board[i / 2][j]);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), col);
				cout << setw(6) << left;
				if (board[i / 2][j] == 'R' || board[i / 2][j] == 'r')
					cout << "Rook";
				else if (board[i / 2][j] == 'N' || board[i / 2][j] == 'n')
					cout << "Knignt";
				else if (board[i / 2][j] == 'B' || board[i / 2][j] == 'b')
					cout << "Bishop";
				else if (board[i / 2][j] == 'Q' || board[i / 2][j] == 'q')
					cout << "Queen";
				else if (board[i / 2][j] == 'K' || board[i / 2][j] == 'k')
					cout << "King";
				else if (board[i / 2][j] == 'P' || board[i / 2][j] == 'p')
					cout << "Pawn";
				else if (board[i / 2][j] == NULL)
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
#pragma endregion Printing

#pragma region
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
#pragma endregion Input Move

#pragma region
bool checkPath(char board[][8], int s[], int d[])
{
	if (s[0] == d[0])
	{
		if (d[1] > s[1])
		{
			for (int i = s[1] + 1; i < d[1]; i++)
			{
				if (board[s[0]][i] != NULL)
					return false;
			}
		}
		else
		{
			for (int i = d[1] + 1; i < s[1]; i++)
			{
				if (board[s[0]][i] != NULL)
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
				if (board[i][s[1]] != NULL)
					return false;
			}
		}
		else
		{
			for (int i = d[0] + 1; i < s[0]; i++)
			{
				if (board[i][s[1]] != NULL)
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
				if (board[s[0] + i][s[1] + i] != NULL)
					return false;
			}
		}
		else
		{
			for (int i = 1; i < (d[0] - s[0]); i++)
			{
				if (board[s[0] + i][s[1] - i] != NULL)
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
				if (board[s[0] - i][s[1] + i] != NULL)
					return false;
			}
		}
		else
		{
			for (int i = 1; i < (s[0] - d[0]); i++)
			{
				if (board[s[0] - i][s[1] - i] != NULL)
					return false;
			}
		}
	}
	return true;
}

int checkMove(char board[][8], bool turn, int s[], int d[])
{
	char piece = board[s[0]][s[1]];
	int valid = 1;

	if (piece == NULL) // No piece to move
		valid = 0;
	else if (turn == true) // white player's turn
	{
		if (piece < 97) // Piece belongs to other player
			valid = -2;
		else if (board[d[0]][d[1]] != NULL && board[d[0]][d[1]] > 97) // trying to kill your own piece
			valid = -1;
		else if (piece == 'k')
		{
			if ((d[0] == s[0] || d[0] == s[0] + 1 || d[0] == s[0] - 1) && (d[1] == s[1] || d[1] == s[1] + 1 || d[1] == s[1] - 1))
				valid = 1;
			else
				valid = -1;
		}
		else if (piece == 'q')
		{
			if (s[0] == d[0] || s[1] == d[1] || s[0] - d[0] == s[1] - d[1] || s[0] - d[0] == d[1] - s[1] || d[0] - s[0] == s[1] - d[1] || d[0] - s[0] == d[1] - s[1])
			{
				if (checkPath(board, s, d))
					valid = 1;
				else
					valid = -1;
			}
			else
				valid = -1;
		}
		else if (piece == 'b')
		{
			if (s[0] - d[0] == s[1] - d[1] || s[0] - d[0] == d[1] - s[1] || d[0] - s[0] == s[1] - d[1] || d[0] - s[0] == d[1] - s[1])
			{
				if (checkPath(board, s, d))
					valid = 1;
				else
					valid = -1;
			}
			else
				valid = -1;
		}
		else if (piece == 'r')
		{
			if (s[0] == d[0] || s[1] == d[1])
			{
				if (checkPath(board, s, d))
					valid = 1;
				else
					valid = -1;
			}
			else
				valid = -1;
		}
		else if (piece == 'n')
		{
			if ((d[0] == s[0] + 2 || d[0] == s[0] - 2) && (d[1] == s[1] + 1 || d[1] == s[1] - 1))
				valid = 1;
			else if ((d[0] == s[0] + 1 || d[0] == s[0] - 1) && (d[1] == s[1] + 2 || d[1] == s[1] - 2))
				valid = 1;
			else
				valid = -1;
		}
		else if (piece == 'p')
		{
			if (s[0] == 6 && d[0] == 4 && d[1] == s[1] && board[d[0]][d[1]] == NULL && board[d[0] + 1][d[1]] == NULL)
				valid = 1;
			else if (d[0] == s[0] - 1 && d[1] == s[1] && board[d[0]][d[1]] == NULL)
				valid = 1;
			else if (d[0] == s[0] - 1 && (d[1] == s[1] - 1 || d[1] == s[1] + 1) && board[d[0]][d[1]] != NULL)
				valid = 1;
			else
				valid = -1;
		}
	}
	else // black player's turn
	{
		if (piece > 97)
			valid = -2;
		else if (board[d[0]][d[1]] != NULL && board[d[0]][d[1]] < 97)
			valid = -1;
		else if (piece == 'K')
		{
			if ((d[0] == s[0] || d[0] == s[0] + 1 || d[0] == s[0] - 1) && (d[1] == s[1] || d[1] == s[1] + 1 || d[1] == s[1] - 1))
				valid = 1;
			else
				valid = -1;
		}
		else if (piece == 'Q')
		{
			if (s[0] == d[0] || s[1] == d[1] || s[0] - d[0] == s[1] - d[1] || s[0] - d[0] == d[1] - s[1] || d[0] - s[0] == s[1] - d[1] || d[0] - s[0] == d[1] - s[1])
			{
				if (checkPath(board, s, d))
					valid = 1;
				else
					valid = -1;
			}
			else
				valid = -1;
		}
		else if (piece == 'B')
		{
			if (s[0] - d[0] == s[1] - d[1] || s[0] - d[0] == d[1] - s[1] || d[0] - s[0] == s[1] - d[1] || d[0] - s[0] == d[1] - s[1])
			{
				if (checkPath(board, s, d))
					valid = 1;
				else
					valid = -1;
			}
			else
				valid = -1;
		}
		else if (piece == 'R')
		{
			if (s[0] == d[0] || s[1] == d[1])
			{
				if (checkPath(board, s, d))
					valid = 1;
				else
					valid = -1;
			}
			else
				valid = -1;
		}
		else if (piece == 'N')
		{
			if ((d[0] == s[0] + 2 || d[0] == s[0] - 2) && (d[1] == s[1] + 1 || d[1] == s[1] - 1))
				valid = 1;
			else if ((d[0] == s[0] + 1 || d[0] == s[0] - 1) && (d[1] == s[1] + 2 || d[1] == s[1] - 2))
				valid = 1;
			else
				valid = -1;
		}
		else if (piece == 'P')
		{
			if (s[0] == 1 && d[0] == 3 && d[1] == s[1] && board[d[0]][d[1]] == NULL && board[d[0] - 1][d[1]] == NULL)
				valid = 1;
			else if (d[0] == s[0] + 1 && d[1] == s[1] && board[d[0]][d[1]] == NULL)
				valid = 1;
			else if (d[0] == s[0] + 1 && (d[1] == s[1] + 1 || d[1] == s[1] - 1) && board[d[0]][d[1]] != NULL)
				valid = 1;
			else
				valid = -1;
		}
	}

	return valid;
}

void makeMove(char board[][8], int s[], int d[])
{
	board[d[0]][d[1]] = board[s[0]][s[1]];
	board[s[0]][s[1]] = NULL;
}
#pragma endregion Validating Move

#pragma region
bool checkByEnemy(char board[][8], bool turn)
{
	if (turn)
	{
		int s[2];
		int d[2];
		for (int i = 0; i < 8; i++)
		{
			bool out = false;
			for (int j = 0; j < 8; j++)
			{
				if (board[i][j] == 'k')
				{
					d[0] = i;
					d[1] = j;
					out = true;
					break;
				}
			}
			if (out)
				break;
		}

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (board[i][j] < 'a' && board[i][j] != NULL)
				{
					s[0] = i;
					s[1] = j;

					if (checkMove(board, !turn, s, d) == 1)
						return true;
				}
			}
		}
	}
	else
	{
		int s[2];
		int d[2];
		for (int i = 0; i < 8; i++)
		{
			bool out = false;
			for (int j = 0; j < 8; j++)
			{
				if (board[i][j] == 'K')
				{
					d[0] = i;
					d[1] = j;
					out = true;
					break;
				}
			}
			if (out)
				break;
		}

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (board[i][j] > 'a' && board[i][j] != NULL)
				{
					s[0] = i;
					s[1] = j;

					if (checkMove(board, !turn, s, d) == 1)
						return true;
				}
			}
		}
	}
	return false;
}

bool checkRemains(char board[][8], bool turn, int s[], int d[])
{
	char del_ch = board[d[0]][d[1]];

	makeMove(board, s, d);

	bool check = checkByEnemy(board, turn);

	makeMove(board, d, s);
	board[d[0]][d[1]] = del_ch;

	return check;
}

int mates(char board[][8], bool turn, bool check)
{
	bool valid = 0;

	for (int i = 0; valid != 1 && i < 8; i++)
	{
		for (int j = 0; valid != 1 && j < 8; j++)
		{
			int s[2] = { i,j };
			if ((board[i][j] == 'k' && turn) || (board[i][j] == 'K' && !turn))
			{
				for (int k = 0; k < 6; k++)
				{
					if (k == 0)
					{
						int d[2] = { i + 1, j };

						if (d[0] < 8 && d[0] >= 0 && d[1] >= 0 && d[1] < 8)
						{
							int move = checkMove(board, turn, s, d);
							if (move == 1)
							{
								if (!checkRemains(board, turn, s, d))
								{
									valid = 1;
									break;
								}
							}
						}
					}
					else if (k == 1)
					{
						int d[2] = { i + 1,j - 1 };
						if (d[0] < 8 && d[0] >= 0 && d[1] >= 0 && d[1] < 8)
						{
							int move = checkMove(board, turn, s, d);
							if (move == 1)
							{
								if (!checkRemains(board, turn, s, d))
								{
									valid = 1;
									break;
								}
							}
						}
					}
					else if (k == 2)
					{
						int d[2] = { i + 1, j - 1 };
						if (d[0] < 8 && d[0] >= 0 && d[1] >= 0 && d[1] < 8)
						{
							int move = checkMove(board, turn, s, d);
							if (move == 1)
							{
								if (!checkRemains(board, turn, s, d))
								{
									valid = 1;
									break;
								}
							}
						}
					}
					else if (k == 3)
					{
						int d[2] = { i - 1,j };
						if (d[0] < 8 && d[0] >= 0 && d[1] >= 0 && d[1] < 8)
						{
							int move = checkMove(board, turn, s, d);
							if (move == 1)
							{
								if (!checkRemains(board, turn, s, d))
								{
									valid = 1;
									break;
								}
							}
						}
					}
					else if (k == 4)
					{
						int d[2] = { i - 1,j - 1 };
						if (d[0] < 8 && d[0] >= 0 && d[1] >= 0 && d[1] < 8)
						{
							int move = checkMove(board, turn, s, d);
							if (move == 1)
							{
								if (!checkRemains(board, turn, s, d))
								{
									valid = 1;
									break;
								}
							}
						}
					}
					else if (k == 5)
					{
						int d[2] = { i - 1,j + 1 };
						if (d[0] < 8 && d[0] >= 0 && d[1] >= 0 && d[1] < 8)
						{
							int move = checkMove(board, turn, s, d);
							if (move == 1)
							{
								if (!checkRemains(board, turn, s, d))
								{
									valid = 1;
									break;
								}
							}
						}
					}
					else if (k == 6)
					{
						int d[2] = { i,j + 1 };
						if (d[0] < 8 && d[0] >= 0 && d[1] >= 0 && d[1] < 8)
						{
							int move = checkMove(board, turn, s, d);
							if (move == 1)
							{
								if (!checkRemains(board, turn, s, d))
								{
									valid = 1;
									break;
								}
							}
						}
					}
					else if (k == 7)
					{
						int d[2] = { i,j - 1 };
						if (d[0] < 8 && d[0] >= 0 && d[1] >= 0 && d[1] < 8)
						{
							int move = checkMove(board, turn, s, d);
							if (move == 1)
							{
								if (!checkRemains(board, turn, s, d))
								{
									valid = 1;
									break;
								}
							}
						}
					}
				}
			}
			else if ((board[i][j] == 'q' && turn) || (board[i][j] == 'K' && !turn))
			{
				for (int k = 0; valid != 1 && k < 8; k++)
				{
					if (k == 0)
					{
						int a = 0;
						while (true)
						{
							int d[2] = { i + a,j };
							if (d[0] < 8 && d[0] >= 0 && d[1] >= 0 && d[1] < 8)
							{
								int move = checkMove(board, turn, s, d);
								if (move == 1)
								{
									if (!checkRemains(board, turn, s, d))
									{
										valid = 1;
										break;
									}
								}
								else
									break;
								a++;
							}
							else
								break;
						}
					}
					else if (k == 1)
					{
						int a = 0;
						while (true)
						{
							int d[2] = { i - a,j };
							if (d[0] < 8 && d[0] >= 0 && d[1] >= 0 && d[1] < 8)
							{
								int move = checkMove(board, turn, s, d);
								if (move == 1)
								{
									if (!checkRemains(board, turn, s, d))
									{
										valid = 1;
										break;
									}
								}
								else
									break;
								a++;
							}
							else
								break;
						}
					}
					else if (k == 2)
					{
						int a = 0;
						while (true)
						{
							int d[2] = { i,j + a };
							if (d[0] < 8 && d[0] >= 0 && d[1] >= 0 && d[1] < 8)
							{
								int move = checkMove(board, turn, s, d);
								if (move == 1)
								{
									if (!checkRemains(board, turn, s, d))
									{
										valid = 1;
										break;
									}
								}
								else
									break;
								a++;
							}
							else
								break;
						}
					}
					else if (k == 3)
					{
						int a = 0;
						while (true)
						{
							int d[2] = { i,j - a };
							if (d[0] < 8 && d[0] >= 0 && d[1] >= 0 && d[1] < 8)
							{
								int move = checkMove(board, turn, s, d);
								if (move == 1)
								{
									if (!checkRemains(board, turn, s, d))
									{
										valid = 1;
										break;
									}
								}
								else
									break;
								a++;
							}
							else
								break;
						}
					}
					else if (k == 4)
					{
						int a = 0;
						while (true)
						{
							int d[2] = { i + a,j + a };
							if (d[0] < 8 && d[0] >= 0 && d[1] >= 0 && d[1] < 8)
							{
								int move = checkMove(board, turn, s, d);
								if (move == 1)
								{
									if (!checkRemains(board, turn, s, d))
									{
										valid = 1;
										break;
									}
								}
								else
									break;
								a++;
							}
							else
								break;
						}
					}
					else if (k == 5)
					{
						int a = 0;
						while (true)
						{
							int d[2] = { i + a,j - a };
							if (d[0] < 8 && d[0] >= 0 && d[1] >= 0 && d[1] < 8)
							{
								int move = checkMove(board, turn, s, d);
								if (move == 1)
								{
									if (!checkRemains(board, turn, s, d))
									{
										valid = 1;
										break;
									}
								}
								else
									break;
								a++;
							}
							else
								break;
						}
					}
					else if (k == 6)
					{
						int a = 0;
						while (true)
						{
							int d[2] = { i - a,j + a };
							if (d[0] < 8 && d[0] >= 0 && d[1] >= 0 && d[1] < 8)
							{
								int move = checkMove(board, turn, s, d);
								if (move == 1)
								{
									if (!checkRemains(board, turn, s, d))
									{
										valid = 1;
										break;
									}
								}
								else
									break;
								a++;
							}
							else
								break;
						}
					}
					else if (k == 7)
					{
						int a = 0;
						while (true)
						{
							int d[2] = { i - a,j + a };
							if (d[0] < 8 && d[0] >= 0 && d[1] >= 0 && d[1] < 8)
							{
								int move = checkMove(board, turn, s, d);
								if (move == 1)
								{
									if (!checkRemains(board, turn, s, d))
									{
										valid = 1;
										break;
									}
								}
								else
									break;
								a++;
							}
							else
								break;
						}
					}
				}
			}
			else if ((board[i][j] == 'r' && turn) || (board[i][j] == 'R' && !turn))
			{
				for (int k = 0; valid != 1 && k < 4; k++)
				{
					if (k == 0)
					{
						int a = 0;
						while (true)
						{
							int d[2] = { i + a,j };
							if (d[0] < 8 && d[0] >= 0 && d[1] >= 0 && d[1] < 8)
							{
								int move = checkMove(board, turn, s, d);
								if (move == 1)
								{
									if (!checkRemains(board, turn, s, d))
									{
										valid = 1;
										break;
									}
								}
								else
									break;
								a++;
							}
							else
								break;
						}
					}
					else if (k == 1)
					{
						int a = 0;
						while (true)
						{
							int d[2] = { i - a,j };
							if (d[0] < 8 && d[0] >= 0 && d[1] >= 0 && d[1] < 8)
							{
								int move = checkMove(board, turn, s, d);
								if (move == 1)
								{
									if (!checkRemains(board, turn, s, d))
									{
										valid = 1;
										break;
									}
								}
								else
									break;
								a++;
							}
							else
								break;
						}
					}
					else if (k == 2)
					{
						int a = 0;
						while (true)
						{
							int d[2] = { i,j + a };
							if (d[0] < 8 && d[0] >= 0 && d[1] >= 0 && d[1] < 8)
							{
								int move = checkMove(board, turn, s, d);
								if (move == 1)
								{
									if (!checkRemains(board, turn, s, d))
									{
										valid = 1;
										break;
									}
								}
								else
									break;
								a++;
							}
							else
								break;
						}
					}
					else if (k == 3)
					{
						int a = 0;
						while (true)
						{
							int d[2] = { i,j - a };
							if (d[0] < 8 && d[0] >= 0 && d[1] >= 0 && d[1] < 8)
							{
								int move = checkMove(board, turn, s, d);
								if (move == 1)
								{
									if (!checkRemains(board, turn, s, d))
									{
										valid = 1;
										break;
									}
								}
								else
									break;
								a++;
							}
							else
								break;
						}
					}
				}
			}
			else if ((board[i][j] == 'b' && turn) || (board[i][j] == 'B' && !turn))
			{
				for (int k = 0; valid != 1 && k < 4; k++)
				{
					if (k == 0)
					{
						int a = 0;
						while (true)
						{
							int d[2] = { i + a,j + a };
							if (d[0] < 8 && d[0] >= 0 && d[1] >= 0 && d[1] < 8)
							{
								int move = checkMove(board, turn, s, d);
								if (move == 1)
								{
									if (!checkRemains(board, turn, s, d))
									{
										valid = 1;
										break;
									}
								}
								else
									break;
								a++;
							}
							else
								break;
						}
					}
					else if (k == 1)
					{
						int a = 0;
						while (true)
						{
							int d[2] = { i + a,j - a };
							if (d[0] < 8 && d[0] >= 0 && d[1] >= 0 && d[1] < 8)
							{
								int move = checkMove(board, turn, s, d);
								if (move == 1)
								{
									if (!checkRemains(board, turn, s, d))
									{
										valid = 1;
										break;
									}
								}
								else
									break;
								a++;
							}
							else
								break;
						}
					}
					else if (k == 2)
					{
						int a = 0;
						while (true)
						{
							int d[2] = { i - a,j + a };
							if (d[0] < 8 && d[0] >= 0 && d[1] >= 0 && d[1] < 8)
							{
								int move = checkMove(board, turn, s, d);
								if (move == 1)
								{
									if (!checkRemains(board, turn, s, d))
									{
										valid = 1;
										break;
									}
								}
								else
									break;
								a++;
							}
							else
								break;
						}
					}
					else if (k == 3)
					{
						int a = 0;
						while (true)
						{
							int d[2] = { i - a,j + a };
							if (d[0] < 8 && d[0] >= 0 && d[1] >= 0 && d[1] < 8)
							{
								int move = checkMove(board, turn, s, d);
								if (move == 1)
								{
									if (!checkRemains(board, turn, s, d))
									{
										valid = 1;
										break;
									}
								}
								else
									break;
								a++;
							}
							else
								break;
						}
					}
				}
			}
			else if ((board[i][j] == 'n' && turn) || (board[i][j] == 'N' && !turn))
			{
				for (int k = 0; k < 8; k++)
				{
					if (k == 0)
					{
						int d[2] = { i - 2,j + 1 };
						if (d[0] < 8 && d[0] >= 0 && d[1] >= 0 && d[1] < 8)
						{
							int move = checkMove(board, turn, s, d);
							if (move == 1)
							{
								if (!checkRemains(board, turn, s, d))
								{
									valid = 1;
									break;
								}
							}
						}
					}
					else if (k == 1)
					{
						int d[2] = { i - 2,j - 1 };
						if (d[0] < 8 && d[0] >= 0 && d[1] >= 0 && d[1] < 8)
						{
							int move = checkMove(board, turn, s, d);
							if (move == 1)
							{
								if (!checkRemains(board, turn, s, d))
								{
									valid = 1;
									break;
								}
							}
						}
					}
					else if (k == 2)
					{
						int d[2] = { i + 2,j + 1 };
						if (d[0] < 8 && d[0] >= 0 && d[1] >= 0 && d[1] < 8)
						{
							int move = checkMove(board, turn, s, d);
							if (move == 1)
							{
								if (!checkRemains(board, turn, s, d))
								{
									valid = 1;
									break;
								}
							}
						}
					}
					else if (k == 3)
					{
						int d[2] = { i + 2,j - 1 };
						if (d[0] < 8 && d[0] >= 0 && d[1] >= 0 && d[1] < 8)
						{
							int move = checkMove(board, turn, s, d);
							if (move == 1)
							{
								if (!checkRemains(board, turn, s, d))
								{
									valid = 1;
									break;
								}
							}
						}
					}
					else if (k == 4)
					{
						int d[2] = { i - 1,j + 2 };
						if (d[0] < 8 && d[0] >= 0 && d[1] >= 0 && d[1] < 8)
						{
							int move = checkMove(board, turn, s, d);
							if (move == 1)
							{
								if (!checkRemains(board, turn, s, d))
								{
									valid = 1;
									break;
								}
							}
						}
					}
					else if (k == 5)
					{
						int d[2] = { i - 1,j - 2 };
						if (d[0] < 8 && d[0] >= 0 && d[1] >= 0 && d[1] < 8)
						{
							int move = checkMove(board, turn, s, d);
							if (move == 1)
							{
								if (!checkRemains(board, turn, s, d))
								{
									valid = 1;
									break;
								}
							}
						}
					}
					else if (k == 6)
					{
						int d[2] = { i + 1,j + 2 };
						if (d[0] < 8 && d[0] >= 0 && d[1] >= 0 && d[1] < 8)
						{
							int move = checkMove(board, turn, s, d);
							if (move == 1)
							{
								if (!checkRemains(board, turn, s, d))
								{
									valid = 1;
									break;
								}
							}
						}
					}
					else if (k == 7)
					{
						int d[2] = { i + 1,j - 2 };
						if (d[0] < 8 && d[0] >= 0 && d[1] >= 0 && d[1] < 8)
						{
							int move = checkMove(board, turn, s, d);
							if (move == 1)
							{
								if (!checkRemains(board, turn, s, d))
								{
									valid = 1;
									break;
								}
							}
						}
					}
				}
			}
			else if ((board[i][j] == 'p' && turn) || (board[i][j] == 'P' && !turn))
			{
				for (int k = 0; k < 8; k++)
				{
					if (k == 0)
					{
						int d[2] = { i - 2,j };
						if (d[0] < 8 && d[0] >= 0 && d[1] >= 0 && d[1] < 8)
						{
							int move = checkMove(board, turn, s, d);
							if (move == 1)
							{
								if (!checkRemains(board, turn, s, d))
								{
									valid = 1;
									break;
								}
							}
						}
					}
					else if (k == 1)
					{
						int d[2] = { i - 1,j };
						if (d[0] < 8 && d[0] >= 0 && d[1] >= 0 && d[1] < 8)
						{
							int move = checkMove(board, turn, s, d);
							if (move == 1)
							{
								if (!checkRemains(board, turn, s, d))
								{
									valid = 1;
									break;
								}
							}
						}
					}
					else if (k == 2)
					{
						int d[2] = { i - 1,j - 1 };
						if (d[0] < 8 && d[0] >= 0 && d[1] >= 0 && d[1] < 8)
						{
							int move = checkMove(board, turn, s, d);
							if (move == 1)
							{
								if (!checkRemains(board, turn, s, d))
								{
									valid = 1;
									break;
								}
							}
						}
					}
					else if (k == 3)
					{
						int d[2] = { i - 1,j + 1 };
						if (d[0] < 8 && d[0] >= 0 && d[1] >= 0 && d[1] < 8)
						{
							int move = checkMove(board, turn, s, d);
							if (move == 1)
							{
								if (!checkRemains(board, turn, s, d))
								{
									valid = 1;
									break;
								}
							}
						}
					}
					else if (k == 4)
					{
						int d[2] = { i + 2,j };
						if (d[0] < 8 && d[0] >= 0 && d[1] >= 0 && d[1] < 8)
						{
							int move = checkMove(board, turn, s, d);
							if (move == 1)
							{
								if (!checkRemains(board, turn, s, d))
								{
									valid = 1;
									break;
								}
							}
						}
					}
					else if (k == 5)
					{
						int d[2] = { i + 1,j };
						if (d[0] < 8 && d[0] >= 0 && d[1] >= 0 && d[1] < 8)
						{
							int move = checkMove(board, turn, s, d);
							if (move == 1)
							{
								if (!checkRemains(board, turn, s, d))
								{
									valid = 1;
									break;
								}
							}
						}
					}
					else if (k == 6)
					{
						int d[2] = { i + 1,j - 1 };
						if (d[0] < 8 && d[0] >= 0 && d[1] >= 0 && d[1] < 8)
						{
							int move = checkMove(board, turn, s, d);
							if (move == 1)
							{
								if (!checkRemains(board, turn, s, d))
								{
									valid = 1;
									break;
								}
							}
						}
					}
					else if (k == 7)
					{
						int d[2] = { i + 1,j + 1 };
						if (d[0] < 8 && d[0] >= 0 && d[1] >= 0 && d[1] < 8)
						{
							int move = checkMove(board, turn, s, d);
							if (move == 1)
							{
								if (!checkRemains(board, turn, s, d))
								{
									valid = 1;
									break;
								}
							}
						}
					}
				}
			}
		}
	}

	if (!valid && check)
		return 0;
	else if (!valid && !check)
		return -1;
	else
		return 1;
}
#pragma endregion Check and Mates

#pragma region

void pawnPromossion(char board[][8], bool turn, int s[], int d[])
{
	if (board[d[0]][d[1]] == 'p' && d[0] == 0)
	{
		char key = 0;
		cout << "Pawn Promotion!\n";
		cout << "Press 1 to promote into Queen\n";
		cout << "Press 2 to promote into Rook\n";
		cout << "Press 3 to promote into Bishop\n";
		cout << "Press 4 to promote into Knight\n";

		while (key < '1' || key > '4')
		{
			key = _getch();
		}

		if (key == '1')
			board[d[0]][d[1]] = 'q';
		else if (key == '2')
			board[d[0]][d[1]] = 'r';
		else if (key == '3')
			board[d[0]][d[1]] = 'b';
		else if (key == '4')
			board[d[0]][d[1]] = 'n';

	}
	else if (board[d[0]][d[1]] == 'P' && d[0] == 7)
	{
		char key = 0;
		cout << "Pawn Promotion!\n";
		cout << "Press 1 to promote into Queen\n";
		cout << "Press 2 to promote into Rook\n";
		cout << "Press 3 to promote into Bishop\n";
		cout << "Press 4 to promote into Knight\n";

		while (key < '1' || key > '4')
		{
			key = _getch();
		}

		if (key == '1')
			board[d[0]][d[1]] = 'Q';
		else if (key == '2')
			board[d[0]][d[1]] = 'R';
		else if (key == '3')
			board[d[0]][d[1]] = 'B';
		else if (key == '4')
			board[d[0]][d[1]] = 'N';
	}

}

bool enPassant(char board[][8], char ** moves, int n, bool turn, int s[], int d[])
{
	if (turn)
	{
		if (s[0] == d[0] + 1 && (s[1] == d[1] + 1 || s[1] == d[1] - 1))
		{
			if (board[d[0] + 1][d[1]] == 'P')
			{
				if (moves[n - 1][0] == 'a' + d[1] && moves[n - 1][1] == '8' - (d[0] - 1) && moves[n - 1][2] == 'a' + d[1] && moves[n - 1][3] == '8' - (d[0] + 1))
				{
					board[d[0] + 1][d[1]] = NULL;
					return true;
				}
			}
		}
	}
	else
	{
		if (s[0] == d[0] - 1 && (s[1] == d[1] + 1 || s[1] == d[1] - 1))
		{
			if (board[d[0] - 1][d[1]] == 'p')
			{
				if (moves[n - 1][0] == 'a' + d[1] && moves[n - 1][1] == '8' - (d[0] + 1) && moves[n - 1][2] == 'a' + d[1] && moves[n - 1][3] == '8' - (d[0] - 1))
				{
					board[d[0] - 1][d[1]] = NULL;
					return true;
				}
			}
		}
	}
	return false;
}

int checkCastle(char board[][8], char ** moves, int n, bool turn, int s[], int d[])
{
	if (turn)
	{
		if (board[d[0]][d[1]] != 'r') // castling is with a rook
			return 0;
		if (d[1] > s[1] && (board[s[0]][s[1] + 1] != NULL || board[s[0]][s[1] + 2] != NULL)) // the path is clear
			return -1;
		else if (d[1] < s[1] && (board[s[0]][s[1] - 1] != NULL || board[s[0]][s[1] - 2] != NULL || board[s[0]][s[1] - 3] != NULL)) // the path is clear
			return -1;
		for (int i = 0; i < n; i++) // They have not moved before
		{
			if (moves[i][0] == 'e' && moves[i][1] == '1')
				return -2;
			else if (d[1] > s[1] && moves[i][0] == 'h' && moves[i][1] == '1')
				return -2;
			else if (d[1] < s[1] && moves[i][0] == 'a' && moves[i][1] == '1')
				return -2;
		}

		// blockes under check
		if (d[1] > s[1])
		{
			d[1] -= 2;
			if (checkRemains(board, turn, s, d))
				return -3;
			d[1]++;
			if (checkRemains(board, turn, s, d))
				return -3;
		}
		else
		{
			d[1] += 3;
			if (checkRemains(board, turn, s, d))
				return -3;
			d[1]--;
			if (checkRemains(board, turn, s, d))
				return -3;
		}
	}
	else
	{
		if (board[d[0]][d[1]] != 'R')
			return 0;
		if (d[1] > s[1] && (board[s[0]][s[1] + 1] != NULL || board[s[0]][s[1] + 2] != NULL))
			return -1;
		else if (d[1] < s[1] && (board[s[0]][s[1] - 1] != NULL || board[s[0]][s[1] - 2] != NULL || board[s[0]][s[1] - 3] != NULL))
			return -1;
		for (int i = 0; i < n; i++)
		{
			if (moves[i][0] == 'e' && moves[i][1] == '8')
				return -2;
			else if (d[1] > s[1] && moves[i][0] == 'h' && moves[i][1] == '8')
				return -2;
			else if (d[1] < s[1] && moves[i][0] == 'a' && moves[i][1] == '8')
				return -2;
		}

		// blockes under check
		if (d[1] > s[1])
		{
			d[1] -= 2;
			if (checkRemains(board, turn, s, d))
				return -3;
			d[1]++;
			if (checkRemains(board, turn, s, d))
				return -3;
		}
		else
		{
			d[1] += 3;
			if (checkRemains(board, turn, s, d))
				return -3;
			d[1]--;
			if (checkRemains(board, turn, s, d))
				return -3;
		}
	}

	return 1;
}
#pragma endregion Special Moves

#pragma region
void storeMove(int s[], int d[], char ** &moves, int &n, int &cap)
{
	if (moves == NULL)
	{
		moves = new char *[cap];
		moves[0] = new char[5];
		moves[0][0] = 'a' + s[1];
		moves[0][1] = '8' - s[0];
		moves[0][2] = 'a' + d[1];
		moves[0][3] = '8' - d[0];
		moves[0][4] = '\0';
		n++;
	}
	else if (n < cap)
	{
		moves[n] = new char[5];
		moves[n][0] = 'a' + s[1];
		moves[n][1] = '8' - s[0];
		moves[n][2] = 'a' + d[1];
		moves[n][3] = '8' - d[0];
		moves[n][4] = '\0';
		n++;
	}
	else
	{
		cap *= 2;
		char ** temp = moves;
		moves = new char *[cap];

		int i = 0;
		while (i < n)
		{
			moves[i] = temp[i];
			i++;
		}
		moves[n] = new char[5];
		moves[n][0] = 'a' + s[1];
		moves[n][1] = '8' - s[0];
		moves[n][2] = 'a' + d[1];
		moves[n][3] = '8' - d[0];
		moves[n][4] = '\0';
		n++;

		delete[] temp;
	}
}

void saveBoard(char board[][8], bool turn)
{
	ofstream fout("Files\\board.txt");
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
	fout << turn;
	fout.close();
}

void saveMoves(char ** moves, int n)
{
	ofstream fout("Files\\moves.txt");

	fout << n << endl;
	for (int i = 0; i < n; i++)
	{
		fout << moves[i] << endl;
	}

	fout.close();
}
#pragma endregion Save Game

#pragma region
void loadBoard(char board[][8], bool &turn)
{
	ifstream fin("Files\\board.txt");
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
			}
			else
			{
				board[i][j] = ch;
			}
		}
	}
	fin >> ch;
	if (ch == '1')
		turn = true;
	else
		turn = false;
	fin.close();
}

void loadMoves(char ** &moves, int &n)
{
	ifstream fin("Files\\moves.txt");

	char move[5];

	fin.getline(move, 5);
	n = atoi(move);

	moves = new char *[n];
	for (int i = 0; i < n; i++)
	{
		moves[i] = new char[5];
		fin.getline(moves[i], 5);
	}

	fin.close();
}
#pragma endregion Load Saved Game

int main()
{
	char board[8][8];
	bool turn = true;
	bool kingUnderCheck = false;
	char ** moves = NULL;
	int movesMade = 0;
	int cap = 2;

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
		initBoard(board);
	}
	else
	{
		loadBoard(board, turn);
		loadMoves(moves, movesMade);
		cap = movesMade;
	}

	gotoxy(0, 0);

	while (true)
	{
		saveBoard(board, turn);
		saveMoves(moves, movesMade);

		char input[100];
		int source[2];
		int des[2];
		bool valid = false;

		printBoard(board);

		if (turn)
			cout << "White Player's Turn\n";
		else
			cout << "Black Player's Turn\n";

		kingUnderCheck = checkByEnemy(board, turn);
		int end = mates(board, turn, kingUnderCheck);

		if (end == 0) {
			cout << "CHECKMATE!\n";
			break;
		}
		else if (end == -1) {
			cout << "STALEMATE!\n";
			break;
		}
		else
		{
			if (kingUnderCheck)
				cout << "King Under Check!\n";

			cout << endl;
			while (valid == false)
			{
				key = NULL;
				cout << "Enter source(eg. e4): ";
				inputBlock(input);
				storeBlock(source, input);

				if (toupper(board[source[0]][source[1]]) == 'K' && !kingUnderCheck)
				{
					cout << "Press 1 for Regular move.\t";
					cout << "Press 2 for Castling.\n";

					while (key != '1' && key != '2')
					{
						key = _getch();
					}
				}
				if (key == '2')
				{
					cout << "Castle with(eg. h1): ";
					inputBlock(input);
					storeBlock(des, input);

					int move = checkCastle(board, moves, movesMade, turn, source, des);

					if (move == 0)
						cout << "Invalid Move! No Rook to castle with.\n";
					else if (move == -1)
						cout << "Invalid Move! Pieces in the path.\n";
					else if (move == -2)
						cout << "Invalid Move! King/Rook have moved before.\n";
					else if (move == -3)
						cout << "Invalid Move! King passes/goes into check.\n";
					else if (move == 1)
						valid = true;
				}
				else
				{
					cout << "Enter destination(eg. e5): ";
					inputBlock(input);
					storeBlock(des, input);

					int move = checkMove(board, turn, source, des);

					if (tolower(board[source[0]][source[1]]) == 'p' && move == -1)
					{
						if (enPassant(board, moves, movesMade, turn, source, des))
							move = 2;
					}

					if (move == 0)
						cout << "Invalid Move! No piece to move\n";
					else if (move == -1)
						cout << "Invalid Move! Piece can not move like this\n";
					else if (move == -2)
						cout << "Invalid Move! Piece does not belong to player!\n";
					else if (move >= 1)
					{
						if (checkRemains(board, turn, source, des))
						{
							cout << "Invalid Move! King enters/remains in check!\n";
							if (move == 2)
							{
								if (turn)
									board[des[0] + 1][des[1]] = 'P';
								else
									board[des[0] - 1][des[1]] = 'p';
							}
						}
						else
							valid = true;
					}
				}
			}
			if (key == '2')
			{
				if (des[1] > source[1])
				{
					board[des[0]][des[1] + 1] = NULL;
					if (turn)
						board[des[0]][des[1] - 1] = 'r';
					else
						board[des[0]][des[1] - 1] = 'R';
				}
				else
				{
					board[des[0]][des[1] - 2] = NULL;
					if (turn)
						board[des[0]][des[1] + 1] = 'r';
					else
						board[des[0]][des[1] + 1] = 'R';
				}
			}
			makeMove(board, source, des);
			storeMove(source, des, moves, movesMade, cap);

			pawnPromossion(board, turn, source, des);

			turn = !turn;
			system("CLS");
		}
	}

	system("pause");
	return 0;
}