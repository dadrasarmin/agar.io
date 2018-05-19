//
// Created by dadrasarmin on 7/29/17.
//

#include "Header/EjectedFood.h"

EjectedFood::EjectedFood(QString xV , QString yV , QString cV) :
x(xV.toDouble()), y(yV.toDouble()), c( cV.toInt() )
{
    // do nothing
}

double EjectedFood::getx()
{
    return x;
}

double EjectedFood::gety()
{
    return y;
}

int EjectedFood::getc()
{
    return c;
}
