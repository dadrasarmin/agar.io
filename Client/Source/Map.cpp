//
// Created by dadrasarmin on 7/29/17.
//

#include <Header/LoginWindow.h>
#include "Header/Map.h"

#include "iostream"
using namespace std;

Map* Map::mapPtr = nullptr;

// Map Constructor
Map::Map()
{

    // initialize timer
    timer = new QTimer(); // create an object from QTimer class
    connect( timer, SIGNAL( timeout() ), this, SLOT( advance() ) ); // connect timeout() to advance()
    timer -> start( FRAME_MS ); // emit the timeout() signal at FRAME_MS constant

    // This enum type defines the brush styles supported by Qt, i.e. the fill pattern of shapes drawn using
    setBackgroundBrush( Qt::Dense7Pattern );

}
// end constructor

// Map destructor
Map::~Map()
{
    delete timer; // delete timer pointer
    delete mapPtr; // delete mapPtr pointer
}
// end destructor

// getInstance return a pointer to Map's object
Map* Map::getInstance()
{
    // if there is no map, creates one
    if (!mapPtr)
        mapPtr = new Map();

    return mapPtr;
}
// end getInstance function

// overloading advance function of QGraphicsScene for handle animation
void Map::advance()
{
    for( int k = 0; k < botsList.size(); k++)
        botsList[k]->checkCollision();

    for( int k = 0; k < playerList.size(); k++)
        playerList[k]->checkCollision();

    getInstance()->update(); // update scene after timeout signal emits
}
// end advance function

// process keyEvent
void Map::keyPressEvent(QKeyEvent *event)
{
    int k = 0;
    for( ; k < playerList.size(); k++)
    {
        if( playerList[k]->getName() == playerName )
        {
            switch(event->key())
            {
                // if it is about food ejecting
                case Qt::Key_F:
                    playerList[k]->ejectFood();
                    break;
                // if it is about cell budding
                case Qt::Key_B:
                    cout << ":)" << endl;
                    break;

                default:
                    break;
            }

            break;
        }
    }
}
// end keyEvent

// mouseMoveEvent handle mouse movement event
void Map::mouseMoveEvent( QGraphicsSceneMouseEvent *event )
{
    if( !playerList.empty() )
    {
        for(int i = 0; i < playerList.size(); i++)
        {
            if( playerList[i]->getName() == playerName )
            {
                playerList[i]->mouseMove( event -> scenePos().x() / VIEW_SCALE,
                                          event -> scenePos().y() / VIEW_SCALE ); // take mouse x and y position

                break;
            }
        }
    }
}
// end mouseMoveEvent

// update bot position
void Map::moveBot(QString id , QString x , QString y)
{
    for(int i = 0; i < botsList.size(); i++)
    {
        if( botsList[i]->getName() == id )
        {
            botsList[i]->setx(x);
            botsList[i]->sety(y);

            botsList[i]->setPos( botsList[i]->getXPosition(), botsList[i]->getYPosition());
            break;
        }
    }
}

// update player position
void Map::movePlayer(QString id , QString x , QString y)
{
    for(int i = 0; i < playerList.size(); i++)
    {
        if( playerList[i]->getName() == id )
        {
            playerList[i]->setx(x);
            playerList[i]->sety(y);

            playerList[i]->setPos( playerList[i]->getXPosition(), playerList[i]->getYPosition());

            break;
        }
    }
}

// update player radius and score
void Map::updatePlayer(QString id , QString s , QString r)
{
    for(int i = 0; i < playerList.size(); i++)
    {
        if( playerList[i]->getName() == id )
        {
            playerList[i]->score_ = s.toInt();
            playerList[i]->radius_ = r.toInt();

            break;
        }
    }
}

// update player that eject food
void Map::playerEjectFood(QString id)
{
    for(int i = 0; i < playerList.size(); i++)
    {
        if( playerList[i]->getName() == id )
        {
            playerList[i]->score_ -= 12; // 9 is radius of ejected food
            playerList[i]->radius_ =( ( playerList[i]->score_ / 5 ) + 17 ); // each 5 points lenghten radius

            break;
        }
    }
}

// remove eaten ejected food
void Map::removeEjectedFood(QString x , QString y)
{
    for( int k = 0; k < ejectedFoodList.size(); k++ )
    {
        if( ejectedFoodList[k]->getYPosition() == y.toDouble() && ejectedFoodList[k]->getXPosition() == x.toDouble())
        {
            removeItem(ejectedFoodList[k]);
            ejectedFoodList.removeOne(ejectedFoodList[k]);
        }
    }
}

// update bot radius and score
void Map::updateBot(QString id , QString s , QString r)
{
    for(int i = 0; i < botsList.size(); i++)
    {
        if( botsList[i]->getName() == id )
        {
            botsList[i]->score_ = s.toInt();
            botsList[i]->radius_ = r.toInt();

            break;
        }
    }
}

