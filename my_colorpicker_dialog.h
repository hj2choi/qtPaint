/****************************************/
//  QT Paint
//  File: my_colorpicker_dialog.h
//  Author: Hong Joon Choi
//  Date: 25.Mar.2015
//  Description: the header file
//  -- MyColorPickerDialog class definition
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
#include <qcolor.h>
#include <qpaintdevice.h>
#include <qimage.h>

#ifndef _MY_COLORPICKER_DIALOG_H
#define _MY_COLORPICKER_DIALOG_H

// MyColorPickerDialog: custormized QDialog 
// The QDialog class provides a dialog window for communications with user

class MyColorPickerDialog: public QDialog {
   // All classes that contain signals or slots
   // must mention Q_OBJECT in their declaration.
   Q_OBJECT

   public:
      /** constructor and destructor */
      MyColorPickerDialog(QWidget* parent = 0, const char* name = 0);
      ~MyColorPickerDialog();
      
      /** retrieve dialog setting*/
      bool selectColorToForeground(){return foregroundColor;}

		/**
      * @brief Selects color of target image at target position. PROTECTION IS NOT APPLIED ON THIS FUNCTION just because it is a bit irritating to do so.
      * @param target: target PIXMAP
      * @param xTarget: target x position to retrieve color
      * @param xTarget: target y position to retrieve color
      * @retval QColor: color obtained from target 2D position
      * @example : bgcolor = selectColorAtTargetPos(image, e->x(), e->y());
      */
      QColor extractColorAtTargetPos(const QPixmap* target, int xTarget, int yTarget);
   /** user defined slots */
   public slots:
      void OnSetColorStorage(int type);

   private:
      // fill color radio buttons group
      QButtonGroup* fillColorBgroup;
      // array of fill color radio buttons
      QRadioButton** rb_fillColors;

      // dialog setting
      bool foregroundColor;
      
};

#endif
