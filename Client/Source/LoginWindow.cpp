//
// Created by dadrasarmin on 7/29/17.
//

#include "Header/LoginWindow.h"

#include <iostream>


LoginWindow* LoginWindow::loginPtr = nullptr;

using namespace std;

LoginWindow::LoginWindow()
{
    this -> setWindowTitle("صفحه ورود");

    // label that show "IP address:" text
    QLabel *ip=new QLabel( this ); // create an object from class Qlabel
    ip -> setText( "IP address:" );
    ip -> setGeometry( 5 ,10, 100, 20); // set where it shows
    // end "IP address" label

    // ip address input
    ipInput = new QLineEdit( this );// create an object from class QLineEdit
    ipInput -> setGeometry(5, 30, 200, 20); // a 200*20  window below ip message
    // end ip address input

    // label that show "Your Port:" text
    QLabel *port = new QLabel( this ); // create an object from class QLabel
    port -> setText( "Your Port:" );
    port -> setGeometry(5, 60, 100, 20); // set it below idInput box
    // end "Your Port:" label

    // port input
    portInput = new QLineEdit( this ); // create an object from class QLineEdit
    portInput -> setGeometry(5, 80, 200, 20); // a 200*20 window below port message
    // end port input

    // label that show "Your ID:" text
    QLabel *id = new QLabel( this ); // create an object from class QLabel
    id -> setText( "Your ID:" );
    id -> setGeometry(5, 110, 200, 20); // set it below ipInput box
    // end "Your ID:" label

    // id input
    idInput = new QLineEdit( this ); // create an object from class QLineEdit
    idInput -> setGeometry(5, 130, 200, 20); // a 200*20 window below id message
    // end ip input

    // label that show "Which mode?" text
    QLabel *playMode=new QLabel( this ); // create an object from class Qlabel
    playMode -> setText( "Which mode?" );
    playMode -> setGeometry( 5 ,160, 100, 20); // set where it shows
    // end "Which mode?" label

    // player button
    playerButton = new QPushButton( "Player", this ); // create an object from class QPushButton with player text on it
    playerButton -> setGeometry(5, 190, 200 , 30); // a 200*30 button below the idInput
    // end player button

    // bot button
    botButton = new QPushButton( "bot", this ); // create an object from class QPushButton with bot text on it
    botButton -> setGeometry(5, 230, 200 , 30); // a 200*30 button below the playerButton
    // end bot button

    // visitor button
    visitorButton = new QPushButton( "Visitor", this ); // create an object from class QPushButton with Visitor text on it
    visitorButton -> setGeometry(5, 270, 200 , 30); // a 200*30 button below the botButton
    // end player button

    // enter button
    loginButton = new QPushButton( "Login", this ); // create an object from class QPushButton with Login text on it
    loginButton -> setGeometry(5, 310, 200 , 30); // a 200*30 button below the idInput

    QPalette loginPalette = loginButton -> palette(); // create an object from QPalette class
    loginPalette.setColor( QPalette::Button, QColor( Qt::red ) ); // button background color = red
    loginButton -> setAutoFillBackground( true ); // fill background automatically
    loginButton -> setPalette( loginPalette ); // replace default color by red color
    // end enter button

    this -> show(); // show login window

    connect( loginButton, SIGNAL( clicked() ), this, SLOT( login() ) ); // if loginButton clicked call login method
    connect( playerButton, SIGNAL( clicked() ), this, SLOT( player() ) ); // if player  clicked
    connect ( botButton, SIGNAL( clicked() ), this, SLOT( bot() ) ); // if bot clicked
    connect( visitorButton, SIGNAL( clicked() ), this, SLOT( visitor() ) ); // if visitor clicked

} // end constructor

// login method sets id and ip value to it's parameter and hide login window then
// create an object from Game class and send ip and id to it
void LoginWindow::login()
{
    id = ( idInput -> text() ); // change idInput to string and set value to id
    ip = ( ipInput -> text() ); // change ipInput to QString and set value to ip
    port = ( portInput -> text() ); // change portInput to QString and set value to port

    this -> hide(); // hide login window after loginButton clicked

    this->start( id, ip, port );

} // end login method

