/****************************************************************************
** MyFillDialog meta object code from reading C++ file 'my_filldialog.h'
**
** Created by Qt MOC ($Id: qt/moc_yacc.cpp   3.3.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "my_filldialog.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *MyFillDialog::className() const
{
    return "MyFillDialog";
}

QMetaObject *MyFillDialog::metaObj = 0;
static QMetaObjectCleanUp cleanUp_MyFillDialog( "MyFillDialog", &MyFillDialog::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString MyFillDialog::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MyFillDialog", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString MyFillDialog::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MyFillDialog", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* MyFillDialog::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QDialog::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "type", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"OnSetFillColor", 1, param_slot_0 };
    static const QMetaData slot_tbl[] = {
	{ "OnSetFillColor(int)", &slot_0, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"MyFillDialog", parentObject,
	slot_tbl, 1,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_MyFillDialog.setMetaObject( metaObj );
    return metaObj;
}

void* MyFillDialog::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "MyFillDialog" ) )
	return this;
    return QDialog::qt_cast( clname );
}

bool MyFillDialog::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: OnSetFillColor((int)static_QUType_int.get(_o+1)); break;
    default:
	return QDialog::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool MyFillDialog::qt_emit( int _id, QUObject* _o )
{
    return QDialog::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool MyFillDialog::qt_property( int id, int f, QVariant* v)
{
    return QDialog::qt_property( id, f, v);
}

bool MyFillDialog::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
