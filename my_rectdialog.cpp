/****************************************/
//  COMP2012 2015S PA2 -- Paint
//  File: my_rectdialog.cpp
//  Author: Hong Joon CHOI
//  Description: the source file
//  -- MyRectDialog class implementation 
//     customizing the QDialog class for the Rectangle tool
/****************************************/

#include <iostream>
using namespace std;
#include <string.h>

#include "my_rectdialog.h"

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

MyRectDialog::MyRectDialog(QWidget* parent, const char* name)
:QDialog(parent, name)
{

   // Initialize Pen, brush and paint and initialize default settings
   paint = new QPainter(parent);
	bgColor = QColor( 255, 255, 255 );
   pen.setCapStyle( Qt::FlatCap );
   pen.setJoinStyle( Qt::BevelJoin );
   pen.setStyle(Qt::SolidLine);
   brush.setStyle(Qt::NoBrush);
   foregroundColor = true;
   drawType = 0;

   // Radio button group for drawTypeGroup
   drawTypeBgroup = new QButtonGroup( this );
   drawTypeBgroup->setGeometry( 10, 10, 480, 40 );
   drawTypeBgroup->setTitle ( "Draw Type" );
   connect( drawTypeBgroup, SIGNAL(clicked(int)), this, SLOT(OnSetDrawType(int)) );
	
   // Radio buttons for drawTypeGroup
   rb_drawTypes = new QRadioButton*[4];
   const char* drawTypeNames[] = {"Rectangle", "Round rectangle", "Circle", "Elipse"};
   for (int i=0; i<4; i++)
   {
      rb_drawTypes[i] = new QRadioButton(drawTypeNames[i], drawTypeBgroup);
      rb_drawTypes[i]->setGeometry(10+i*115, 15, 110, 20);
   }
   rb_drawTypes[0]->setChecked(TRUE);	// DEFAULT SETTING

   // Radio button group for fill style
   fillStyleBgroup = new QButtonGroup( this );
   fillStyleBgroup->setGeometry( 10, 55, 480, 110 );
   fillStyleBgroup->setTitle ( "Fill Style" );
   connect( fillStyleBgroup, SIGNAL(clicked(int)), this, SLOT(OnSetFillStyle(int)) );

   // Radio buttons for fill style
   rb_fillStyles = new QRadioButton*[15];
   const char* fileStyleNames[] = {"Solid", "Dense1", "Dense2", "Dense3", "Dense4", "Dense5", "Dense6", "Dense7", "Horizontal", "Vertical", "Cross", "B. Diag", "F. Diag", "C. Diag", "No Pattern"};
   for (int j=0; j<3; j++)
   for (int i=0; i<5; i++)
   {
      rb_fillStyles[i+j*5] = new QRadioButton(fileStyleNames[i+j*5], fillStyleBgroup);
      rb_fillStyles[i+j*5]->setGeometry(10+i*92, 15+j*30, 85, 20);
   }
   rb_fillStyles[14]->setChecked(TRUE);	// DEFAULT SETTING


   // Radio button group for boundaryStyle
   boundaryStyleBgroup = new QButtonGroup( this );
   boundaryStyleBgroup->setGeometry( 10, 170, 340, 70 );
   boundaryStyleBgroup->setTitle ( "Boundary Style" );
   connect( boundaryStyleBgroup, SIGNAL(clicked(int)), this, SLOT(OnSetBoundaryStyle(int)) );
   rb_boundaryStyles = new QRadioButton*[6];

   // Radio buttons for boundaryStyle
   const char* boundaryStyleNames[] = {"Solid line", "Dash line", "Dot line", "Dash dot line", "Dash dot dot line", "No line"};
   for (int j=0; j<2; j++)
      for (int i=0; i<3; i++)
      {
         rb_boundaryStyles[i+j*3] = new QRadioButton(boundaryStyleNames[i+j*3], boundaryStyleBgroup);
         rb_boundaryStyles[i+j*3]->setGeometry(10+i*105, 15+j*30, 95, 20);
      }
   rb_boundaryStyles[0]->setChecked(TRUE);	// DEFAULT SETTING


   // Radio button group for fillColor
   fillColorBgroup = new QButtonGroup( this );
   fillColorBgroup->setGeometry( 360, 170, 130, 125 );
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


   // Radio button group for boundaryJoinStyle
   boundaryJoinStyleBGroup = new QButtonGroup( this );
   boundaryJoinStyleBGroup->setGeometry( 10, 245, 340, 50 );
   boundaryJoinStyleBGroup->setTitle ( "Boundary Join Style" );
   connect( boundaryJoinStyleBGroup, SIGNAL(clicked(int)), this, SLOT(OnSetBounaryJoinStyle(int)) );

   // Radio buttons for boundaryJoinStyle
   rb_boundaryJoinStyles = new QRadioButton*[3];
   const char* boundaryJoinStyleNames[] = {"Miter Join", "Bevel Join", "Round Join"};
   for (int i=0; i<3; i++)
   {
      rb_boundaryJoinStyles[i] = new QRadioButton(boundaryJoinStyleNames[i], boundaryJoinStyleBGroup);
      rb_boundaryJoinStyles[i]->setGeometry(10+100*i, 15, 110, 20);
   }
   rb_boundaryJoinStyles[0]->setChecked(TRUE);	// DEFAULT SETTING




   // Horizontal Slider For setting the line width
   boundaryWidthSlider = new QSlider( QSlider::Horizontal, this, "Boundary Width" );
   boundaryWidthSlider->setRange ( 1, 40 );
   boundaryWidthSlider->setValue ( pen.width() );
   boundaryWidthSlider->setGeometry  ( 140, 300, 280, 20 );

   connect( boundaryWidthSlider, SIGNAL(valueChanged(int)), this, SLOT(OnSetBoundaryWidth(int)) );

   sliderLabel = new QLabel( this );
   sliderLabel->setGeometry( 10,300,120,20 );
   sliderLabel->setText( "Boundary Width" );

   boundaryWidthLabel = new QLabel( this );
   boundaryWidthLabel->setGeometry( 450, 300, 30, 20 );
   char widthsldrvalue[1024];
   sprintf( widthsldrvalue,"%d",boundaryWidthSlider->value() );
   boundaryWidthLabel->setText( widthsldrvalue );

   resize(500,330);
}

