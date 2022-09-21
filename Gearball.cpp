#include "Gearball.h"
#include <time.h>
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

Gearball::Gearball() {
	initializeGears();
	initializeFaces();
}

void Gearball::initializeGears() {
	gears[0] = Gear('O', 'B');
	gears[1] = Gear('B', 'R');
	gears[2] = Gear('B', 'P');
	gears[3] = Gear('B', 'Y');
	gears[4] = Gear('Y', 'R');
	gears[5] = Gear('Y', 'P');
	gears[6] = Gear('Y', 'G');
	gears[7] = Gear('G', 'R');
	gears[8] = Gear('G', 'P');
	gears[9] = Gear('G', 'O');
	gears[10] = Gear('O', 'R');
	gears[11] = Gear('O', 'P');
}

void Gearball::initializeFaces() {
	faces[0] = Face('B', "top");
	faces[1] = Face('R', "left");
	faces[2] = Face('Y', "front");
	faces[3] = Face('P', "right");
	faces[4] = Face('G', "bottom");
	faces[5] = Face('O', "back");
}

void Gearball::resetGearball() {
	// reset gears to original colors
	gears[0].setColor1('O');
	gears[0].setColor2('B');
	gears[1].setColor1('B');
	gears[1].setColor2('R');
	gears[2].setColor1('B');
	gears[2].setColor2('P');
	gears[3].setColor1('B');
	gears[3].setColor2('Y');
	gears[4].setColor1('Y');
	gears[4].setColor2('R');
	gears[5].setColor1('Y');
	gears[5].setColor2('P');
	gears[6].setColor1('Y');
	gears[6].setColor2('G');
	gears[7].setColor1('G');
	gears[7].setColor2('R');
	gears[8].setColor1('G');
	gears[8].setColor2('P');
	gears[9].setColor1('G');
	gears[9].setColor2('O');
	gears[10].setColor1('O');
	gears[10].setColor2('R');
	gears[11].setColor1('O');
	gears[11].setColor2('P');

	// reset gears' number of rotations
	gears[0].setNumRotations(0);
	gears[1].setNumRotations(0);
	gears[2].setNumRotations(0);
	gears[3].setNumRotations(0);
	gears[4].setNumRotations(0);
	gears[5].setNumRotations(0);
	gears[6].setNumRotations(0);
	gears[7].setNumRotations(0);
	gears[8].setNumRotations(0);
	gears[9].setNumRotations(0);
	gears[10].setNumRotations(0);
	gears[11].setNumRotations(0);

	// reset faces to original colors
	faces[0].faceSetup('B');
	faces[1].faceSetup('R');
	faces[2].faceSetup('Y');
	faces[3].faceSetup('P');
	faces[4].faceSetup('G');
	faces[5].faceSetup('O');
}

void Gearball::printGearball() {
	int x = 0;
	while (x < 6) {
		// for printing out left, front, and right faces
		if (x == 1) {
			for (int i = 0; i < 9; i++) {
				faces[x].printRow(i); // left
				cout << "  ";
				faces[x + 1].printRow(i); // front
				cout << "  ";
				faces[x + 2].printRow(i); // right
				cout << endl;
			}
			x = 3;
		}
		// for printing out top and bottom faces
		else if (x != 5) {
			for (int i = 0; i < 9; i++) {
				cout << "           ";
				faces[x].printRow(i);
				cout << endl;
			}
		}
		// for printing out back face (must be printed out rotated 180 degrees)
		else {
			for (int i = 8; i >= 0; i--) {
				cout << "           ";
				faces[x].printRowBackwards(i);
				cout << endl;
			}
		}
		x++;
	}
}

// function to randomize the gearball, according to an inputted number of moves
// returns a string of the moves performed
string Gearball::randomizeGearball(int numMoves) {
	string movesPerformed = "";
	int randomMove;
	int prevMove = -2;
	int numSameMoves = 0;
	srand(time(0)); // to make sure I get different random numbers

	while (numMoves != 0) {
		randomMove = rand() % 6; // gets a random number between 0 and 5
		if (randomMove % 2 == 0) { // CW move
			while (randomMove == (prevMove - 1)) { // opposite of prev move
				randomMove = rand() % 6; // gets a new random number
			}
		}
		else if (randomMove % 2 == 1) { // CCW move
			while (randomMove == (prevMove + 1)) { // opposite of prev move
				randomMove = rand() % 6; // gets a new random number
			}
		}
		if (randomMove == prevMove) {
			numSameMoves++;
		}
		else {
			numSameMoves = 0;
		}
		if (numSameMoves >= 12) {
			while (randomMove == prevMove) {
				randomMove = rand() % 6; // gets a new random number until it is not the same as the previous move
			}
			numSameMoves = 0;
		}
		prevMove = randomMove;

		switch (randomMove) {
		case 0: {
			rotateRightAndLeftCW();
			break;
		}
		case 1: {
			rotateRightAndLeftCCW();
			break;
		}
		case 2: {
			rotateTopAndBottomCW();
			break;
		}
		case 3: {
			rotateTopAndBottomCCW();
			break;
		}
		case 4: {
			rotateFrontAndBackCW();
			break;
		}
		case 5: {
			rotateFrontAndBackCCW();
			break;
		}
		}
		movesPerformed = movesPerformed + to_string(randomMove);
		//cout << randomMove; // for testing purposes
		numMoves--;
	}
	//cout << endl; // for testing purposes
	//cout << movesPerformed << endl;
	return movesPerformed;
}

