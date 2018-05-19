//
// Created by dadrasarmin on 7/29/17.
//

#ifndef CLIENT_LOGINWINDOW_H
#define CLIENT_LOGINWINDOW_H


#include <QThread>
#include <QLabel>
#include <QComboBox>
#include <QtWidgets>
#include <QtNetwork>

#include "Game.h"
#include "Map.h"

class LoginWindow:public QWidget
{
Q_OBJECT

public:
    // Prefixing the explicit keyword to the constructor prevents the compiler from using that constructor for implicit conversions
    explicit LoginWindow();

    static LoginWindow * getInstance();

    QString id;
    QLineEdit *idInput;

    QString ip;
    QLineEdit *ipInput;

    QString port;
    QLineEdit *portInput;

    QPushButton *playerButton;
    QPushButton *botButton;
    QPushButton *visitorButton;
    QPushButton *loginButton;


    int defaultMode = 2; // defaultMode is by default in player mode

    void sendInfo( QString );
    void updateMonitor( QString );


private:

    static LoginWindow * loginPtr;
    void start( QString , QString, QString );
    QTcpSocket *userTcpSocket;
    quint16 userPort;

public slots:
    void login();
    void getInfo();

private slots:
    void player();
    void bot();
    void visitor();
};


#endif //CLIENT_LOGINWINDOW_H
