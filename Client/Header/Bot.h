//
// Created by dadrasarmin on 7/29/17.
//

#ifndef CLIENT_BOT_H
#define CLIENT_BOT_H


#include <iostream>
#include <cmath>

#include <QGraphicsItem>
#include "MovingCell.h"

const int DISPLACEMENT = 5;

const float SPEED_FACTOR = (-1.0)/(32.0);
const float MINIMUM_SPEED = 0.5;
const float ADDITIONAL_SPEED_FACTOR = 2.5;

// Class representing bot player
class Bot :  public MovingCell
{

public:
    Bot( QString,QString,QString,QString,QString,QString ); // constructor

    double computeDistance(const Cell *otherCell) const; // Computing distance between two cells
    bool isBiggerThanOtherCell(const Cell* otherCell) const; // Comparing two cells
    float getAngle(const Cell *otherCell) const; // Getting angle between this bot and other Cell
    float getAngle( QPointF &vec) const; // Getting angle of given vector
    float speed() const; // Getting speed of the bot (depends on the radius)
    virtual void eatCell(const Cell* toBeEaten); // Eating other cell
    virtual void isEaten(); // Informing map about being eaten
    virtual QString who(); // inform who is this

    QString getName();
    void setx( QString );
    void sety( QString );

private:
    void checkIfEscapeOrFollow(Cell* cell, int viewDis); // Checking if bot need to escape or follow given Cell
    void addEdgeInfluenceVector(QPointF& vec, int edgeDistance ); // Taking care of map edges, to prevent crossing edge by bot

protected:
    // override Qt methods
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void advance(int step) override;

private:
    // attributes
    QString name_;
    QPointF targetVector_; // in which way the bot should go
    Cell* targetCell_; // which Cell bot should follow

};


#endif //CLIENT_BOT_H
