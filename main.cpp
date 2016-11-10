/****************************************/
//  COMP2012 2015S PA2 -- Paint
//  File: main.cpp
//  Description: the main function
/****************************************/

#include <qapplication.h>

#include "my_widget.h"

int main(int argc, char* argv[])
{
   QApplication a( argc, argv );
   QWidget* w = new MyMainWindow();
   a.setMainWidget( w );
   w->show();
   return a.exec();
};
