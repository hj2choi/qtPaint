/****************************************************************************
** MyLineDialog meta object code from reading C++ file 'my_linedialog.h'
**
** Created by Qt MOC ($Id: qt/moc_yacc.cpp   3.3.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "my_linedialog.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *MyLineDialog::className() const
{
    return "MyLineDialog";
}

QMetaObject *MyLineDialog::metaObj = 0;
static QMetaObjectCleanUp cleanUp_MyLineDialog( "MyLineDialog", &MyLineDialog::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString MyLineDialog::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MyLineDialog", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString MyLineDialog::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MyLineDialog", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* MyLineDialog::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QDialog::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "w", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"OnSetPenWidth", 1, param_slot_0 };
    static const QUParameter param_slot_1[] = {
	{ "type", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_1 = {"OnSetCapStyle", 1, param_slot_1 };
    static const QUParameter param_slot_2[] = {
	{ "type", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_2 = {"OnSetLineStyle", 1, param_slot_2 };
    static const QUParameter param_slot_3[] = {
	{ "type", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_3 = {"OnSetLineType", 1, param_slot_3 };
    static const QMetaData slot_tbl[] = {
	{ "OnSetPenWidth(int)", &slot_0, QMetaData::Public },
	{ "OnSetCapStyle(int)", &slot_1, QMetaData::Public },
	{ "OnSetLineStyle(int)", &slot_2, QMetaData::Public },
	{ "OnSetLineType(int)", &slot_3, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"MyLineDialog", parentObject,
	slot_tbl, 4,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_MyLineDialog.setMetaObject( metaObj );
    return metaObj;
}

void* MyLineDialog::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "MyLineDialog" ) )
	return this;
    return QDialog::qt_cast( clname );
}

bool MyLineDialog::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: OnSetPenWidth((int)static_QUType_int.get(_o+1)); break;
    case 1: OnSetCapStyle((int)static_QUType_int.get(_o+1)); break;
    case 2: OnSetLineStyle((int)static_QUType_int.get(_o+1)); break;
    case 3: OnSetLineType((int)static_QUType_int.get(_o+1)); break;
    default:
	return QDialog::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool MyLineDialog::qt_emit( int _id, QUObject* _o )
{
    return QDialog::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool MyLineDialog::qt_property( int id, int f, QVariant* v)
{
    return QDialog::qt_property( id, f, v);
}

bool MyLineDialog::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
