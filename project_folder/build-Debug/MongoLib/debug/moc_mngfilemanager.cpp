/****************************************************************************
** Meta object code from reading C++ file 'mngfilemanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../MongoLib/mngfilemanager.h"
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
    QByteArrayData data[9];
    char stringdata0[144];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Mongo__MngFileManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Mongo__MngFileManager_t qt_meta_stringdata_Mongo__MngFileManager = {
    {
QT_MOC_LITERAL(0, 0, 21), // "Mongo::MngFileManager"
QT_MOC_LITERAL(1, 22, 14), // "processNewFile"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 13), // "SafeFileHansz"
QT_MOC_LITERAL(4, 52, 15), // "sendingFinished"
QT_MOC_LITERAL(5, 68, 15), // "newFileReceived"
QT_MOC_LITERAL(6, 84, 21), // "transmissionCancelled"
QT_MOC_LITERAL(7, 106, 20), // "receiveNewConnection"
QT_MOC_LITERAL(8, 127, 16) // "MongoFileSocket*"

    },
    "Mongo::MngFileManager\0processNewFile\0"
    "\0SafeFileHansz\0sendingFinished\0"
    "newFileReceived\0transmissionCancelled\0"
    "receiveNewConnection\0MongoFileSocket*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Mongo__MngFileManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    1,   42,    2, 0x06 /* Public */,
       5,    1,   45,    2, 0x06 /* Public */,
       6,    1,   48,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 8,    2,

       0        // eod
};

void Mongo::MngFileManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MngFileManager *_t = static_cast<MngFileManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->processNewFile((*reinterpret_cast< SafeFileHansz(*)>(_a[1]))); break;
        case 1: _t->sendingFinished((*reinterpret_cast< SafeFileHansz(*)>(_a[1]))); break;
        case 2: _t->newFileReceived((*reinterpret_cast< SafeFileHansz(*)>(_a[1]))); break;
        case 3: _t->transmissionCancelled((*reinterpret_cast< SafeFileHansz(*)>(_a[1]))); break;
        case 4: _t->receiveNewConnection((*reinterpret_cast< MongoFileSocket*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (MngFileManager::*_t)(SafeFileHansz );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MngFileManager::processNewFile)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MngFileManager::*_t)(SafeFileHansz );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MngFileManager::sendingFinished)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MngFileManager::*_t)(SafeFileHansz );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MngFileManager::newFileReceived)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (MngFileManager::*_t)(SafeFileHansz );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MngFileManager::transmissionCancelled)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Mongo::MngFileManager::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_Mongo__MngFileManager.data,
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
    return QThread::qt_metacast(_clname);
}

int Mongo::MngFileManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void Mongo::MngFileManager::processNewFile(SafeFileHansz _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Mongo::MngFileManager::sendingFinished(SafeFileHansz _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Mongo::MngFileManager::newFileReceived(SafeFileHansz _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Mongo::MngFileManager::transmissionCancelled(SafeFileHansz _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
