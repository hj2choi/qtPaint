/****************************************************************************
** MyToolBar meta object code from reading C++ file 'my_toolbar.h'
**
** Created by Qt MOC ($Id: qt/moc_yacc.cpp   3.3.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "my_toolbar.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *MyToolBar::className() const
{
    return "MyToolBar";
}

QMetaObject *MyToolBar::metaObj = 0;
static QMetaObjectCleanUp cleanUp_MyToolBar( "MyToolBar", &MyToolBar::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString MyToolBar::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MyToolBar", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString MyToolBar::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MyToolBar", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* MyToolBar::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QToolBar::staticMetaObject();
    static const QUMethod signal_0 = {"OnPaint", 0, 0 };
    static const QMetaData signal_tbl[] = {
	{ "OnPaint()", &signal_0, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"MyToolBar", parentObject,
	0, 0,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_MyToolBar.setMetaObject( metaObj );
    return metaObj;
}

void* MyToolBar::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "MyToolBar" ) )
	return this;
    return QToolBar::qt_cast( clname );
}

// SIGNAL OnPaint
void MyToolBar::OnPaint()
{
    activate_signal( staticMetaObject()->signalOffset() + 0 );
}

bool MyToolBar::qt_invoke( int _id, QUObject* _o )
{
    return QToolBar::qt_invoke(_id,_o);
}

bool MyToolBar::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: OnPaint(); break;
    default:
	return QToolBar::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool MyToolBar::qt_property( int id, int f, QVariant* v)
{
    return QToolBar::qt_property( id, f, v);
}

bool MyToolBar::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
