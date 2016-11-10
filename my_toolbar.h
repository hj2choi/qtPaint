/****************************************/
//  COMP2012 2015S PA2 -- Paint
//  File: my_toolbar.h
//  Description: the header file
//  -- MyToolBar class definition
//     customizing QToolBar class to add the OnPaint() signal
//     and overriding the paintEvent() handler
/****************************************/

#ifndef MY_TOOL_BAR_H
#define MY_TOOL_BAR_H

#include <qtoolbar.h>

class MyToolBar: public QToolBar {
   // All classes that contain signals or slots
   // must mention Q_OBJECT in their declaration.
   Q_OBJECT

   public:
      MyToolBar(QMainWindow* parent = 0, const char* name = 0);
      ~MyToolBar();

   signals:
      void OnPaint();

   protected:
      virtual void paintEvent(QPaintEvent* event);
};

#endif