// player method make play game status player
void LoginWindow::player()
{
    defaultMode = 1;
    // if this button clicked change it's color and other button color become white
    QPalette modeOnPalette = playerButton -> palette(); // create an object from QPalette class
    modeOnPalette.setColor( QPalette::Button, QColor( Qt::blue ) ); // button background color = blue
    playerButton -> setAutoFillBackground( true ); // fill background automatically
    playerButton -> setPalette( modeOnPalette ); // replace default color by blue color
    playerButton -> update(); // update button settings

    QPalette modeOffPalette = botButton -> palette(); // create an object from QPalette class
    modeOffPalette.setColor( QPalette::Button, QColor( Qt::white ) ); // button background color = white
    botButton -> setAutoFillBackground( true ); // fill background automatically
    botButton -> setPalette( modeOffPalette ); // replace default color by white color
    botButton -> update(); // update button settings

    QPalette modeOffTooPalette = visitorButton -> palette(); // create an object from QPalette class
    modeOffTooPalette.setColor( QPalette::Button, QColor( Qt::white ) ); // button background color = white
    visitorButton -> setAutoFillBackground( true ); // fill background automatically
    visitorButton -> setPalette( modeOffTooPalette ); // replace default color by white color
    visitorButton -> update(); // update button settings
}
// end player method

// bot method make play game status bot
void LoginWindow::bot()
{
    defaultMode = 0;
    // if this button clicked change it's color and other button color become white
    QPalette modeOffPalette = botButton -> palette(); // create an object from QPalette class
    modeOffPalette.setColor( QPalette::Button, QColor( Qt::blue ) ); // button background color = blue
    botButton -> setAutoFillBackground( true ); // fill background automatically
    botButton -> setPalette( modeOffPalette ); // replace default color by blue color
    botButton -> update(); // update button settings

    QPalette modeOnPalette = playerButton -> palette(); // create an object from QPalette class
    modeOnPalette.setColor( QPalette::Button, QColor( Qt::white ) ); // button background color = white
    playerButton -> setAutoFillBackground( true ); // fill background automatically
    playerButton -> setPalette( modeOnPalette ); // replace default color by white color
    playerButton -> update(); // update button settings

    QPalette modeOffTooPalette = visitorButton -> palette(); // create an object from QPalette class
    modeOffTooPalette.setColor( QPalette::Button, QColor( Qt::white ) ); // button background color = white
    visitorButton -> setAutoFillBackground( true ); // fill background automatically
    visitorButton -> setPalette( modeOffTooPalette ); // replace default color by white color
    visitorButton -> update(); // update button settings
}
// end bot method

// visitor method make play game status visitor
void LoginWindow::visitor()
{
    defaultMode = 2;
    // if this button clicked change it's color and other button color become white
    QPalette modeOffPalette = visitorButton -> palette(); // create an object from QPalette class
    modeOffPalette.setColor( QPalette::Button, QColor( Qt::blue ) ); // button background color = blue
    visitorButton -> setAutoFillBackground( true ); // fill background automatically
    visitorButton -> setPalette( modeOffPalette ); // replace default color by blue color
    visitorButton -> update(); // update button settings

    QPalette modeOnPalette = playerButton -> palette(); // create an object from QPalette class
    modeOnPalette.setColor( QPalette::Button, QColor( Qt::white ) ); // button background color = white
    playerButton -> setAutoFillBackground( true ); // fill background automatically
    playerButton -> setPalette( modeOnPalette ); // replace default color by white color
    playerButton -> update(); // update button settings

    QPalette modeOffTooPalette = botButton -> palette(); // create an object from QPalette class
    modeOffTooPalette.setColor( QPalette::Button, QColor( Qt::white ) ); // button background color = white
    botButton -> setAutoFillBackground( true ); // fill background automatically
    botButton -> setPalette( modeOffTooPalette ); // replace default color by white color
    botButton -> update(); // update button settings
}
// end visitor method

