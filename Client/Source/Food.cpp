//
// Created by dadrasarmin on 7/29/17.
//

#include <Header/LoginWindow.h>
#include "Header/Food.h"

// constructor
Food::Food(QString xP, QString yP, QString cP)
{
    radius_ = FOOD_RADIUS;

    xPosition_ = xP.toDouble();
    yPosition_ = yP.toDouble();

    // randomize color
    color_.setNamedColor( QColor::colorNames().at( cP.toInt() ) );

    // set position at map
    setRect(getLeftEdge(), getTopEdge(), QRECT_SCALE * radius_, QRECT_SCALE * radius_);
    setPos(getLeftEdge(), getTopEdge());
}
// end constructor

// sets food attributes for painting on scene (because this is an overloaded function two last parameters should be writen)
void Food::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget )
{
    painter->setBrush(color_); // set color of food
    painter->drawEllipse( boundingRect() ); // call boundingRect from cell class
}
// end paint

// overloaded isEaten function. Map object remove this food and add new food to map
void Food::isEaten()
{
    QString foodEaten = "f|";
    foodEaten += QString::number(this->getXPosition());
    foodEaten += "|";
    foodEaten += QString::number(this->getYPosition());
    foodEaten += "|";

    LoginWindow::getInstance()->sendInfo( foodEaten );
}
// end isEaten

QString Food::who()
{
    QString F = "Food";
    return F;
}
