
// program use QApplication for gui
#include <QApplication>
#include <QTimer>
#include "Header/LoginWindow.h"


// function main begins program execution
int main( int argc, char **argv )
{
    // The QApplication class manages the GUI application's control flow and main settings.
    QApplication app(argc,argv);

     LoginWindow::getInstance(); // Create an object from login class

    return app.exec();
} // end main function
