 /****************************************/
//  COMP2012 2015S PA2 -- Paint
//  File: my_rectdialog.h
//  Author: Hong Joon Choi
//  Description: the header file
//  -- MyRectDialog class definition
//     customizing the QDialog class for the Rectangle tool
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

#ifndef _MY_RECT_DIALOG_H
#define _MY_RECT_DIALOG_H

// MyLineDialog: custormized QDialog 
// The QDialog class provides a dialog window for communications with user

class MyRectDialog: public QDialog {
   // All classes that contain signals or slots
   // must mention Q_OBJECT in their declaration.
   Q_OBJECT

   public:
      /** constructor and destructor */
      MyRectDialog(QWidget* parent = 0, const char* name = 0);
      ~MyRectDialog();

      /** for storing the color, pen and brush settings */
      QColor bgColor;	// stores bgColor.
      QColor fgColor;	// stores fgColor.
      QPen pen;			// stores pen settings
      QBrush brush;		// stores brush settings
      

		/**
      * @brief Sets color of the shape to be drawn, according to fill color settings. Simply setting fg or bg color DO NOT affect the shape color
      * @param none
      * @retval none
      * @example : bgColor=windowColor; setColor();
      */
      void setColor();

		/**
      * @brief Draws shape onto the target PaintDevice according to the dialog settings.
      * @param target: target paintDevice
      * @param clip: Rectangle area of where the drawing is allowed.
		* @param shape: Sets position and size of the shape in rectangle format.
      * @retval none
      * @example : drawShapeWithSettings(image, clip, rectangle); 
      */
      void drawShapeWithSettings(const QPaintDevice* target, const QRect& clip, const QRect& shape);

   /** user defined slots */
   public slots:
      void OnSetBoundaryWidth(int w);
      void OnSetDrawType(int type);
      void OnSetBoundaryStyle(int type);
      void OnSetFillStyle(int type);
      void OnSetFillColor(int type);
      void OnSetBounaryJoinStyle(int type);

   private:
      // Slider pointer
      QSlider* boundaryWidthSlider;
      // Slider labels
      QLabel* sliderLabel;
      QLabel* boundaryWidthLabel;

      // draw type radio buttons group
      QButtonGroup* drawTypeBgroup;
      // array of draw type radio buttons
      QRadioButton** rb_drawTypes;

      // fill style radio buttons group
      QButtonGroup* fillStyleBgroup;
      // array of fill style radio buttons
      QRadioButton** rb_fillStyles;

      // boundary style radio buttons group
      QButtonGroup* boundaryStyleBgroup;
      // array of boundary style radio buttons
      QRadioButton** rb_boundaryStyles;
		
      // fill color radio buttons group
      QButtonGroup* fillColorBgroup;
      // array of fill color radio buttons
      QRadioButton** rb_fillColors;

      // boundary join style radio buttons group
      QButtonGroup* boundaryJoinStyleBGroup;
      // array of boundary join style radio buttons
      QRadioButton** rb_boundaryJoinStyles;

      // painter for drawing rectangles
      QPainter* paint;

      // dialog settings
      bool foregroundColor;
      int drawType;
};

#endif