// aligns the colors of the top gears according to its number of rotations
void Gearball::alignTopGearValues(Gear gear, Face &face) {
	if (face.getName() == "back") {
		switch (gear.getNumRotations()) {
		case 0:
		case 6:
		case -6: {
			for (int i = 2; i < 7; i++) {
				face.faceArray[0][i] = gear.getColor1();
			}
			face.faceArray[1][4] = gear.getColor1();
			break;
		}
		case 1:
		case -5: {
			face.faceArray[0][2] = gear.getColor2();
			face.faceArray[0][3] = '/';
			face.faceArray[0][4] = gear.getColor1();
			face.faceArray[0][5] = gear.getColor1();
			face.faceArray[0][6] = gear.getColor1();
			face.faceArray[1][4] = gear.getColor1();
			break;
		}
		case 2:
		case -4: {
			face.faceArray[0][2] = gear.getColor2();
			face.faceArray[0][3] = gear.getColor2();
			face.faceArray[0][4] = gear.getColor2();
			face.faceArray[0][5] = '\\';
			face.faceArray[0][6] = gear.getColor1();
			face.faceArray[1][4] = gear.getColor2();
			break;
		}
		case 3:
		case -3: {
			for (int i = 2; i < 7; i++) {
				face.faceArray[0][i] = gear.getColor2();
			}
			face.faceArray[1][4] = gear.getColor2();
			break;
		}
		case 4:
		case -2: {
			face.faceArray[0][2] = gear.getColor1();
			face.faceArray[0][3] = '/';
			face.faceArray[0][4] = gear.getColor2();
			face.faceArray[0][5] = gear.getColor2();
			face.faceArray[0][6] = gear.getColor2();
			face.faceArray[1][4] = gear.getColor2();
			break;
		}
		case 5:
		case -1: {
			face.faceArray[0][2] = gear.getColor1();
			face.faceArray[0][3] = gear.getColor1();
			face.faceArray[0][4] = gear.getColor1();
			face.faceArray[0][5] = '\\';
			face.faceArray[0][6] = gear.getColor2();
			face.faceArray[1][4] = gear.getColor1();
			break;
		}
		}
	}
	else {
		switch (gear.getNumRotations()) {
		case 0:
		case 6:
		case -6: {
			for (int i = 2; i < 7; i++) {
				face.faceArray[0][i] = gear.getColor2();
			}
			face.faceArray[1][4] = gear.getColor2();
			break;
		}
		case 1:
		case -5: {
			face.faceArray[0][2] = gear.getColor1();
			face.faceArray[0][3] = '/';
			face.faceArray[0][4] = gear.getColor2();
			face.faceArray[0][5] = gear.getColor2();
			face.faceArray[0][6] = gear.getColor2();
			face.faceArray[1][4] = gear.getColor2();
			break;
		}
		case 2:
		case -4: {
			face.faceArray[0][2] = gear.getColor1();
			face.faceArray[0][3] = gear.getColor1();
			face.faceArray[0][4] = gear.getColor1();
			face.faceArray[0][5] = '\\';
			face.faceArray[0][6] = gear.getColor2();
			face.faceArray[1][4] = gear.getColor1();
			break;
		}
		case 3:
		case -3: {
			for (int i = 2; i < 7; i++) {
				face.faceArray[0][i] = gear.getColor1();
			}
			face.faceArray[1][4] = gear.getColor1();
			break;
		}
		case 4:
		case -2: {
			face.faceArray[0][2] = gear.getColor2();
			face.faceArray[0][3] = '/';
			face.faceArray[0][4] = gear.getColor1();
			face.faceArray[0][5] = gear.getColor1();
			face.faceArray[0][6] = gear.getColor1();
			face.faceArray[1][4] = gear.getColor1();
			break;
		}
		case 5:
		case -1: {
			face.faceArray[0][2] = gear.getColor2();
			face.faceArray[0][3] = gear.getColor2();
			face.faceArray[0][4] = gear.getColor2();
			face.faceArray[0][5] = '\\';
			face.faceArray[0][6] = gear.getColor1();
			face.faceArray[1][4] = gear.getColor2();
			break;
		}
		}
	}
}

