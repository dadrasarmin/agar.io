//
// Created by dadrasarmin on 7/29/17.
//

#ifndef CLIENT_GAME_H
#define CLIENT_GAME_H


#include <QMainWindow>
#include <QGraphicsView>
#include <QtCore>

#include "Map.h"

const int DIFFERENCE_SCENE_VIEW = 50;

// Game class that view
class Game : public QMainWindow
{

Q_OBJECT

public:
    QGraphicsView * graphicsView; // set game window settings

    static Game* getInstance(); // get pointer to object
    ~Game(); // Game destructor

private:

    explicit Game(QWidget *parent = 0); // Game constructor
    static Game* gamePtr; // a pointer to game objects that create
    Map * myMap;
};
// end Game class



#endif //CLIENT_GAME_H
