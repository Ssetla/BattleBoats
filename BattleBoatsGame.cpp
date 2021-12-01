#include "BattleBoatsGame.h"
#include "BattleBoat.h"

using namespace std;

const bool BattleBoatsGame::isRevealed(unsigned int x, unsigned int y) const
{
    return visited[x][y];
}

bool BattleBoatsGame::shot(unsigned int x, unsigned int y)
{
    // First, reveal the location and increment the turn count
    turnCount++;
    if (x >= board.BOARD_SIZE || y >= board.BOARD_SIZE) {
        return false;
    }
    visited[x][y] = true;

    BattleBoat* boat = board.getBoat(x, y);

    // Return false if there is no boat
    if (boat == nullptr) {
        return false;
    }
    // If the boat was already hit, also return false, otherwise true
    if (boat->isHit(x, y)) {
        return false;
    }
    else {
        boat->hit(x, y);
        return true;
    }
}

unsigned int BattleBoatsGame::getBoatsSunk() const
{
    int ct = 0;
    for (int i = 0; i < board.getBoatCount(); i++) {
        if (board.getBoats()[i].isSunk()) {
            ct++;
        }
    }
    return ct;
}

/*Your first task is to write the definition of a function called shot() in the BattleBoatsGame class.
bool shot(unsigned int x, unsigned int y);

This function should attempt to hit a boat at the coordinates (x, y) and return a value as follows:
• If there is no boat at the location, or the user has already attacked that location, or the
location is out of bounds, shot() should return false.
• If there is a boat at the location and the location has not been previously attacked, shot()
should return true.
You should also increment the turnCount variable maintained by BattleBoatsGame.
In addition, shot() should somehow mark the square that was targeted as “revealed” (you may
want to use a 2D array to keep track of this). However you keep track of this, implement
isRevealed() to return true if the specified coordinates have been revealed, or false otherwise:
const bool isRevealed(unsigned int x, unsigned int y) const;
If x or y is out of bounds, this function should just return false.
Finally, you should be able to use BattleBoat::isSunk() to implement a function called
getBoatsSunk() in the BattleBoatsGame class that counts the number of boats that are sunk:
unsigned int getBoatsSunk() const;
*/