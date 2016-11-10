 /****************************************/
//  COMP2012 2015S PA2 -- Paint
//  File: my_linedialog.h
//  Author: Hong Joon CHOI
//  Description: the header file
//  -- MyLineDialog class definition
//     customizing the QDialog class for the Line tool
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

#ifndef _MY_LINE_DIALOG_H
#define _MY_LINE_DIALOG_H

// MyLineDialog: custormized QDialog 
// The QDialog class provides a dialog window for communications with user

class MyLineDialog: public QDialog {
   // All classes that contain signals or slots
   // must mention Q_OBJECT in their declaration.
   Q_OBJECT

   public:
      /** constructor and destructor */
      MyLineDialog(QWidget* parent = 0, const char* name = 0);
      ~MyLineDialog();

      /** for storing the pen settings */
      QPen pen;
      

      /**
      * @brief Set or initiate reference position for drawing line. If line type is set to poly, this function will not behave.
      * @param x: reference position x
      * @param y: reference position y
      * @retval none
      * @example : setReferencePosition(mouseEvent->x(),mouseEvent->y()); 
      */
      void setReferencePosition(int x, int y);


      /**
      * @brief Draw line from reference to target position, onto target paintDevice.
      * @param target: target PaintDevice for line to be drawn onto
      * @param clip: rectangle area where the line is allowed to be drawn
      * @param xTarget: target position x
      * @param yTarget: target position y
      * @param onDrawImage: when it is set to true, reference position will be updated.
      * @param xDisplacement: x position of target PaintDevice
      * @param yDisplacement: y position of target PaintDevice
      * @retval none
      * @example : drawLineWithSettings(myWidget, clip, e->x(), e->y()); OR drawLineWithSettings(image, clip, e->x(), e->y(), true, xPos, yPos);
      */
      void drawLineWithSettings(const QPaintDevice* target, const QRect& clip, int xTarget, int yTarget, bool onDrawImage=false, int xDisplacement=0, int yDisplacement=0);


   /** user defined slots */
   public slots:
      void OnSetPenWidth(int w);
      void OnSetCapStyle(int type);
      void OnSetLineStyle(int type);
      void OnSetLineType(int type);

   private:
      // Slider pointer
      QSlider* widthslider;
      // Slider labels
      QLabel* wl;
      QLabel* widthlabel;

      // cap style button pointers
      QButtonGroup* capstylebgroup;
      QRadioButton *rb_flatcap;
      QRadioButton *rb_squarecap;
      QRadioButton *rb_roundcap;

      // line style button pointers
      QButtonGroup* linestylebgroup;
      QRadioButton** rb_styles;

      // line type button pointers
      QButtonGroup* linetypebgroup;
      QRadioButton *rb_singletype;
      QRadioButton *rb_polytype;
      
      // Painter for drawing lines.
      QPainter* paint;
      
      // sotre line type setting
      bool polyType;
      // px and py stores the reference vector for drawing line
      int px;
      int py;
};

#endif
