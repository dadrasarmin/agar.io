//
// Created by dadrasarmin on 7/30/17.
//

#include "Header/Virus.h"
#include "Header/LoginWindow.h"

// constructor
Virus::Virus(QString xP, QString yP)
{
    radius_ = Virus_RADIUS;

    xPosition_ = xP.toDouble();
    yPosition_ = yP.toDouble();
    color_.setNamedColor( "steelblue" );

    // set position at map
    setRect(getLeftEdge(), getTopEdge(), QRECT_SCALE * radius_, QRECT_SCALE * radius_);
    setPos(getLeftEdge(), getTopEdge());
}
// end constructor

// sets virus attributes for painting on scene (because this is an overloaded function two last parameters should be writen)
void Virus::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget )
{
    painter->setBrush(color_); // set color of food
    painter->drawEllipse( boundingRect() ); // call boundingRect from cell class

    painter->setBrush(Qt::black); // set text Brush
    painter->drawText(xPosition_ - DISPLACEMENT_X, yPosition_ + DISPLACEMENT_Y, "Virus"); // set name on item
}
// end paint

// overloaded isEaten function. Because this is Virus it shouldn't be eaten :) it should punish that cell
void Virus::isEaten()
{
    // do nothing
}
// end isEaten

QString Virus::who()
{
    QString V = "Virus";
    return V;
}
