#ifndef LANG_SELECTOR_H
#define LANG_SELECTOR_H

#include <QWidget>

class LangSelector : public QWidget
{
    Q_OBJECT

public:
    LangSelector(const QString& label, QWidget* parent = nullptr);
    ~LangSelector();

signals:
    void selected(int lang);
};

#endif
