/****************************************************************************
** Meta object code from reading C++ file 'nodeeditdialog.h'
**
** Created: Sun 15. May 10:03:49 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/nodeeditdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'nodeeditdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_gui__NodeEditorDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      23,   22,   22,   22, 0x08,
      39,   22,   22,   22, 0x08,
      61,   55,   22,   22, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_gui__NodeEditorDialog[] = {
    "gui::NodeEditorDialog\0\0acceptPressed()\0"
    "rejectPressed()\0state\0isActive(bool)\0"
};

const QMetaObject gui::NodeEditorDialog::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_gui__NodeEditorDialog,
      qt_meta_data_gui__NodeEditorDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &gui::NodeEditorDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *gui::NodeEditorDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *gui::NodeEditorDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_gui__NodeEditorDialog))
        return static_cast<void*>(const_cast< NodeEditorDialog*>(this));
    return QWidget::qt_metacast(_clname);
}

int gui::NodeEditorDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: acceptPressed(); break;
        case 1: rejectPressed(); break;
        case 2: isActive((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE