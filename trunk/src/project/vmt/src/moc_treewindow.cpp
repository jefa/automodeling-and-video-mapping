/****************************************************************************
** Meta object code from reading C++ file 'treewindow.h'
**
** Created: Fri Apr 1 17:32:10 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/treewindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'treewindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_gui__TreeWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x0a,
      33,   16,   16,   16, 0x08,
      59,   52,   47,   16, 0x08,
      85,   16,   47,   16, 0x28,
     100,   16,   16,   16, 0x08,
     112,   52,   47,   16, 0x08,
     138,   16,   47,   16, 0x28,
     153,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_gui__TreeWindow[] = {
    "gui::TreeWindow\0\0updateActions()\0"
    "insertChild()\0bool\0parent\0"
    "insertColumn(QModelIndex)\0insertColumn()\0"
    "insertRow()\0removeColumn(QModelIndex)\0"
    "removeColumn()\0removeRow()\0"
};

const QMetaObject gui::TreeWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_gui__TreeWindow,
      qt_meta_data_gui__TreeWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &gui::TreeWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *gui::TreeWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *gui::TreeWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_gui__TreeWindow))
        return static_cast<void*>(const_cast< TreeWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int gui::TreeWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updateActions(); break;
        case 1: insertChild(); break;
        case 2: { bool _r = insertColumn((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: { bool _r = insertColumn();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: insertRow(); break;
        case 5: { bool _r = removeColumn((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 6: { bool _r = removeColumn();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 7: removeRow(); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
