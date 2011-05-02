#ifndef EFFECTEDITDIALOG_H
#define EFFECTEDITDIALOG_H

#include "Effect.h"
#include "VmtModel.h"

#include <QDialog>

QT_BEGIN_NAMESPACE
class QListWidget;
class QListWidgetItem;
class QStackedWidget;
QT_END_NAMESPACE

class EffectEditDialog : public QDialog
{
    Q_OBJECT

public:
    EffectEditDialog(VmtModel *vmtModel, Effect *ef);

public slots:
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);
    void save();

private:
    void createIcons();

    QListWidget *contentsWidget;
    QStackedWidget *pagesWidget;

    VmtModel *vmtModel;
    Effect *effect;
};

#endif
