/****************************************/
//  QT Paint
//  File: my_filldialog.cpp
//  Author: Hong Joon CHOI
//  Date: 25.Mar.2015
//  Description: the source file
//  -- MyFillDialog class implementation 
//     Implementation for fill color functionality
/****************************************/

#include <iostream>
using namespace std;
#include <string.h>

#include "my_filldialog.h"

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
#include <qradiobutton.h>
#include <qbuttongroup.h>

MyFillDialog::MyFillDialog(QWidget* parent, const char* name)
:QDialog(parent, name)
{
   // Initialize Pen, brush and paint and initialize default settings
   paint = new QPainter(parent);
   bgColor = QColor( 255, 255, 255 );
   pen.setStyle(Qt::SolidLine);
   pen.setColor(QColor( 0, 0, 0 ));
   foregroundColor = true;
   filledImg = new bool*[5000];
   for (int i=0; i<5000; i++)
      filledImg[i] = new bool[5000];


   // Radio button group for fillColor
   fillColorBgroup = new QButtonGroup( this );
   fillColorBgroup->setGeometry( 10, 10, 130, 125 );
   fillColorBgroup->setTitle ( "Fill Color" );
   connect( fillColorBgroup, SIGNAL(clicked(int)), this, SLOT(OnSetFillColor(int)) );
      
   // Radio buttons for fillColor
   rb_fillColors = new QRadioButton*[2];
   const char* fillColorNames[] = {"Foreground", "Background"};
   for (int i=0; i<2; i++)
   {
      rb_fillColors[i] = new QRadioButton(fillColorNames[i], fillColorBgroup);
      rb_fillColors[i]->setGeometry(10, 15+50*i, 95, 40);
   }
   rb_fillColors[0]->setChecked(TRUE);	// DEFAULT SETTING

   resize(150,150);
}

MyFillDialog::~MyFillDialog()
{
   
   delete fillColorBgroup;
   delete[] rb_fillColors;

   delete paint;
   for (int i=0; i<10000; i++)
      delete[] filledImg[i];
   delete[] filledImg;
}

// set actual color accroding to dialog settings
void MyFillDialog::setColor()
{
   foregroundColor?(pen.setColor(fgColor)):(pen.setColor(bgColor));
}

// fill shape with dialog settings
void MyFillDialog::fillEntireAreaWithSettings(const QPixmap* target, const QRect& clip, int xTarget, int yTarget)
{
   if (xTarget<0 || yTarget<0 || xTarget>=target->width() || yTarget>=target->height())
   {
      cout << "INVALID fill target location" << endl;
      return;
   }
   for (int i=0; i<target->height(); i++)
      for (int j=0; j<target->width(); j++)
         filledImg[i][j] = false;
	

	if( paint->isActive() )
      paint->end();

   cout << "initiate fill "<< xTarget << ", "<< yTarget << endl;

   // set reference color
   targetImage = target->convertToImage();
   referenceColor.setRgb(targetImage.pixel(xTarget, yTarget));
   cout << "color value in decimal = " << referenceColor.rgb() << endl;

   // start drawing
   paint->begin(target);
   paint->setPen(pen);	// set pen for the color
   paint->setClipRect ( clip );	// clipping

   // start recusive function
   fillColor(xTarget, yTarget);

   paint->end();

   //target->convertFromImage(targetImage,0);// = &(targetImage.convertFromImage());
}

// recursive function for filling color
void MyFillDialog::fillColor(int x, int y, int terminateCounter)
{
   // base case 1: return if x and y is out of bounds.
   if (x >= targetImage.width() || x<0 || y<0 || y>=targetImage.height())
      return;
   // base case 2: return if reference color differ from color in x and y.
   if (referenceColor.rgb()!=targetImage.pixel(x,y))
      return;
   // base case 3: return if target point is already filled
   if (filledImg[y][x])
      return;
   // base case 4: Protection code 1 => prevents program from hanging, and protects from unknown segmentation fault.
   if (terminateCounter<=0)
      return;

   // draw a color to target point
   paint->drawPoint(x,y);
   filledImg[y][x]=true;
   
   
   // recursive call: flood out to all 2D directions
   fillColor(x+1, y, terminateCounter-1);
   fillColor(x-1, y, terminateCounter-1);
   fillColor(x, y+1, terminateCounter-1);
   fillColor(x, y-1, terminateCounter-1);
}

////////////////////////////////////////////////
// Handle Callback function
////////////////////////////////////////////////
// slot to set fill color
void MyFillDialog::OnSetFillColor(int type)
{
	foregroundColor=!type;
	setColor();

}
