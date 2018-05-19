//
// Created by dadrasarmin on 7/29/17.
//

#include "Header/MovingCell.h"

// constructor
MovingCell::MovingCell()
{
    score_ = 0;
}
// end constructor

// check collision cells and eat cells that are smaller
void MovingCell::checkCollision()
{
    QList<QGraphicsItem*> collisions = QGraphicsItem::collidingItems(); // Returns a list of all items that collide with this item

    foreach (QGraphicsItem* item, collisions)
    {
        if(Cell* cell = dynamic_cast<Cell*>(item)) // this is for when i added score board
        {
            if(cell->getRadius() < radius_)    // if want a spacial ratio we can insert it here
                eatCell(cell); // eat cell when is smaller. this function is pure virtual
        }

    }
}
// end checkCollision
