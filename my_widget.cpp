/****************************************/
//  COMP2012 2015S PA2 -- Paint
//  File: my_widget.cpp
//  Description: the source file
//  -- MyMainWindow class implementation 
/****************************************/

#include <iostream>
#include <cmath>
using namespace std;

#include "my_widget.h"

#include <qfiledialog.h>
#include <qpainter.h>
#include <qmessagebox.h>
#include <qinputdialog.h>
#include <qimage.h>
#include <qpixmap.h>
#include <qpopupmenu.h>
#include <qtextedit.h>
#include <qfile.h>
#include <qfiledialog.h>
#include <qstatusbar.h>
#include <qmessagebox.h>
#include <qprinter.h>
#include <qapplication.h>
#include <qaccel.h>
#include <qtextstream.h>
#include <qpainter.h>
#include <qpaintdevicemetrics.h>
#include <qwhatsthis.h>
#include <qsimplerichtext.h>
#include <qcolordialog.h> 

#include "stack.h"

////////////////////////////////////////////////
// Constructor and Destructor
////////////////////////////////////////////////

MyMainWindow::MyMainWindow(QWidget* parent, const char* name)
:QMainWindow(parent, name)
{
   // initialize the default background color
   bgcolor = QColor( 255, 255, 255 );
   selectedbutton = DPen;
   
   // create the QPixmap image
   image = new QPixmap();
   imageLayers = new LayeredPixmap(this, imageLayerCount);
   undoStack = new Stack<LayeredPixmap>(maxUndoLevel);
   redoStack = new Stack<LayeredPixmap>(maxUndoLevel);
   cout << "Level " << maxUndoLevel << " undo and redo supported." << endl;   // debug log
   // build the menu
   CreateMenu();





   // build the tool bar 
   drawTools = new MyToolBar( this, "tool bar" );
   drawTools->setLabel( "Tool Bar" );

   connect( drawTools, SIGNAL( OnPaint() ), 
         this, SLOT( OnDockWindowPositionChanged() ) );

   // build the tool bar for layers.
   layerTools = new MyToolBar(this, "layers");
   layerTools->setLabel("Layer Tools");
   connect(layerTools, SIGNAL(OnPaint()), this, SLOT(OnDockWindowPositionChanged()));



   QPixmap pix;

   pix.load( "new_icon.bmp" );
   newButton = new QToolButton( pix, "New Image", QString::null,
                                this, SLOT( OnNewImage() ), drawTools, "new image" );

   pix.load( "open_icon.bmp" );
   openButton = new QToolButton( pix, "Open Image", QString::null,
                                this, SLOT( OnLoadImage() ), drawTools, "open image" );

   pix.load( "save_icon.bmp" );
   saveButton = new QToolButton( pix, "Save Image", QString::null,
                                this, SLOT( OnSaveImage() ), drawTools, "save image" );

   pix.load( "undo_icon.bmp" );
   penButton = new QToolButton( pix, "Undo", QString::null,
                                this, SLOT( OnEditUndo() ), drawTools, "undo" );

   pix.load( "redo_icon.bmp" );
   penButton = new QToolButton( pix, "Redo", QString::null,
                                this, SLOT( OnEditRedo() ), drawTools, "redo" );

   pix.load( "clearall_icon.bmp" );
   penButton = new QToolButton( pix, "Clear All", QString::null,
                                this, SLOT( OnEditClearAll() ), drawTools, "clear all" );

   pix.load( "resize_icon.bmp" );
   penButton = new QToolButton( pix, "Resize", QString::null,
                                this, SLOT( OnEditResize() ), drawTools, "resize" );

   pix.load( "pen_icon.bmp" );
   penButton = new QToolButton( pix, "Pen", QString::null,
                                this, SLOT( OnChoosePen() ), drawTools, "pen" );
   penButton->setToggleButton(1);
   penButton->setOn(1);    // pre toggle the button for default setting.

   pix.load( "line_icon.bmp" );
   lineButton = new QToolButton( pix, "Line", QString::null,
                                 this, SLOT( OnChooseLine() ), drawTools, "line" );
   lineButton->setToggleButton(1);

   pix.load( "eraser_icon.bmp" );
   eraserButton = new QToolButton( pix, "Eraser", QString::null,
                                 this, SLOT( OnChooseEraser() ), drawTools, "eraser" );
   eraserButton->setToggleButton(1);

   pix.load( "rect_icon.bmp" );
   rectButton = new QToolButton( pix, "Rectangle", QString::null,
                                 this, SLOT( OnChooseRect() ), drawTools, "rectangle" );
   rectButton->setToggleButton(1);
   
   // Create fill icon
   pix.load( "fill_icon.bmp" );
   fillButton = new QToolButton( pix, "Fill", QString::null,
                                 this, SLOT( OnChooseFill() ), drawTools, "Fill" );
   fillButton->setToggleButton(1);
   
   // Create color picker icon
   pix.load( "colorpicker_icon.bmp" );
   colorPickerButton = new QToolButton( pix, "Color Picker", QString::null,
                                 this, SLOT( OnChooseColorPicker() ), drawTools, "Color Picker" );
   colorPickerButton->setToggleButton(1);

   pix.load( "fcolor_icon.bmp" );
   colorButton = new QToolButton( pix, "Color", QString::null,
                                 this, SLOT( OnChooseColor() ), drawTools, "color" );
   
   pix.load( "bcolor_icon.bmp" );
   bcolorButton = new QToolButton( pix, "BG Color", QString::null,
                                 this, SLOT( OnChooseBGColor() ), drawTools, "BG Color" );

   // color and bgcolor indicator for convenience
   pix.resize(16,16);
   pix.fill(QColor(0,0,0));
   colorIndicator = new QToolButton( pix, "Color", QString::null,
                                 this, SLOT( OnChooseColor() ), drawTools, "Color" );
   pix.fill(bgcolor);
   bgColorIndicator = new QToolButton( pix, "BG Color", QString::null,
                                 this, SLOT( OnChooseBGColor() ), drawTools, "BG Color" );
   
   layerIndicators = new QToolButton*[imageLayers->getLayerCount()];
   layerDisplayIndicators = new QToolButton*[imageLayers->getLayerCount()];
   

   // Icons for image layers
   for (int i=0; i<imageLayers->getLayerCount(); i++)
   {
      pix.resize(22,22);
      pix.fill(bgcolor);
      layerIndicators[i] = new QToolButton(pix, "Enable edit", QString::null, this, SLOT(OnChooseLayer()), layerTools, "Layers");
      layerIndicators[i]->setToggleButton(1);
      layerIndicators[i]->setOn(false);
      pix.load("eye.bmp");
      layerDisplayIndicators[i] = new QToolButton(pix, "Display layer", QString::null, this, SLOT(OnChangeLayerDisplay()), layerTools, "Display");
      layerDisplayIndicators[i]->setToggleButton(1);
      layerDisplayIndicators[i]->setOn(true);
   }
   layerIndicators[0]->setOn(true);



   // create the QPainter object
   paint = new QPainter( this );

   // create the pen dialog
   pendialog = new MyPenDialog( this, "Pen Dialog" );
   pendialog->setCaption( "Pen Dialog" );
   
   // create the eraser dialog
   eraserDialog = new MyEraserDialog( this, "Eraser Dialog" );
   eraserDialog->setCaption( "Eraser Dialog" );
   
   // create the line dialog
   lineDialog = new MyLineDialog(this, "Line Dialog");
   lineDialog->setCaption("Line Dialog");
   
   // create the rect dialog
   rectDialog = new MyRectDialog(this, "Rectangle Dialog");
   rectDialog->setCaption("Rectangle Dialog");

   // create the fill dialog
   fillDialog = new MyFillDialog(this, "Fill Dialog");
   fillDialog->setCaption("Fill Dialog");
   
   // create the color picker dialog 
   colorPickerDialog = new MyColorPickerDialog(this, "Color Picker Dialog");
   colorPickerDialog->setCaption("Color Picker Dialog");

   resize(800,600);

   QDockArea* leftDockWin = leftDock();
   QDockArea* topDockWin = topDock();
      
   xPos = ((QWidget*)leftDockWin)->frameSize().width();
   yPos = menuBar()->height() + ((QWidget*)topDockWin)->frameSize().height();

   // initialize the undo flag to false (i.e. disable undo)
   //undoflag = false;
}

