//
// Created by dadrasamrin on 7/29/17.
//

#ifndef CLIENT_CELLSFACTORY_H
#define CLIENT_CELLSFACTORY_H


#include "Food.h"
#include "Bot.h"
#include "Player.h"
#include "EjectedFood.h"
#include "Virus.h"

// Class that represents factory, which creates Food and Bot cells
class CellsFactory
{

public:

    static CellsFactory* getInstance(); // return a pointer to CellsFactory object
    ~CellsFactory(); // delete Instance

    Food* createFood(QString, QString, QString); // create new food cell
    Bot* createBot( QString, QString, QString, QString, QString, QString ); // create new bot cell
    Player* createPlayer( QString, QString, QString, QString, QString, QString ); // create new player cell
    EjectedFood* createEjectedFood( QString , QString , QString ); // create new ejectedfood cell
    Virus* createVirus(QString, QString); // create new virus cell

private:

    static CellsFactory* cellsFactoryPtr; // pointer to CellsFactory object
};


#endif //CLIENT_CELLSFACTORY_H
