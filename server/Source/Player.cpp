#include "Header/Player.h"

Player::Player( QString n )
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

void Player::sety(double ny)
{
    y = ny;
}

void Player::setx(double nx)
{
    x = nx;
}

void Player::setc(int nc)
{
    c = nc;
}

void Player::sets(QString ns)
{
    s += ns.toInt();
}

void Player::setr( int  nr)
{
    r = nr;
}

void Player::setn(QString nn)
{
    n = nn;
}

double Player::getx()
{
    return x;
}

double Player::gety()
{
    return y;
}

int Player::getc()
{
    return  c;
}

int  Player::gets()
{
    return s;
}

int Player::getr()
{
    return r;
}

QString Player::getn()
{
    return n;
}