MyMainWindow::~MyMainWindow()
{
   delete newButton;
   delete openButton;
   delete saveButton;
   delete undoButton;
   delete redoButton;
   delete clearallButton;
   delete resizeButton;
   delete rectButton;
   delete penButton;
   delete lineButton;
   delete eraserButton;
   delete colorButton;
   delete bcolorButton;
   delete drawTools;

   delete colorIndicator;
   delete bgColorIndicator;

   delete image;
   delete imageLayers;
   //if(undo != NULL) delete undo;
   //if(redo != NULL) delete redo;
   delete undoStack;
   delete redoStack;
   delete paint;

   delete pendialog;
   delete eraserDialog;
   delete lineDialog;
   delete rectDialog;
   delete fillDialog;
   delete colorPickerDialog;
   delete layerIndicators;
   delete layerDisplayIndicators;

   delete file;
   delete edit;
   delete view;
   delete help;
}


////////////////////////////////////////////////
// Below are private functions for code-reuse and organization
////////////////////////////////////////////////

////////////////////////////////////////////////
// Postprocess after choosing color
////////////////////////////////////////////////
void MyMainWindow::processChooseColor(QColor windowcolor)
{
   // set color for pen, line and rect dialogs.
   pendialog->pen.setColor( windowcolor );
   lineDialog->pen.setColor(windowcolor);
   rectDialog->pen.setColor(windowcolor);
   rectDialog->fgColor = windowcolor;
   rectDialog->setColor();
   fillDialog->fgColor = windowcolor;
   fillDialog->setColor();
   
   // update color for color icon.
   QPixmap pix;
   pix.resize(16,16);
   pix.fill(windowcolor);
   colorIndicator->setIconSet(pix);

}

