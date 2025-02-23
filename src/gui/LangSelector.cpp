#include <emerald-em.h>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include "LangSelector.h"

LangSelector::LangSelector(const QString& label, QWidget* parent)
: QWidget(parent)
{
    /* Create the layout */
    QHBoxLayout* layout = new QHBoxLayout;
    setLayout(layout);

    QLabel *lbl = new QLabel(label);
    layout->addWidget(lbl);

    QComboBox* combo = new QComboBox;
    combo->addItem("English", EMERALDEM_LANG_EN_US);
    combo->addItem("Français", EMERALDEM_LANG_FR_FR);
    layout->addWidget(combo);

    connect(combo, QOverload<int>::of(&QComboBox::activated), this, [this](int index) { emit selected(index); });
}

LangSelector::~LangSelector()
{
}