MyRectDialog::~MyRectDialog()
{

   delete boundaryWidthSlider;
   delete sliderLabel;
   delete boundaryWidthLabel;

   delete drawTypeBgroup;
   delete[] rb_drawTypes;

   delete fillStyleBgroup;
   delete[] rb_fillStyles;

   delete boundaryStyleBgroup;
   delete[] rb_boundaryStyles;
   
   delete fillColorBgroup;
   delete[] rb_fillColors;

   delete boundaryJoinStyleBGroup;
   delete[] rb_boundaryJoinStyles;

   delete paint;
}

// set actual color accroding to dialog settings
void MyRectDialog::setColor()
{
   foregroundColor?(brush.setColor(fgColor)):(brush.setColor(bgColor));
}


// for convenience
inline int abs(int x)
{
   return (x<0)?(-x):(x);
}

inline int min(int x, int y)
{
   return abs(x)<abs(y)?abs(x):abs(y);
}

inline int sign(int x)
{
   return x<0?-1:1;
}

// draw shape with dialog settings
void MyRectDialog::drawShapeWithSettings(const QPaintDevice* target, const QRect& clip, const QRect& shape)
{
	
	if( paint->isActive() )
      paint->end();

   paint->begin(target);
   paint->setPen(pen);	// set pen for the shape
   paint->setBrush(brush);		// set brush for the shape
   paint->setClipRect ( clip );	// clipping
   int m;
   // draw shape according to the dialog settings.
   switch (drawType)
   {
      case 0:
         paint->drawRect(shape);
         break;
      case 1:
         paint->drawRoundRect(shape);
         break;
      case 2:
         //(abs(shape.width())<abs(shape.height()))?(paint->drawEllipse(shape.x(), shape.y(), shape.width(), shape.width())):(paint->drawEllipse(shape.x(), shape.y(), shape.height(), shape.height()));
         m = min(shape.width(), shape.height());
         paint->drawEllipse(shape.x(), shape.y(), sign(shape.width())*m, sign(shape.height())*m);
         break;
      case 3:
         paint->drawEllipse(shape);
         break;
   }
   
   paint->end();
}

