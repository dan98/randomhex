/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      35,   11,   11,   11, 0x08,
      66,   11,   11,   11, 0x08,
      93,   11,   11,   11, 0x08,
     120,   11,   11,   11, 0x08,
     148,   11,   11,   11, 0x08,
     171,   11,   11,   11, 0x08,
     201,   11,   11,   11, 0x08,
     226,   11,   11,   11, 0x08,
     249,   11,   11,   11, 0x08,
     274,  272,   11,   11, 0x08,
     288,  272,   11,   11, 0x08,
     302,  272,   11,   11, 0x08,
     316,  272,   11,   11, 0x08,
     336,  272,   11,   11, 0x08,
     357,  272,   11,   11, 0x08,
     374,  272,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0on_fillBoard_clicked()\0"
    "on_articulationPoint_clicked()\0"
    "on_simulatePivot_clicked()\0"
    "on_fillAndPivots_clicked()\0"
    "on_nextRandomTurn_clicked()\0"
    "on_resetGame_clicked()\0"
    "on_startAlternative_clicked()\0"
    "on_startRandom_clicked()\0"
    "on_moveBlack_clicked()\0on_moveWhite_clicked()\0"
    "v\0setMProb(int)\0setMSize(int)\0"
    "setSSize(int)\0setWaitTimeSim(int)\0"
    "setGameWaitTime(int)\0setGameProb(int)\0"
    "setGameSize(int)\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->on_fillBoard_clicked(); break;
        case 1: _t->on_articulationPoint_clicked(); break;
        case 2: _t->on_simulatePivot_clicked(); break;
        case 3: _t->on_fillAndPivots_clicked(); break;
        case 4: _t->on_nextRandomTurn_clicked(); break;
        case 5: _t->on_resetGame_clicked(); break;
        case 6: _t->on_startAlternative_clicked(); break;
        case 7: _t->on_startRandom_clicked(); break;
        case 8: _t->on_moveBlack_clicked(); break;
        case 9: _t->on_moveWhite_clicked(); break;
        case 10: _t->setMProb((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->setMSize((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->setSSize((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->setWaitTimeSim((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->setGameWaitTime((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->setGameProb((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->setGameSize((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}
QT_END_MOC_NAMESPACE