// aligns right gear color values according to numRotations
void Gearball::alignRightGearValues(Gear gear, Face& face) {
	if (face.getName() == "top" || face.getName() == "front" || face.getName() == "bottom" || face.getName() == "back") {
		switch (gear.getNumRotations()) {
		case 0:
		case 6:
		case -6: {
			for (int i = 2; i < 7; i++) {
				face.faceArray[i][8] = gear.getColor1();
			}
			face.faceArray[4][7] = gear.getColor1();
			break;
		}
		case 1:
		case -5: {
			face.faceArray[2][8] = gear.getColor2();
			face.faceArray[3][8] = '\\';
			face.faceArray[4][8] = gear.getColor1();
			face.faceArray[4][7] = gear.getColor1();
			face.faceArray[5][8] = gear.getColor1();
			face.faceArray[6][8] = gear.getColor1();
			break;
		}
		case 2:
		case -4: {
			face.faceArray[2][8] = gear.getColor2();
			face.faceArray[3][8] = gear.getColor2();
			face.faceArray[4][8] = gear.getColor2();
			face.faceArray[4][7] = gear.getColor2();
			face.faceArray[5][8] = '/';
			face.faceArray[6][8] = gear.getColor1();
			break;
		}
		case 3:
		case -3: {
			for (int i = 2; i < 7; i++) {
				face.faceArray[i][8] = gear.getColor2();
			}
			face.faceArray[4][7] = gear.getColor2();
			break;
		}
		case 4:
		case -2: {
			face.faceArray[2][8] = gear.getColor1();
			face.faceArray[3][8] = '\\';
			face.faceArray[4][8] = gear.getColor2();
			face.faceArray[4][7] = gear.getColor2();
			face.faceArray[5][8] = gear.getColor2();
			face.faceArray[6][8] = gear.getColor2();
			break;
		}
		case 5:
		case -1: {
			face.faceArray[2][8] = gear.getColor1();
			face.faceArray[3][8] = gear.getColor1();
			face.faceArray[4][8] = gear.getColor1();
			face.faceArray[4][7] = gear.getColor1();
			face.faceArray[5][8] = '/';
			face.faceArray[6][8] = gear.getColor2();
			break;
		}
		}
	}
	else {
		switch (gear.getNumRotations()) {
		case 0:
		case 6:
		case -6: {
			for (int i = 2; i < 7; i++) {
				face.faceArray[i][8] = gear.getColor2();
			}
			face.faceArray[4][7] = gear.getColor2();
			break;
		}
		case 1:
		case -5: {
			face.faceArray[2][8] = gear.getColor1();
			face.faceArray[3][8] = '\\';
			face.faceArray[4][8] = gear.getColor2();
			face.faceArray[4][7] = gear.getColor2();
			face.faceArray[5][8] = gear.getColor2();
			face.faceArray[6][8] = gear.getColor2();
			break;
		}
		case 2:
		case -4: {
			face.faceArray[2][8] = gear.getColor1();
			face.faceArray[3][8] = gear.getColor1();
			face.faceArray[4][8] = gear.getColor1();
			face.faceArray[4][7] = gear.getColor1();
			face.faceArray[5][8] = '/';
			face.faceArray[6][8] = gear.getColor2();
			break;
		}
		case 3:
		case -3: {
			for (int i = 2; i < 7; i++) {
				face.faceArray[i][8] = gear.getColor1();
			}
			face.faceArray[4][7] = gear.getColor1();
			break;
		}
		case 4:
		case -2: {
			face.faceArray[2][8] = gear.getColor2();
			face.faceArray[3][8] = '\\';
			face.faceArray[4][8] = gear.getColor1();
			face.faceArray[4][7] = gear.getColor1();
			face.faceArray[5][8] = gear.getColor1();
			face.faceArray[6][8] = gear.getColor1();
			break;
		}
		case 5:
		case -1: {
			face.faceArray[2][8] = gear.getColor2();
			face.faceArray[3][8] = gear.getColor2();
			face.faceArray[4][8] = gear.getColor2();
			face.faceArray[4][7] = gear.getColor2();
			face.faceArray[5][8] = '/';
			face.faceArray[6][8] = gear.getColor1();
			break;
		}
		}
	}
}