// playerLost show "You lost" text
void Map::playerLost( QString id )
{
    if( playerName == id )
    {
        for(int i = 0; i < playerList.size(); i++)
        {
            if( playerList[i]->getName() == id )
            {
                QMessageBox messageBox; // create a messageBox
                messageBox.setText( "You lost!" ); // assign "You lost" text to it
                messageBox.exec(); // show messageBox

                removeItem(playerList[i]);
                playerList.erase( playerList.begin() + i );

                break;
            }
        }
    }
    else
    {
        for(int i = 0; i < playerList.size(); i++)
        {
            if( playerList[i]->getName() == id )
            {
                removeItem(playerList[i]);
                playerList.erase( playerList.begin() + i );

                break;
            }
        }
    }
}
// end playerLost function

// botLost show "You lost" text
void Map::botLost( QString id )
{
    if( playerName == id )
    {
        for(int i = 0; i < botsList.size(); i++)
        {
            if( botsList[i]->getName() == id )
            {
                QMessageBox messageBox; // create a messageBox
                messageBox.setText( "You lost!" ); // assign "You lost" text to it
                messageBox.exec(); // show messageBox

                removeItem(botsList[i]);
                botsList.removeOne(botsList[i]);

                break;
            }
        }
    }
    else
    {
        for(int i = 0; i < botsList.size(); i++)
        {
            if( botsList[i]->getName() == id )
            {
                removeItem(botsList[i]);
                botsList.removeOne(botsList[i]);

                break;
            }
        }
    }
}
// end playerLost function

// getNewFood add more food to map
void Map::getNewFood( QString x, QString y, QString c )
{
    Food* food = CellsFactory::getInstance() -> createFood( x, y, c); // creates an object from food class
    addItem( food ); // add food item to scene
    foodList.append( food ); // add food item to foodList
}
// end getNewFood

// add new virus to scene
void Map::getNewVirus( QString x, QString y)
{
    Virus* virus = CellsFactory::getInstance() -> createVirus( x, y); // creates an object from virus class
    addItem( virus ); // add virus item to scene
    virusList.append( virus ); // add virus item to foodList
}

// if food is eat remove it and add new food
void Map::foodCellIsEaten(QString xp, QString yp, QString x, QString y, QString c)
{
    for( int i = 0; i < foodList.size(); i++)
    {
        if( foodList[i]->getXPosition() == xp.toDouble() && foodList[i]->getYPosition() == yp.toDouble() )
        {
            removeItem(foodList[i]);
            foodList.removeOne(foodList[i]);
            getNewFood( x, y, c);

            break;
        }
    }
}
// end foodCellIsEaten

// add new bot mode Player to map
void Map::getNewBot( QString x, QString y, QString c , QString r, QString s, QString id )
{
    Bot* bot = CellsFactory::getInstance()->createBot( x, y, c, r, s, id ); // creates an object from bot class
    addItem(bot); // add bot item to scene
    botsList.append(bot); // add bot item to botList
}
// end getNewBot

// add new player
void Map::getNewPlayer(QString x, QString y, QString c , QString r, QString s, QString id)
{
    Player* player = CellsFactory::getInstance()->createPlayer( x, y, c, r, s, id ); // creates an object from player class
    addItem(player); // add player item to scene
    playerList.append(player); // add player item to playerList
}

// add new EjectedFood to map
void Map::getNewEjectedFood(QString x, QString y, QString cP)
{
    EjectedFood* efood = CellsFactory::getInstance()->createEjectedFood(x, y, cP);
    addItem(efood);
    ejectedFoodList.append(efood);
}
// end getNewEjectedFood

// return first bot in botList
QList<Bot*>::iterator Map::getBotItBegin()
{
    return botsList.begin();
}
// end getBotItBegin

// return last bot in botList
QList<Bot*>::iterator Map::getBotItEnd()
{
    return botsList.end();
}
// end getBotItEnd

// return this player :)
Player* Map::thisPlayer()
{
    for( int k = 0; k < playerList.size(); k++ )
    {
        if( playerList[k]->getName() == playerName )
            return playerList[k];
    }
}

// return this Bot :)
Bot* Map::thisBot()
{
    for(int k = 0; k < botsList.size();k++)
    {
        if(botsList[k]->getName() == playerName )
            return botsList[k];
    }
}

// punish bot
void Map::botPunish(QString id)
{
    for(int k = 0; k < botsList.size(); k++)
    {
        if( botsList[k]->getName() == id )
        {
            botsList[k]->score_ -= 14; // 9 is radius of ejected food
            botsList[k]->radius_ =( ( botsList[k]->score_ / 5 ) + 17 ); // each 5 points lenghten radius

            break;
        }
    }
}

// punish player
void Map::playerPunish(QString n)
{
    for(int k = 0; k < playerList.size(); k++)
    {
        if( playerList[k]->getName() == n )
        {
            playerList[k]->score_ -= 14; // 14 is punish
            playerList[k]->radius_ =( ( playerList[k]->score_ / 5 ) + 17 ); // each 5 points lenghten radius

            break;
        }
    }
}
