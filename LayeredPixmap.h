/****************************************/
//  QT Paint
//  File: LayeredPixmap.h
//  Author: Hong Joon Choi
//  Date: 01.04.2015
//  Description: the header file
//  -- LayeredPixmap class declaration. Derived by QPixmap class.
//     Stores array of images and useful properties.
//     Image layer acts as set of transparent papers with reference of white color. (CONCISE WHITE COLOR (#ffffff) IS SET TO BE TRANSPARENT)
//
/****************************************/

#include <iostream>
#include <qmainwindow.h>
#include <qmessagebox.h>
#include <qpopupmenu.h>
#include <qapplication.h>
#include <qpushbutton.h>
#include <qpen.h>
#include <qslider.h> 
#include <qpainter.h>
#include <qdialog.h>
#include <qlabel.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>
#include <qcolor.h>
#include <qpaintdevice.h>
#include <qimage.h>
#ifndef _LAYEREDPIXMAP_H
#define _LAYEREDPIXMAP_H

class LayeredPixmap
{



public :
   // public array of boolean variables storing wheter to show or hide layer.
   bool* displayLayer;
   
   /** constructor and distructors */
   LayeredPixmap(const QWidget* parent, int count);
   LayeredPixmap(const LayeredPixmap& other);
   ~LayeredPixmap();
   void clearAllLayers();

   /** getter and setter functions */
   int getLayerCount() const;
   void setCurrentLayerOnEdit(int);
   int getCurrentIndexOnEdit() const;
   // Returns the reference of current layer for edit.
   QPixmap* currentLayerOnEdit() const;

   /**
   * @brief Clears current image layers and replaces with new image of given width and height. Layer in last order is filled with bgcolor
   * @param width: image width for individual layers.
   * @param height: image height for individual layers.
   * @param bgcolor: background color to initiate image with. Only last layer is filed with background color.
   * @retval none
   */
   void newImageLayersWithSize(int width, int height, const QColor& bgcolor);

   /**
   * @brief Resizes all images in layer with given width and height. Whereas other layers are initialized with white color, last layer in order is initialized with bgcolor (only in the case of expansion)
   * @param width: image width for individual layers.
   * @param height: image height for individual layers.
   * @param bgcolor: background color to initiate image with. Only last layer is resized with background color.
   * @retval none
   */
   void resizeImageLayers(int width, int height, const QColor& bgcolor);

   /**
   * @brief Combines all layers to one image for it to be displayed on main widget.
   * @param image: image to be overwritten
   * @retval none
   */
   void combineLayersToImage(QPixmap *image) const;

   /**
   * @brief Creates rescaled image of size 23*23 for layer icon on toolbar.
   * @param index: layer index to work with.
   * @retval QPixmap : QPixmap image of the size precisely 23*23
   */
   QPixmap* getIconSizedImage(int index) const;





private :
   /** Pointer for parent widget. */
   const QWidget* parentWidget;

   /** Painter object for paint operations */
   QPainter* paint;


   /** array of QPixmap images, including array size and current index */
   QPixmap** layers;
   int layerCount;
   int currentIndexOnEdit;
};











#endif