// aligns left gear color values according to numRotations
void Gearball::alignLeftGearValues(Gear gear, Face& face) {
	if (face.getName() == "top" || face.getName() == "front" || face.getName() == "bottom" || face.getName() == "back") {
		switch (gear.getNumRotations()) {
		case 0:
		case 6:
		case -6: {
			for (int i = 2; i < 7; i++) {
				face.faceArray[i][0] = gear.getColor1();
			}
			face.faceArray[4][1] = gear.getColor1();
			break;
		}
		case 1:
		case -5: {
			face.faceArray[2][0] = gear.getColor1();
			face.faceArray[3][0] = gear.getColor1();
			face.faceArray[4][0] = gear.getColor1();
			face.faceArray[4][1] = gear.getColor1();
			face.faceArray[5][0] = '\\';
			face.faceArray[6][0] = gear.getColor2();
			break;
		}
		case 2:
		case -4: {
			face.faceArray[2][0] = gear.getColor1();
			face.faceArray[3][0] = '/';
			face.faceArray[4][0] = gear.getColor2();
			face.faceArray[4][1] = gear.getColor2();
			face.faceArray[5][0] = gear.getColor2();
			face.faceArray[6][0] = gear.getColor2();
			break;
		}
		case 3:
		case -3: {
			for (int i = 2; i < 7; i++) {
				face.faceArray[i][0] = gear.getColor2();
			}
			face.faceArray[4][1] = gear.getColor2();
			break;
		}
		case 4:
		case -2: {
			face.faceArray[2][0] = gear.getColor2();
			face.faceArray[3][0] = gear.getColor2();
			face.faceArray[4][0] = gear.getColor2();
			face.faceArray[4][1] = gear.getColor2();
			face.faceArray[5][0] = '\\';
			face.faceArray[6][0] = gear.getColor1();
			break;
		}
		case 5:
		case -1: {
			face.faceArray[2][0] = gear.getColor2();
			face.faceArray[3][0] = '/';
			face.faceArray[4][0] = gear.getColor1();
			face.faceArray[4][1] = gear.getColor1();
			face.faceArray[5][0] = gear.getColor1();
			face.faceArray[6][0] = gear.getColor1();
			break;
		}
		}
	}
	else {
		switch (gear.getNumRotations()) {
		case 0:
		case 6:
		case -6: {
			for (int i = 2; i < 7; i++) {
				face.faceArray[i][0] = gear.getColor2();
			}
			face.faceArray[4][1] = gear.getColor2();
			break;
		}
		case 1:
		case -5: {
			face.faceArray[2][0] = gear.getColor2();
			face.faceArray[3][0] = gear.getColor2();
			face.faceArray[4][0] = gear.getColor2();
			face.faceArray[4][1] = gear.getColor2();
			face.faceArray[5][0] = '\\';
			face.faceArray[6][0] = gear.getColor1();
			break;
		}
		case 2:
		case -4: {
			face.faceArray[2][0] = gear.getColor2();
			face.faceArray[3][0] = '/';
			face.faceArray[4][0] = gear.getColor1();
			face.faceArray[4][1] = gear.getColor1();
			face.faceArray[5][0] = gear.getColor1();
			face.faceArray[6][0] = gear.getColor1();
			break;
		}
		case 3:
		case -3: {
			for (int i = 2; i < 7; i++) {
				face.faceArray[i][0] = gear.getColor1();
			}
			face.faceArray[4][1] = gear.getColor1();
			break;
		}
		case 4:
		case -2: {
			face.faceArray[2][0] = gear.getColor1();
			face.faceArray[3][0] = gear.getColor1();
			face.faceArray[4][0] = gear.getColor1();
			face.faceArray[4][1] = gear.getColor1();
			face.faceArray[5][0] = '\\';
			face.faceArray[6][0] = gear.getColor2();
			break;
		}
		case 5:
		case -1: {
			face.faceArray[2][0] = gear.getColor1();
			face.faceArray[3][0] = '/';
			face.faceArray[4][0] = gear.getColor2();
			face.faceArray[4][1] = gear.getColor2();
			face.faceArray[5][0] = gear.getColor2();
			face.faceArray[6][0] = gear.getColor2();
			break;
		}
		}
	}
}

// aligns bottom gear color values according to numROtations
void Gearball::alignBottomGearValues(Gear gear, Face& face) {
	if (face.getName() == "top" || face.getName() == "front" || face.getName() == "bottom") {
		switch (gear.getNumRotations()) {
		case 0:
		case 6:
		case -6: {
			for (int i = 2; i < 7; i++) {
				face.faceArray[8][i] = gear.getColor1();
			}
			face.faceArray[7][4] = gear.getColor1();
			break;
		}
		case 1:
		case -5: {
			face.faceArray[8][2] = gear.getColor1();
			face.faceArray[8][3] = gear.getColor1();
			face.faceArray[8][4] = gear.getColor1();
			face.faceArray[7][4] = gear.getColor1();
			face.faceArray[8][5] = '/';
			face.faceArray[8][6] = gear.getColor2();
			break;
		}
		case 2:
		case -4: {
			face.faceArray[8][2] = gear.getColor1();
			face.faceArray[8][3] = '\\';
			face.faceArray[8][4] = gear.getColor2();
			face.faceArray[7][4] = gear.getColor2();
			face.faceArray[8][5] = gear.getColor2();
			face.faceArray[8][6] = gear.getColor2();
			break;
		}
		case 3:
		case -3: {
			for (int i = 2; i < 7; i++) {
				face.faceArray[8][i] = gear.getColor2();
			}
			face.faceArray[7][4] = gear.getColor2();
			break;
		}
		case 4:
		case -2: {
			face.faceArray[8][2] = gear.getColor2();
			face.faceArray[8][3] = gear.getColor2();
			face.faceArray[8][4] = gear.getColor2();
			face.faceArray[7][4] = gear.getColor2();
			face.faceArray[8][5] = '/';
			face.faceArray[8][6] = gear.getColor1();
			break;
		}
		case 5:
		case -1: {
			face.faceArray[8][2] = gear.getColor2();
			face.faceArray[8][3] = '\\';
			face.faceArray[8][4] = gear.getColor1();
			face.faceArray[7][4] = gear.getColor1();
			face.faceArray[8][5] = gear.getColor1();
			face.faceArray[8][6] = gear.getColor1();
			break;
		}
		}
	}
	else {
		switch (gear.getNumRotations()) {
		case 0:
		case 6:
		case -6: {
			for (int i = 2; i < 7; i++) {
				face.faceArray[8][i] = gear.getColor2();
			}
			face.faceArray[7][4] = gear.getColor2();
			break;
		}
		case 1:
		case -5: {
			face.faceArray[8][2] = gear.getColor2();
			face.faceArray[8][3] = gear.getColor2();
			face.faceArray[8][4] = gear.getColor2();
			face.faceArray[7][4] = gear.getColor2();
			face.faceArray[8][5] = '/';
			face.faceArray[8][6] = gear.getColor1();
			break;
		}
		case 2:
		case -4: {
			face.faceArray[8][2] = gear.getColor2();
			face.faceArray[8][3] = '\\';
			face.faceArray[8][4] = gear.getColor1();
			face.faceArray[7][4] = gear.getColor1();
			face.faceArray[8][5] = gear.getColor1();
			face.faceArray[8][6] = gear.getColor1();
			break;
		}
		case 3:
		case -3: {
			for (int i = 2; i < 7; i++) {
				face.faceArray[8][i] = gear.getColor1();
			}
			face.faceArray[7][4] = gear.getColor1();
			break;
		}
		case 4:
		case -2: {
			face.faceArray[8][2] = gear.getColor1();
			face.faceArray[8][3] = gear.getColor1();
			face.faceArray[8][4] = gear.getColor1();
			face.faceArray[7][4] = gear.getColor1();
			face.faceArray[8][5] = '/';
			face.faceArray[8][6] = gear.getColor2();
			break;
		}
		case 5:
		case -1: {
			face.faceArray[8][2] = gear.getColor1();
			face.faceArray[8][3] = '\\';
			face.faceArray[8][4] = gear.getColor2();
			face.faceArray[7][4] = gear.getColor2();
			face.faceArray[8][5] = gear.getColor2();
			face.faceArray[8][6] = gear.getColor2();
			break;
		}
		}
	}
}

