/****************************************************************************
** Meta object code from reading C++ file 'mngfilemanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../MongoLib/files/mngfilemanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mngfilemanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Mongo__MngFileManager_t {
    QByteArrayData data[19];
    char stringdata0[310];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Mongo__MngFileManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Mongo__MngFileManager_t qt_meta_stringdata_Mongo__MngFileManager = {
    {
QT_MOC_LITERAL(0, 0, 21), // "Mongo::MngFileManager"
QT_MOC_LITERAL(1, 22, 12), // "FileIncoming"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 13), // "SafeFileHansz"
QT_MOC_LITERAL(4, 50, 12), // "FileReceived"
QT_MOC_LITERAL(5, 63, 13), // "FileCancelled"
QT_MOC_LITERAL(6, 77, 16), // "connectionClosed"
QT_MOC_LITERAL(7, 94, 19), // "connectionInitiated"
QT_MOC_LITERAL(8, 114, 16), // "connectionFailed"
QT_MOC_LITERAL(9, 131, 18), // "connectionReceived"
QT_MOC_LITERAL(10, 150, 13), // "updateManager"
QT_MOC_LITERAL(11, 164, 8), // "sendFile"
QT_MOC_LITERAL(12, 173, 19), // "transmissionStarted"
QT_MOC_LITERAL(13, 193, 17), // "transmissionEnded"
QT_MOC_LITERAL(14, 211, 18), // "incomingConnection"
QT_MOC_LITERAL(15, 230, 14), // "MngFileSocket*"
QT_MOC_LITERAL(16, 245, 17), // "handleServerError"
QT_MOC_LITERAL(17, 263, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(18, 292, 17) // "handleClientError"

    },
    "Mongo::MngFileManager\0FileIncoming\0\0"
    "SafeFileHansz\0FileReceived\0FileCancelled\0"
    "connectionClosed\0connectionInitiated\0"
    "connectionFailed\0connectionReceived\0"
    "updateManager\0sendFile\0transmissionStarted\0"
    "transmissionEnded\0incomingConnection\0"
    "MngFileSocket*\0handleServerError\0"
    "QAbstractSocket::SocketError\0"
    "handleClientError"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Mongo__MngFileManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,
       4,    1,   87,    2, 0x06 /* Public */,
       5,    1,   90,    2, 0x06 /* Public */,
       6,    0,   93,    2, 0x06 /* Public */,
       7,    0,   94,    2, 0x06 /* Public */,
       8,    0,   95,    2, 0x06 /* Public */,
       9,    0,   96,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,   97,    2, 0x08 /* Private */,
      11,    1,   98,    2, 0x08 /* Private */,
      12,    0,  101,    2, 0x08 /* Private */,
      13,    0,  102,    2, 0x08 /* Private */,
      14,    1,  103,    2, 0x08 /* Private */,
      16,    1,  106,    2, 0x08 /* Private */,
      18,    1,  109,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 15,    2,
    QMetaType::Void, 0x80000000 | 17,    2,
    QMetaType::Void, 0x80000000 | 17,    2,

       0        // eod
};

void Mongo::MngFileManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MngFileManager *_t = static_cast<MngFileManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->FileIncoming((*reinterpret_cast< SafeFileHansz(*)>(_a[1]))); break;
        case 1: _t->FileReceived((*reinterpret_cast< SafeFileHansz(*)>(_a[1]))); break;
        case 2: _t->FileCancelled((*reinterpret_cast< SafeFileHansz(*)>(_a[1]))); break;
        case 3: _t->connectionClosed(); break;
        case 4: _t->connectionInitiated(); break;
        case 5: _t->connectionFailed(); break;
        case 6: _t->connectionReceived(); break;
        case 7: _t->updateManager(); break;
        case 8: _t->sendFile((*reinterpret_cast< SafeFileHansz(*)>(_a[1]))); break;
        case 9: _t->transmissionStarted(); break;
        case 10: _t->transmissionEnded(); break;
        case 11: _t->incomingConnection((*reinterpret_cast< MngFileSocket*(*)>(_a[1]))); break;
        case 12: _t->handleServerError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 13: _t->handleClientError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        case 13:
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
            typedef void (MngFileManager::*_t)(SafeFileHansz );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MngFileManager::FileIncoming)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MngFileManager::*_t)(SafeFileHansz );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MngFileManager::FileReceived)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MngFileManager::*_t)(SafeFileHansz );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MngFileManager::FileCancelled)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (MngFileManager::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MngFileManager::connectionClosed)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (MngFileManager::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MngFileManager::connectionInitiated)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (MngFileManager::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MngFileManager::connectionFailed)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (MngFileManager::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MngFileManager::connectionReceived)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Mongo::MngFileManager::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Mongo__MngFileManager.data,
      qt_meta_data_Mongo__MngFileManager,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Mongo::MngFileManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Mongo::MngFileManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Mongo__MngFileManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Mongo::MngFileManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void Mongo::MngFileManager::FileIncoming(SafeFileHansz _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Mongo::MngFileManager::FileReceived(SafeFileHansz _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Mongo::MngFileManager::FileCancelled(SafeFileHansz _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Mongo::MngFileManager::connectionClosed()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Mongo::MngFileManager::connectionInitiated()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Mongo::MngFileManager::connectionFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void Mongo::MngFileManager::connectionReceived()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE