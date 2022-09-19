#pragma once
#include <string>
#include <iostream>

using namespace std;

class Gear
{
private:
	char color1;
	char color2;
	int numRotations;

public:
	Gear();
	Gear(char newColor1, char newColor2);
	void setColor1(char color);
	char getColor1();
	void setColor2(char color);
	char getColor2();
	void switchColors();
	void setNumRotations(int newNum);
	int getNumRotations();
	void rotate(bool direction);
};