void Gearball::swapLeftCols(Face &face, char** newCols) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 3; j++) {
			face.faceArray[i][j] = newCols[i][j];
		}
	}
}

void Gearball::swapRightCols(Face &face, char** newCols) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 3; j++) {
			face.faceArray[i][6 + j] = newCols[i][j];
		}
	}
}

void Gearball::swapTopRows(Face &face, char** newCols) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 9; j++) {
			face.faceArray[i][j] = newCols[i][j];
		}
	}
}

void Gearball::swapBottomRows(Face &face, char** newCols) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 9; j++) {
			face.faceArray[6 + i][j] = newCols[i][j];
		}
	}
}

// for dealing with swapping between the orange and blue faces and the orange and green faces
void Gearball::swapRightToLeftCols(Face& face, char** rightCols) {
	for (int i = 0; i < 3; i++) { // for each column
		for (int j = 0; j < 9; j++) {
			face.faceArray[j][i] = rightCols[8 - j][2 - i];
		}
	}
}
void Gearball::swapLeftToRightCols(Face& face, char** leftCols) {
	for (int i = 0; i < 3; i++) { // for each column
		for (int j = 0; j < 9; j++) {
			face.faceArray[j][6 + i] = leftCols[8 - j][2 - i];
		}
	}
}

// for swapping between left, right, front, and back faces
void Gearball::swapLeftColsToTopRows(Face& face, char** leftCols) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 9; j++) {
			face.faceArray[i][8 - j] = leftCols[j][i];
		}
	}
}
void Gearball::swapRightColsToTopRows(Face& face, char** rightCols) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 9; j++) {
			face.faceArray[2- i][j] = rightCols[j][i];
		}
	}
}
void Gearball::swapRightColsToBottomRows(Face& face, char** rightCols) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 9; j++) {
			face.faceArray[6 + i][ 8 - j] = rightCols[j][i];
		}
	}
}
void Gearball::swapLeftColsToBottomRows(Face& face, char** leftCols) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 9; j++) {
			face.faceArray[8 - i][j] = leftCols[j][i];
		}
	}
}
void Gearball::swapTopRowsToLeftCols(Face& face, char** topRows) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 3; j++) {
			face.faceArray[8 - i][j] = topRows[j][i];
		}
	}
}
void Gearball::swapBottomRowsToLeftCols(Face& face, char** bottomRows) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 3; j++) {
			face.faceArray[i][2 - j] = bottomRows[j][i];
		}
	}
}
void Gearball::swapBottomRowsToRightCols(Face& face, char** bottomRows) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 3; j++) {
			face.faceArray[8 - i][6 + j] = bottomRows[j][i];
		}
	}
}
void Gearball::swapTopRowsToRightCols(Face& face, char** topRows) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 3; j++) {
			face.faceArray[i][8 - j] = topRows[j][i];
		}
	}
}

