/****************************************************************************
** Meta object code from reading C++ file 'evteffecteditdialog.h'
**
** Created: Sun 15. May 10:03:48 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/evteffecteditdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'evteffecteditdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_gui__evtEffecteditdialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      26,   25,   25,   25, 0x08,
      42,   25,   25,   25, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_gui__evtEffecteditdialog[] = {
    "gui::evtEffecteditdialog\0\0acceptPressed()\0"
    "rejectPressed()\0"
};

const QMetaObject gui::evtEffecteditdialog::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_gui__evtEffecteditdialog,
      qt_meta_data_gui__evtEffecteditdialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &gui::evtEffecteditdialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *gui::evtEffecteditdialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *gui::evtEffecteditdialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_gui__evtEffecteditdialog))
        return static_cast<void*>(const_cast< evtEffecteditdialog*>(this));
    return QWidget::qt_metacast(_clname);
}

int gui::evtEffecteditdialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: acceptPressed(); break;
        case 1: rejectPressed(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE