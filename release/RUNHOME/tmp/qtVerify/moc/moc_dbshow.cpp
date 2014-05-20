/****************************************************************************
** Meta object code from reading C++ file 'dbshow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../qtVerify/include/dbshow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dbshow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DbShow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x08,
      35,    7,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DbShow[] = {
    "DbShow\0\0slotConnectMySqlDataBase()\0"
    "slotQueryData()\0"
};

void DbShow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DbShow *_t = static_cast<DbShow *>(_o);
        switch (_id) {
        case 0: _t->slotConnectMySqlDataBase(); break;
        case 1: _t->slotQueryData(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData DbShow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DbShow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DbShow,
      qt_meta_data_DbShow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DbShow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DbShow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DbShow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DbShow))
        return static_cast<void*>(const_cast< DbShow*>(this));
    return QWidget::qt_metacast(_clname);
}

int DbShow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