////////////////////////////////////////////////
// Handle Callback function
////////////////////////////////////////////////
// slot to set the boundary width
void MyRectDialog::OnSetBoundaryWidth(int w)
{
   char widthsldrvalue[1024];
   sprintf( widthsldrvalue,"%d",w );
   boundaryWidthLabel->setText( widthsldrvalue );
	
   pen.setWidth( w );
}

// slot to set the draw type
void MyRectDialog::OnSetDrawType(int type)
{
   if (type >=0 && type < 4)
      drawType = type;
}

// slot to set fill style
void MyRectDialog::OnSetFillStyle(int type)
{
   switch(type){
      case 0:
         brush.setStyle(Qt::SolidPattern);
         break;
      case 1:
         brush.setStyle(Qt::Dense1Pattern);
         break;
      case 2:
         brush.setStyle(Qt::Dense2Pattern);
         break;
      case 3:
         brush.setStyle(Qt::Dense3Pattern);
         break;
      case 4:
         brush.setStyle(Qt::Dense4Pattern);
         break;
      case 5:
         brush.setStyle(Qt::Dense5Pattern);
         break;
      case 6:
         brush.setStyle(Qt::Dense6Pattern);
         break;
      case 7:
         brush.setStyle(Qt::Dense7Pattern);
         break;
      case 8:
         brush.setStyle(Qt::HorPattern);
         break;
      case 9:
         brush.setStyle(Qt::VerPattern);
         break;
      case 10:
         brush.setStyle(Qt::CrossPattern);
         break;
      case 11:
         brush.setStyle(Qt::BDiagPattern);
         break;
      case 12:
         brush.setStyle(Qt::FDiagPattern);
         break;
      case 13:
         brush.setStyle(Qt::DiagCrossPattern);
         break;
      case 14:
         brush.setStyle(Qt::NoBrush);
         break;
   }

}

// slot to set fill color
void MyRectDialog::OnSetFillColor(int type)
{
	foregroundColor=!type;
	setColor();

}

// slot to set the boundary style
void MyRectDialog::OnSetBoundaryStyle(int type)
{
   switch( type ){
      case 0:
         pen.setStyle( Qt::SolidLine );
         break;
      case 1:
         pen.setStyle( Qt::DashLine );
         break;
      case 2:
         pen.setStyle( Qt::DotLine );
         break;
      case 3:
         pen.setStyle( Qt::DashDotLine );
         break;
      case 4:
         pen.setStyle( Qt::DashDotDotLine );
         break;
      case 5:
         pen.setStyle( Qt::NoPen );
         break;
   }



}

// slot to set pen join style
void MyRectDialog::OnSetBounaryJoinStyle(int type)
{
   switch( type ){
      case 0:
         pen.setCapStyle( Qt::FlatCap );
         pen.setJoinStyle( Qt::MiterJoin );
         break;
      case 1:
         pen.setCapStyle( Qt::SquareCap );
         pen.setJoinStyle( Qt::BevelJoin );
         break;
      case 2:
         pen.setCapStyle( Qt::RoundCap );
         pen.setJoinStyle( Qt::RoundJoin );
         break;
   }

}
