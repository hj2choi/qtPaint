/****************************************/
//  COMP2012 2015S PA2 -- Paint
//  File: my_toolbar.cpp
//  Description: the source file
//  -- MyToolBar class implementation 
/****************************************/

#include "my_toolbar.h"
#include <qmainwindow.h>

MyToolBar::MyToolBar(QMainWindow* parent, const char* name)
   : QToolBar(parent, name)
{
   // nothing else to do
}
      
MyToolBar::~MyToolBar()
{
   // nothing else to do
}

void MyToolBar::paintEvent(QPaintEvent* event)
{
   QToolBar::paintEvent( event );

   emit OnPaint();
}
