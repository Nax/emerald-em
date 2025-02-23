#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include "PathSelector.h"

PathSelector::PathSelector(const QString& label, PathSelector::Mode mode, const QString& fileAccepts, QWidget* parent)
: QWidget(parent)
, _mode(mode)
, _fileAccepts(fileAccepts)
{
    /* Create the layout */
    QHBoxLayout* layout = new QHBoxLayout;
    setLayout(layout);

    QLabel *lbl = new QLabel(label);
    layout->addWidget(lbl);

    _editPath = new QLineEdit;
    _editPath->setReadOnly(true);
    layout->addWidget(_editPath);

    QPushButton* btnBrowse = new QPushButton("...");
    layout->addWidget(btnBrowse);

    connect(btnBrowse, &QPushButton::clicked, this, &PathSelector::browse);
}

PathSelector::~PathSelector()
{
}

void PathSelector::browse()
{
    QString path;

    if (_mode == Mode::File)
    {
        path = QFileDialog::getOpenFileName(this, "Select a file", QString(), _fileAccepts);
    }
    else
    {
        path = QFileDialog::getExistingDirectory(this, "Select a directory");
    }

    if (!path.isEmpty())
    {
        _editPath->setText(path);
        emit selected(path);
    }
}
