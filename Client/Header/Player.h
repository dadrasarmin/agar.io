//
// Created by dadrasarmin on 7/29/17.
//

#ifndef CLIENT_PLAYER_H
#define CLIENT_PLAYER_H


#include <QGraphicsItem>
#include <QString>

#include "MovingCell.h"

const int DISPLACEMENT_X = 11;
const int DISPLACEMENT_Y = 4;


const float PLAYER_SPEED_FACTOR = (-1.0)/(32.0);
const float PLAYER_MINIMUM_SPEED = 0.5;
const float PLAYER_ADDITIONAL_SPEED_FACTOR = 2.5;

class Player : public MovingCell
{
public:

    Player(QString,QString,QString,QString,QString,QString); // constructor

    void mouseMove(qreal x, qreal y); // movement
    virtual void eatCell(const Cell* toBeEaten); // eating other cells
    float speed() const; // Getting speed of the player (depends on the radius)
    void ejectFood();

    QString getName();
    void setx( QString );
    void sety( QString );

    int col; // save player color number


protected:
    // override QGraphicsItem function
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual void isEaten(); // overload Cell isEaten function
    virtual QString who();

    void advance(int step) override;


private:
    // attributes
    QString name_;
    QPointF targetVector_; // in which way the player should go
};


#endif //CLIENT_PLAYER_H
