//
// Created by dadrasarmin on 7/29/17.
//

#ifndef CLIENT_MOVINGCELL_H
#define CLIENT_MOVINGCELL_H


#include <QList>

#include "Cell.h"

// Base class for player and bots
class MovingCell : public Cell
{

public:
    MovingCell(); // constructor
    virtual void eatCell(const Cell* toBeEaten) = 0; // pure virtual
    int score_;

    void checkCollision(); // checking collision
};


#endif //CLIENT_MOVINGCELL_H
