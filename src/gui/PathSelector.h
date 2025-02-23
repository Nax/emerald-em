#ifndef PATH_SELECTOR_H
#define PATH_SELECTOR_H

#include <QString>
#include <QWidget>
#include <QLineEdit>

class PathSelector : public QWidget
{
    Q_OBJECT

signals:
    void selected(const QString& path);

public:
    enum class Mode
    {
        File,
        Dir,
    };

    PathSelector(const QString& label, PathSelector::Mode mode, const QString& fileAccepts = "", QWidget* parent = nullptr);
    ~PathSelector();

private slots:
    void browse();

private:
    Mode        _mode;
    QString     _fileAccepts;
    QLineEdit*  _editPath;
};

#endif
