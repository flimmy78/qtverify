/****************************************************************************
** Meta object code from reading C++ file 'serialportset.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../qtVerify/include/serialportset.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serialportset.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SerialPortSet[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x08,
      27,   14,   14,   14, 0x08,
      53,   14,   14,   14, 0x08,
      80,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SerialPortSet[] = {
    "SerialPortSet\0\0readMyCom()\0"
    "on_openMyComBtn_clicked()\0"
    "on_closeMyComBtn_clicked()\0"
    "on_sendMsgBtn_clicked()\0"
};

void SerialPortSet::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SerialPortSet *_t = static_cast<SerialPortSet *>(_o);
        switch (_id) {
        case 0: _t->readMyCom(); break;
        case 1: _t->on_openMyComBtn_clicked(); break;
        case 2: _t->on_closeMyComBtn_clicked(); break;
        case 3: _t->on_sendMsgBtn_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData SerialPortSet::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SerialPortSet::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SerialPortSet,
      qt_meta_data_SerialPortSet, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SerialPortSet::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SerialPortSet::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SerialPortSet::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SerialPortSet))
        return static_cast<void*>(const_cast< SerialPortSet*>(this));
    return QWidget::qt_metacast(_clname);
}

int SerialPortSet::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