// start method takes id and ip, then connected to server with appropriate address then takes new port and
// connect to it.
void LoginWindow::start( QString id, QString ip, QString port )
{
    userTcpSocket = new QTcpSocket; // create and object from QTcpSocket class
    userTcpSocket -> connectToHost( ip, port.toUShort() ); // attempts to make a connection to ipAddress on the given port.
    userTcpSocket -> waitForReadyRead(); // this function blocks until new data is available for reading
    // and the readyRead() signal has been emitted.
    userPort = userTcpSocket -> readAll().toUShort(); // read All function reads all remaining data from the device,
    // and returns it as a byte array. toUshort function returns the string converted to an unsigned short using base 10.
    userTcpSocket -> disconnectFromHost(); // attempts to close the previous socket
    userTcpSocket -> connectToHost( ip, userPort ); // attempts to make a connection to ipAddress on the port
    // that server gives to it.

    ////////////////////////////////////////////////////
    //////////////////////////////////////////////////// SEND THIS PLAYER INFORMATION TO SERVER
    QString myInfo = "init|";

    if( defaultMode == 0) // bot mode
        myInfo += "new|b|"; // add playing mode and name together
    else if( defaultMode == 1) // player mode
        myInfo += "new|p|"; // add playing mode and name together
    else if( defaultMode == 2 ) // visitor mode
        myInfo += "v|";

    myInfo += id;
    myInfo += "|";

    userTcpSocket -> write(&myInfo.toStdString()[0]); // write myMessage on socket

    ////////////////////////////////////////////////////
    //////////////////////////////////////////////////// SET BACKGROUND

    QString windowTitle = "Agar.io\n";
    windowTitle += id;
    Game::getInstance()->graphicsView->setWindowTitle(windowTitle);

    Map::getInstance()->playerName = id;

    if(defaultMode == 1)
    {
        Game::getInstance()->graphicsView -> setMouseTracking( true );
        Game::getInstance()->graphicsView->setFixedSize( 450, 450 );
        Game::getInstance()->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        Game::getInstance()->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    }
        //enable mouse tracking
    else
    {
        Game::getInstance()->graphicsView -> setMouseTracking( false );

        // this is for bot
        if( defaultMode == 0)
        {
            Game::getInstance()->graphicsView->setFixedSize( 450, 450 );
            Game::getInstance()->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            Game::getInstance()->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        }
        // this is for visitor
        if( defaultMode == 2)
        {

            // initialize scene
            Map::getInstance()->setSceneRect( 0, 0, BOARD_WIDTH, BOARD_HEIGHT );

            // Sets the width of the widget to w and the height to h
            Game::getInstance()->graphicsView->setBaseSize( VIEW_SCALE * BOARD_WIDTH + DIFFERENCE_SCENE_VIEW,
                                        VIEW_SCALE * BOARD_HEIGHT + DIFFERENCE_SCENE_VIEW );

            // SceneRect property holds the area of the scene visualized by this view.
            Game::getInstance()->graphicsView->setSceneRect( 0, 0, VIEW_SCALE * BOARD_WIDTH, VIEW_SCALE* BOARD_HEIGHT );

            Game::getInstance()->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
            Game::getInstance()->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        }

    }

    Game::getInstance()->graphicsView->show();

    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////

    // readyRead function, this signal is emitted once every time new data is available for reading from
    // the device's current read channel. It will only be emitted again once new data is available,
    // such as when a new payload of network data has arrived on your network socket,
    // or when a new block of data has been appended to your device.
    connect( userTcpSocket, SIGNAL( readyRead() ), this, SLOT( getInfo() ) ); // if signal emitted call getData function

} // end start method

