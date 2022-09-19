#pragma once
#include "Gear.h"
#include "Face.h"
#include <string>
#include <iostream>

using namespace std;


class Gearball
{
private:
	Gear gears[12]; // 12 gears in whole puzzle
	Face faces[6];  // 6 faces in whole puzzle

public:
	Gearball();
	void initializeGears();
	void initializeFaces();
	void resetGearball();
	void printGearball();
	string randomizeGearball(int numMoves);
	void swapLeftCols(Face &face, char** newCols);
	void swapRightCols(Face &face, char** newCols);
	void swapTopRows(Face &face, char** newRows);
	void swapBottomRows(Face &face, char** newRows);
	void swapRightToLeftCols(Face& face, char** rightCols);
	void swapLeftToRightCols(Face& face, char** leftCols);
	void swapLeftColsToTopRows(Face& face, char** leftCols);
	void swapRightColsToTopRows(Face& face, char** rightCols);
	void swapRightColsToBottomRows(Face& face, char** rightCols);
	void swapLeftColsToBottomRows(Face& face, char** leftCols);
	void swapTopRowsToLeftCols(Face& face, char** topRows);
	void swapTopRowsToRightCols(Face& face, char** topRows);
	void swapBottomRowsToRightCols(Face& face, char** bottomRows);
	void swapBottomRowsToLeftCols(Face& face, char** bottomRows);
	void alignTopGearValues(Gear gear, Face &face);
	void alignRightGearValues(Gear gear, Face& face);
	void alignLeftGearValues(Gear gear, Face& face);
	void alignBottomGearValues(Gear gear, Face& face);
	void rotateRightAndLeftCW();
	void rotateRightAndLeftCCW();
	void rotateTopAndBottomCW();
	void rotateTopAndBottomCCW();
	void rotateFrontAndBackCW();
	void rotateFrontAndBackCCW();
	int countNumSpacesIncorrect();
	int countMaxGearRotation();
	int calculateHeuristicValue();
	bool isSolved();
};

