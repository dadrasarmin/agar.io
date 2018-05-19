//
// Created by dadrasarmin on 7/29/17.
//

#include "Header/EjectedFood.h"
#include <Header/LoginWindow.h>


// constructor
EjectedFood::EjectedFood( QString xD, QString yD, QString cP)
{
    radius_ = EJECTED_FOOD_RADIUS;
    // randomize color
    color_.setNamedColor( QColor::colorNames().at( cP.toInt() ) );
    xPosition_ = xD.toDouble();
    yPosition_ = yD.toDouble();


    // set position at map
    setRect(getLeftEdge(), getTopEdge(), QRECT_SCALE * radius_, QRECT_SCALE * radius_);
    setPos(getLeftEdge(), getTopEdge());
}
// end constructor

// sets ejectedFood attributes for painting on scene (because this is an overloaded function two last parameters should be writen)
void EjectedFood::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget )
{
    painter->setBrush(color_); // set color of food
    painter->drawEllipse( boundingRect() ); // call boundingRect from cell class
}
// end paint

// overloaded isEaten function. Map object remove this food and add new food to map
void EjectedFood::isEaten()
{
    QString foodEaten = "ef|";
    foodEaten += QString::number(this->getXPosition());
    foodEaten += "|";
    foodEaten += QString::number(this->getYPosition());
    foodEaten += "|";

    LoginWindow::getInstance()->sendInfo( foodEaten );
}
// end isEaten

QString EjectedFood::who()
{
    QString ej = "EjectedFood";
    return ej;
}
