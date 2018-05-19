//
// Created by dadrasarmin on 7/29/17.
//

#include "Header/Cell.h"

// constructor
Cell::Cell(QGraphicsEllipseItem *parent) : QGraphicsEllipseItem(parent)
{
    hasBeenEaten_ = false; // set initial status of cell to not hasBeenEaten
}
// end constructor

// return x position
qreal Cell::getXPosition() const
{
    return xPosition_;
}
// end getXPosition

// return y position
qreal Cell::getYPosition() const
{
    return yPosition_;
}
// end getYPosition

// return cell's radius
int Cell::getRadius() const
{
    return radius_;
}
// edn getRadius

// return TopEdge of cell
qreal Cell::getTopEdge() const
{
    return yPosition_ - radius_;
}
// end getTopEdge

// return left edge of cell
qreal Cell::getLeftEdge() const
{
    return xPosition_ - radius_;
}
// end getLeftEdge

// check whether a cell can be eaten or not, and if it can, it has be eaten!
bool Cell::canBeEaten()
{
    if(hasBeenEaten_) // if not eaten yet!
        return false;

    if(this->who() != "Virus")
    {
        hasBeenEaten_ = true; // eat this
        setVisible(false); // remove it from scene
    }


    return true;
}
// end canBeEaten

// return a rectangle that use in shape function
QRectF Cell::boundingRect() const
{
    // return a rectangle with given upper left corner, width and height
    return QRectF( xPosition_ - radius_, yPosition_ - radius_,
                   QRECT_SCALE * radius_, QRECT_SCALE * radius_ );
}
// end boundingRect

// The shape is used for many things,
// including collision detection, hit tests, and for the QGraphicsScene::items() functions.
// build a container for cell's painting operations
QPainterPath Cell::shape() const
{
    QPainterPath path; // create an object of QPainterPath
    path.addEllipse( boundingRect() ); // add an ellipse to this object via given boundary and size
    return path; // return the object
}
// end shape
