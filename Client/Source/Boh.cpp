//
// Created by dadrasarmin on 7/29/17.
//

#include <Header/LoginWindow.h>
#include "Header/Bot.h"

// constructor
Bot::Bot( QString x, QString y, QString c, QString r, QString s, QString n )
{
    //initialize player
    xPosition_ = x.toDouble();
    yPosition_ = y.toDouble();
    radius_ = r.toInt();

    // set color by random
    color_.setNamedColor(QColor::colorNames().at(c.toInt()));

    score_ = s.toInt();
    name_ = n;


    //set position
    setRect(xPosition_ - radius_, yPosition_ - radius_,
            QRECT_SCALE * radius_, QRECT_SCALE * radius_);
    setPos(xPosition_ - radius_, yPosition_ - radius_);
}
// end constructor

// show bot cell
void Bot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(color_); // set color
    painter->drawEllipse(xPosition_ - radius_, yPosition_ - radius_, QRECT_SCALE * radius_, QRECT_SCALE * radius_); // draw ellipse
    painter->setBrush(Qt::black); // set text color
    painter->drawText(xPosition_ - DISPLACEMENT, yPosition_ + DISPLACEMENT, name_ ); // set bot ID
}
// end paint

// remove bot from map
void Bot::isEaten()
{
    QString botLost = "b|lost|";
    botLost += getName();
    botLost += "|";

    LoginWindow::getInstance()->sendInfo( botLost );
}
// end isEaten

// check whether is bigger than other cell or not
bool Bot::isBiggerThanOtherCell(const Cell *otherCell) const
{
    if(radius_ > otherCell->getRadius())
        return true;
    else
        return false;
}
// end isBiggerThanOtherCell

// compute distance with other cell
double Bot::computeDistance(const Cell *otherCell) const
{
    qreal xDis = xPosition_ - otherCell->getXPosition();
    qreal yDis = yPosition_ - otherCell->getYPosition();

    double distance = sqrt(xDis * xDis + yDis * yDis); //sqrt(dx^2 + dy^2)

    return distance;
}
// end computeDistance

// get angle in radians
float Bot::getAngle(const Cell *otherCell) const
{
    // handle vertical and horizontal lines.
    if (xPosition_ == otherCell->getXPosition())
    {
        if (yPosition_ < otherCell->getYPosition())
            return M_PI_2;
        else
            return -M_PI_2;
    }
    return atan2(yPosition_ - otherCell->getYPosition(), xPosition_ - otherCell->getXPosition());
}
// end getAngle

// get angle in radians of vector
float Bot::getAngle(QPointF &vec) const
{
    // handle vertical and horizontal lines.
    if (vec.rx() == 0)
    {
        if (vec.ry() > 0)
            return M_PI_2;
        else
            return -M_PI_2;
    }
    return atan2(vec.ry(), vec.rx());
}
// end getAngle

// return speed of cell
float Bot::speed() const
{
    float speed = ( (SPEED_FACTOR) * radius_ * radius_ ) + ADDITIONAL_SPEED_FACTOR;
    if(speed < MINIMUM_SPEED)
        speed = MINIMUM_SPEED;

    return speed;
}
// end speed

