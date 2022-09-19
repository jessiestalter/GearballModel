#pragma once
#include "Gearball.h"
#include <string>
#include <iostream>
#include <vector>
//#include <unordered_map>
#include <queue>

using namespace std;

// creating a node struct
struct node {
	node* parent; // pointer to its parent node
	Gearball state; // the node's puzzle state
	int g; // cost
	int h; // heuristic
	int movePerformed; // an int representing the move that was performed to get from the previous puzzle state to this one
	// definition for the < operator used within priority queues
	// makes sure the node with the minimum f value (g+h) is first in the queue
	bool operator<(const node& n) const
	{
		return (g + h) > (n.g + n.h);
	}
};

// function to implement the A* algorithm on a randomized Gearball
// returns a solved state of the gearball after running the algorithm
Gearball solveUsingAStar(Gearball randomizedBall) {
	cout << "Solving Gearball..." << endl;

	// initialize priority queue
	priority_queue<node> queue;

	// initialize variable to keep track of the number of nodes visited
	int numNodesExpanded = 0;

	// create new node for the initial state
	node startNode = node();
	startNode.parent = NULL;
	startNode.state = randomizedBall;
	startNode.g = 1;
	startNode.h = 1;
	startNode.movePerformed = -1;
	queue.push(startNode); // put it into the queue

	// initialize variable for current node
	node current;

	// while the priority queue is not empty
	while (!queue.empty()) {
		// remove the top element off the queue (the one w/ the lowest f value)
		current = queue.top();
		queue.pop();

		// check if the current node is solved
		if (current.state.isSolved()) {
			cout << "The gearball has been solved!" << endl;
			cout << numNodesExpanded << " total nodes were expanded" << endl;
			node* pointer = &current;

			// TODO: get backtracking portion of code working to figure out the path
			/*while (pointer != NULL) {
				cout << pointer->movePerformed;
				pointer = pointer->parent;
			}
			cout << endl;*/
			return current.state;
		}

		numNodesExpanded++; // increment number of nodes expanded

		// set up children of the current state, one for each possible move on the ball
		Gearball copies[6];
		for (int i = 0; i < 6; i++) {
			copies[i] = current.state;
			switch (i) {
			case 0: {
				copies[i].rotateRightAndLeftCW();
				break;
			}
			case 1: {
				copies[i].rotateRightAndLeftCCW();
				break;
			}
			case 2: {
				copies[i].rotateTopAndBottomCW();
				break;
			}
			case 3: {
				copies[i].rotateTopAndBottomCCW();
				break;
			}
			case 4: {
				copies[i].rotateFrontAndBackCW();
				break;
			}
			case 5: {
				copies[i].rotateFrontAndBackCCW();
				break;
			}
			}
		}

		// get the move that would undo the previous move so it can not be included as one of the children
		int nodeNotToInclude;
		if (current.movePerformed % 2 == 0) {
			nodeNotToInclude = current.movePerformed + 1;
		}
		else {
			nodeNotToInclude = current.movePerformed - 1;
		}

		// assign children to nodes (avoiding the node not to include)
		node nodes[6];
		for (int i = 0; i < 6; i++) {
			if (i != nodeNotToInclude) {
				nodes[i] = node();
				nodes[i].parent = &current;
				nodes[i].state = copies[i];
				nodes[i].g = current.g + 1;
				nodes[i].h = copies[i].calculateHeuristicValue();
				nodes[i].movePerformed = i;

				// push the new node onto the queue
				queue.push(nodes[i]);
			}
		}
	}
	// if algorithm doesn't find a solution (although it should), just return the most recent node's state
	return current.state;
}

// function to generate random puzzles and solve them using A*
// function generates 5 k-randomized puzzles, where k is the randomizing parameter from 3 to 20
// function then solves each puzzle using the A* algorithm defined above
Gearball* generateAndSolveRandomizedGearballs(int k) {
	// generate 5 k-randomized gearballs and solves them
	Gearball randomizedBalls[5];
	Gearball solvedBalls[5];

	// array of the moves performed to randomize the gearball
	vector<string> moves;
	for (int i = 0; i < 5; i++) {
		cout << endl << "Gearball " << i + 1 << " ..." << endl;
		randomizedBalls[i] = Gearball();
		string movesPerformed = randomizedBalls[i].randomizeGearball(k);

		// check if a gearball with the same moves performed has been solved
		while (find(moves.begin(), moves.end(), movesPerformed) != moves.end()) {
			movesPerformed = randomizedBalls[i].randomizeGearball(k);
		}

		cout << "Moves performed (printed for testing): " << movesPerformed << endl;
		moves.push_back(movesPerformed);

		// solve the randomized gearball
		solvedBalls[i] = solveUsingAStar(randomizedBalls[i]);
	}

	return solvedBalls;
}
