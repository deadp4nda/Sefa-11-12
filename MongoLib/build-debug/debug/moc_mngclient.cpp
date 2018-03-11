/****************************************************************************
** Meta object code from reading C++ file 'mngclient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mngclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mngclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Mongo__MngClient_t {
    QByteArrayData data[13];
    char stringdata0[160];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Mongo__MngClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Mongo__MngClient_t qt_meta_stringdata_Mongo__MngClient = {
    {
QT_MOC_LITERAL(0, 0, 16), // "Mongo::MngClient"
QT_MOC_LITERAL(1, 17, 10), // "newMessage"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 10), // "DataHansz*"
QT_MOC_LITERAL(4, 40, 7), // "newFile"
QT_MOC_LITERAL(5, 48, 10), // "FileHansz*"
QT_MOC_LITERAL(6, 59, 14), // "newInstruction"
QT_MOC_LITERAL(7, 74, 17), // "InstructionHansz*"
QT_MOC_LITERAL(8, 92, 12), // "newUndefined"
QT_MOC_LITERAL(9, 105, 8), // "sendFile"
QT_MOC_LITERAL(10, 114, 15), // "sendInstruction"
QT_MOC_LITERAL(11, 130, 13), // "sendUndefined"
QT_MOC_LITERAL(12, 144, 15) // "handleReadyRead"

    },
    "Mongo::MngClient\0newMessage\0\0DataHansz*\0"
    "newFile\0FileHansz*\0newInstruction\0"
    "InstructionHansz*\0newUndefined\0sendFile\0"
    "sendInstruction\0sendUndefined\0"
    "handleReadyRead"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Mongo__MngClient[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    1,   57,    2, 0x06 /* Public */,
       6,    1,   60,    2, 0x06 /* Public */,
       8,    1,   63,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   66,    2, 0x0a /* Public */,
      10,    1,   69,    2, 0x0a /* Public */,
      11,    1,   72,    2, 0x0a /* Public */,
      12,    0,   75,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Bool, 0x80000000 | 5,    2,
    QMetaType::Bool, 0x80000000 | 7,    2,
    QMetaType::Bool, 0x80000000 | 3,    2,
    QMetaType::Void,

       0        // eod
};

void Mongo::MngClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MngClient *_t = static_cast<MngClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newMessage((*reinterpret_cast< DataHansz*(*)>(_a[1]))); break;
        case 1: _t->newFile((*reinterpret_cast< FileHansz*(*)>(_a[1]))); break;
        case 2: _t->newInstruction((*reinterpret_cast< InstructionHansz*(*)>(_a[1]))); break;
        case 3: _t->newUndefined((*reinterpret_cast< DataHansz*(*)>(_a[1]))); break;
        case 4: { bool _r = _t->sendFile((*reinterpret_cast< FileHansz*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 5: { bool _r = _t->sendInstruction((*reinterpret_cast< InstructionHansz*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 6: { bool _r = _t->sendUndefined((*reinterpret_cast< DataHansz*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 7: _t->handleReadyRead(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (MngClient::*_t)(DataHansz * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MngClient::newMessage)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MngClient::*_t)(FileHansz * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MngClient::newFile)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MngClient::*_t)(InstructionHansz * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MngClient::newInstruction)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (MngClient::*_t)(DataHansz * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MngClient::newUndefined)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject Mongo::MngClient::staticMetaObject = {
    { &QTcpSocket::staticMetaObject, qt_meta_stringdata_Mongo__MngClient.data,
      qt_meta_data_Mongo__MngClient,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Mongo::MngClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Mongo::MngClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Mongo__MngClient.stringdata0))
        return static_cast<void*>(this);
    return QTcpSocket::qt_metacast(_clname);
}

int Mongo::MngClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpSocket::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void Mongo::MngClient::newMessage(DataHansz * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Mongo::MngClient::newFile(FileHansz * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Mongo::MngClient::newInstruction(InstructionHansz * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Mongo::MngClient::newUndefined(DataHansz * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
