#include "Header/Bot.h"

Bot::Bot(QString n)
{
    // making a random point for initial appearance
    double xPosition_ = qrand() % (BOARD_WIDTH - QRECT_SCALE * 6);
    if(xPosition_ < QRECT_SCALE * 6)
        xPosition_ = QRECT_SCALE * 6;

    double yPosition_ = qrand() % (BOARD_HEIGHT - QRECT_SCALE * 6);
    if(yPosition_ < QRECT_SCALE * 6)
        yPosition_ = QRECT_SCALE * 6;

    // set color by random
    int color = qrand() % QColor::colorNames().size();

    setx(xPosition_);
    sety(yPosition_);
    setc(color);
    setn(n);
}

void Bot::sety(double ny)
{
    y = ny;
}

void Bot::setx(double nx)
{
    x = nx;
}

void Bot::setc(int nc)
{
    c = nc;
}

void Bot::sets(QString ns)
{
    s += ns.toInt();
}

void Bot::setr( int  nr)
{
    r = nr;
}

void Bot::setn(QString nn)
{
    n = nn;
}

double Bot::getx()
{
    return x;
}

double Bot::gety()
{
    return y;
}

int Bot::getc()
{
    return  c;
}

int  Bot::gets()
{
    return s;
}

int Bot::getr()
{
    return r;
}

QString Bot::getn()
{
    return n;
}
