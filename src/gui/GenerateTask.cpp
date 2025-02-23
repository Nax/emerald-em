#include "GenerateTask.h"

GenerateTask::GenerateTask(EmeraldGenerator* gen, const QString& originalRomPath, const QString& outDirPath, QObject* parent)
: QObject(parent)
, _gen(gen)
, _originalRomPath(originalRomPath)
, _outDirPath(outDirPath)
{
    EmSetCallbackLog(_gen, [](void* arg, const char* msg) { emit ((GenerateTask*)arg)->log(QString(msg), false); }, this);
    EmSetCallbackError(_gen, [](void* arg, const char* msg) { emit ((GenerateTask*)arg)->log(QString(msg), true); }, this);
}

GenerateTask::~GenerateTask()
{
}

void GenerateTask::run()
{
    int res;
    std::string outDirPath = _outDirPath.toStdString();
    std::string originalRomPath = _originalRomPath.toStdString();

    res = EmRun(_gen, originalRomPath.c_str(), outDirPath.c_str());
    emit done(res);
}
