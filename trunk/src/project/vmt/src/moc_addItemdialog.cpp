/****************************************************************************
** Meta object code from reading C++ file 'addItemdialog.h'
**
** Created: Thu 12. May 11:23:49 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/addItemdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'addItemdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_gui__addItemDialog[] = {

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
      20,   19,   19,   19, 0x08,
      36,   19,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_gui__addItemDialog[] = {
    "gui::addItemDialog\0\0acceptPressed()\0"
    "rejectPressed()\0"
};

const QMetaObject gui::addItemDialog::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_gui__addItemDialog,
      qt_meta_data_gui__addItemDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &gui::addItemDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *gui::addItemDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *gui::addItemDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_gui__addItemDialog))
        return static_cast<void*>(const_cast< addItemDialog*>(this));
    return QWidget::qt_metacast(_clname);
}

int gui::addItemDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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