////////////////////////////////////////////////
// Postprocess after choosing background color
////////////////////////////////////////////////
void MyMainWindow::processChooseBGColor(QColor windowcolor)
{
   // set color for fill and rect dialogs.
   bgcolor = windowcolor;
   rectDialog->bgColor = windowcolor;
   rectDialog->setColor();
   fillDialog->bgColor = windowcolor;
   fillDialog->setColor();

   // update color for color icon.
   QPixmap pix;
   pix.resize(16,16);
   pix.fill(windowcolor);
   bgColorIndicator->setIconSet(pix);

}

////////////////////////////////////////////////
// Push current images to undo stack, and clear the redo.
////////////////////////////////////////////////
void MyMainWindow::updateUndo()
{
   // only updates undo if image is not null. Pushes current image to stack (pass pointer).
   if (!image->isNull() && image!=NULL)
   {
      undoStack->push(*imageLayers);
      redoStack->reset();
      cout << "undoStackSize = " << undoStack->size() << "  redoStackSize = " << redoStack->size() << endl << endl;
   }

}

////////////////////////////////////////////////
// set toolset on toggle, and untoggle any other unactivated icon.
////////////////////////////////////////////////
void MyMainWindow::untoggleUnactivatedButtons()
{
   switch( selectedbutton ){
      case DPen:
         penButton->toggle();
         break;
      case DLine:
         lineButton->toggle();
         break;

      case DEraser:
         eraserButton->toggle();
         break;
      case Drect:
         rectButton->toggle();
         break;
      case DFill:
         fillButton->toggle();
         break;
      case DColorPicker:
         colorPickerButton->toggle();
         break;
   }
}

////////////////////////////////////////////////
// repaint the image of layerIcon
////////////////////////////////////////////////

void MyMainWindow::updateLayerIcon(int index)
{
   layerIndicators[index]->setIconSet(*(imageLayers->getIconSizedImage(index)));
   //cout << (imageLayers->getIconSizedImage(index))->height() << endl;
}


