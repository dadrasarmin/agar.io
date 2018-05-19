//
// Created by dadrasarmin on 7/29/17.
//

#include "Header/LoginWindow.h"
#include "Header/Player.h"

#include <iostream>
using namespace std;


// constructor
Player::Player( QString x, QString y, QString c, QString r, QString s, QString n )
{
    //initialize player
    xPosition_ = x.toDouble();
    yPosition_ = y.toDouble();
    radius_ = r.toInt();

    // set color by random
    color_.setNamedColor(QColor::colorNames().at(c.toInt()));
    col = c.toInt();

    score_ = s.toInt();
    name_ = n;


    //set position
    setRect(xPosition_ - radius_, yPosition_ - radius_,
            QRECT_SCALE * radius_, QRECT_SCALE * radius_);
    setPos(xPosition_ - radius_, yPosition_ - radius_);

    //make player focusable
    setFlag(QGraphicsEllipseItem::ItemIsFocusable); // the item supports keyboard input focus
    setFocus(); // Gives keyboard input focus to this item
}
// end constructor

// return speed of cell
float Player::speed() const
{
    float speed = ( (PLAYER_SPEED_FACTOR) * radius_ ) + PLAYER_ADDITIONAL_SPEED_FACTOR;
    if(speed < PLAYER_MINIMUM_SPEED)
        speed = PLAYER_MINIMUM_SPEED;

    return speed;
}
// end speed

// handle mouse movement and moving cell
void Player::mouseMove(qreal x, qreal y)
{
    QPointF tmpVec = QPointF(x - xPosition_ , y - yPosition_);;

    qreal xDis = xPosition_ - x;
    qreal yDis = yPosition_ - y;

    double distance = sqrt(xDis * xDis + yDis * yDis); //sqrt(dx^2 + dy^2)

    if (distance != 0)
    {
        tmpVec = tmpVec / distance; // normalize vector
        targetVector_ = tmpVec;
    }

    if ( targetVector_.x() != 0 || targetVector_.y() != 0 )
    {
        targetVector_ = targetVector_ / (sqrt( targetVector_.x() * targetVector_.x() + targetVector_.y() * targetVector_.y() ) ); // normalize

        qreal dx = (targetVector_.x() * speed()); // how far move in x direction
        qreal dy = (targetVector_.y() * speed()); // how far move in y direction

        xPosition_ += dx;
        yPosition_ += dy;
    }

    QString playerMove = "p|m|";
    playerMove += getName();
    playerMove += "|";
    playerMove += QString::number( xPosition_ );
    playerMove += "|";
    playerMove += QString::number( yPosition_ );
    playerMove += "|";

    LoginWindow::getInstance()->sendInfo(playerMove);

    checkCollision();
}
// end mouseMove

// overloading eatCell function of MovingCell class
void Player::eatCell(const Cell* toBeEaten)
{
    Cell* cell = const_cast<Cell*>(toBeEaten);
    if( cell->canBeEaten() ) // if that cell can be eaten
    {
        QString what = cell->who();

        if( what != "Virus" )
        {
            cell->isEaten(); // change that cell status to eaten


            QString eatCell = "p|eatCell|";
            eatCell += getName();
            eatCell += "|";
            eatCell += QString::number(cell->getRadius());
            eatCell += "|";

            LoginWindow::getInstance() ->sendInfo(eatCell);
        }
        else if( what == "Virus" )
        {
            QString punish = "p|punish|";
            punish += getName();
            punish += "|";

            LoginWindow::getInstance()->sendInfo(punish);
        }

    }
}
// end eatCell overloading

QString Player::who()
{
    QString P = "Player";
    return P;
}

// show lost message
void Player::isEaten()
{
    QString playerLost = "p|lost|";
    playerLost += getName();
    playerLost += "|";

    LoginWindow::getInstance()->sendInfo(playerLost);
}
// end isEaten

// painting player cell with appropriate name and color
void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(color_); // set color
    painter->drawEllipse( Cell::boundingRect() ); // draw rectangle

    painter->setBrush(Qt::black); // set text Brush
    painter->drawText(xPosition_ - DISPLACEMENT_X, yPosition_ + DISPLACEMENT_Y, name_); // set name on item

}
// end paint

// return player name
QString Player::getName()
{
    return name_;
}

// update x position
void Player::setx(QString nx)
{
    xPosition_ = nx.toDouble();
}

// update y position
void Player::sety(QString ny)
{
    yPosition_ = ny.toDouble();
}

// check collision for every update
void Player::advance(int step)
{
    // In the first phase, item is notified that the scene is about to change,and in the second phase items is notified that they can move.
    //In the first phase, QGraphicsItem::advance() is called passing a value of 0 as an argument, and 1 is passed in the second phase.
    if(!step)
        return;

    for(int k = 0; k < Map::getInstance()->playerList.size(); k++)
    {
        if( Map::getInstance()->playerList[k]->getName() == Map::getInstance()->playerName )
        {
            checkCollision();
            QString p = "p";
            LoginWindow::getInstance()->updateMonitor( p );

            break;
        }
    }
}

// eject food from this cell
void Player::ejectFood()
{
    if( radius_ < 25 )
        return;

    QPointF mousePos = QCursor::pos();

    double xD = mousePos.x() ;
    double yD = mousePos.y() ;

    qreal xDis = getXPosition() - xD;
    qreal yDis = getYPosition() - yD;

    if( xDis > 300 )
        xD /= 10;
    if( yDis > 300 )
        yD /= 10;




    QString ejectedFood = "new|ef|";
    ejectedFood += QString::number( xD );
    ejectedFood += "|";
    ejectedFood += QString::number( yD );
    ejectedFood += "|";
    ejectedFood += QString::number(col);
    ejectedFood += "|";
    ejectedFood += getName();
    ejectedFood += "|";

    LoginWindow::getInstance()->sendInfo(ejectedFood);
}
// end ejectFood
