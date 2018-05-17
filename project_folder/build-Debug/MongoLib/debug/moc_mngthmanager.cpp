/****************************************************************************
** Meta object code from reading C++ file 'mngthmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../MongoLib/mngthmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mngthmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Mongo__MngThManager_t {
    QByteArrayData data[18];
    char stringdata0[285];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Mongo__MngThManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Mongo__MngThManager_t qt_meta_stringdata_Mongo__MngThManager = {
    {
QT_MOC_LITERAL(0, 0, 19), // "Mongo::MngThManager"
QT_MOC_LITERAL(1, 20, 7), // "Message"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 15), // "SafeInstruction"
QT_MOC_LITERAL(4, 45, 13), // "FileProcessed"
QT_MOC_LITERAL(5, 59, 13), // "SafeFileHansz"
QT_MOC_LITERAL(6, 73, 19), // "FileSendingFinished"
QT_MOC_LITERAL(7, 93, 12), // "FileReceived"
QT_MOC_LITERAL(8, 106, 13), // "FileCancelled"
QT_MOC_LITERAL(9, 120, 16), // "connectionClosed"
QT_MOC_LITERAL(10, 137, 19), // "connectionInitiated"
QT_MOC_LITERAL(11, 157, 18), // "incomingConnection"
QT_MOC_LITERAL(12, 176, 16), // "MongoConnection*"
QT_MOC_LITERAL(13, 193, 12), // "incomingData"
QT_MOC_LITERAL(14, 206, 13), // "SafeByteArray"
QT_MOC_LITERAL(15, 220, 17), // "handleServerError"
QT_MOC_LITERAL(16, 238, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(17, 267, 17) // "handleClientError"

    },
    "Mongo::MngThManager\0Message\0\0"
    "SafeInstruction\0FileProcessed\0"
    "SafeFileHansz\0FileSendingFinished\0"
    "FileReceived\0FileCancelled\0connectionClosed\0"
    "connectionInitiated\0incomingConnection\0"
    "MongoConnection*\0incomingData\0"
    "SafeByteArray\0handleServerError\0"
    "QAbstractSocket::SocketError\0"
    "handleClientError"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Mongo__MngThManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       4,    1,   72,    2, 0x06 /* Public */,
       6,    1,   75,    2, 0x06 /* Public */,
       7,    1,   78,    2, 0x06 /* Public */,
       8,    1,   81,    2, 0x06 /* Public */,
       9,    0,   84,    2, 0x06 /* Public */,
      10,    0,   85,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    1,   86,    2, 0x0a /* Public */,
      13,    1,   89,    2, 0x08 /* Private */,
      15,    1,   92,    2, 0x08 /* Private */,
      17,    1,   95,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 12,    2,
    QMetaType::Void, 0x80000000 | 14,    2,
    QMetaType::Void, 0x80000000 | 16,    2,
    QMetaType::Void, 0x80000000 | 16,    2,

       0        // eod
};

void Mongo::MngThManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MngThManager *_t = static_cast<MngThManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Message((*reinterpret_cast< SafeInstruction(*)>(_a[1]))); break;
        case 1: _t->FileProcessed((*reinterpret_cast< SafeFileHansz(*)>(_a[1]))); break;
        case 2: _t->FileSendingFinished((*reinterpret_cast< SafeFileHansz(*)>(_a[1]))); break;
        case 3: _t->FileReceived((*reinterpret_cast< SafeFileHansz(*)>(_a[1]))); break;
        case 4: _t->FileCancelled((*reinterpret_cast< SafeFileHansz(*)>(_a[1]))); break;
        case 5: _t->connectionClosed(); break;
        case 6: _t->connectionInitiated(); break;
        case 7: _t->incomingConnection((*reinterpret_cast< MongoConnection*(*)>(_a[1]))); break;
        case 8: _t->incomingData((*reinterpret_cast< const SafeByteArray(*)>(_a[1]))); break;
        case 9: _t->handleServerError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 10: _t->handleClientError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< MongoConnection* >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        case 10:
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
            typedef void (MngThManager::*_t)(SafeInstruction );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MngThManager::Message)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MngThManager::*_t)(SafeFileHansz );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MngThManager::FileProcessed)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MngThManager::*_t)(SafeFileHansz );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MngThManager::FileSendingFinished)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (MngThManager::*_t)(SafeFileHansz );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MngThManager::FileReceived)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (MngThManager::*_t)(SafeFileHansz );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MngThManager::FileCancelled)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (MngThManager::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MngThManager::connectionClosed)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (MngThManager::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MngThManager::connectionInitiated)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Mongo::MngThManager::staticMetaObject = {
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
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void Mongo::MngThManager::Message(SafeInstruction _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Mongo::MngThManager::FileProcessed(SafeFileHansz _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Mongo::MngThManager::FileSendingFinished(SafeFileHansz _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Mongo::MngThManager::FileReceived(SafeFileHansz _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Mongo::MngThManager::FileCancelled(SafeFileHansz _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Mongo::MngThManager::connectionClosed()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void Mongo::MngThManager::connectionInitiated()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