// Function for rotating the right and left faces clockwise
void Gearball::rotateRightAndLeftCW() {
	gears[0].rotate(false);
	gears[3].rotate(false);
	gears[6].rotate(false);
	gears[9].rotate(false);

	// rotating gears around on right face
	Gear tempGear = gears[5]; 
	gears[5] = gears[8];
	gears[8] = gears[11];
	gears[11] = gears[2];
	gears[2] = tempGear;

	// rotating gears around on left face
	tempGear = gears[4];
	gears[4] = gears[1];
	gears[1] = gears[10];
	gears[10] = gears[7];
	gears[7] = tempGear;

	// rotate the faceArray for each of the faces being rotated (right and left)
	faces[3].rotateFaceCCW();
	faces[3].rotateFaceCCW();
	faces[3].rotateFaceCCW();
	faces[1].rotateFaceCCW();
	faces[1].rotateFaceCCW();
	faces[1].rotateFaceCCW();

	char** orangeRightCols = faces[5].copyRightCols();
	char** orangeLeftCols = faces[5].copyLeftCols();
	char** blueRightCols = faces[0].copyRightCols();
	char** greenLeftCols = faces[4].copyLeftCols();

	// swapping of left columns
	char** tempCols = faces[0].copyLeftCols();
	swapRightToLeftCols(faces[0], orangeRightCols);
	swapLeftCols(faces[4], faces[2].copyLeftCols());
	swapLeftCols(faces[2], tempCols);
	swapRightToLeftCols(faces[5], blueRightCols);

	// swapping of right columns
	swapRightCols(faces[0], faces[2].copyRightCols());
	swapRightCols(faces[2], faces[4].copyRightCols());
	swapLeftToRightCols(faces[4], orangeLeftCols);
	swapLeftToRightCols(faces[5], greenLeftCols);

	alignTopGearValues(gears[0], faces[0]);
	alignTopGearValues(gears[3], faces[2]);
	alignTopGearValues(gears[6], faces[4]);
	alignTopGearValues(gears[0], faces[5]);
	alignBottomGearValues(gears[3], faces[0]);
	alignBottomGearValues(gears[6], faces[2]);
	alignBottomGearValues(gears[9], faces[4]);
	alignBottomGearValues(gears[9], faces[5]);
}

// Function for rotating the right and left faces counterclockwise
void Gearball::rotateRightAndLeftCCW() {
	gears[0].rotate(true);
	gears[3].rotate(true);
	gears[6].rotate(true);
	gears[9].rotate(true);

	// rotating gears around on right face
	Gear tempGear = gears[5];
	gears[5] = gears[2];
	gears[2] = gears[11];
	gears[11] = gears[8];
	gears[8] = tempGear;

	// rotating gears around on left face
	tempGear = gears[4];
	gears[4] = gears[7];
	gears[7] = gears[10];
	gears[10] = gears[1];
	gears[1] = tempGear;

	// rotate the faceArray for right and left faces
	faces[3].rotateFaceCCW();
	faces[1].rotateFaceCCW();

	char** orangeRightCols = faces[5].copyRightCols();
	char** orangeLeftCols = faces[5].copyLeftCols();
	char** blueLeftCols = faces[0].copyLeftCols();
	char** greenRightCols = faces[4].copyRightCols();

	// swapping of left columns
	swapLeftCols(faces[0], faces[2].copyLeftCols());
	swapLeftCols(faces[2], faces[4].copyLeftCols());
	swapRightToLeftCols(faces[4], orangeRightCols);
	swapRightToLeftCols(faces[5], greenRightCols);

	// swapping of right columns
	swapRightCols(faces[4], faces[2].copyRightCols());
	swapRightCols(faces[2], faces[0].copyRightCols());
	swapLeftToRightCols(faces[0], orangeLeftCols);
	swapLeftToRightCols(faces[5], blueLeftCols);

	alignTopGearValues(gears[0], faces[0]);
	alignTopGearValues(gears[3], faces[2]);
	alignTopGearValues(gears[6], faces[4]);
	alignTopGearValues(gears[0], faces[5]);
	alignBottomGearValues(gears[3], faces[0]);
	alignBottomGearValues(gears[6], faces[2]);
	alignBottomGearValues(gears[9], faces[4]);
	alignBottomGearValues(gears[9], faces[5]);
}

// Function for rotating the top and bottom faces clockwise
void Gearball::rotateTopAndBottomCW() {
	gears[4].rotate(false);
	gears[5].rotate(false);
	gears[10].rotate(false);
	gears[11].rotate(false);

	// rotating gears around on top face
	Gear tempGear = gears[3];
	gears[3] = gears[2];
	gears[2] = gears[0];
	gears[0] = gears[1];
	gears[1] = tempGear;

	// rotating gears around on bottom face
	tempGear = gears[6];
	gears[6] = gears[7];
	gears[7] = gears[9];
	gears[9] = gears[8];
	gears[8] = tempGear;

	// adjusting for the reorientation of colors
	gears[0].switchColors();
	gears[2].switchColors();
	gears[6].switchColors();
	gears[8].switchColors();

	// rotate top and bottom faces
	faces[0].rotateFaceCCW();
	faces[0].rotateFaceCCW();
	faces[0].rotateFaceCCW();
	faces[4].rotateFaceCCW();
	faces[4].rotateFaceCCW();
	faces[4].rotateFaceCCW();

	// swapping of top rows
	char** tempRows = faces[1].copyTopRows();
	swapTopRows(faces[1], faces[2].copyTopRows());
	swapTopRows(faces[2], faces[3].copyTopRows());
	swapTopRows(faces[3], faces[5].copyTopRows());
	swapTopRows(faces[5], tempRows);

	// swapping of bottom rows
	tempRows = faces[1].copyBottomRows();
	swapBottomRows(faces[1], faces[5].copyBottomRows());
	swapBottomRows(faces[5], faces[3].copyBottomRows());
	swapBottomRows(faces[3], faces[2].copyBottomRows());
	swapBottomRows(faces[2], tempRows);

	alignLeftGearValues(gears[10], faces[1]);
	alignLeftGearValues(gears[4], faces[2]);
	alignLeftGearValues(gears[5], faces[3]);
	alignLeftGearValues(gears[11], faces[5]);
	alignRightGearValues(gears[4], faces[1]);
	alignRightGearValues(gears[5], faces[2]);
	alignRightGearValues(gears[11], faces[3]);
	alignRightGearValues(gears[10], faces[5]);
}

