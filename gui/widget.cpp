#include "widget.h"
#include "ui_widget.h"
#include <QFormLayout>
#include <QMessageBox>
#include <QProcess>
#include <QCheckBox>
#include <QSpinBox>
#include <QLabel>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget) {

    ui->setupUi(this);
    this->setWindowTitle("Test pins");
    QFormLayout* digitalLayout1 = ui->formLayout_4;
    QFormLayout* digitalLayout2 = ui->formLayout_5;
    QFormLayout* digitalLayout3 = ui->formLayout_2;
    QFormLayout* digitalLayout4 = ui->formLayout_6;
    QFormLayout* digitalLayout5 = ui->formLayout_3;
    QFormLayout* analogLayout1 = ui->formLayout_7;
    QFormLayout* analogLayout2 = ui->formLayout_8;

    for (int i = 1; i <= 11; ++i) {
        addDigital(i, digitalLayout1);
    }
    for (int i = 12; i <= 22; ++i) {
        addDigital(i, digitalLayout2);
    }
    for (int i = 23; i <= 33; ++i) {
        addDigital(i, digitalLayout3);
    }
    for (int i = 34; i <= 44; ++i) {
        addDigital(i, digitalLayout4);
    }
    for (int i = 45; i <= 55; ++i) {
        addDigital(i, digitalLayout5);
    }
    for (int i = 1; i <= 8; ++i) {
        addAnalog(i, analogLayout1);
    }
    for (int i = 9; i <= 15; ++i) {
        addAnalog(i, analogLayout2);
    }

    connect(ui->pushButton, &QPushButton::released, [this]() {
        QString output;
        output.reserve(600);
        for (int i = 0; i < 55; ++i) {
            output += QString("{%1,%2};").arg(i + 1).arg(digitalCheckBoxes[i]->checkState() ? 1 : 0);
        }
        for (int i = 0; i < 15; ++i) {
            output += QString("{A%1,%2};").arg(i + 1).arg(analogSpinBoxes[i]->value());
        }
        output.truncate(output.size() - 1);
        QProcess proc;
        QStringList args;
        args << output; // {1,0};{2,1};{3,0};...;{A15,123}
        proc.execute(/* /path/to/cli-prog */"echo", args);
        proc.close();
    });
    connect(ui->pushButton_2, &QPushButton::released, [this]() {
        QString output;
        output.reserve(600);
        for (int i = 0; i < 55; ++i) {
            output += QString("{%1,%2};").arg(i + 1).arg(digitalCheckBoxes[i]->checkState() ? 1 : 0);
        }
        for (int i = 0; i < 15; ++i) {
            output += QString("{A%1,%2};").arg(i + 1).arg(analogSpinBoxes[i]->value());
        }
        output.truncate(output.size() - 1);
        QMessageBox msgBox(QMessageBox::NoIcon, "Output", output, QMessageBox::Ok, this);
        msgBox.setTextInteractionFlags(Qt::TextSelectableByMouse);
        msgBox.exec();
    });
}

inline void Widget::addDigital(const int& index, QFormLayout* layout) {
    auto checkBox = new QCheckBox;
    digitalCheckBoxes << checkBox;
    layout->addRow(QString("&%1:").arg(index), checkBox);
}

inline void Widget::addAnalog(const int& index, QFormLayout* layout) {
    auto spinBox = new QSpinBox;
    spinBox->setMaximum(1023);
    spinBox->setMinimum(0);
    analogSpinBoxes << spinBox;
    layout->addRow(QString("&A%1:").arg(index), spinBox);
}

Widget::~Widget() {
    delete ui;
}
