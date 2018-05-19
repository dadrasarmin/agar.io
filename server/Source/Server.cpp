#include "Header/Server.h"

// constructor block
Server::Server()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));  // set the seed so can use random numbers

    foodInfo();
    virusInfo();

    serverVector = new vector<QTcpServer *>; // a vector that handle server objects
    clientsVector = new vector<QTcpSocket *>; // a vector that handle clients sockets
    newPort = 4445; // type quint16

    serverObject = new QTcpServer; // create an object from QTcpServer

    // The QHostAddress class provides an IP address.
    // listen function tells the server to listen for incoming connections on address address and port port.
    serverObject -> listen( QHostAddress::LocalHost, 4444 );

    // if newConnection called then call createConnection method
    // newConnection(), This signal is emitted every time a new connection is available.
    connect( serverObject, SIGNAL( newConnection() ), this, SLOT( createServer() ) );

} // end constructor

// createServer method, when a new client connected to server this method do required things so
// server listen (and write) to this new user.
void Server::createServer()
{
    // nextPendingConnection function returns the next pending connection as a connected QTcpSocket object.
    QTcpSocket *newUserSocket = serverObject -> nextPendingConnection();

    // QByteArray::number returns a byte array containing the string equivalent of the number n to base 10
    // write() is an overloaded function writes data from a zero-terminated string of 8-bit characters to the device.
    newUserSocket -> write( QByteArray::number( newPort ) );

    QTcpServer *newServer = new QTcpServer; // create an object from QTcpServer class
    // listen function tells the server to listen for incoming connections on address address and port port.
    newServer -> listen( QHostAddress::LocalHost, newPort );
    // push_back function adds a new element at the end of the vector, after its current last element.
    serverVector -> push_back( newServer );

    // when newConnection method called, this signal is emitted every time a new connection is available.
    connect( newServer, SIGNAL ( newConnection() ), this, SLOT( createClient() ) );

    newPort++;
}
// end createServer method

// createClient method
void Server::createClient()
{
    // The QList class is a template class that provides lists.back function is provided for STL
    // (standard template library) compatibility. returns a reference to the last item in the list.
    QTcpSocket *clientSocket = serverVector -> back() -> nextPendingConnection();

    clientsVector -> push_back( clientSocket );

    // readyRead function signifying that data has been received
    connect( clientSocket, SIGNAL( readyRead() ), this, SLOT( sendInfo() ) );
}
// end createClient method

