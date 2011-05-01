/****************************************************************************
** Meta object code from reading C++ file 'effectswindow.h'
**
** Created: Sat Apr 30 23:30:01 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/effectswindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'effectswindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_gui__ListWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      23,   17,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_gui__ListWindow[] = {
    "gui::ListWindow\0\0index\0clickedList(QModelIndex)\0"
};

const QMetaObject gui::ListWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_gui__ListWindow,
      qt_meta_data_gui__ListWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &gui::ListWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *gui::ListWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *gui::ListWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_gui__ListWindow))
        return static_cast<void*>(const_cast< ListWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int gui::ListWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: clickedList((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