// screen the scene and decide to follow or escape
void Bot::advance(int step)
{
    // In the first phase, item is notified that the scene is about to change,and in the second phase items is notified that they can move.
    //In the first phase, QGraphicsItem::advance() is called passing a value of 0 as an argument, and 1 is passed in the second phase.
    if(!step)
        return;

    for(int i = 0; i < Map::getInstance()->botsList.size(); i++)
    {
        if( Map::getInstance()->botsList[i]->getName() == Map::getInstance()->playerName )
        {
            auto it = Map::getInstance()->getBotItBegin();
            auto itEnd = Map::getInstance()->getBotItEnd();

            QPointF tmpVec;

            targetVector_ = QPointF(0,0);
            targetCell_ = nullptr;

            // check bots
            for(; it != itEnd; ++it) // go through every bot
            {
                if(this == (*it))
                    continue;
                checkIfEscapeOrFollow(*it, 100);
            }

            // check foods
            for( int k = 0; k < 25; k++)
            {
                checkIfEscapeOrFollow(Map::getInstance()->foodList[k], 200);
            }


            //Taking care of edges, bot cannot cross them
            tmpVec = QPointF(1, 0); //left
            addEdgeInfluenceVector(tmpVec, xPosition_);

            tmpVec = QPointF(-1, 0); //right
            addEdgeInfluenceVector(tmpVec, BOARD_WIDTH - xPosition_);

            tmpVec = QPointF(0, -1); //bottom
            addEdgeInfluenceVector(tmpVec, BOARD_HEIGHT - yPosition_);

            tmpVec = QPointF(0, 1); //top
            addEdgeInfluenceVector(tmpVec, yPosition_);

            if(targetCell_) // if there was found Cell to attack
            {
                tmpVec = QPointF(targetCell_->getXPosition() - xPosition_ , targetCell_->getYPosition() - yPosition_);
                float distTarget = computeDistance(targetCell_);

                if (distTarget != 0)
                {
                    tmpVec = tmpVec / distTarget; // normalize vector
                    if(fabs(getAngle(targetCell_) - getAngle(targetVector_)) > M_PI_2) // if the angle to follow Cell is close to escape angle
                        targetVector_ = targetVector_ + tmpVec;
                    else
                        targetVector_ = tmpVec; // attack directly the Cell
                }
            }

            if ( targetVector_.x() != 0 || targetVector_.y() != 0 )
            {
                targetVector_ = targetVector_ / (sqrt( targetVector_.x() * targetVector_.x() + targetVector_.y() * targetVector_.y() ) ); // normalize

                qreal dx = (targetVector_.x() * speed()); // how far move in x direction
                qreal dy = (targetVector_.y() * speed()); // how far move in y direction

                xPosition_ += dx;
                yPosition_ += dy;
            }

            QString botMove = "b|m|";
            botMove += getName();
            botMove += "|";
            botMove += QString::number( xPosition_ );
            botMove += "|";
            botMove += QString::number( yPosition_ );
            botMove += "|";

            LoginWindow::getInstance()->sendInfo(botMove);

            QString  b = "b";
            LoginWindow::getInstance()->updateMonitor( b );

            checkCollision();
            break;
        }
    }

}
// end bot::advance

// decide whether follow a cell or escape from it
void Bot::checkIfEscapeOrFollow(Cell* cell, int viewDis)
{
    double vecLen;
    QPointF tmpVec;

    vecLen = computeDistance(cell); // distance between 2 Cells
    if(vecLen < viewDis && vecLen != 0 ) // if in visual field and not in this same place
    {
        if(!isBiggerThanOtherCell(cell)) // need to escape
        {
            // vector in the opposite direction from the direction where is bigger Cell
            tmpVec = QPointF(xPosition_ - cell->getXPosition(), yPosition_ - cell->getYPosition());

            tmpVec = tmpVec / (vecLen * vecLen); // vector normalize and getting dependence of distance between 2 Cells

            targetVector_ = targetVector_ + tmpVec;
        }
        else if(!targetCell_ || vecLen < computeDistance(targetCell_)) // attack the smaller Cell
            targetCell_ = cell;
    }
}
// end checkIfEscapeOrFollow

// Taking care of map edges, to prevent crossing edge by bot
void Bot::addEdgeInfluenceVector(QPointF& vec, int edgeDistance )
{
    vec = vec / (edgeDistance * edgeDistance); // Getting dependence of distance between bot and edge
    targetVector_ = targetVector_ + vec;
}
// end addEdgeInfluenceVector

// if a cell can be eaten then eat it
void Bot::eatCell(const Cell *toBeEaten)
{
    Cell* cell = const_cast<Cell*>(toBeEaten);

    if(cell->canBeEaten())
    {
        QString what = cell->who();

        if( what != "Virus" )
        {
            cell->isEaten(); // change that cell status to eaten


            QString eatCell = "b|eatCell|";
            eatCell += getName();
            eatCell += "|";
            eatCell += QString::number(cell->getRadius());
            eatCell += "|";

            LoginWindow::getInstance() ->sendInfo(eatCell);
        }
        else if( what == "Virus" )
        {
            QString punish = "b|punish|";
            punish += getName();
            punish += "|";

            LoginWindow::getInstance()->sendInfo(punish);
        }

    }
}
// end eatCell

// tell what is this cell
QString Bot::who()
{
    QString B = "Bot";
    return B;
}

// return player name
QString Bot::getName()
{
    return name_;
}

// update x position
void Bot::setx(QString nx)
{
    xPosition_ = nx.toDouble();
}

// update y position
void Bot::sety(QString ny)
{
    yPosition_ = ny.toDouble();
}
