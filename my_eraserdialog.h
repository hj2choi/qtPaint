/****************************************/
//  COMP2012 2015S PA2 -- Paint
//  File: my_eraserdialog.h
//  Author: HongJoon CHOI 20161472
//  Description: the header file
//  -- MyEraserDialog class definition
//     customizing the QDialog class for the Eraser tool
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

#ifndef _MY_ERASER_DIALOG_H
#define _MY_ERASER_DIALOG_H

// MyEraserDialog: Customized for QDialog
// The QDialog class provides a dialog window for communications with user

class MyEraserDialog : public QDialog
{
   Q_OBJECT

   public:
      /** constructor and destructor */
      MyEraserDialog(QWidget* parent = 0, const char* name = 0);
      ~MyEraserDialog();

      /**
      * @brief Erase target image at target location, according to dialog settings.
      * @param target: target image
      * @param xTarget: x position to erase
      * @param yTarget: y position to erase
      * @param bgColor: background color for eraser to work with
      * @retval none
      */
      void eraseTargetPosition(const QPixmap* target, int xTarget, int yTarget, const QColor& bgColor);

      /**
      * @brief Displays cursor of eraser. Should be used along with eraseTargetPosition()
      * @param target: target QPaintDevice
      * @param clip: rectangle area where cursor can be drawn onto
      * @param xTarget: x position to display cursor
      * @param yTarget: y position to display cursor
      * @retval none
      */
      void displayEraserCursor(const QPaintDevice* target, const QRect& clip, int xTarget, int yTarget);

   /** user defined slots */
   public slots:
      void OnSetEraserSize(int s);

   private:
      //Slider pointer
      QSlider* sizeSlider;
      //Slider labels
      QLabel* sliderLabel;
      QLabel* sizeLabel;
      
      QPainter* paint;
      int eraserSize;
};

#endif