////////////////////////////////////////////////
// Create the menu
////////////////////////////////////////////////

void MyMainWindow::CreateMenu()
{
   // create the "File" popup menu
   file = new QPopupMenu( this );

   file->insertItem( "New image", this, SLOT( OnNewImage() ) );
   file->insertItem( "Load image", this, SLOT( OnLoadImage() ) );
   file->insertItem( "Save image", this, SLOT( OnSaveImage() ) );
   file->insertSeparator();
   file->insertItem( "Foregound Color", this, SLOT( OnChooseColor() ) );
   file->insertItem( "Backgound Color", this, SLOT( OnChooseBGColor() ) );
   file->insertSeparator();
   file->insertItem( "Exit", this, SLOT( OnExit() ) );
   
   menuBar()->insertItem( "File", file );

   // create the "Edit" popup menu
   edit = new QPopupMenu( this );
   edit->insertItem( "Undo", this, SLOT( OnEditUndo() ) );
   edit->insertItem( "Redo", this, SLOT( OnEditRedo() ) );
   file->insertSeparator();
   edit->insertItem( "Clear All", this, SLOT( OnEditClearAll() ) );
   file->insertSeparator();
   edit->insertItem( "Resize", this, SLOT( OnEditResize() ) );
   menuBar()->insertItem( "Edit", edit );

   view = new QPopupMenu( this );
   view->insertItem( "Tool Bar", this, SLOT( OnViewToolBar() ) );
   menuBar()->insertItem( "View", view );

   help = new QPopupMenu( this );
   help->insertItem( "About", this, SLOT( OnAbout() ) );
   menuBar()->insertItem( "Help", help );
}

////////////////////////////////////////////////
// Paint the image onto the widget 
////////////////////////////////////////////////

void MyMainWindow::paintbmp(bool constructLayers)
{
   
   // close active painter
   if(paint->isActive () )
   {
      paint->end();
   }
   
   // combine layers to one image. for the sake of optimization, layers are only reconstructed when necessary.
   if (constructLayers)
   {
      imageLayers->combineLayersToImage(image);
      updateLayerIcon(imageLayers->getCurrentIndexOnEdit());
      this->erase();
      
   }
   
   // paint current image OR reconstructed image onto the widget.
   paint->begin( this );
   if ( ! image->isNull() ) 
   {
      paint->drawPixmap( xPos, yPos, (*image) );
   }
   paint->end();
   //cout << " paintbmp" << constructLayers << endl;  // log for debugging.
}

////////////////////////////////////////////////
// Handle Paint Event
////////////////////////////////////////////////

void MyMainWindow::paintEvent(QPaintEvent* e)
{
   paintbmp();
}

////////////////////////////////////////////////
// Handle Callback function
////////////////////////////////////////////////

// Create a new image
void MyMainWindow::OnNewImage()
{
   bool ok;

   // get the user input of width from the input diaplog
   int width = QInputDialog::getInteger( "New Image", "Enter the bitmap width:", 400, 0, 10000, 1,
            &ok, this );

   if ( !ok || width <= 0 ) 
      return;

   // get the user input of height from the input diaplog
   int height = QInputDialog::getInteger( "New Image", "Enter the bitmap height:", 300, 0, 10000, 1,
            &ok, this );

   if ( !ok || height <= 0 ) 
      return;
    
   if ( image->isNull() )
   {
      delete image;   
      image=NULL;
   }

   // create an image with the input width & height with background color
   image = new QPixmap(width, height );

   imageLayers->newImageLayersWithSize(width, height, bgcolor);

   paintbmp(1);
}

// Load an image
void MyMainWindow::OnLoadImage()
{
   QString s = QFileDialog::getOpenFileName( "", "*.bmp", this, "", "Load image..." );
   if ( ! s.isNull() ) 
   {
      if( imageLayers->currentLayerOnEdit()->load( s ) ){
         paintbmp(1);
      }
   }
}

