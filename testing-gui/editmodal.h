#ifndef NEWTEST_H
#define NEWTEST_H

#include <QDialog>
#include <QCheckBox>
#include <QSpinBox>
#include <QFormLayout>
#include "state.h"

namespace Ui {
class EditModal;
}

class EditModal : public QDialog
{
    Q_OBJECT

public:
    explicit EditModal(QWidget *parent, State* state, bool loadState = false);
    ~EditModal();

private:
    State* state;
    Ui::EditModal *ui;
    QList<QCheckBox*> digitalCheckBoxes;
    QList<QSpinBox*> analogSpinBoxes;
    inline void addDigital(const int& index, QFormLayout* layout);
    inline void addAnalog(const int& index, QFormLayout* layout);
public slots:
    void resolve();
};

#endif // NEWTEST_H
