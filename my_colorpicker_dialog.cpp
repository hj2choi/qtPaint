/****************************************/
//  QT Paint
//  File: my_colorpickerdialog.cpp
//  Author: Hong Joon CHOI
//  Date: 25.Mar.2015
//  Description: the source file
//  -- MyColorPickerDialog class implementation 
//     Implementation for picking color from target image.
/****************************************/

#include <iostream>
using namespace std;
#include <string.h>

#include "my_colorpicker_dialog.h"

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

MyColorPickerDialog::MyColorPickerDialog(QWidget* parent, const char* name)
:QDialog(parent, name)
{
   // Initialize for default setting
   foregroundColor = false;


   // Radio button group for colorStorage
   fillColorBgroup = new QButtonGroup( this );
   fillColorBgroup->setGeometry( 10, 10, 130, 125 );
   fillColorBgroup->setTitle ( "Extract color for" );
   connect( fillColorBgroup, SIGNAL(clicked(int)), this, SLOT(OnSetColorStorage(int)) );
      
   // Radio buttons for colorStorage
   rb_fillColors = new QRadioButton*[2];
   const char* fillColorNames[] = {"Foreground", "Background"};
   for (int i=0; i<2; i++)
   {
      rb_fillColors[i] = new QRadioButton(fillColorNames[i], fillColorBgroup);
      rb_fillColors[i]->setGeometry(10, 15+50*i, 95, 40);
   }
   rb_fillColors[1]->setChecked(TRUE);	// DEFAULT SETTING

   resize(150,150);
}

MyColorPickerDialog::~MyColorPickerDialog()
{
   
   delete fillColorBgroup;
   delete[] rb_fillColors;

}

// retrieve color from target pos
QColor MyColorPickerDialog::extractColorAtTargetPos(const QPixmap* target, int xTarget, int yTarget)
{
   if (xTarget<0 || yTarget<0 || xTarget>=target->width() || yTarget>=target->height())
   {
      cout << "INVALID target location for color extraction" << endl;
      return QColor();
   }
   QImage targetImage = target->convertToImage();
   return QColor(targetImage.pixel(xTarget, yTarget));
}

////////////////////////////////////////////////
// Handle Callback function
////////////////////////////////////////////////
// slot to set fill color
void MyColorPickerDialog::OnSetColorStorage(int type)
{
	foregroundColor=!type;
}
