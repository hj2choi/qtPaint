/****************************************/
//  COMP2012 2015S PA2 -- Paint
//  File: my_pendialog.h
//  Description: the header file
//  -- MyPenDialog class definition
//     customizing the QDialog class for the Pen tool
/****************************************/

#include <qmainwindow.h>
#include <qmessagebox.h>
#include <qpopupmenu.h>
#include <qapplication.h>
#include <qpushbutton.h>
#include <qpen.h>
#include <qslider.h> 
#include <qdialog.h>
#include <qlabel.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>

#ifndef _MY_PEN_DIALOG_H
#define _MY_PEN_DIALOG_H

// MyPenDialog: custormized QDialog 
// The QDialog class provides a dialog window for communications with user

class MyPenDialog: public QDialog {
   // All classes that contain signals or slots
   // must mention Q_OBJECT in their declaration.
   Q_OBJECT

   public:
      /** constructor and destructor */
      MyPenDialog(QWidget* parent = 0, const char* name = 0);
      ~MyPenDialog();

      /** for storing the pen settings */
      QPen pen;

   /** user defined slots */
   public slots:
      void OnSetPenWidth(int w);
      void OnSetCapStyle(int type);
   
   private:
      // Slider pointer
      QSlider* widthslider;
      // Slider labels
      QLabel* wl;
      QLabel* widthlabel;

      // Style button pointers
      QButtonGroup* capstylebgroup;
      QRadioButton *rb_flatcap;
      QRadioButton *rb_squarecap;
      QRadioButton *rb_roundcap;
      
};

#endif
