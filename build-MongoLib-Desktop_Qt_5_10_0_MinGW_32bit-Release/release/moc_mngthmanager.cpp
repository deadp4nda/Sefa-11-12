/****************************************************************************
** Meta object code from reading C++ file 'mngthmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MongoLib/mngthmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mngthmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Mongo__MngThManager_t {
    QByteArrayData data[13];
    char stringdata0[200];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Mongo__MngThManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Mongo__MngThManager_t qt_meta_stringdata_Mongo__MngThManager = {
    {
QT_MOC_LITERAL(0, 0, 19), // "Mongo::MngThManager"
QT_MOC_LITERAL(1, 20, 7), // "message"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 10), // "DataHansz*"
QT_MOC_LITERAL(4, 40, 10), // "newMessage"
QT_MOC_LITERAL(5, 51, 16), // "connectionClosed"
QT_MOC_LITERAL(6, 68, 19), // "connectionInitiated"
QT_MOC_LITERAL(7, 88, 18), // "incomingConnection"
QT_MOC_LITERAL(8, 107, 10), // "MngClient*"
QT_MOC_LITERAL(9, 118, 16), // "handleNewMessage"
QT_MOC_LITERAL(10, 135, 17), // "handleServerError"
QT_MOC_LITERAL(11, 153, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(12, 182, 17) // "handleClientError"

    },
    "Mongo::MngThManager\0message\0\0DataHansz*\0"
    "newMessage\0connectionClosed\0"
    "connectionInitiated\0incomingConnection\0"
    "MngClient*\0handleNewMessage\0"
    "handleServerError\0QAbstractSocket::SocketError\0"
    "handleClientError"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Mongo__MngThManager[] = {

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
       5,    0,   60,    2, 0x06 /* Public */,
       6,    0,   61,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   62,    2, 0x0a /* Public */,
       9,    1,   65,    2, 0x0a /* Public */,
      10,    1,   68,    2, 0x08 /* Private */,
      12,    1,   71,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, 0x80000000 | 11,    2,
    QMetaType::Void, 0x80000000 | 11,    2,

       0        // eod
};

void Mongo::MngThManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MngThManager *_t = static_cast<MngThManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->message((*reinterpret_cast< DataHansz*(*)>(_a[1]))); break;
        case 1: _t->newMessage((*reinterpret_cast< DataHansz*(*)>(_a[1]))); break;
        case 2: _t->connectionClosed(); break;
        case 3: _t->connectionInitiated(); break;
        case 4: _t->incomingConnection((*reinterpret_cast< MngClient*(*)>(_a[1]))); break;
        case 5: _t->handleNewMessage((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 6: _t->handleServerError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 7: _t->handleClientError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (MngThManager::*_t)(DataHansz * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MngThManager::message)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MngThManager::*_t)(DataHansz * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MngThManager::newMessage)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MngThManager::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MngThManager::connectionClosed)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (MngThManager::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MngThManager::connectionInitiated)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject Mongo::MngThManager::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Mongo__MngThManager.data,
      qt_meta_data_Mongo__MngThManager,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Mongo::MngThManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Mongo::MngThManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Mongo__MngThManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Mongo::MngThManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void Mongo::MngThManager::message(DataHansz * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Mongo::MngThManager::newMessage(DataHansz * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Mongo::MngThManager::connectionClosed()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Mongo::MngThManager::connectionInitiated()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
