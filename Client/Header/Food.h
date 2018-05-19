//
// Created by dadrasarmin on 7/29/17.
//

#ifndef CLIENT_FOOD_H
#define CLIENT_FOOD_H


#include "Cell.h"

const int FOOD_RADIUS = 6;

class Food : public Cell
{
public:
    Food(QString , QString , QString ); // constructor

    // inform map about being eaten
    virtual void isEaten(); // overload cell's isEaten pure virtual function
    virtual QString who(); // inform who is it

protected:
    // override Qt method
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};



#endif //CLIENT_FOOD_H
