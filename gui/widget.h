#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QSpinBox>
#include <QList>
#include <QFormLayout>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    QList<QCheckBox*> digitalCheckBoxes;
    QList<QSpinBox*> analogSpinBoxes;
    inline void addDigital(const int& index, QFormLayout* layout);
    inline void addAnalog(const int& index, QFormLayout* layout);
};

#endif // WIDGET_H
