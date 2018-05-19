//
// Created by dadrasarmin on 7/29/17.
//

#include "Header/CellsFactory.h"


CellsFactory* CellsFactory::cellsFactoryPtr = nullptr;

// return a pointer to class's object and if it is not created, make one and then return a pointer to it
CellsFactory* CellsFactory::getInstance()
{
    if (!cellsFactoryPtr)
        cellsFactoryPtr = new CellsFactory();

    return cellsFactoryPtr;
}
// end getInstance

// destructor
CellsFactory::~CellsFactory()
{
    delete cellsFactoryPtr; // delete pointer
}
// end destructor

// call Food constructor
Food *CellsFactory::createFood(QString x, QString y, QString c)
{
    return new Food(x, y, c);
}
// end createFood

// call Bot constructor via wanted radius
Bot *CellsFactory::createBot( QString x , QString y , QString c , QString r , QString s , QString n )
{
    return new Bot( x , y, c, r, s, n );
}
// end createBot

// call player constructor via wanted info
Player *CellsFactory::createPlayer(QString x , QString y , QString c , QString r , QString s , QString n)
{
    return new Player(x , y, c, r, s, n);
}

// call EjectedFood constructor via wanted info
EjectedFood *CellsFactory::createEjectedFood(QString xP, QString yP,QString cP)
{
    return new EjectedFood(xP, yP, cP);
}

// call virus constructor via wanted info
Virus *CellsFactory::createVirus(QString x , QString y)
{
    return new Virus(x, y);
}
