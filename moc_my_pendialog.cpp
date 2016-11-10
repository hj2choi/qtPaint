/****************************************************************************
** MyPenDialog meta object code from reading C++ file 'my_pendialog.h'
**
** Created by Qt MOC ($Id: qt/moc_yacc.cpp   3.3.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "my_pendialog.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *MyPenDialog::className() const
{
    return "MyPenDialog";
}

QMetaObject *MyPenDialog::metaObj = 0;
static QMetaObjectCleanUp cleanUp_MyPenDialog( "MyPenDialog", &MyPenDialog::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString MyPenDialog::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MyPenDialog", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString MyPenDialog::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MyPenDialog", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* MyPenDialog::staticMetaObject()
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
    static const QMetaData slot_tbl[] = {
	{ "OnSetPenWidth(int)", &slot_0, QMetaData::Public },
	{ "OnSetCapStyle(int)", &slot_1, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"MyPenDialog", parentObject,
	slot_tbl, 2,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_MyPenDialog.setMetaObject( metaObj );
    return metaObj;
}

void* MyPenDialog::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "MyPenDialog" ) )
	return this;
    return QDialog::qt_cast( clname );
}

bool MyPenDialog::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: OnSetPenWidth((int)static_QUType_int.get(_o+1)); break;
    case 1: OnSetCapStyle((int)static_QUType_int.get(_o+1)); break;
    default:
	return QDialog::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool MyPenDialog::qt_emit( int _id, QUObject* _o )
{
    return QDialog::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool MyPenDialog::qt_property( int id, int f, QVariant* v)
{
    return QDialog::qt_property( id, f, v);
}

bool MyPenDialog::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
