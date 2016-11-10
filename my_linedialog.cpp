/****************************************/
//  COMP2012 2015S PA2 -- Paint
//  File: my_linedialog.cpp
//  Author: Hong Joon CHOI
//  Description: the source file
//  -- MyLineDialog class implementation 
//     customizing the QDialog class for the Line tool
/****************************************/

#include <iostream>
using namespace std;
#include <string.h>

#include "my_linedialog.h"

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

MyLineDialog::MyLineDialog(QWidget* parent, const char* name)
:QDialog(parent, name)
{

   /** set default settings and initialize*/
   paint = new QPainter(parent);
   pen.setCapStyle( Qt::FlatCap );
   pen.setJoinStyle( Qt::BevelJoin );
   pen.setStyle(Qt::SolidLine);
   polyType=false;
   px=0;
   py=0;

   /** Radio button group for cap style */
   // Create a button group to contain all buttons
   capstylebgroup = new QButtonGroup( this );
   capstylebgroup->setGeometry( 180, 10, 105, 110 );
   capstylebgroup->setTitle ( "Cap Style" );
   connect( capstylebgroup, SIGNAL(clicked(int)), SLOT(OnSetCapStyle(int)) );

   rb_flatcap = new QRadioButton( "Flat", capstylebgroup );
   rb_flatcap->setGeometry( 10, 20, 80, 20 );

   rb_squarecap = new QRadioButton( "Square", capstylebgroup );
   rb_squarecap->setGeometry( 10, 50, 80, 20 );

   rb_roundcap = new QRadioButton( "Round", capstylebgroup );
   rb_roundcap->setGeometry( 10, 80, 80, 20 );

   
   switch( pen.capStyle() ){
      case Qt::MPenCapStyle:
      case Qt::FlatCap:
         rb_flatcap->setChecked( TRUE );
      break;
      case Qt::SquareCap:
         rb_squarecap->setChecked( TRUE );
      break;
      case Qt::RoundCap:
         rb_roundcap->setChecked( TRUE );
      break;
   }


   /** Radio button group for line style */
   linestylebgroup = new QButtonGroup( this );
   linestylebgroup->setGeometry( 10, 10, 160, 200 );
   linestylebgroup->setTitle ( "Cap Style" );
   connect( linestylebgroup, SIGNAL(clicked(int)), SLOT(OnSetLineStyle(int)) );

   rb_styles = new QRadioButton*[5];
   const char* buttonNames[] = {"Solid line", "Dash line", "Dot line", "Dash dot line", "Dash dot dot line"};
   for (int i=0; i<5; i++)
   {
      rb_styles[i] = new QRadioButton(buttonNames[i], linestylebgroup);
      rb_styles[i]->setGeometry(10, 30*i+20, 140, 20);
   }
   rb_styles[0]->setChecked(TRUE);	// DEFAULT SETTING => SOLID LINE


   /** Radio button group for line type */
   linetypebgroup = new QButtonGroup( this );
   linetypebgroup->setGeometry( 180, 130, 105, 80 );
   linetypebgroup->setTitle ( "Line Type" );
   connect( linetypebgroup, SIGNAL(clicked(int)), this, SLOT(OnSetLineType(int)) );

   rb_singletype = new QRadioButton( "Single", linetypebgroup );
   rb_singletype->setGeometry( 10, 20, 80, 20 );

   rb_polytype = new QRadioButton( "Poly", linetypebgroup );
   rb_polytype->setGeometry( 10, 50, 80, 20 );

   rb_singletype->setChecked( TRUE );


   /** Horizontal Slider For setting the line width */
   widthslider = new QSlider( QSlider::Horizontal, this, "width slider" );
   widthslider->setRange ( 1, 40 );
   widthslider->setValue ( pen.width() );
   widthslider->setGeometry  ( 100, 220, 140, 20 );

   connect( widthslider, SIGNAL(valueChanged(int)),
                 this, SLOT(OnSetPenWidth(int)) );

   wl = new QLabel( this );
   wl->setGeometry( 10,220,70,20 );
   wl->setText( "Pen Width" );

   widthlabel = new QLabel( this );
   widthlabel->setGeometry( 260, 220, 30, 20 );
   char widthsldrvalue[1024];
   sprintf( widthsldrvalue,"%d",widthslider->value() );
   widthlabel->setText( widthsldrvalue );

   resize(300,250);
}

MyLineDialog::~MyLineDialog()
{
   delete rb_flatcap;
   delete rb_squarecap;
   delete rb_roundcap;
   delete capstylebgroup;

   delete widthslider;
   delete widthlabel;
   delete wl;

   delete linestylebgroup;
   delete[] rb_styles;
   
   delete linetypebgroup;
   delete rb_singletype;
   delete rb_polytype;
}

// set or initiate reference position for drawing line. If polyType = true, reference position is set automatically
void MyLineDialog::setReferencePosition(int x, int y)
{
   if (!polyType || (px==0 && py==0) || (x==0 && y==0))
   {
      px=x;
      py=y;
   }
}

// Draw line to the target position, in target paint device. When drawing on the image, reference position is updated depending on dialog settings.
void MyLineDialog::drawLineWithSettings(const QPaintDevice* target, const QRect& clip, int xTarget, int yTarget, bool onDrawImage, int xDisplacement, int yDisplacement)
{
   // if reference position is not set, return.
	if( px == 0 && py ==0)
		return;
   if( paint->isActive() )
      paint->end();
   
   // draw line to target paint device
   paint->begin(target);
   paint->setClipRect ( clip );  // clipping
   paint->setPen(pen);
   paint->drawLine(px+xDisplacement, py+yDisplacement, xTarget+xDisplacement, yTarget+yDisplacement);
   paint->end();

   // reset to zero or automatically set the reference position.
   if (onDrawImage)
   {
      if (!polyType)
      {
         px=0;
         py=0;
      }
      else
      {
         px=xTarget;
         py=yTarget;
      }
   }

}
////////////////////////////////////////////////
// Handle Callback function
////////////////////////////////////////////////
// slot to set the pen width
void MyLineDialog::OnSetPenWidth(int w)
{
   char widthsldrvalue[1024];
   sprintf( widthsldrvalue,"%d",w );
   widthlabel->setText( widthsldrvalue );

   pen.setWidth( w );
}

// slot to set the cap style
void MyLineDialog::OnSetCapStyle(int type)
{
   switch( type ){
      case 0:
         pen.setCapStyle( Qt::FlatCap );
         pen.setJoinStyle( Qt::BevelJoin );
         break;
      case 1:
         pen.setCapStyle( Qt::SquareCap );
         pen.setJoinStyle( Qt::MiterJoin );
         break;
      case 2:
         pen.setCapStyle( Qt::RoundCap );
         pen.setJoinStyle( Qt::RoundJoin );
         break;
   }
}

// slot to set the line style
void MyLineDialog::OnSetLineStyle(int type)
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
   }

}

// slot to set the line type
void MyLineDialog::OnSetLineType(int type)
{
   switch( type ){
      case 0:
         polyType=false;
         break;
      case 1:
         polyType=true;
         break;
   }
}