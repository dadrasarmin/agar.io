//
// Created by dadrasarmin on 7/30/17.
//

#ifndef CLIENT_VIRUS_H
#define CLIENT_VIRUS_H


#include "Cell.h"

const int Virus_RADIUS = 40;

class Virus : public Cell
{
public:
    Virus(QString , QString); // constructor

    virtual void isEaten(); // overload cell's isEaten pure virtual function
    virtual QString who();

protected:
    // override Qt method
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};


#endif //CLIENT_VIRUS_H
