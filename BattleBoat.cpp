#include "BattleBoat.h"
#include <algorithm>
using namespace std;

BattleBoat::BattleBoat(unsigned int length) 
    : length { min(MAX_LENGTH, length) }
{
}

unsigned int BattleBoat::getLength() const
{
    return length;
}

unsigned int BattleBoat::getStartX() const
{
    return startX;
}

unsigned int BattleBoat::getStartY() const
{
    return startY;
}

bool BattleBoat::isVertical() const
{
    return vertical;
}

ostream& BattleBoat::printSegment(ostream& out, unsigned int x, unsigned int y) const
{
    if (length == 1)
    {
        // Single cell boat
        out << "<";
        
        if (hits[0])
        {
            out << "X";
        }
        else
        {
            out << "O";
        }

        out << ">";
    }
    else if (vertical)
    {
        if (y == startY)
        {
            // Top end cap
            out << "/";

            if (hits[0])
            {
                out << "X";
            }
            else
            {
                out << "O";
            }

            out << "\\";
        }
        else if (y == startY + length - 1)
        {
            // Bottom end cap
            out << "\\";

            if (hits[length - 1])
            {
                out << "X";
            }
            else
            {
                out << "O";
            }

            out << "/";
        }
        else
        {
            // Middle vertical segment
            out << "|";

            if (hits[y - startY])
            {
                out << "X";
            }
            else
            {
                out << "O";
            }

            out << "|";
        }
    }
    else
    {
        // Left end cap
        if (x == startX)
        {
            out << "<";

            if (hits[0])
            {
                out << "X";
            }
            else
            {
                out << "O";
            }

            out << "=";
        }
        else if (x == startX + length - 1)
        {
            // Right end cap
            out << "=";

            if (hits[length - 1])
            {
                out << "X";
            }
            else
            {
                out << "O";
            }

            out << ">";
        }
        else
        {
            // Middle horizontal segment
            out << "=";

            if (hits[x - startX])
            {
                out << "X";
            }
            else
            {
                out << "O";
            }

            out << "=";
        }
    }

    return out;
}

void BattleBoat::setStartX(unsigned int startX)
{
    this->startX = startX;
}

void BattleBoat::setStartY(unsigned int startY)
{
    this->startY = startY;
}

void BattleBoat::setVertical(bool vertical)
{
    this->vertical = vertical;
}

bool BattleBoat::intersects(const BattleBoat& other) const
{
    for (unsigned int i = 0; i < length; i++) {
        for (unsigned int j = 0; j < other.length; j++) {
            if (this->isVertical()) {
                if (other.isVertical()) {
                    // Two vertical boats
                    if (this->getStartX() == other.getStartX() && this->getStartY() + i == other.getStartY() + j) {
                        return true;
                    }
                }
                else {
                    // One vertical and one horizontal boat
                    if (this->getStartX() == other.getStartX() + j && this->getStartY() + i == other.getStartY()) {
                        return true;
                    }
                }
            }
            else {
                // One vertical and one horizontal boat
                if (other.isVertical()) {
                    if (this->getStartX() + i == other.getStartX() && this->getStartY() == other.getStartY() + j) {
                        return true;
                    }
                }
                else {
                    // Two horizontal boats
                    if (this->getStartX() + i == other.getStartX() + j && this->getStartY() == other.getStartY()) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
} 



bool BattleBoat::isHit(unsigned int x, unsigned int y) const
{   if (vertical) {
        // Check boat
        bool isBoatPresent = x == startX && startY <= y && y < startY + length;
        if (!isBoatPresent) {
            return false;
        }
        return hits[y - startY];
    }
    else {
        // Check boat
        bool isBoatPresent = y == startY && startX <= x && x < startX + length;
        if (!isBoatPresent) {
            return false;
        }
        return hits[x - startX];
    }   
}

void BattleBoat::hit(unsigned int x, unsigned int y)
{
    if (vertical) {
        // Vertical hits
        bool isBoatPresent = x == startX && startY <= y && y < startY + length;
        if (isBoatPresent) {
            hits[y - startY] = true;
        }
    }
    else {
        // Horizontal hits
        bool isBoatPresent = y == startY && startX <= x && x < startX + length;
        if (isBoatPresent) {
            hits[x - startX] = true;
        }
    } 
}

bool BattleBoat::isSunk() const
{   // This function should return true if every segment in the boat has been hit (each square on the
    // board that the ship occupies), or false otherwise(if any square that it occupies has not been hit).
    for (unsigned int i = 0; i < length; i++) {
        if (!hits[i]) {
            return false;
        }
    }
    return true;
}

/*
  for (int i = 0; i < this->getLength(); i++) {
      for (int j = 0; j < other.getLength(); j++) {
          if (this->isVertical()) {
              if (other.isVertical()) {
                  // Two vertical boats
                  if (this->getStartX() == other.getStartX() && this->getStartY() + i == other.getStartY() + j) {
                      return true;
                  }
              }
              else {
                  // One vertical and one horizontal boat
                  if (this->getStartX() == other.getStartX() + j && this->getStartY() + i == other.getStartY()) {
                      return true;
                  }
              }
          }
          else {
              // One vertical and one horizontal boat
              if (other.isVertical()) {
                  if (this->getStartX() + i == other.getStartX() + j && this -> getStartY() == other.getStartY()) {
                      return true;
                  }
              }
              else {
                  // Two horizontal boats
                  if (this->getStartX() + i == other.getStartX() + j && this->getStartY() == other.getStartY()) {
                      return true;
                  }
              }
          }
      }
  } */


/*if (this->isVertical() && other.isVertical() && this->getStartX() != other.getStartX()) {
        //both starting points can't be the same, cannot intersect
        return false;
    }
    // If not true
    if (!this->isVertical() && !other.isVertical() && this->getStartY() != other.getStartY()) {
        return false;
    } 

    if (!this->isVertical() && other.isVertical()) {
        unsigned int planeY = this->getStartY();
        unsigned int endY = other.getStartY() + other.getLength();

        if (planeY >= other.getStartY() && planeY <= endY) {
            unsigned int planeX = other.getStartX();
            unsigned int endX = this->getStartX() + this->getLength();
            return true;
        }
        
        return false;
    } */

    /*
    // Information about this boat
    unsigned int xLen = vertical ? 0 : length;
    unsigned int yLen = vertical ? length : 0;
    unsigned int x1 = startX;
    unsigned int x2 = startX + xLen;
    unsigned int y1 = startY;
    unsigned int y2 = startY + yLen;

    // Information about the other boat
    unsigned int xLenOther = other.vertical ? 0 : other.length;
    unsigned int yLenOther = other.vertical ? other.length : 0;
    unsigned int x1Other = other.startX;
    unsigned int x2Other = other.startX + xLenOther;
    unsigned int y1Other = other.startY;
    unsigned int y2Other = other.startY + yLenOther;

    // Check if their x values intersect
    bool xIntersect = (x1 <= x1Other && x1Other <= x2) || (x1 <= x2Other && x2Other <= x2);

    // Check if their y values intersect
    bool yIntersect = (y1 <= y1Other && y1Other <= y2) || (y1 <= y2Other && y2Other <= y2);

    return xIntersect && yIntersect;
    */