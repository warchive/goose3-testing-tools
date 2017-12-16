#include "editmodal.h"
#include "ui_editmodal.h"
#include <QDialogButtonBox>

EditModal::EditModal(QWidget *parent, State* state, bool loadState) :
    QDialog(parent),
    state(state),
    ui(new Ui::EditModal)
{
    ui->setupUi(this);
    setWindowTitle(loadState ? "Edit test state" : "New test state");
    for (int i = 1; i <= 11; ++i) {
        addDigital(i, ui->digital1);
    }
    for (int i = 12; i <= 22; ++i) {
        addDigital(i, ui->digital2);
    }
    for (int i = 23; i <= 33; ++i) {
        addDigital(i, ui->digital3);
    }
    for (int i = 34; i <= 44; ++i) {
        addDigital(i, ui->digital4);
    }
    for (int i = 45; i <= 55; ++i) {
        addDigital(i, ui->digital5);
    }
    for (int i = 1; i <= 8; ++i) {
        addAnalog(i, ui->analog1);
    }
    for (int i = 9; i <= 15; ++i) {
        addAnalog(i, ui->analog2);
    }
    if (loadState) {
        for (int i = 0; i < 55; i++) {
            digitalCheckBoxes[i]->setChecked(state->digital[i] ? true : false);
        }
        for (int i = 0; i < 15; i++) {
            analogSpinBoxes[i]->setValue(state->analog[i]);
        }
        ui->delayAfter->setValue(state->delayAfter);
    }

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &EditModal::resolve);
}

void EditModal::resolve() {
    for (int i = 0; i < 55; i++) {
        state->digital[i] = digitalCheckBoxes[i]->checkState() ? true : false;
    }
    for (int i = 0; i < 15; i++) {
        state->analog[i] = analogSpinBoxes[i]->value();
    }
    state->delayAfter = ui->delayAfter->value();
}

EditModal::~EditModal()
{
    delete ui;
}

inline void EditModal::addDigital(const int& index, QFormLayout* layout) {
    auto checkBox = new QCheckBox;
    digitalCheckBoxes << checkBox;
    layout->addRow(QString("&%1:").arg(index), checkBox);
}

inline void EditModal::addAnalog(const int& index, QFormLayout* layout) {
    auto spinBox = new QSpinBox;
    spinBox->setMaximum(1023);
    spinBox->setMinimum(0);
    analogSpinBoxes << spinBox;
    layout->addRow(QString("&A%1:").arg(index), spinBox);
}
