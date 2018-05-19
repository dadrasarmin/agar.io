#ifndef SERVER_PLAYER_H
#define SERVER_PLAYER_H

#include <QtCore>
#include <QColor>

class Player
{

public:

    Player(QString);


    double x;
    double y;
    int c;
    int s = 0;
    int r = 17;
    QString n;

    void setx(double);
    void sety(double);
    void setc(int);
    void sets(QString);
    void setr( int );
    void setn(QString);

    double getx();
    double gety();
    int getc();
    int gets();
    int getr();
    QString getn();

private:
    const int BOARD_WIDTH = 800;
    const int BOARD_HEIGHT = 600;
    const int QRECT_SCALE = 2;



};


#endif //SERVER_PLAYER_H
