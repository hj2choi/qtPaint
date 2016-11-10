/****************************************/
//  QT Paint
//  File: my_filldialog.h
//  Author: Hong Joon Choi
//  Date: 25.Mar.2015
//  Description: the header file
//  -- MyFillDialog class definition
//     implemented QDialog class to implement fill will color functionality.
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

#ifndef _MY_FILL_DIALOG_H
#define _MY_FILL_DIALOG_H

// MyFillDialog: custormized QDialog 
// The QDialog class provides a dialog window for communications with user

class MyFillDialog: public QDialog {
   // All classes that contain signals or slots
   // must mention Q_OBJECT in their declaration.
   Q_OBJECT

   public:
      /** constructor and destructor */
      MyFillDialog(QWidget* parent = 0, const char* name = 0);
      ~MyFillDialog();

      /** for storing the color, pen and brush settings */
      QColor bgColor;	// stores bgColor.
      QColor fgColor;	// stores fgColor.
      QPen pen;			// stores pen settings for fill color

		/**
      * @brief Sets color, according to fill color settings. Simply setting fg or bg color DO NOT affect the fill color
      * @param none
      * @retval none
      * @example : bgColor=windowColor; setColor();
      */
      void setColor();

		/**
      * @brief Fills shape with dialog color settings onto the target Pixmap. It reucrively fills colors until boundary is detected. Boundary is defined by any nearby pixel with different color value AND pixel that is out of image.
      * @param target: target PIXMAP
      * @param clip: Rectangle area of where the drawing is allowed.
		* @param shape: Sets position and size of the shape in rectangle format.
      * @param xTarget: target x position to start filling
      * @param xTarget: target y position to start filling
      * @retval none
      * @example : fillEntireAreaWithSettings(image, clip, e->x(), e->y()); 
      */
      void fillEntireAreaWithSettings(const QPixmap* target, const QRect& clip, int xTarget, int yTarget);


   /** user defined slots */
   public slots:
      void OnSetFillColor(int type);

   private:
      
      // recursive function for filling shape with color
      void fillColor(int x, int y, int terminateCounter = 150000);

      // fill color radio buttons group
      QButtonGroup* fillColorBgroup;
      // array of fill color radio buttons
      QRadioButton** rb_fillColors;

      // painter for fillling with color
      QPainter* paint;
      QImage targetImage;
      QColor referenceColor;
      bool** filledImg;

      // dialog settings
      bool foregroundColor;
};

#endif
