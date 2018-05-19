//
// Created by dadrasarmin on 7/29/17.
//

#ifndef SERVER_EJECTEDFOOD_H
#define SERVER_EJECTEDFOOD_H


#include <QtCore/QString>

class EjectedFood
{
public:
    EjectedFood( QString, QString, QString);

    double x;
    double y;
    int c;

    double getx();
    double gety();
    int getc();

};


#endif //SERVER_EJECTEDFOOD_H