// Save the image as a bitmap
void MyMainWindow::OnSaveImage()
{
   QString s = QFileDialog::getSaveFileName( "", "*.bmp", this, "", "Save image..." );
   if (! s.isNull() )
   {
      image->save( s, "BMP" );
   }
}

// Change the foreground color
void MyMainWindow::OnChooseColor()
{
   QColor windowcolor = QColorDialog::getColor( pendialog->pen.color(), this );
   if( windowcolor.isValid() ){
      processChooseColor(windowcolor);
   }

}

// Change the background color
void MyMainWindow::OnChooseBGColor()
{
   QColor windowcolor = QColorDialog::getColor( bgcolor, this );
   if( windowcolor.isValid() ){
      processChooseBGColor(windowcolor);
   }
}

// Undo the last action
void MyMainWindow::OnEditUndo()
{
   // TODO!
   if (!undoStack->isEmpty())
   {
      // push copy of the current image to redostack.
      redoStack->push(*imageLayers);
      // delete current image.
      delete imageLayers;
      //cout << " item deleted from OnEditUndo()" << endl;
      // retrieve image from undo.
      imageLayers = undoStack->pop();
      
      cout << "undoSize = " << undoStack->size() << "  redoSize = " << redoStack->size() << endl;  // log current stack size

      // update toggle status of layer icons
      for (int i=0; i<imageLayers->getLayerCount(); i++)
      {
         if (i==imageLayers->getCurrentIndexOnEdit())
            layerIndicators[i]->setOn(true);
         else
            layerIndicators[i]->setOn(false);
      }
      OnChangeLayerDisplay();
      cout << "layer " << imageLayers->getCurrentIndexOnEdit() << " on edit mode!" << endl;  // log current layer on edit

      paintbmp(1);
   }
}

// Redo the last action
void MyMainWindow::OnEditRedo()
{
   // TODO!
   if (!redoStack->isEmpty())
   {
      // push copy of the current image to undostack.
      undoStack->push(*imageLayers);
      // delete current image.
      delete imageLayers;
      //cout << " item deleted from OnEditRedo()" << endl;
      // retrieve image from undo.
      imageLayers = redoStack->pop();
      
      cout << "undoStackSize = " << undoStack->size() << "  redoStackSize = " << redoStack->size() << endl; // log current stack size
      
      // update toggle status of layer icons
      for (int i=0; i<imageLayers->getLayerCount(); i++)
      {
         if (i==imageLayers->getCurrentIndexOnEdit())
            layerIndicators[i]->setOn(true);
         else
            layerIndicators[i]->setOn(false);
      }
      OnChangeLayerDisplay();
      cout << "layer " << imageLayers->getCurrentIndexOnEdit() << " on edit mode!" << endl;  // log current layer on edit

      paintbmp(1);
   }
}


// Clear the drawing
void MyMainWindow::OnEditClearAll()
{
   // TODO!
   updateUndo();
   
   // create an image with the input width & height
   imageLayers->newImageLayersWithSize(image->width(), image->height(), bgcolor);
   
   OnChangeLayerDisplay();
   // fill it with default background
   paintbmp(1);
}

// Resize the image
void MyMainWindow::OnEditResize()
{
   // TODO!
   bool ok;

   // get the user input of width from the input diaplog
   int width = QInputDialog::getInteger( "New Image", "Enter the bitmap width:", 400, 0, 10000, 1,
            &ok, this );
   if ( !ok || width <= 0 ) 
      return;

   // get the user input of height from the input diaplog
   int height = QInputDialog::getInteger( "New Image", "Enter the bitmap height:", 300, 0, 10000, 1,
            &ok, this );
   if ( !ok || height <= 0 ) 
      return;
   
   //update undo
   updateUndo();
   image = new QPixmap(width, height );
   // resize
   imageLayers->resizeImageLayers(width,height,bgcolor);

   OnChangeLayerDisplay();
   paintbmp(1);

}

// Show the tool bar
void MyMainWindow::OnViewToolBar()
{
   drawTools->show();
}

