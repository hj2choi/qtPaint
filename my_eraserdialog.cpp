 
/****************************************/
//  COMP2012 2015S PA2 -- Paint
//  File: my_eraserdialog.cpp
//  Author: Hong Joon CHOI 20161472
//  Description: the source file
//  -- MyEraserDialog class implementation 
//     customizing the QDialog class for the Eraser tool
/****************************************/

#include <iostream>
using namespace std;
#include <string.h>

#include "my_eraserdialog.h"

#include <qpainter.h>
#include <qmessagebox.h>
#include <qimage.h>
#include <qpixmap.h>
#include <qtextedit.h>
#include <qmessagebox.h>
#include <qprinter.h>
#include <qapplication.h>
#include <qaccel.h>
#include <qtextstream.h>
#include <qpainter.h>
#include <qpushbutton.h>

MyEraserDialog::MyEraserDialog(QWidget* parent, const char* name)
:QDialog(parent, name)
{
   // initialize Eraser width and painter
   paint = new QPainter(parent);
   eraserSize=10;

   // Slider for setting the Eraser size
   sizeSlider = new QSlider( QSlider::Horizontal, this, "size slider" );
   sizeSlider->setRange ( 10, 100 );
   sizeSlider->setValue ( eraserSize );
   sizeSlider->setGeometry  ( 80, 10, 190, 20 );

   connect( sizeSlider, SIGNAL(valueChanged(int)),
                 this, SLOT(OnSetEraserSize(int)) );

   sliderLabel = new QLabel( this );
   sliderLabel->setGeometry( 10,10,70,20 );
   sliderLabel->setText( "Size" );

   sizeLabel = new QLabel( this );
   sizeLabel->setGeometry( 280, 10, 20, 20 );
   char sizesldrvalue[1024];
   sprintf( sizesldrvalue,"%d",sizeSlider->value() );
   sizeLabel->setText( sizesldrvalue );

   resize(300,40);
}


MyEraserDialog::~MyEraserDialog()
{
   delete sizeSlider;
   delete sizeLabel;
   delete sliderLabel;

   delete paint;
}


// Erase target Image
void MyEraserDialog::eraseTargetPosition(const QPixmap* target, int xTarget, int yTarget, const QColor& bgColor)
{

   // erase the target image in square area
   paint->begin(target);
   paint->setClipRect ( 0, 0, target->width(), target->height() );  // clipping
   paint->fillRect(xTarget-eraserSize/2, yTarget-eraserSize/2, eraserSize, eraserSize, bgColor);
   paint->end();

}

// Display eraser cursor
void MyEraserDialog::displayEraserCursor(const QPaintDevice* target, const QRect& clip, int xTarget, int yTarget)
{
   paint->begin(target);
   paint->setClipRect ( clip );  // clipping
   paint->drawRect(xTarget-eraserSize/2, yTarget-eraserSize/2, eraserSize, eraserSize);
   paint->end();

}
////////////////////////////////////////////////
// Handle Callback function
////////////////////////////////////////////////
// slot to set the eraser size
void MyEraserDialog::OnSetEraserSize(int s)
{
   char sizesldrvalue[1024];
   sprintf( sizesldrvalue,"%d",s );
   sizeLabel->setText( sizesldrvalue );
   eraserSize=s;
}