// Function for rotating the top and bottom faces counterclockwise
void Gearball::rotateTopAndBottomCCW() {
	gears[4].rotate(true);
	gears[5].rotate(true);
	gears[10].rotate(true);
	gears[11].rotate(true);

	// rotating gears around on top face
	Gear tempGear = gears[3];
	gears[3] = gears[1];
	gears[1] = gears[0];
	gears[0] = gears[2];
	gears[2] = tempGear;

	// rotating gears around on bottom face
	tempGear = gears[6];
	gears[6] = gears[8];
	gears[8] = gears[9];
	gears[9] = gears[7];
	gears[7] = tempGear;

	// adjusting for the reorientation of colors
	gears[0].switchColors();
	gears[1].switchColors();
	gears[6].switchColors();
	gears[7].switchColors();

	// rotate top and bottom faces
	faces[0].rotateFaceCCW();
	faces[4].rotateFaceCCW();

	// swapping of top rows
	char** tempRows = faces[1].copyTopRows();
	swapTopRows(faces[1], faces[5].copyTopRows());
	swapTopRows(faces[5], faces[3].copyTopRows());
	swapTopRows(faces[3], faces[2].copyTopRows());
	swapTopRows(faces[2], tempRows);

	// swapping of bottom rows
	tempRows = faces[1].copyBottomRows();
	swapBottomRows(faces[1], faces[2].copyBottomRows());
	swapBottomRows(faces[2], faces[3].copyBottomRows());
	swapBottomRows(faces[3], faces[5].copyBottomRows());
	swapBottomRows(faces[5], tempRows);

	alignLeftGearValues(gears[10], faces[1]);
	alignLeftGearValues(gears[4], faces[2]);
	alignLeftGearValues(gears[5], faces[3]);
	alignLeftGearValues(gears[11], faces[5]);
	alignRightGearValues(gears[4], faces[1]);
	alignRightGearValues(gears[5], faces[2]);
	alignRightGearValues(gears[11], faces[3]);
	alignRightGearValues(gears[10], faces[5]);
}

void Gearball::rotateFrontAndBackCW() {
	gears[1].rotate(false);
	gears[2].rotate(false);
	gears[7].rotate(false);
	gears[8].rotate(false);

	// rotate gears around on front face
	Gear tempGear = gears[3];
	gears[3] = gears[4];
	gears[4] = gears[6];
	gears[6] = gears[5];
	gears[5] = tempGear;
	
	// rotate gears around on back face
	tempGear = gears[0];
	gears[0] = gears[11];
	gears[11] = gears[9];
	gears[9] = gears[10];
	gears[10] = tempGear;

	// adjusting for the reorientation of colors
	gears[3].switchColors();
	gears[5].switchColors();
	gears[9].switchColors();
	gears[11].switchColors();

	// rotate front and back faces CW
	faces[2].rotateFaceCCW();
	faces[2].rotateFaceCCW();
	faces[2].rotateFaceCCW();
	faces[5].rotateFaceCCW();
	faces[5].rotateFaceCCW();
	faces[5].rotateFaceCCW();

	// swapping of rows & columns
	char** temp = faces[0].copyTopRows();
	swapRightColsToTopRows(faces[0], faces[3].copyRightCols());
	swapBottomRowsToRightCols(faces[3], faces[4].copyBottomRows());
	swapLeftColsToBottomRows(faces[4], faces[1].copyLeftCols());
	swapTopRowsToLeftCols(faces[1], temp);

	temp = faces[0].copyBottomRows();
	swapRightColsToBottomRows(faces[0], faces[1].copyRightCols());
	swapTopRowsToRightCols(faces[1], faces[4].copyTopRows());
	swapLeftColsToTopRows(faces[4], faces[3].copyLeftCols());
	swapBottomRowsToLeftCols(faces[3], temp);

	// align gear values
	alignRightGearValues(gears[2], faces[0]);
	alignLeftGearValues(gears[1], faces[0]);
	alignRightGearValues(gears[8], faces[4]);
	alignLeftGearValues(gears[7], faces[4]);
	alignTopGearValues(gears[1], faces[1]);
	alignBottomGearValues(gears[7], faces[1]);
	alignTopGearValues(gears[2], faces[3]);
	alignBottomGearValues(gears[8], faces[3]);
}

