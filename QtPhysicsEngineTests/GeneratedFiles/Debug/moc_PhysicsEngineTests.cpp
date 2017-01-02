/****************************************************************************
** Meta object code from reading C++ file 'PhysicsEngineTests.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PhysicsEngineTests.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PhysicsEngineTests.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PhysicsEngineTests_t {
    QByteArrayData data[11];
    char stringdata0[174];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PhysicsEngineTests_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PhysicsEngineTests_t qt_meta_stringdata_PhysicsEngineTests = {
    {
QT_MOC_LITERAL(0, 0, 18), // "PhysicsEngineTests"
QT_MOC_LITERAL(1, 19, 12), // "initTestCase"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 11), // "testXMLRead"
QT_MOC_LITERAL(4, 45, 18), // "testXMLReadFailure"
QT_MOC_LITERAL(5, 64, 16), // "testXMLRoundTrip"
QT_MOC_LITERAL(6, 81, 16), // "testRayCollision"
QT_MOC_LITERAL(7, 98, 17), // "testAABBCollision"
QT_MOC_LITERAL(8, 116, 22), // "testLinePlaneCollision"
QT_MOC_LITERAL(9, 139, 18), // "testUnitConversion"
QT_MOC_LITERAL(10, 158, 15) // "cleanupTestCase"

    },
    "PhysicsEngineTests\0initTestCase\0\0"
    "testXMLRead\0testXMLReadFailure\0"
    "testXMLRoundTrip\0testRayCollision\0"
    "testAABBCollision\0testLinePlaneCollision\0"
    "testUnitConversion\0cleanupTestCase"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PhysicsEngineTests[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x08 /* Private */,
       3,    0,   60,    2, 0x08 /* Private */,
       4,    0,   61,    2, 0x08 /* Private */,
       5,    0,   62,    2, 0x08 /* Private */,
       6,    0,   63,    2, 0x08 /* Private */,
       7,    0,   64,    2, 0x08 /* Private */,
       8,    0,   65,    2, 0x08 /* Private */,
       9,    0,   66,    2, 0x08 /* Private */,
      10,    0,   67,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PhysicsEngineTests::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PhysicsEngineTests *_t = static_cast<PhysicsEngineTests *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->initTestCase(); break;
        case 1: _t->testXMLRead(); break;
        case 2: _t->testXMLReadFailure(); break;
        case 3: _t->testXMLRoundTrip(); break;
        case 4: _t->testRayCollision(); break;
        case 5: _t->testAABBCollision(); break;
        case 6: _t->testLinePlaneCollision(); break;
        case 7: _t->testUnitConversion(); break;
        case 8: _t->cleanupTestCase(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject PhysicsEngineTests::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PhysicsEngineTests.data,
      qt_meta_data_PhysicsEngineTests,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PhysicsEngineTests::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PhysicsEngineTests::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PhysicsEngineTests.stringdata0))
        return static_cast<void*>(const_cast< PhysicsEngineTests*>(this));
    return QObject::qt_metacast(_clname);
}

int PhysicsEngineTests::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
