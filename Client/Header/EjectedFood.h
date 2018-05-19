//
// Created by dadrasarmin on 7/29/17.
//

#ifndef CLIENT_CELL_H
#define CLIENT_CELL_H


#include <QGraphicsEllipseItem>
#include <QPainter>
#include <QTime>
#include <QObject>

const int BOARD_WIDTH = 800;
const int BOARD_HEIGHT = 600;
const int QRECT_SCALE = 2;

// Base class for every cell in game
class Cell : public QObject, public QGraphicsEllipseItem
{
Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)

public:

    Cell(QGraphicsEllipseItem *parent = NULL);

    qreal getXPosition() const;
    qreal getYPosition() const;
    int getRadius() const;

    // Functions that return max circle position
    qreal getTopEdge() const;
    qreal getLeftEdge() const;

    bool canBeEaten(); // check whether cell can be eaten
    virtual void isEaten() = 0; // inform map if being eaten, this is pure virtual :)
    virtual QString who() = 0; // inform who is it? :)

    int radius_; // radius of cell
    bool hasBeenEaten_; // determine cell has been eaten



protected:
    // overload Qt method
    QPainterPath shape() const override ; // return shape of the cell
    QRectF boundingRect() const override ; // determine rectangle in which cell is painted in it


    /* attributes */
    qreal xPosition_, yPosition_; // coordination of circle's center
    QColor color_; // color of the cell
};


#endif //CLIENT_CELL_H
