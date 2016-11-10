/****************************************************************************
** MyMainWindow meta object code from reading C++ file 'my_widget.h'
**
** Created by Qt MOC ($Id: qt/moc_yacc.cpp   3.3.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "my_widget.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *MyMainWindow::className() const
{
    return "MyMainWindow";
}

QMetaObject *MyMainWindow::metaObj = 0;
static QMetaObjectCleanUp cleanUp_MyMainWindow( "MyMainWindow", &MyMainWindow::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString MyMainWindow::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MyMainWindow", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString MyMainWindow::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MyMainWindow", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* MyMainWindow::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QMainWindow::staticMetaObject();
    static const QUMethod slot_0 = {"OnNewImage", 0, 0 };
    static const QUMethod slot_1 = {"OnLoadImage", 0, 0 };
    static const QUMethod slot_2 = {"OnSaveImage", 0, 0 };
    static const QUMethod slot_3 = {"OnChooseColor", 0, 0 };
    static const QUMethod slot_4 = {"OnChooseBGColor", 0, 0 };
    static const QUMethod slot_5 = {"OnExit", 0, 0 };
    static const QUMethod slot_6 = {"OnEditUndo", 0, 0 };
    static const QUMethod slot_7 = {"OnEditRedo", 0, 0 };
    static const QUMethod slot_8 = {"OnEditResize", 0, 0 };
    static const QUMethod slot_9 = {"OnEditClearAll", 0, 0 };
    static const QUMethod slot_10 = {"OnViewToolBar", 0, 0 };
    static const QUMethod slot_11 = {"OnAbout", 0, 0 };
    static const QUMethod slot_12 = {"OnDockWindowPositionChanged", 0, 0 };
    static const QUMethod slot_13 = {"OnChoosePen", 0, 0 };
    static const QUMethod slot_14 = {"OnChooseLine", 0, 0 };
    static const QUMethod slot_15 = {"OnChooseEraser", 0, 0 };
    static const QUMethod slot_16 = {"OnChooseRect", 0, 0 };
    static const QUMethod slot_17 = {"OnChooseFill", 0, 0 };
    static const QUMethod slot_18 = {"OnChooseColorPicker", 0, 0 };
    static const QUMethod slot_19 = {"OnChooseLayer", 0, 0 };
    static const QUMethod slot_20 = {"OnChangeLayerDisplay", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "OnNewImage()", &slot_0, QMetaData::Public },
	{ "OnLoadImage()", &slot_1, QMetaData::Public },
	{ "OnSaveImage()", &slot_2, QMetaData::Public },
	{ "OnChooseColor()", &slot_3, QMetaData::Public },
	{ "OnChooseBGColor()", &slot_4, QMetaData::Public },
	{ "OnExit()", &slot_5, QMetaData::Public },
	{ "OnEditUndo()", &slot_6, QMetaData::Public },
	{ "OnEditRedo()", &slot_7, QMetaData::Public },
	{ "OnEditResize()", &slot_8, QMetaData::Public },
	{ "OnEditClearAll()", &slot_9, QMetaData::Public },
	{ "OnViewToolBar()", &slot_10, QMetaData::Public },
	{ "OnAbout()", &slot_11, QMetaData::Public },
	{ "OnDockWindowPositionChanged()", &slot_12, QMetaData::Public },
	{ "OnChoosePen()", &slot_13, QMetaData::Public },
	{ "OnChooseLine()", &slot_14, QMetaData::Public },
	{ "OnChooseEraser()", &slot_15, QMetaData::Public },
	{ "OnChooseRect()", &slot_16, QMetaData::Public },
	{ "OnChooseFill()", &slot_17, QMetaData::Public },
	{ "OnChooseColorPicker()", &slot_18, QMetaData::Public },
	{ "OnChooseLayer()", &slot_19, QMetaData::Public },
	{ "OnChangeLayerDisplay()", &slot_20, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"MyMainWindow", parentObject,
	slot_tbl, 21,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_MyMainWindow.setMetaObject( metaObj );
    return metaObj;
}

void* MyMainWindow::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "MyMainWindow" ) )
	return this;
    return QMainWindow::qt_cast( clname );
}

bool MyMainWindow::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: OnNewImage(); break;
    case 1: OnLoadImage(); break;
    case 2: OnSaveImage(); break;
    case 3: OnChooseColor(); break;
    case 4: OnChooseBGColor(); break;
    case 5: OnExit(); break;
    case 6: OnEditUndo(); break;
    case 7: OnEditRedo(); break;
    case 8: OnEditResize(); break;
    case 9: OnEditClearAll(); break;
    case 10: OnViewToolBar(); break;
    case 11: OnAbout(); break;
    case 12: OnDockWindowPositionChanged(); break;
    case 13: OnChoosePen(); break;
    case 14: OnChooseLine(); break;
    case 15: OnChooseEraser(); break;
    case 16: OnChooseRect(); break;
    case 17: OnChooseFill(); break;
    case 18: OnChooseColorPicker(); break;
    case 19: OnChooseLayer(); break;
    case 20: OnChangeLayerDisplay(); break;
    default:
	return QMainWindow::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool MyMainWindow::qt_emit( int _id, QUObject* _o )
{
    return QMainWindow::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool MyMainWindow::qt_property( int id, int f, QVariant* v)
{
    return QMainWindow::qt_property( id, f, v);
}

bool MyMainWindow::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
