#pragma once
#include <iostream>
#include "BattleBoat.h"

// Class for keeping track of a collection of boats conceptually laid out on a 2D grid.
class BattleBoatBoard
{
public:
    // Initialize board using an array of boat sizes
    BattleBoatBoard(const unsigned int* boatLengths, unsigned int boatCount);

    // Gets the number of boats on the board.
    const unsigned int getBoatCount() const 
    { 
        return boatCount; 
    }

    // Gets a pointer to the array of boats.
    const BattleBoat* getBoats() const
    {
        return boats;
    }

    // Gets a pointer to the array of boats.
    BattleBoat* getBoats()
    {
        return boats;
    }

    // Get boat by (x,y) coordinate.
    // Returns nullptr if coords are out of bounds or boat does not exist
    const BattleBoat* getBoat(unsigned int x, unsigned int y) const;
    
    // Get boat by (x,y) coordinate.
    // Returns nullptr if coords are out of bounds or boat does not exist
    BattleBoat* getBoat(unsigned int x, unsigned int y);

    // Maximum possible number of boats
    const static unsigned int MAX_BOAT_COUNT = 10;

    // The fixed size of the game board
    const static unsigned int BOARD_SIZE = 10;

private:

    // The "master" array of boats
    BattleBoat boats[MAX_BOAT_COUNT] { };

    // The number of boats (i.e., the number of positions in the boat array that are actually used).
    unsigned int boatCount;

    // Add any other private variables you need here.

};

// Print out the board (with all boats revealed).
inline std::ostream& operator << (std::ostream& out, const BattleBoatBoard& board)
{
    // X-axis labels
    out << "  ";
    for (int i = 0; i < BattleBoatBoard::BOARD_SIZE; i++)
    {
        out << " " << i << " ";
    }
    out << std::endl;

    for (int j = 0; j < BattleBoatBoard::BOARD_SIZE; j++)
    {
        // y-axis label
        out << j << " ";

        for (int i = 0; i < BattleBoatBoard::BOARD_SIZE; i++)
        {
            const BattleBoat* boat = board.getBoat(i, j);
            if (boat)
            {
                // Print a segment of the boat
                boat->printSegment(out, i, j);
            }
            else
            {
                // Empty water
                out << "   ";
            }
        }
        out << std::endl;
    }

    return out;
}
