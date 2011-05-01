#ifndef LISTWINDOW_H
#define LISTWINDOW_H

#include "VmtModel.h"

#include <QModelIndex>
#include <QWidget>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QPushButton>
#include <QString>


class QAction;
class QListView;

namespace gui {

class ListWindow : public QWidget
{
    Q_OBJECT

public:
    ListWindow(VmtModel *vmtModel);
    ~ListWindow();

public slots:
    void clickedList(const QModelIndex &index);

private slots:

private:
    void setupUi(QWidget *);
    void retranslateUi(QWidget *);

public:
    QVBoxLayout *vboxLayout;
    QGridLayout *layout;
    QListView *view;
};

}

#endif
