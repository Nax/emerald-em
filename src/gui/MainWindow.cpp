#include <QVBoxLayout>
#include <QPushButton>
#include "GenerateTask.h"
#include "MainWindow.h"
#include "PathSelector.h"

MainWindow::MainWindow(QWidget* parent)
: QMainWindow(parent)
{
    QWidget* centralWidget = new QWidget;
    setCentralWidget(centralWidget);

    /* Create the layout */
    QVBoxLayout* layout = new QVBoxLayout;
    centralWidget->setLayout(layout);

    PathSelector* selOriginalRom = new PathSelector("Original ROM", PathSelector::Mode::File, "Gameboy Advance ROM (*.gba)");
    layout->addWidget(selOriginalRom);
    connect(selOriginalRom, &PathSelector::selected, this, [this](const QString& path) { _pathOriginalRom = path; updateCanGenSeed(); });

    PathSelector* selOutputDir = new PathSelector("Destination Folder", PathSelector::Mode::Dir);
    layout->addWidget(selOutputDir);
    connect(selOutputDir, &PathSelector::selected, this, [this](const QString& path) { _pathOutputDir = path; updateCanGenSeed(); });

    _btnGenerate = new QPushButton("Generate");
    _btnGenerate->setEnabled(false);
    layout->addWidget(_btnGenerate);
    connect(_btnGenerate, &QPushButton::clicked, this, &MainWindow::generate);

    _log = new QTextEdit;
    _log->setReadOnly(true);
    QPalette p = _log->palette();
    p.setColor(QPalette::Base, Qt::white);
    _log->setPalette(p);
    layout->addWidget(_log);

    _em = EmCreate();
}

MainWindow::~MainWindow()
{
    EmDestroy(_em);
}

void MainWindow::updateCanGenSeed()
{
    if (!_pathOriginalRom.isEmpty() && !_pathOutputDir.isEmpty())
    {
        _btnGenerate->setEnabled(true);
    }
    else
    {
        _btnGenerate->setEnabled(false);
    }
}

void MainWindow::generate()
{
    _log->clear();
    this->setEnabled(false);

    GenerateTask* task;
    task = new GenerateTask(_em, _pathOriginalRom, _pathOutputDir);
    connect(task, &GenerateTask::log, this, &MainWindow::appendLog);
    connect(task, &GenerateTask::done, this, &MainWindow::generateEnd);
    QThreadPool::globalInstance()->start(task);
}

void MainWindow::generateEnd(int result)
{
    this->setEnabled(true);
    if (result)
    {
        appendLog("Generation successful", false);
    }
    else
    {
        appendLog("Generation failed", true);
    }
}

void MainWindow::appendLog(QString msg, bool isError)
{
    _log->setTextColor(isError ? Qt::red : Qt::black);
    _log->append(msg);
}
