/****************************************************************************
** MyRectDialog meta object code from reading C++ file 'my_rectdialog.h'
**
** Created by Qt MOC ($Id: qt/moc_yacc.cpp   3.3.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "my_rectdialog.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *MyRectDialog::className() const
{
    return "MyRectDialog";
}

QMetaObject *MyRectDialog::metaObj = 0;
static QMetaObjectCleanUp cleanUp_MyRectDialog( "MyRectDialog", &MyRectDialog::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString MyRectDialog::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MyRectDialog", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString MyRectDialog::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MyRectDialog", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* MyRectDialog::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QDialog::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "w", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"OnSetBoundaryWidth", 1, param_slot_0 };
    static const QUParameter param_slot_1[] = {
	{ "type", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_1 = {"OnSetDrawType", 1, param_slot_1 };
    static const QUParameter param_slot_2[] = {
	{ "type", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_2 = {"OnSetBoundaryStyle", 1, param_slot_2 };
    static const QUParameter param_slot_3[] = {
	{ "type", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_3 = {"OnSetFillStyle", 1, param_slot_3 };
    static const QUParameter param_slot_4[] = {
	{ "type", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_4 = {"OnSetFillColor", 1, param_slot_4 };
    static const QUParameter param_slot_5[] = {
	{ "type", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_5 = {"OnSetBounaryJoinStyle", 1, param_slot_5 };
    static const QMetaData slot_tbl[] = {
	{ "OnSetBoundaryWidth(int)", &slot_0, QMetaData::Public },
	{ "OnSetDrawType(int)", &slot_1, QMetaData::Public },
	{ "OnSetBoundaryStyle(int)", &slot_2, QMetaData::Public },
	{ "OnSetFillStyle(int)", &slot_3, QMetaData::Public },
	{ "OnSetFillColor(int)", &slot_4, QMetaData::Public },
	{ "OnSetBounaryJoinStyle(int)", &slot_5, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"MyRectDialog", parentObject,
	slot_tbl, 6,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_MyRectDialog.setMetaObject( metaObj );
    return metaObj;
}

void* MyRectDialog::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "MyRectDialog" ) )
	return this;
    return QDialog::qt_cast( clname );
}

bool MyRectDialog::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: OnSetBoundaryWidth((int)static_QUType_int.get(_o+1)); break;
    case 1: OnSetDrawType((int)static_QUType_int.get(_o+1)); break;
    case 2: OnSetBoundaryStyle((int)static_QUType_int.get(_o+1)); break;
    case 3: OnSetFillStyle((int)static_QUType_int.get(_o+1)); break;
    case 4: OnSetFillColor((int)static_QUType_int.get(_o+1)); break;
    case 5: OnSetBounaryJoinStyle((int)static_QUType_int.get(_o+1)); break;
    default:
	return QDialog::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool MyRectDialog::qt_emit( int _id, QUObject* _o )
{
    return QDialog::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool MyRectDialog::qt_property( int id, int f, QVariant* v)
{
    return QDialog::qt_property( id, f, v);
}

bool MyRectDialog::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
