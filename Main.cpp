#include "Gear.h"
#include "Face.h"
#include "Gearball.h"
#include "AStar.h"

#include <iostream>
#include <string>

using namespace std;

void printMenu() {
    cout << endl;
    cout << "Program Options (Type the desired number): " << endl;
    cout << "0 - Stop running the program" << endl;
    cout << "1 - Print the menu again" << endl;
    cout << "2 - Print the gearball GUI" << endl;
    cout << "3 - Randomize the gearball" << endl;
    cout << "4 - Reset the gearball" << endl;
    cout << "5 - Determine heuristic value of the gearball in its current state" << endl;
    cout << "6 - Determine whether or not the gearball is in a solved state" << endl;
    cout << "7 - Solve current gearball using A* algorithm" << endl;
    cout << "8 - Generate 5 k-randomized instances of the gearball & solve them using A*" << endl;
    cout << endl;
}

int main()
{
    // initialize Gearball object
    Gearball gearball = Gearball();

    // initializing input with a value that is not present in the menu
    int input = 5;

    printMenu();

    while (input != 0) {
        cout << "Enter menu Selection:" << endl;
        cin >> input;

        switch (input) {
        case 0: 
            break;
        case 1: {
            printMenu();
            break;
        }
        case 2: {
            gearball.printGearball();
            break;
        }
        case 3: {
            cout << "How many moves would you like to perform? " << endl;
            int numMoves;
            cin >> numMoves;
            gearball.randomizeGearball(numMoves);
            if (numMoves == 1)
                cout << "1 random move has been performed." << endl << endl;
            else
                cout << numMoves << " random moves have been performed." << endl << endl;
            break;
        }
        case 4: {
            gearball.resetGearball();
            cout << "The gearball has been reset to its original state." << endl << endl;
            break;
        }
        case 5: {
            cout << "The gearball's current heuristic value is " << gearball.calculateHeuristicValue() << "." << endl << endl;
            break;
        }
        case 6: {
            if (gearball.isSolved())
                cout << "The gearball is solved!" << endl << endl;
            else
                cout << "The gearball is not solved." << endl << endl;
            break;
        }
        case 7: {
            gearball = solveUsingAStar(gearball);
            break;
        }
        case 8: {
            cout << "What would you like the value of the randomizing parameter (k) to be?" << endl;
            int k;
            cin >> k;
            generateAndSolveRandomizedGearballs(k);
        }
        default: {
            printMenu();
            break;
        }
        }
    }
}
