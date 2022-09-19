#include "Face.h"
#include <string>
#include <iostream>

using namespace std;

Face::Face() {
	name = " ";
	faceSetup(' ');
}

Face::Face(char color, string n1) {
	name = n1;

	// initialize faceArray
	faceSetup(color);
}

void Face::setName(string newName) {
	name = newName;
}

string Face::getName() {
	return name;
}

void Face::faceSetup(char color) {

	// set whole faceArray with the given color
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			faceArray[i][j] = color;
		}
	}
	
	// put in the blank spaces
	faceArray[0][0] = ' ';
	faceArray[0][8] = ' ';
	faceArray[1][3] = ' ';
	faceArray[1][5] = ' ';
	faceArray[2][2] = ' ';
	faceArray[2][4] = ' ';
	faceArray[2][6] = ' ';
	faceArray[3][1] = ' ';
	faceArray[3][7] = ' ';
	faceArray[4][2] = ' ';
	faceArray[4][6] = ' ';
	faceArray[5][1] = ' ';
	faceArray[5][7] = ' ';
	faceArray[6][2] = ' ';
	faceArray[6][4] = ' ';
	faceArray[6][6] = ' ';
	faceArray[7][3] = ' ';
	faceArray[7][5] = ' ';
	faceArray[8][0] = ' ';
	faceArray[8][8] = ' ';
}

char** Face::copyTopRows() {
	char** topRows = 0;
	topRows = new char* [3];
	for (int i = 0; i < 3; i++) {
		topRows[i] = new char[9];
	}

	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 9; c++) {
			topRows[r][c] = faceArray[r][c];
		}
	}

	return topRows;
}

char** Face::copyBottomRows() {
	char** bottomRows = 0;
	bottomRows = new char* [3];
	for (int i = 0; i < 3; i++) {
		bottomRows[i] = new char[9];
	}

	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 9; c++) {
			bottomRows[r][c] = faceArray[6 + r][c];
		}
	}

	return bottomRows;
}

char** Face::copyLeftCols() {
	char** leftCols = 0;
	leftCols = new char* [9];
	for (int i = 0; i < 9; i++) {
		leftCols[i] = new char[3];
	}

	for (int r = 0; r < 9; r++) {
		for (int c = 0; c < 3; c++) {
			leftCols[r][c] = faceArray[r][c];
		}
	}

	return leftCols;
}

char** Face::copyRightCols() {
	char** rightCols = 0;
	rightCols = new char* [9];
	for (int i = 0; i < 9; i++) {
		rightCols[i] = new char[3];
	}

	for (int r = 0; r < 9; r++) {
		for (int c = 0; c < 3; c++) {
			rightCols[r][c] = faceArray[r][6 + c];
		}
	}

	return rightCols;
}

// function to rotate the faceArray by 90 degrees CCW
void Face::rotateFaceCCW() {
	// first transpose the matrix
	for (int i = 0; i < 9; i++) {
		for (int j = i; j < 9; j++) {
			swap(faceArray[i][j], faceArray[j][i]);
		}
	}

	// then reverse the columns of the matrix
	for (int i = 0; i < 9; i++) {
		for (int j = 0, k = 8; j < k; j++, k--) {
			swap(faceArray[j][i], faceArray[k][i]);
		}
	}
}

// for printing each face
void Face::printRow(int row) {
	for (int i = 0; i < 9; i++) {
		cout << faceArray[row][i];
	}
}

// for printing the orange (back) face
void Face::printRowBackwards(int row) {
	for (int i = 8; i >= 0; i--) {
		cout << faceArray[row][i];
	}
}

// function to return whether or not the given row, col pair is a gear space
bool Face::isGearSpace(int row, int col) {
	if ((row == 0 || row == 8) && (col >= 2 && col <= 6)) {
		return true;
	}
	else if ((row == 1 || row == 7) && col == 4) {
		return true;
	}
	else if ((col == 0 || col == 8) && (row >= 2 && row <= 6)) {
		return true;
	}
	else if ((col == 1 || col == 7) && row == 4) {
		return true;
	}
	else {
		return false;
	}
}