// Close the application
void MyMainWindow::OnExit()
{
   // qApp is a global pointer points to
   // our application object (QApplication)
   qApp->quit(); // quit this application program
}

// About Paint
void MyMainWindow::OnAbout()
{
   QMessageBox::about( this, "About", "CS2012 Spring 2015 Paint\nHong Joon CHOI, 20161472\nhjchoi@stu.ust.hk" );
}

////////////////////////////////////////////////
// Handle Button Click Event
////////////////////////////////////////////////
// Activate the Pen tool
void MyMainWindow::OnChoosePen()
{
   untoggleUnactivatedButtons();
   selectedbutton = DPen;
   mouseevent = 0;
}

// Activate the other drawing tools
// TODO: other OnChooseXX()
void MyMainWindow::OnChooseLine()
{
   untoggleUnactivatedButtons();
   selectedbutton = DLine;
   mouseevent = 0;
}

void MyMainWindow::OnChooseEraser()
{
   untoggleUnactivatedButtons();
   selectedbutton = DEraser;
   mouseevent = 0;
}

void MyMainWindow::OnChooseRect()
{
   untoggleUnactivatedButtons();
   selectedbutton = Drect;
   mouseevent = 0;
}

void MyMainWindow::OnChooseFill()
{
   untoggleUnactivatedButtons();
   selectedbutton = DFill;
   mouseevent = 0;
}

void MyMainWindow::OnChooseColorPicker()
{
   untoggleUnactivatedButtons();
   selectedbutton = DColorPicker;
   mouseevent = 0;
}

void MyMainWindow::OnChooseLayer()
{
   //cout << "layer " << imageLayers->getCurrentIndexOnEdit() << " currently seleted" << endl;
   bool layerChangeFlag = true;

   // case 1 : when index of chosen layer is same as current layer on edit.
   for (int i=0; i<imageLayers->getLayerCount(); i++)
      if (!layerIndicators[i]->isOn() && i==imageLayers->getCurrentIndexOnEdit())
      {
         layerIndicators[i]->setOn(true);
         layerChangeFlag=false;
         return;
      }

   // case 2 : when index of chosen layer is different from current layer on edit.
   for (int i=0; i<imageLayers->getLayerCount(); i++)
   {
      if (layerChangeFlag && layerIndicators[i]->isOn() && i!=imageLayers->getCurrentIndexOnEdit())
      {
         imageLayers->setCurrentLayerOnEdit(i);
         layerChangeFlag=false;
      }
      else
         layerIndicators[i]->setOn(false);
   }
   
   updateLayerIcon(imageLayers->getCurrentIndexOnEdit());
   cout << "layer " << imageLayers->getCurrentIndexOnEdit() << " on edit mode!" << endl;
}

void MyMainWindow::OnChangeLayerDisplay()
{
   // set list of layers on display on user toggling buttons.
   for (int i=0; i<imageLayers->getLayerCount(); i++)
   {
      if (imageLayers->displayLayer[i] != layerDisplayIndicators[i]->isOn())
      {
         imageLayers->displayLayer[i] = layerDisplayIndicators[i]->isOn();
         cout << i << "th layer set for display"<< endl;
      }
   }

   paintbmp(true);
}

