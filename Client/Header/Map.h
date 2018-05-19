//
// Created by dadrasarmin on 7/29/17.
//

#ifndef CLIENT_MAP_H
#define CLIENT_MAP_H


#include <QGraphicsScene>
#include <QCursor>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QList>
#include <QTimer>
#include <QMessageBox>

#include "CellsFactory.h"

const int VIEW_SCALE = 2; // view scale constant
const int FRAME_MS = 120; // frame millisecond constant

// Class map handle QGraphicsScene items
class Map : public QGraphicsScene
{

public:

    static Map* getInstance(); // get a pointer to object
    ~Map() override ; // Map destructor

    // dynamic functions
    void foodCellIsEaten( QString, QString, QString, QString, QString ); // remove eaten food
    void getNewFood( QString, QString, QString); // adding new food

    void getNewVirus( QString, QString ); // adding new virus

    void getNewBot(QString, QString, QString, QString, QString, QString); // adding new bot
    void moveBot(QString, QString, QString); // move player
    void updateBot( QString, QString, QString ); // update bot info
    void botLost( QString ); // show lost message
    void botPunish( QString ); // punish this bot
    Bot* thisBot();


    void getNewPlayer(QString, QString, QString, QString, QString, QString); // add new player
    void movePlayer( QString, QString, QString); // move player
    void updatePlayer( QString, QString, QString ); // update player info
    void playerLost( QString ); // Show lost message
    void playerEjectFood(QString); // player eject food
    void playerPunish( QString ); // punish this player
    Player* thisPlayer();

    void getNewEjectedFood(QString, QString, QString); // add new ejectedFood
    void removeEjectedFood(QString, QString);



    virtual void advance(); // this function is overloaded from QGraphicsScene for handle animation thing

    QList<Bot*>::iterator getBotItBegin();
    QList<Bot*>::iterator getBotItEnd();

    QString playerName;

    QList<Food*> foodList; // A list of pointers that hold food
    QList<Bot*> botsList; // A list of pointers that hold bot
    QList<Virus*> virusList; // a list of pointers that hold virus
    QList<Player*> playerList; // A list of pointers that hold player
    QList<EjectedFood*> ejectedFoodList; // A list of pointer that hold ejectedFoodList

protected:

    // events function
    void keyPressEvent(QKeyEvent *event) override ;
    void mouseMoveEvent( QGraphicsSceneMouseEvent *event ) override ; // Events function

private:
    Map(); // Map constructor

    // attributes
    static Map* mapPtr; // a pointer to Map's object that creates
    QTimer* timer; // A pointer that hold time

};


#endif //CLIENT_MAP_H
