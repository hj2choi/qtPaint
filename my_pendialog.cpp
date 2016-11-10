/****************************************/
//  COMP2012 2015S PA2 -- Paint
//  File: my_pendialog.cpp
//  Description: the source file
//  -- MyPenDialog class implementation 
//     customizing the QDialog class for the Pen tool
/****************************************/

#include <iostream>
using namespace std;
#include <string.h>

#include "my_pendialog.h"

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

MyPenDialog::MyPenDialog(QWidget* parent, const char* name)
:QDialog(parent, name)
{
   // For setting the line's captstyle
   // Create a button group to contain all buttons
   capstylebgroup = new QButtonGroup( this );
   capstylebgroup->setGeometry( 0, 0, 300, 60 );
   capstylebgroup->setTitle ( "Cap Style" );
   connect( capstylebgroup, SIGNAL(clicked(int)), SLOT(OnSetCapStyle(int)) );

   rb_flatcap = new QRadioButton( "Flat", capstylebgroup );
   rb_flatcap->setGeometry( 20, 20, 80, 30 );

   rb_squarecap = new QRadioButton( "Square", capstylebgroup );
   rb_squarecap->setGeometry( 100, 20, 80, 30 );

   rb_roundcap = new QRadioButton( "Round", capstylebgroup );
   rb_roundcap->setGeometry( 200, 20, 80, 30 );

   pen.setCapStyle( Qt::FlatCap );
   pen.setJoinStyle( Qt::BevelJoin );
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

   // For setting the line width
   widthslider = new QSlider( QSlider::Horizontal, this, "width slider" );
   widthslider->setRange ( 1, 40 );
   widthslider->setLineStep ( 1 );
   widthslider->setValue ( pen.width() );
   widthslider->setGeometry  ( 80, 80, 190, 20 );
   widthslider->setTickmarks( QSlider::Below );
   widthslider->setTickInterval( 1 );

   connect( widthslider, SIGNAL(valueChanged(int)),
                 this, SLOT(OnSetPenWidth(int)) );

   wl = new QLabel( this );
   wl->setGeometry( 10,80,70,20 );
   wl->setText( "Pen Width" );

   widthlabel = new QLabel( this );
   widthlabel->setGeometry( 280, 80, 20, 20 );
   char widthsldrvalue[1024];
   sprintf( widthsldrvalue,"%d",widthslider->value() );
   widthlabel->setText( widthsldrvalue );

   resize(300,110);
}

MyPenDialog::~MyPenDialog()
{
   delete rb_flatcap;
   delete rb_squarecap;
   delete rb_roundcap;
   delete capstylebgroup;

   delete widthslider;
   delete widthlabel;
   delete wl;
}

////////////////////////////////////////////////
// Handle Callback function
////////////////////////////////////////////////
// slot to set the pen width
void MyPenDialog::OnSetPenWidth(int w)
{
   char widthsldrvalue[1024];
   sprintf( widthsldrvalue,"%d",w );
   widthlabel->setText( widthsldrvalue );

   pen.setWidth( w );
}

// slot to set the cap style
void MyPenDialog::OnSetCapStyle(int type)
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
