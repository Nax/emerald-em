#ifndef GENERATE_TASK_H
#define GENERATE_TASK_H

#include <emerald-em.h>
#include <QRunnable>
#include <QObject>

class GenerateTask : public QObject, public QRunnable
{
    Q_OBJECT

signals:
    void log(QString msg, bool isError);
    void done(int result);

public:
    GenerateTask(EmeraldGenerator* gen, const QString& originalRomPath, const QString& outDirPath, QObject* parent = nullptr);
    ~GenerateTask();

private:
    void run() override;

    EmeraldGenerator*   _gen;
    QString             _originalRomPath;
    QString             _outDirPath;
};

#endif /* GENERATE_TASK_H */