////////////////////////////////////////////////
// Handle Mouse Event
////////////////////////////////////////////////
// Mouse press event handler
void MyMainWindow::mousePressEvent(QMouseEvent* e)
{
   // User presses the left button -- start drawing
   if ( e->button() == Qt::LeftButton )
   {

      // update undo
      updateUndo();

      mouseevent = 1;

      // Create a new image if necessary
      if ( image->isNull() ) 
         OnNewImage(); 
      else 
      {
         if( paint->isActive() )
            paint->end();

         QRect clip;

         switch( selectedbutton ){
            case DPen:  // drawing with the Pen tool
               // update the cursor positions
               px = e->x(); py = e->y();
               dx = e->x(); dy = e->y();
               break;

            case DLine: // drawing with the Line tool
               // TODO:
               // set current mouse position as reference position
               lineDialog->setReferencePosition(e->x(), e->y());
               clip.setRect(xPos, yPos, image->width(), image->height());
               // draw line that links reference position and current mouse position onto the widget
               lineDialog->drawLineWithSettings(this, clip, e->x(), e->y());
               break;

            case DEraser: // drawing with the Eraser tool
               // TODO
               // erase current mouse position in square area
               clip.setRect(xPos, yPos, image->width(), image->height());
               eraserDialog->eraseTargetPosition(imageLayers->currentLayerOnEdit(), e->x()-xPos, e->y()-yPos, bgcolor);
               eraserDialog->eraseTargetPosition(image, e->x()-xPos, e->y()-yPos, bgcolor);
               paintbmp();
               // display eraser cursor
               eraserDialog->displayEraserCursor(this, clip, e->x(), e->y());
               break;

            case Drect:  // drawing witth the Rectangle tool
               // TODO
               // store base position to px and py
               px = e->x(); py = e->y();
               break;
         }
      }
   }
   // User presses the right button -- show the tools' dialogs 
   else if( e->button() == Qt::RightButton )
   {
      mouseevent = 2;

      switch( selectedbutton ){
         case DPen:
            pendialog->show();
            break;
         case DLine:
            lineDialog->show();
            break;
         case DEraser:
            eraserDialog->show();
            break;
         case Drect:
            rectDialog->show();
            break;
         case DFill:
            fillDialog->show();
            break;
         case DColorPicker:
            colorPickerDialog->show();
            break;
      }
   }
}

// Mouse move event handler
void MyMainWindow::mouseMoveEvent(QMouseEvent* e)
{
   // dragging by left button click
   if( mouseevent == 1 )
   {
      if ( image->isNull() ) {}
      else 
      { 
         QPointArray a;
         QRect shape;
         QRect clip;

         // close active painter
         if( paint->isActive() )
            paint->end();

         switch( selectedbutton ){
            case DPen:  // drawing with the Pen tool
               paint->begin( imageLayers->currentLayerOnEdit() ); // begin painting onto the picture

               paint->setClipRect ( 0, 0, image->width(), image->height() );  // clipping
               paint->setPen( pendialog->pen );  // set the painter settings from the pen dialog
               // Set the array of points 
               a.setPoints( 3, dx - xPos, dy - yPos,
                               px - xPos, py - yPos,
                               e->x() - xPos, e->y() - yPos );
               paint->drawPolyline( a, 0, 3 );
 
               // update the cursor positions
               dx = px; dy = py; 
               px = e->x(); py = e->y();

               paint->end(); // end painting onto the picture

               // temporarily draws on the image.
               paint->begin( image );
               paint->setClipRect ( 0, 0, image->width(), image->height() );
               paint->setPen( pendialog->pen );
               paint->drawPolyline( a, 0, 3 );
               paint->end();

               paintbmp();
               break;

            case DLine:  // drawing with the Line tool
               paintbmp();
               // TODO
               // draw line that links reference position and current mouse position onto the widget
               clip.setRect(xPos, yPos, image->width(), image->height());
               lineDialog->drawLineWithSettings(this, clip, e->x(), e->y());
               break;

            case DEraser:  // drawing with the Eraser tool
               // TODO
					// erase current mouse position in square area
               clip.setRect(xPos, yPos, image->width(), image->height());
               eraserDialog->eraseTargetPosition(imageLayers->currentLayerOnEdit(), e->x()-xPos, e->y()-yPos, bgcolor);
               eraserDialog->eraseTargetPosition(image, e->x()-xPos, e->y()-yPos, bgcolor);
               paintbmp();
               // display eraser cursor
               eraserDialog->displayEraserCursor(this, clip, e->x(), e->y());
               break;
					
            case Drect:  // drawing with the Rectangle tool
               paintbmp();
               // TODO
               // draw a shape inside the clip area using with dialog settings, onto the widget
               shape.setRect(px, py, e->x()-px, e->y()-py);
               clip.setRect(xPos, yPos, image->width(), image->height());
               rectDialog->drawShapeWithSettings(this, clip, shape);
               break;
         }                      
      }
   }
}