void Gearball::rotateFrontAndBackCCW() {
	gears[1].rotate(true);
	gears[2].rotate(true);
	gears[7].rotate(true);
	gears[8].rotate(true);

	// rotate gears around on front face
	Gear tempGear = gears[3];
	gears[3] = gears[5];
	gears[5] = gears[6];
	gears[6] = gears[4];
	gears[4] = tempGear;

	// rotate gears around on back face
	tempGear = gears[0];
	gears[0] = gears[10];
	gears[10] = gears[9];
	gears[9] = gears[11];
	gears[11] = tempGear;

	// adjusting for the reorientation of colors
	gears[3].switchColors();
	gears[4].switchColors();
	gears[9].switchColors();
	gears[10].switchColors();

	// rotate front and back faces CCW
	faces[2].rotateFaceCCW();
	faces[5].rotateFaceCCW();

	// swapping of rows & columns
	char** temp = faces[0].copyTopRows();
	swapLeftColsToTopRows(faces[0], faces[1].copyLeftCols());
	swapBottomRowsToLeftCols(faces[1], faces[4].copyBottomRows());
	swapRightColsToBottomRows(faces[4], faces[3].copyRightCols());
	swapTopRowsToRightCols(faces[3], temp);

	temp = faces[0].copyBottomRows();
	swapLeftColsToBottomRows(faces[0], faces[3].copyLeftCols());
	swapTopRowsToLeftCols(faces[3], faces[4].copyTopRows());
	swapRightColsToTopRows(faces[4], faces[1].copyRightCols());
	swapBottomRowsToRightCols(faces[1], temp);

	// align gear values
	alignRightGearValues(gears[2], faces[0]);
	alignLeftGearValues(gears[1], faces[0]);
	alignRightGearValues(gears[8], faces[4]);
	alignLeftGearValues(gears[7], faces[4]);
	alignTopGearValues(gears[1], faces[1]);
	alignBottomGearValues(gears[7], faces[1]);
	alignTopGearValues(gears[2], faces[3]);
	alignBottomGearValues(gears[8], faces[3]);
}

// function to count the number of spaces on the gearball's faces (not including gear spots) that are not in the correct spot
int Gearball::countNumSpacesIncorrect() {
	int count = 0;
	for (int i = 0; i < 6; i++) {
		for (int x = 0; x < 9; x++) {
			for (int y = 0; y < 9; y++) {
				// makes sure the space being checked is not a blank space or a gear space
				if (faces[i].faceArray[x][y] != ' ' && !faces[i].isGearSpace(x, y)) {
					if (i == 0) {
						if (faces[i].faceArray[x][y] != 'B') {
							count++;
						}
					}
					else if (i == 1) {
						if (faces[i].faceArray[x][y] != 'R') {
							count++;
						}
					}
					else if (i == 2) {
						if (faces[i].faceArray[x][y] != 'Y') {
							count++;
						}
					}
					else if (i == 3) {
						if (faces[i].faceArray[x][y] != 'P') {
							count++;
						}
					}
					else if (i == 4) {
						if (faces[i].faceArray[x][y] != 'G') {
							count++;
						}
					}
					else if (i == 5) {
						if (faces[i].faceArray[x][y] != 'O') {
							count++;
						}
					}
				}
			}
		}
	}
	return count;
}

// function to find the maximum number of gear rotations needed amongst the gears on the gearball
int Gearball::countMaxGearRotation() {
	int maxNum = 0;
	for (int i = 0; i < 12; i++) {
		int num = abs(gears[i].getNumRotations());
		if (num > 3) {
			num = 6 - num;
		}
		maxNum = max(maxNum, abs(num));
	}
	return maxNum;
}

// function to calculate the heuristic value for the current state of the gearball
// combines both the face heuristic and gear heuristic and returns the maximum
int Gearball::calculateHeuristicValue() {
	float faceValueFloat = (float)countNumSpacesIncorrect() / 96.0;
	int faceValue = ceil(faceValueFloat); // always round the value up
	int gearValue = countMaxGearRotation();

	int maxValue = max(faceValue, gearValue);

	return maxValue;
}

// function to determined whether or not the gearball is currently in a solved state
bool Gearball::isSolved() {
	for (int i = 0; i < 6; i++) {
		for (int x = 0; x < 9; x++) {
			for (int y = 0; y < 9; y++) {
				// makes sure the space being checked is not a blank space
				if (faces[i].faceArray[x][y] != ' ') {
					if (i == 0) {
						if (faces[i].faceArray[x][y] != 'B') {
							return false;
						}
					}
					else if (i == 1) {
						if (faces[i].faceArray[x][y] != 'R') {
							return false;
						}
					}
					else if (i == 2) {
						if (faces[i].faceArray[x][y] != 'Y') {
							return false;
						}
					}
					else if (i == 3) {
						if (faces[i].faceArray[x][y] != 'P') {
							return false;
						}
					}
					else if (i == 4) {
						if (faces[i].faceArray[x][y] != 'G') {
							return false;
						}
					}
					else if (i == 5) {
						if (faces[i].faceArray[x][y] != 'O') {
							return false;
						}
					}
				}
			}
		}
	}
	return true;
}
