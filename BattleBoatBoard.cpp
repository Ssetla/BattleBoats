#include "BattleBoatBoard.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;


BattleBoatBoard::BattleBoatBoard(const unsigned int* boatLengths, unsigned int count) {
    // Seed the RNG
    srand(time(NULL));

    // Make sure the boat count is not greater than 10
    boatCount = count > 10 ? 10 : count;
    cout << "Boat count: " << boatCount << endl;

    // Generate the random boats
    for (unsigned int i = 0; i < boatCount; i++) {
        // Make sure the length is not greater than 6
        unsigned int length = boatLengths[i] > 6 ? 6 : boatLengths[i];

        BattleBoat* b = new BattleBoat(length);
        // Try to find a place for the boat
        bool canPlace = false;
        while (!canPlace) {
            // Figure out the alignment
            bool isVertical = rand() % 2;
            // Choose a random starting x and y coordinate
            unsigned int startX = rand() % BOARD_SIZE;
            unsigned int startY = rand() % BOARD_SIZE;
            // Assign the boat its new position
            b->setStartX(startX);
            b->setStartY(startY);
            b->setVertical(isVertical);
            // Check if the end of the boat is in bounds, if it is out of bounds skip this loop as it can not be placed
            unsigned int endpoint = isVertical ? startY + length : startX + length;
            if (endpoint >= BOARD_SIZE) {
                continue;
            }
            // Now that we know it is in bounds, make sure it does not intersect any other boats
            canPlace = true;
            for (unsigned int j = 0; j < i; j++) {
                if (b->intersects(boats[j])) {
                    // Break out early if it intersects since we dont need to bother checking other boats
                    canPlace = false;
                    break;
                }
            }
        }
        // Add the boat
        boats[i] = *b;
    } 
}


const BattleBoat* BattleBoatBoard::getBoat(unsigned int x, unsigned int y) const {
    return getBoat(x, y);
}

BattleBoat* BattleBoatBoard::getBoat(unsigned int x, unsigned int y)
{
    for (int i = 0; i < boatCount; i++) {
        if (boats[i].isVertical()) {
            if (x == boats[i].getStartX() && y >= boats[i].getStartY() && y < boats[i].getStartY() + boats[i].getLength()) {
                return &boats[i];
            }
        }
        else {
            if (y == boats[i].getStartY() && x >= boats[i].getStartX() && x < boats[i].getStartX() + boats[i].getLength()) {
                return &boats[i];
            }
        }
    }
    return nullptr;
}
