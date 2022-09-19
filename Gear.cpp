#include "Gear.h"
#include <string>
#include <iostream>

using namespace std;

Gear::Gear() {
	color1 = ' ';
	color2 = ' ';
	numRotations = 0;
}

Gear::Gear(char newColor1, char newColor2) {
	color1 = newColor1;
	color2 = newColor2;
	numRotations = 0;
}

void Gear::setColor1(char color) {
	color1 = color;
}

char Gear::getColor1() {
	return color1;
}

void Gear::setColor2(char color) {
	color2 = color;
}

char Gear::getColor2() {
	return color2;
}

void Gear::switchColors() {
	char temp = color1;
	color1 = color2;
	color2 = temp;
}

void Gear::setNumRotations(int newNum) {
	numRotations = newNum;
}

int Gear::getNumRotations() {
	return numRotations;
}

void Gear::rotate(bool direction) {
	// for direction, true = clockwise, false = counterclockwise
	if (direction) { // clockwise
		numRotations++;
	}
	else { // counterclockwise
		numRotations--;
	}
	// once it reaches 6 rotations, the gear is reset to starting position
	numRotations = numRotations % 6;
}
