#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <emerald-em.h>
#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QString>
#include <QFuture>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    void updateCanGenSeed();
    void generate();

private slots:
    void appendLog(QString msg, bool isError);
    void generateEnd(int result);

private:
    QString                 _pathOriginalRom;
    QString                 _pathOutputDir;
    QPushButton*            _btnGenerate;
    QTextEdit*              _log;

    EmeraldGenerator* _em;
};

#endif
