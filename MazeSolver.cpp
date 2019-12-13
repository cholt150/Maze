#include "stack.h"
#include<fstream>
#include<string>
#include<iostream>
using namespace std;




int main()
{
	//VARIABLE DECLARATIONS
	string filename;
	char startChar = 'S';
	char endChar = 'G';
	char pathChar = '.';
	int Xdim = 0, Ydim = 0;
	int X, Y; //Variables to hold start coordinates
	int startX, startY; //Variables to remember starting location
	int count, maxCount; //variables to keep track of number of loops we make.
	count = 0;

	int dX[4] = { -1, 1, 0, 0 }; //Arrays for managing stepping in each direction.
	int dY[4] = { 0, 0, -1, 1 };

	ifstream mazeFile;
	Stack S; //create a new stack.
	
	cout << "Simple Maze Solver\nEnter the file name of the maze to be read." << endl;
	getline(cin, filename); //Get the filename
	mazeFile.open(filename);
	if (!mazeFile) {
		cout << "Unable to open file. Try again." << endl;
		exit(1);
	}
	
	cout << "Using maze from: " << filename << endl;

	mazeFile >> Xdim; //Read Maze Dimensions
	mazeFile >> Ydim;
	maxCount = Xdim * Ydim; //upper limit for number of steps we can make. Heavy overestimate, but the process is not very intensive.
	Xdim++; //Increment dimensions so we can add edges
	Ydim++;

	//Confusing Dyanmic array allocation. Lots of pointers to pointers.

	char** maze = new char* [Ydim]; //array for holding the maze file.
	for (int i = 0; i <= Ydim; i++)
		maze[i] = new char[Xdim];

	

	bool startExists = 0;
	bool endExists = 0;

	for (int i = 0; i <= Xdim; i++)
	{
		for (int j = 0; j <= Ydim; j++)
		{
			if ((i == 0) || (i == Xdim) || (j == 0) || (j == Ydim))
				maze[i][j] = '#'; //Pad edges of maze so we don't navigate beyond them.
			else
			{
				mazeFile >> maze[i][j];
				if (maze[i][j] == startChar) {
					startExists = 1;
					S.push(i, j); //Push start location onto stack.
					startX = i;
					startY = j;
				}
				if (maze[i][j] == endChar)
					endExists = 1;
			}
		}
	}

	mazeFile.close(); //Close the file after reading.

	cout << endl << "----Unsolved Maze----" << endl;

	for (int i = 0; i <= Xdim; i++)
	{
		for (int j = 0; j <= Ydim; j++)
		{
			cout << maze[i][j];
		}
		cout << endl;
	}

	if (!startExists || !endExists)
	{
		cout << "No start or end character found. Please check the maze formatting." << endl;
		exit(1);
	}

	while (1) {
		S.pop(X, Y); //Pop starting coordinates from stack into X and Y
		if ((maze[X - 1][Y] == endChar) || (maze[X + 1][Y] == endChar) || (maze[X][Y - 1] == endChar) || (maze[X][Y + 1] == endChar)) {
			maze[X][Y] = '@'; //Mark as visited within maze.
			break;
		}
		maze[X][Y] = '@'; //Mark as visited within maze.
		for (int i = 0; i < 4; i++) { //Loop to check each direction.
			if (maze[X + dX[i]][Y + dY[i]] == pathChar)
				S.push(X + dX[i], Y + dY[i]); //Push if the character is a valid path character.
		}
		if (count == maxCount) {
			cout << endl << "No solution found. Exiting after " << maxCount << " steps." << endl;
			exit(1);
		}
		count++;
	}
	maze[startX][startY] = startChar; //rewrite the start character for displaying.
	cout << endl << "----Solved Maze----" << endl;
	for (int i = 0; i <= Xdim; i++)
	{
		for (int j = 0; j <= Ydim; j++)
		{
			cout << maze[i][j];
		}
		cout << endl;
	}
	cout << endl << "Solution found in " << count << " steps." << endl;

	exit(1);
}