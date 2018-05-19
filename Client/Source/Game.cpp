//
// Created by dadrasarmin on 7/29/17.
//

#include "Header/Game.h"

Game* Game::gamePtr = nullptr;

// Game constructor
Game::Game( QWidget *parent ) : QMainWindow( parent )
{
    //set window for the view
    graphicsView = new QGraphicsView();

    myMap = Map::getInstance();
    graphicsView->setScene(myMap);

}
// end Game constructor

// destructor delete Game instance
Game::~Game()
{
    delete gamePtr;
}
// end destructor

// getInstance return a pointer to game's object
Game *Game::getInstance()
{
    // if there is no gamePtr creates one
    if ( !gamePtr )
        gamePtr = new Game();

    // return pointer to game's object
    return gamePtr;
}
// end getInstance
