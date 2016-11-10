/****************************************/
//  QT Paint
//  File: LayeredPixmap.cpp
//  Author: Hong Joon Choi
//  Date: 01.04.2015
//  Description: the header file
//  -- LayeredPixmap class implementation.
//
/****************************************/


#include "LayeredPixmap.h"

using namespace std;


// constructor
LayeredPixmap::LayeredPixmap(const QWidget* parent, int count)
{
   
   parentWidget = parent;
   paint = new QPainter(parentWidget);

   layerCount = count;
   layers = new QPixmap*[count];
   for (int i=0; i<count; i++)
   {
      layers[i] = new QPixmap();
   }
   displayLayer = new bool[count];
   for (int i=0; i<count; i++)
      displayLayer[i]=true;
   currentIndexOnEdit=0;
}


// destructor
LayeredPixmap::LayeredPixmap(const LayeredPixmap& other)
{
   
   parentWidget = other.parentWidget;
   paint = new QPainter(parentWidget);
   layerCount = other.layerCount;
   
   layers = new QPixmap*[layerCount];
   for (int i=0; i<layerCount; i++)
   {
      layers[i] = new QPixmap(*other.layers[i]);
   }
   displayLayer = new bool[layerCount];
   for (int i=0; i<layerCount; i++)
      displayLayer[i]=other.displayLayer[i];
   currentIndexOnEdit=other.currentIndexOnEdit;
   //cout << "copy constructor called " << endl;
}

LayeredPixmap::~LayeredPixmap()
{
   clearAllLayers();
   delete paint;
   delete[] displayLayer;
}

void LayeredPixmap::clearAllLayers()
{
   for (int i=0; i<layerCount; i++)
   {
      if (layers[i]!=NULL){ delete layers[i];layers[i]=NULL;}
   }

}


////////////////////////////////////////////////
// Getter and setter functions
////////////////////////////////////////////////

int LayeredPixmap::getLayerCount() const
{
   return layerCount;
}
void LayeredPixmap::setCurrentLayerOnEdit(int index)
{
   currentIndexOnEdit = index;
}
int LayeredPixmap::getCurrentIndexOnEdit() const
{
   return currentIndexOnEdit;
}
// Both read and write are enabled.
QPixmap* LayeredPixmap::currentLayerOnEdit() const
{

   return layers[currentIndexOnEdit];
}

////////////////////////////////////////////////
// Feature implementations
////////////////////////////////////////////////

void LayeredPixmap::newImageLayersWithSize(int width, int height, const QColor& bgcolor)
{
   clearAllLayers();
   for (int i=0; i<layerCount-1; i++)
   {
      layers[i] = new QPixmap(width, height);
      layers[i]->fill(Qt::white);
   }
   // fill background color only for the last layer
   layers[layerCount-1] = new QPixmap(width, height);
   layers[layerCount-1]->fill(bgcolor);
}

void LayeredPixmap::resizeImageLayers(int width, int height, const QColor& bgcolor)
{
   for (int i=0; i<layerCount-1; i++)
   {
      // Create imageTemp, resize image filled with WHITE color.	
      QPixmap* imageTemp;
      imageTemp = new QPixmap(*layers[i]);
      imageTemp->resize(width, height);
      imageTemp->fill(Qt::white);
      
      // then, draw current image onto imageTemp.
      paint->begin(imageTemp);
      paint->drawPixmap(0, 0, *layers[i]);
      paint->end();

      delete layers[i];
      layers[i]=imageTemp;
   }
   // Create imageTemp, resize the LAST image filled with BACKGROUND color.	
   QPixmap* imageTemp;
   imageTemp = new QPixmap(*layers[layerCount-1]);
   imageTemp->resize(width, height);
   imageTemp->fill(bgcolor);
   
   // then, draw current image onto imageTemp.
   
   paint->begin(imageTemp);
   paint->drawPixmap(0, 0, *layers[layerCount-1]);
   paint->end();

   delete layers[layerCount-1];
   layers[layerCount-1]=imageTemp;

}


void LayeredPixmap::combineLayersToImage(QPixmap *image) const
{
   if (layers[0]==NULL || layers[0]->isNull()) return;
   
   if (image!=NULL){ delete image; image = NULL;}
   if( paint->isActive() )
      paint->end();
   
   // temporary pen for setting color for each pixel.
   QPen pen;

   // creates new image and initialize to white color.
   image = new QPixmap(*(layers[layerCount-1]));
   image->fill(Qt::white);


   // Begins painting all layers to image.
   paint->begin(image);
   for (int index=layerCount-1; index>=0; index--)
   {
      
      if (displayLayer[index])
      {
         QImage currentLayer = layers[index]->convertToImage();
         
         // for each layers.. copy pixel by pixel.
         for (int i=0; i<layers[index]->width(); i++)
         {
            for (int j=0; j<layers[index]->height(); j++)
            {
               if (Qt::white.rgb() != currentLayer.pixel(i,j))
               {
                  
                  pen.setColor(QColor(currentLayer.pixel(i,j)));
                  paint->setPen(pen);
                  paint->drawPoint(i,j);
                  
               }
            }
         }
      }
      
   }
   paint->end();
}

// returns rescaled image in specified index.
QPixmap* LayeredPixmap::getIconSizedImage(int index) const
{
   QPen pen;
   QPixmap* pix = new QPixmap(22,22);
   QImage imageTemp = layers[index]->convertToImage();
   QImage resizedImage = imageTemp.smoothScale(22,22);
   

   paint->begin(pix);
   for (int i=0; i<22; i++)
      for (int j=0; j<22; j++)
      {
         pen.setColor(QColor(resizedImage.pixel(i,j)));
         paint->setPen(pen);
         paint->drawPoint(i,j);
      }

   paint->end();
   return pix;
}