// displayMessage method listen to messages and display them for everyone who listen to this ip and port
void Server::sendInfo()
{
    // QString stores a string of 16-bit QChars, where each QChar corresponds one Unicode 4.0 character.
    QString message;

    int i = 0; // know which user send info

    for( ; i < clientsVector -> size(); i++ )
    {
        // this module find what client send messages to the server
        // bytesAvailable function returns the number of bytes that are available for reading.
        if( clientsVector -> at( i ) -> bytesAvailable() ) // if number of bytes are zero "if" doesn't execute
        {
            // readAll function reads all remaining data from the device, and returns it as a byte array.
            message = clientsVector -> at( i ) -> readAll();
            break; // exit from "for" and print message on screen
        }
    } // end for module

    cout << message.toStdString() << endl;
    /////////// end receive message

    QStringList msg;
    msg = message.split("|");

    for( int m = 0; m < msg.size(); m++)
    {
        if( msg.at(m).toStdString() == "init" )
        {
            QString initMsg = "init|";

            // send virus information
            for( int k = 0; k < 7; k++ )
            {
                initMsg += QString::number(virus[k][0]);
                initMsg += "|";
                initMsg += QString::number(virus[k][1]);
                initMsg += "|";
            }

            // send food information
            for(int k = 0; k < 25; k++)
            {
                initMsg += QString::number(food[k][0]);
                initMsg += "|";
                initMsg += QString::number(food[k][1]);
                initMsg += "|";
                initMsg += QString::number(food[k][2]);
                initMsg += "|";
            }

            // if there is ejected food
            if( !ejectedFoodlist.empty() )
            {
                int cize = ejectedFoodlist.size();

                initMsg += "old|ef|";
                initMsg += QString::number(cize);
                initMsg += "|";

                for( int k = 0; k < ejectedFoodlist.size(); k++)
                {
                    initMsg += QString::number(ejectedFoodlist[k]->getx());
                    initMsg += "|";
                    initMsg += QString::number(ejectedFoodlist[k]->gety());
                    initMsg += "|";
                    initMsg += QString::number(ejectedFoodlist[k]->getc());
                    initMsg += "|";
                }
            } // end previous ejected food on map

            // if there is player
            if( !playerlist.empty() )
            {
                int cize = playerlist.size();

                initMsg += "old|p|";
                initMsg += QString::number(cize);
                initMsg += "|";

                for( int k = 0; k < playerlist.size(); k++)
                {
                    initMsg +=  QString::number(playerlist[k]->getx());
                    initMsg += "|";
                    initMsg +=  QString::number(playerlist[k]->gety());
                    initMsg += "|";
                    initMsg += QString::number(playerlist[k]->getc());
                    initMsg += "|";
                    initMsg += QString::number(playerlist[k]->getr());
                    initMsg += "|";
                    initMsg += QString::number(playerlist[k]->gets());
                    initMsg += "|";
                    initMsg += playerlist[k]->getn();
                    initMsg += "|";
                }
            } // add previous player on map

            // if there is bot
            if( !botlist.empty() )
            {
                int cize = botlist.size();

                initMsg += "old|b|";
                initMsg += QString::number(cize);
                initMsg += "|";

                for( int k = 0; k < botlist.size(); k++)
                {
                    initMsg +=  QString::number(botlist[k]->getx());
                    initMsg += "|";
                    initMsg +=  QString::number(botlist[k]->gety());
                    initMsg += "|";
                    initMsg += QString::number(botlist[k]->getc());
                    initMsg += "|";
                    initMsg += QString::number(botlist[k]->getr());
                    initMsg += "|";
                    initMsg += QString::number(botlist[k]->gets());
                    initMsg += "|";
                    initMsg += botlist[k]->getn();
                    initMsg += "|";
                }
            }

            clientsVector -> at(i) -> write(&initMsg.toStdString()[0]); // send initial info
        } // end init info



        // if new player add to game
        if( msg.at(m).toStdString() == "new" )
        {
            m++;
            // it is player
            if( msg.at(m).toStdString() == "p" )
            {
                QString id = msg.at(++m);
                Player* player = new Player( id );
                playerlist.push_back(player);

                QString addPlayer = "new|p|";
                addPlayer += QString::number( player->getx() );
                addPlayer += "|";
                addPlayer += QString::number( player->gety() );
                addPlayer += "|";
                addPlayer += QString::number( player->getc() );
                addPlayer += "|";
                addPlayer += QString::number( player->getr() );
                addPlayer += "|";
                addPlayer += QString::number( player->gets() );
                addPlayer += "|";
                addPlayer += player->getn();
                addPlayer += "|";

                // send message to every clients
                for( int w = 0; w < clientsVector -> size(); w++ )
                    clientsVector -> at(w) -> write( &addPlayer.toStdString()[0] );
            } // end add new player to map

            // if it is bot
            if( msg.at(m).toStdString() == "b" )
            {
                QString id = msg.at(++m);
                Bot* bot = new Bot( id );
                botlist.push_back(bot);

                QString addBot = "new|b|";
                addBot += QString::number( bot->getx() );
                addBot += "|";
                addBot += QString::number( bot->gety() );
                addBot += "|";
                addBot += QString::number( bot->getc() );
                addBot += "|";
                addBot += QString::number( bot->getr() );
                addBot += "|";
                addBot += QString::number( bot->gets() );
                addBot += "|";
                addBot += bot->getn();
                addBot += "|";

                // send message to every clients
                for( int w = 0; w < clientsVector -> size(); w++ )
                    clientsVector -> at(w) -> write( &addBot.toStdString()[0] );
            } // end add new bot to game

            if( msg.at(m).toStdString() == "ef" )
            {
                QString x = msg.at(++m);
                QString y = msg.at(++m);
                QString c = msg.at(++m);
                QString n = msg.at(++m);

                EjectedFood * eFood = new EjectedFood(x, y, c);
                ejectedFoodlist.push_back(eFood);

                QString addEjectedFood = "new|ef|";
                addEjectedFood += x; // x
                addEjectedFood += "|";
                addEjectedFood += y; // y
                addEjectedFood += "|";
                addEjectedFood += c; // c
                addEjectedFood += "|";
                addEjectedFood +=  n; // player id
                addEjectedFood += "|";

                for(int k = 0; k < playerlist.size(); k++)
                {
                    if( playerlist[k]->getn() == n )
                    {
                        playerlist[k]->sets(QString::number(-12)); // 9 is radius of ejected food
                        playerlist[k]->setr( ( playerlist[k]->gets() / 5 ) + 17 ); // each 5 points lenghten radius

                        break;
                    }
                }


                // send message to every clients
                for( int w = 0; w < clientsVector -> size(); w++ )
                    clientsVector -> at(w) -> write( &addEjectedFood.toStdString()[0] );
            }

        } // end add new player to game

        // update bot information
        if( msg.at(m).toStdString() == "b" )
        {
            m++;
            // move bot
            if( msg.at(m).toStdString() == "m" )
            {
                QString name = msg.at(++m);

                for(int k = 0; k < botlist.size(); k++)
                {

                    if( name == botlist[k]-> getn() )
                    {
                        botlist[k]->setx( msg.at(++m).toDouble() );
                        botlist[k]->sety( msg.at(++m).toDouble() );

                        QString botMove = "b|m|";
                        botMove += botlist[k]->getn();
                        botMove += "|";
                        botMove += QString::number(botlist[k]->getx());
                        botMove += "|";
                        botMove += QString::number(botlist[k]->gety());
                        botMove += "|";

                        // send message to every clients
                        for( int w = 0; w < clientsVector -> size(); w++ )
                            clientsVector -> at(w) -> write( &botMove.toStdString()[0] );

                        break;
                    }
                }
            } // end update move

            // update score and radius
            if( msg.at(m).toStdString() == "eatCell")
            {
                QString name = msg.at(++m);

                for(int k = 0; k < botlist.size(); k++)
                {
                    if( botlist[k]->getn() == name )
                    {

                        botlist[k]->sets(msg.at(++m)); // rise score by radius of that cell
                        botlist[k]->setr( ( botlist[k]->gets() / LENGHTEN_RADIUS_RANGE ) + 17 ); // each 20 points lenghten radius


                        QString eatCell = "b|eatCell|";
                        eatCell += botlist[k]->getn();
                        eatCell += "|";
                        eatCell += QString::number(botlist[k]->gets());
                        eatCell += "|";
                        eatCell += QString::number(botlist[k]->getr());
                        eatCell += "|";

                        // send message to every clients
                        for( int w = 0; w < clientsVector -> size(); w++ )
                            clientsVector -> at(w) -> write( &eatCell.toStdString()[0] );

                        break;
                    }
                }
            } // end eatCell

            // if this is about punish :)
            if( msg.at(m).toStdString() == "punish" )
            {
                QString id = msg.at(++m);

                for( int k = 0; k < botlist.size(); k++)
                {
                    if( botlist[k]->getn() == id)
                    {
                        botlist[k]->sets(QString::number(-14));
                        botlist[k]->setr( ( botlist[k]->gets() / 5 ) + 17 );

                        QString pun = "b|punish|";
                        pun += botlist[k]->getn();
                        pun += "|";

                        // send message to every clients
                        for( int w = 0; w < clientsVector -> size(); w++ )
                            clientsVector -> at(w) -> write( &pun.toStdString()[0] );

                        break;
                    }
                }
            }

            // if this is about player lost
            if( msg.at(m).toStdString() == "lost")
            {
                QString id = msg.at(++m);

                for(int k = 0; k < botlist.size(); k++)
                {
                    if( botlist[k]->getn() == id )
                    {
                        QString lost = "b|lost|";
                        lost += botlist[k]->getn();
                        lost += "|";

                        // send message to every clients
                        for( int w = 0; w < clientsVector -> size(); w++ )
                            clientsVector -> at(w) -> write( &lost.toStdString()[0] );

                        botlist.erase( botlist.begin() + k );

                        break;
                    }
                }
            } // end lost bot

        } // end bot update

        // update player information
        if( msg.at(m).toStdString() == "p" )
        {
            m++;
            // move player
            if( msg.at(m).toStdString() == "m" )
            {
                QString name = msg.at(++m);

                for(int k = 0; k < playerlist.size(); k++)
                {

                    if( name == playerlist[k]-> getn() )
                    {
                        playerlist[k]->setx( msg.at(++m).toDouble() );
                        playerlist[k]->sety( msg.at(++m).toDouble() );

                        QString playerMove = "p|m|";
                        playerMove += playerlist[k]->getn();
                        playerMove += "|";
                        playerMove += QString::number(playerlist[k]->getx());
                        playerMove += "|";
                        playerMove += QString::number(playerlist[k]->gety());
                        playerMove += "|";

                        // send message to every clients
                        for( int w = 0; w < clientsVector -> size(); w++ )
                            clientsVector -> at(w) -> write( &playerMove.toStdString()[0] );

                        break;
                    }
                }
            } // end update move

            // update score and radius
            if( msg.at(m).toStdString() == "eatCell")
            {
                QString name = msg.at(++m);

                for(int k = 0; k < playerlist.size(); k++)
                {
                    if( playerlist[k]->getn() == name )
                    {

                        playerlist[k]->sets(msg.at(++m)); // rise score by radius of that cell
                        playerlist[k]->setr( ( playerlist[k]->gets() / LENGHTEN_RADIUS_RANGE ) + 17 ); // each 5 points lenghten radius


                        QString eatCell = "p|eatCell|";
                        eatCell += playerlist[k]->getn();
                        eatCell += "|";
                        eatCell += QString::number(playerlist[k]->gets());
                        eatCell += "|";
                        eatCell += QString::number(playerlist[k]->getr());
                        eatCell += "|";

                        // send message to every clients
                        for( int w = 0; w < clientsVector -> size(); w++ )
                            clientsVector -> at(w) -> write( &eatCell.toStdString()[0] );

                        break;
                    }
                }
            } // end eatCell

            // if this is about punish :)
            if( msg.at(m).toStdString() == "punish" )
            {
                QString id = msg.at(++m);

                for( int k = 0; k < playerlist.size(); k++)
                {
                    if( playerlist[k]->getn() == id)
                    {
                        playerlist[k]->sets(QString::number(-14));
                        playerlist[k]->setr( ( playerlist[k]->gets() / 5 ) + 17 );

                        QString pun = "p|punish|";
                        pun += playerlist[k]->getn();
                        pun += "|";

                        // send message to every clients
                        for( int w = 0; w < clientsVector -> size(); w++ )
                            clientsVector -> at(w) -> write( &pun.toStdString()[0] );

                        break;
                    }
                }
            }


            // if this is about player lost
            if( msg.at(m).toStdString() == "lost")
            {
                QString id = msg.at(++m);

                for(int k = 0; k < playerlist.size(); k++)
                {
                    if( playerlist[k]->getn() == id )
                    {
                        QString lost = "p|lost|";
                        lost += playerlist[k]->getn();
                        lost += "|";

                        // send message to every clients
                        for( int w = 0; w < clientsVector -> size(); w++ )
                            clientsVector -> at(w) -> write( &lost.toStdString()[0] );

                        playerlist.erase( playerlist.begin() + k );

                        break;
                    }
                }
            } // end lost player

        } // end player update

        // update ejected food info
        if( msg.at(m).toStdString() == "ef")
        {
            QString x = msg.at(++m);
            QString y = msg.at(++m);

            for ( int k = 0; k < ejectedFoodlist.size(); k++ )
            {
                if( ejectedFoodlist[k]->getx() == x.toDouble() && ejectedFoodlist[k]->gety() == y.toDouble() )
                {
                    ejectedFoodlist.erase( ejectedFoodlist.begin() + k );

                    QString removeEF = "ef|";
                    removeEF += x;
                    removeEF += "|";
                    removeEF += y;
                    removeEF += "|";

                    // send message to every clients
                    for( int w = 0; w < clientsVector -> size(); w++ )
                        clientsVector -> at(w) -> write( &removeEF.toStdString()[0] );

                    break;
                }
            }
        }

        // update food info
        if( msg.at(m).toStdString() == "f")
        {
            QString xP = msg.at(++m);
            QString yP = msg.at(++m);

            for( int k = 0; k < 25; k++)
            {
                if( ( food[k][0] == xP.toDouble() ) && ( food[k][1] == yP.toDouble() ) )
                {
                    QString upFood = "f|";
                    upFood += xP;
                    upFood += "|";
                    upFood += yP;
                    upFood += "|";

                    ///// make new position and color

                    // making a random point for initial appearance
                    double xPosition_ = qrand() % (BOARD_WIDTH - QRECT_SCALE * 6);
                    if(xPosition_ < QRECT_SCALE * 6)
                        xPosition_ = QRECT_SCALE * 6;

                    double yPosition_ = qrand() % (BOARD_HEIGHT - QRECT_SCALE * 6);
                    if(yPosition_ < QRECT_SCALE * 6)
                        yPosition_ = QRECT_SCALE * 6;

                    // set color by random
                    int color = qrand() % QColor::colorNames().size();

                    food[k][0] = xPosition_;
                    food[k][1] = yPosition_;
                    food[k][2] = color;

                    ////// add new food information to message

                    upFood += QString::number(food[k][0]);
                    upFood += "|";
                    upFood += QString::number(food[k][1]);
                    upFood += "|";
                    upFood += QString::number(food[k][2]);
                    upFood += "|";

                    // send message to every clients
                    for( int w = 0; w < clientsVector -> size(); w++ )
                        clientsVector -> at(w) -> write( &upFood.toStdString()[0] );

                    break;
                }
            }
        } // end food update

        // if this is a visitor
        if( msg.at(m).toStdString() == "v" )
        {
            // do nothing
        }

    } // end responding to received message

} // end displayMessage method

// make food information
void Server::foodInfo()
{
    for( int n = 0; n < 25; n++)
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

        food[n][0] = xPosition_;
        food[n][1] = yPosition_;
        food[n][2] = color;
    }

}

// make virus information
void Server::virusInfo()
{
    for( int n = 0; n < 7; n++)
    {
        // making a random point for initial appearance
        double xPosition_ = qrand() % (BOARD_WIDTH - QRECT_SCALE * 40);
        if(xPosition_ < QRECT_SCALE * 40)
            xPosition_ = QRECT_SCALE * 40;

        double yPosition_ = qrand() % (BOARD_HEIGHT - QRECT_SCALE * 40);
        if(yPosition_ < QRECT_SCALE * 40)
            yPosition_ = QRECT_SCALE * 40;

        virus[n][0] = xPosition_;
        virus[n][1] = yPosition_;
    }
}