// Mouse release event handler
void MyMainWindow::mouseReleaseEvent(QMouseEvent* e)
{
   if( e->button() == Qt::LeftButton )
   {
      if ( image->isNull() ) {}//OnLoadImage();
      else 
      { 
         QPointArray a;
         QRect shape;
         QRect clip;

         // close active painter
         if( paint->isActive () )
         {
            paint->end();
         }
         switch( selectedbutton ){
            case DPen:  // drawing with the Pen tool
               paint->begin( imageLayers->currentLayerOnEdit() );  // begin painting onto picture   
               paint->setClipRect ( 0, 0, image->width(), image->height() ); // clipping
               paint->setPen( pendialog->pen ); // set the painter settings from the pen dialog
              
               // Set the array of points 
               a.setPoints( 3, dx - xPos, dy - yPos,
                               px - xPos, py - yPos,
                               e->x() - xPos, e->y() - yPos );
               paint->drawPolyline( a, 0, 3 );

               // update the cursor positions
               dx = px; dy = py;
               px = e->x(); py = e->y();

               paint->end();
               break;

            case DLine:  // drawing with the Line tool 
               // TODO 
               // draw line that links reference position and current mouse position onto the image, then update or reset reference position.
               clip.setRect(0, 0, image->width(), image->height());
               lineDialog->drawLineWithSettings(imageLayers->currentLayerOnEdit(), clip, e->x(), e->y(), true, -xPos, -yPos);
               break;
   
            case Drect:  // drawing with the Rectangle tool
               // TODO
               // draw a shape inside the clip area using with dialog settings => onto the widget
               shape.setRect(px, py, e->x()-px, e->y()-py);
               clip.setRect(xPos, yPos, image->width(), image->height());
               rectDialog->drawShapeWithSettings(this, clip, shape);
               // draw a shape inside the clip area using dialog settings => onto the image
               shape.setRect(px-xPos, py-yPos, e->x()-px, e->y()-py);
               clip.setRect(0, 0, image->width(), image->height());
               rectDialog->drawShapeWithSettings(imageLayers->currentLayerOnEdit(), clip, shape);
               break;

            case DFill:    // fill any shape with color. Follows dialog settings
               clip.setRect(0, 0, image->width(), image->height());
               fillDialog->fillEntireAreaWithSettings(imageLayers->currentLayerOnEdit(), clip, e->x()-xPos, e->y()-yPos);
               break;

            case DColorPicker:   // extracts color from mouse position, and stores it into foreground color or background color
               if (e->x()-xPos < 0 || e->x()-xPos > image->width() || e->y()-yPos < 0 || e->y()-yPos > image->height() )
                  break;
               QColor colorTemp(colorPickerDialog->extractColorAtTargetPos(image, e->x()-xPos, e->y()-yPos));
               // if color is valid (user clicks valid position), set front color or background color.
               if (colorTemp.isValid())
               {
                  if (colorPickerDialog->selectColorToForeground())
                     processChooseColor(colorTemp);
                  else
                     processChooseBGColor(colorTemp);
               }
               break;

         }     
                 
         paintbmp(1);
      }
   }
   mouseevent = 0; // reset the mouse event type
}

// Mouse double click event handler
void MyMainWindow::mouseDoubleClickEvent(QMouseEvent* e)
{
   // reset reference position for line dialog.
   mouseevent = 0; 
	lineDialog->setReferencePosition(0, 0);
}

////////////////////////////////////////////////
// Other user defined slots 
////////////////////////////////////////////////

void MyMainWindow::OnDockWindowPositionChanged()
{
   QDockArea* leftDockWin = leftDock();
   QDockArea* topDockWin = topDock();
   
   xPos = ((QWidget*)leftDockWin)->frameSize().width();
   yPos = menuBar()->height() + ((QWidget*)topDockWin)->frameSize().height();

   this->erase();
   paintbmp();
}
