#pragma once
#include "Gear.h"
#include <string>
#include <iostream>

using namespace std;

class Face
{
private:
	string name;

public:
	Face();
	Face(char color, string n1);
	char faceArray[9][9];
	void setName(string newName);
	string getName();
	void faceSetup(char color);
	char** copyTopRows();
	char** copyBottomRows();
	char** copyLeftCols();
	char** copyRightCols();
	void rotateFaceCCW();
	void printRow(int row);
	void printRowBackwards(int row);
	bool isGearSpace(int row, int col);
};

