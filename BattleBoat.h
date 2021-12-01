#pragma once
#include <iostream>

// Class for keeping track of the state of a single boat
class BattleBoat
{
public:
    // Constructor: takes length as a parameter
    BattleBoat(unsigned int length = 6);

    // Gets the length of the boat
    unsigned int getLength() const;

    // Gets the x-coordinate of the left-most space occupied by the boat.
    unsigned int getStartX() const;

    // Gets the y-coordinate of the left-most space occupied by the boat.
    unsigned int getStartY() const;

    // Gets whether the boat is aligned vertically (extending downward from the starting space)
    // or horizontally (extending to the right from the starting space).
    bool isVertical() const;

    // Prints out a single segment of the boat using ASCII art.
    std::ostream& printSegment(std::ostream& out, unsigned int x, unsigned int y) const;

    // Sets the x-coordinate of the left-most space occupied by the boat.
    void setStartX(unsigned int startX);

    // Sets the y-coordinate of the left-most space occupied by the boat.
    void setStartY(unsigned int startY);

    // Sets whether the boat is aligned vertically (extending downward from the starting space)
    // or horizontally (extending to the right from the starting space).
    void setVertical(bool vertical);

    // Returns true if this boat overlaps the other boat, false otherwise.
    // This can be used to check if two boats can simulataneously exist on the same board legally.
    bool intersects(const BattleBoat& other) const;

    // Check if the boat has been hit at a particular (x,y) coordinate
    bool isHit(unsigned int x, unsigned int y) const;

    // Set a single segment of the boat as "hit" at a particular (x,y) coordinate
    void hit(unsigned int x, unsigned int y);

    // Check if the boat is sunk (all segments have been hit)
    bool isSunk() const;

    // The maximum possible boat length
    const static unsigned int MAX_LENGTH = 6;

private:
    // Stores the length of the boat.
    unsigned int length;

    // Stores the x-coordinate of the left-most space occupied by the boat.
    unsigned int startX = 0;

    // Stores the y-coordinate of the upper-most space occupied by the boat.
    unsigned int startY = 0;

    // Stores whether the boat is aligned vertically (extending downward from the starting space)
    // or horizontally (extending to the right from the starting space).
    bool vertical = false;

    // An array to keep track of the locations of hits when the boat is targeted during the game.
    bool hits[MAX_LENGTH] = { };

    // Add any other private variables you need here.

};