// get information from server
void LoginWindow::getInfo()
{

    QString message = userTcpSocket -> readAll(); // get message from server

    cout << message.toStdString() << endl;

    QStringList list;
    list = message.split("|");

    for( int q = 0; q < list.size(); q++)
    {
        // if it is initial info
        if( list.at(q).toStdString() == "init" )
        {
            // virus
            for( int k = 0; k < 7; k++)
            {
                QString x = list.at(++q);
                QString y = list.at(++q);

                Map::getInstance()->getNewVirus( x, y ); // add virus to scene
            }

            // foods
            for(int k = 0; k < 25; k++)
            {
                QString x = list.at(++q);
                QString y = list.at(++q);
                QString c = list.at(++q);

                Map::getInstance()->getNewFood( x, y, c); // add food to scene
            }

            if( q + 1 < list.size() )
                q++;

            // add current player to map
            if( list.at(q).toStdString() == "old")
            {
                q++;

                // if previous ejected food is on map
                if( list.at(q).toStdString() == "ef")
                {
                    int iter = list.at(++q).toInt();

                    for( int k = 0; k < iter; k++)
                    {
                        QString x = list.at(++q);
                        QString y = list.at(++q);
                        QString c = list.at(++q);

                        Map::getInstance()->getNewEjectedFood(x, y, c);
                    }

                    if( list.at(q + 1).toStdString() == "old" )
                        q += 2;
                }

                // if previous gamer is player
                if( list.at(q).toStdString() == "p" )
                {
                    int iter = list.at(++q).toInt();

                    for( int k = 0; k < iter ; k++)
                    {
                        QString x = list.at(++q);
                        QString y = list.at(++q);
                        QString c = list.at(++q);
                        QString r = list.at(++q);
                        QString s = list.at(++q);
                        QString n = list.at(++q);

                        Map::getInstance()->getNewPlayer(x, y, c, r, s, n);
                    }

                    if( list.at(q + 1).toStdString() == "old" )
                        q += 2;
                }

                // add current bot to map
                if( list.at(q).toStdString() == "b" )
                {
                    int iter = list.at(++q).toInt();

                    for( int k = 0; k < iter ; k++)
                    {
                        QString x = list.at(++q);
                        QString y = list.at(++q);
                        QString c = list.at(++q);
                        QString r = list.at(++q);
                        QString s = list.at(++q);
                        QString n = list.at(++q);

                        Map::getInstance()->getNewBot(x, y, c, r, s, n);
                    }

                    if( q + 1 < list.size() )
                        q++;
                }
            }// end add current bot to map

        }// end init info

        // it is about food
        if(list.at(q).toStdString() == "f")
        {
            QString pX = list.at(++q);
            QString pY = list.at(++q);
            QString x = list.at(++q);
            QString y = list.at(++q);
            QString c = list.at(++q);

            Map::getInstance()->foodCellIsEaten(pX, pY, x, y, c);

        }

        // it is about adding new player
        if(list.at(q).toStdString() == "new")
        {
            q++;
            // new player
            if( list.at(q).toStdString() == "p" )
            {
                QString x = list.at(++q);
                QString y = list.at(++q);
                QString c = list.at(++q);
                QString r = list.at(++q);
                QString s = list.at(++q);
                QString n = list.at(++q);

                Map::getInstance()->getNewPlayer(x, y, c, r, s, n); // add new player to map
            }
            // new bot
            if( list.at(q).toStdString() == "b" )
            {
                QString x = list.at(++q);
                QString y = list.at(++q);
                QString c = list.at(++q);
                QString r = list.at(++q);
                QString s = list.at(++q);
                QString n = list.at(++q);

                Map::getInstance()->getNewBot(x, y, c, r, s, n); // add new bot to map

            }

            // if ejected food
            if( list.at(q).toStdString() == "ef" )
            {
                QString x = list.at(++q);
                QString y = list.at(++q);
                QString c = list.at(++q);
                QString id = list.at(++q); // which player eject this food

                Map::getInstance()->getNewEjectedFood( x, y, c);
                Map::getInstance()->playerEjectFood(id);
            }
        } // end add new person to map

        // it is about updating player
        if(list.at(q).toStdString() == "p")
        {
            q++;

            // if this is about move
            if(list.at(q).toStdString() == "m")
            {
                QString id = list.at(++q);
                QString x = list.at(++q);
                QString y = list.at(++q);

                Map::getInstance()->movePlayer(id , x, y);

            }
            // if this is about radius and score
            if( list.at(q).toStdString() == "eatCell" )
            {
                QString id = list.at(++q);
                QString s = list.at(++q);
                QString r = list.at(++q);

                Map::getInstance()->updatePlayer(id, s, r);
            }
            // if this is about lost
            if( list.at(q).toStdString() == "lost")
            {
                QString id = list.at(++q);

                Map::getInstance()->playerLost(id);

                if( Map::getInstance()->playerName == id)
                    Game::getInstance()->graphicsView->close();
            }

            // if this is about punish
            if( list.at(q).toStdString() == "punish" )
            {
                QString id = list.at(++q);

                Map::getInstance()->playerPunish(id);

            }

        }

        // it is about updating bot
        if(list.at(q).toStdString() == "b")
        {
            q++;

            // if this is about move
            if(list.at(q).toStdString() == "m")
            {
                QString id = list.at(++q);
                QString x = list.at(++q);
                QString y = list.at(++q);

                Map::getInstance()->moveBot(id , x, y);

            }

            // if this is about radius and score
            if( list.at(q).toStdString() == "eatCell" )
            {
                QString id = list.at(++q);
                QString s = list.at(++q);
                QString r = list.at(++q);

                Map::getInstance()->updateBot(id, s, r);
            }
            // if this is about lost
            if( list.at(q).toStdString() == "lost")
            {
                QString id = list.at(++q);

                Map::getInstance()->botLost(id);

                if( Map::getInstance()->playerName == id)
                    Game::getInstance()->graphicsView->close();
            }

            // if this is about punish
            if( list.at(q).toStdString() == "punish" )
            {
                QString id = list.at(++q);

                Map::getInstance()->botPunish(id);

            }
        }

        if( list.at(q).toStdString() == "ef")
        {
            QString x = list.at(++q);
            QString y = list.at(++q);

            Map::getInstance()->removeEjectedFood(x, y);
        }

    } // end processing information
}
// end getInfo

// send information to server
void LoginWindow::sendInfo(QString message)
{
    userTcpSocket -> write(&message.toStdString()[0]); // write myMessage on socket
}

// getInstance return a pointer to LoginWindow's object
LoginWindow* LoginWindow::getInstance()
{
    // if there is no map, creates one
    if (!loginPtr)
        loginPtr = new LoginWindow();

    return loginPtr;
}
// end getInstance function

// update monitor
void LoginWindow::updateMonitor( QString what )
{
    if( what == "p")
    {
        Game::getInstance()->graphicsView->ensureVisible( Map::getInstance()->thisPlayer(), 350, 350 );
        Game::getInstance()->graphicsView->centerOn( Map::getInstance()->thisPlayer() );
    }
    else if( what == "b" )
    {
        Game::getInstance()->graphicsView->ensureVisible( Map::getInstance()->thisBot(), 350, 350 );
        Game::getInstance()->graphicsView->centerOn( Map::getInstance()->thisBot() );
    }

}
