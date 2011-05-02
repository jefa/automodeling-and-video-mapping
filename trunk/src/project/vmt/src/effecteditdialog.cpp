#include "effecteditdialog.h"
#include "effectpages.h"
#include <QtGui>

EffectEditDialog::EffectEditDialog(VmtModel *vmtModel, Effect *ef)
{
    this->vmtModel = vmtModel;
    this->effect = ef;

    contentsWidget = new QListWidget;
    contentsWidget->setViewMode(QListView::IconMode);
    contentsWidget->setIconSize(QSize(96, 84));
    contentsWidget->setMovement(QListView::Static);
    contentsWidget->setMaximumWidth(128);
    contentsWidget->setSpacing(12);

    pagesWidget = new QStackedWidget;
    pagesWidget->addWidget(new PositionEffectPage(vmtModel, ef));
    pagesWidget->addWidget(new FadeEffectPage(vmtModel, ef));
    pagesWidget->addWidget(new TextureEffectPage(vmtModel, ef));

    QPushButton *closeButton = new QPushButton(tr("Close"));
    QPushButton *saveButton = new QPushButton(tr("Save"));

    createIcons();
    if (effect == NULL)
        contentsWidget->setCurrentRow(0);
    else {
        contentsWidget->setCurrentRow(effect->getType());
    }

    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(save()));

    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(contentsWidget);
    horizontalLayout->addWidget(pagesWidget, 1);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(saveButton);
    buttonsLayout->addWidget(closeButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(horizontalLayout);
    mainLayout->addStretch(1);
    mainLayout->addSpacing(12);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Config Dialog"));
}

void EffectEditDialog::createIcons()
{
    QListWidgetItem *configButton = new QListWidgetItem(contentsWidget);
    //configButton->setIcon(QIcon(":/images/config.png"));
    configButton->setIcon(QIcon("/images/config.png"));
    configButton->setText(tr("Position"));
    configButton->setTextAlignment(Qt::AlignHCenter);
    if (this->effect == NULL){
        configButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    } else if (this->effect->getType() != POSITION_EFFECT){
        configButton->setFlags(Qt::ItemIsSelectable);
    }

    QListWidgetItem *updateButton = new QListWidgetItem(contentsWidget);
    updateButton->setIcon(QIcon(":/images/update.png"));
    updateButton->setText(tr("Fade"));
    updateButton->setTextAlignment(Qt::AlignHCenter);
    if (this->effect == NULL){
        updateButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    } else if (this->effect->getType() != FADE_EFFECT){
        updateButton->setFlags(Qt::ItemIsSelectable);
    }

    QListWidgetItem *queryButton = new QListWidgetItem(contentsWidget);
    queryButton->setIcon(QIcon(":/images/query.png"));
    queryButton->setText(tr("Texture"));
    queryButton->setTextAlignment(Qt::AlignHCenter);
    if (this->effect == NULL){
        queryButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    } else if (this->effect->getType() != TEXTURE_EFFECT){
        queryButton->setFlags(Qt::ItemIsSelectable);
    }

    connect(contentsWidget,
            SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(changePage(QListWidgetItem*,QListWidgetItem*)));
}

void EffectEditDialog::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;

    pagesWidget->setCurrentIndex(contentsWidget->row(current));
}

void EffectEditDialog::save()
{
}
