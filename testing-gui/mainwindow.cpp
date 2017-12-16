#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "editmodal.h"
#include <QPushButton>
#include <QMessageBox>
#include <QTableView>
#include <QHeaderView>

MainWindow::MainWindow() :
    ui(new Ui::MainWindow),
    model(new QStandardItemModel(0, 71)),
    opened(false),
    dirty(false)
{
    ui->setupUi(this);
    setWindowTitle("Untitled");
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::open);
    connect(ui->actionClose, &QAction::triggered, this, &MainWindow::close);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::save);
    connect(ui->actionSaveAs, &QAction::triggered, this, &MainWindow::saveAs);
    connect(ui->plusButton, &QPushButton::released, this, &MainWindow::addState);
    connect(ui->minusButton, &QPushButton::released, this, &MainWindow::deleteState);
    QStringList headerLabels;
    headerLabels.reserve(71);
    headerLabels << "Delay After (ms)";
    for (int i = 1; i <= 55; ++i) {
        headerLabels << QString("D%1").arg(i);
    }
    for (int i = 1; i <= 15; ++i) {
        headerLabels << QString("A%1").arg(i);
    }
    model->setHorizontalHeaderLabels(headerLabels);
    auto tableView = ui->tableView;
    tableView->setModel(model);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    tableView->horizontalHeader()->setHighlightSections(false);
    connect(tableView, &QTableView::doubleClicked, this, &MainWindow::editState);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::open() {
    if (opened || dirty) {
        auto reply = QMessageBox::question(this, "?", "Close current file?",
                                           QMessageBox::Ok|QMessageBox::Cancel);
        if (reply == QMessageBox::Cancel) {
            return false;
        } else {
            if (!close()) {
                return false;
            }
        }
    }
    fileName = QFileDialog::getOpenFileName(this,
        tr("Open JSON File"), "", tr("JSON Files (*.json)"));
    setWindowTitle(fileName);
    QFile jsonFile(fileName);
    if (!jsonFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }
    QByteArray data = jsonFile.readAll();
    jsonFile.close();
    QJsonDocument jsonDoc(QJsonDocument::fromJson(data));
    QJsonArray statesArr = jsonDoc.object().value("states").toArray();
    for (QJsonValue val: statesArr) {
        State* state = new State(val.toObject());
        appendState(state);
    }
    return true;
}

bool MainWindow::save() {
    if (!dirty) {
        return false;
    }
    if (!opened) {
        saveAs();
    }
    QFile jsonFile(fileName);
    if (!jsonFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }
    QJsonDocument jsonDoc(makeJsonObj());
    jsonFile.write(jsonDoc.toJson());
    jsonFile.close();
    setWindowTitle(fileName);
    dirty = false;
    return true;
}

bool MainWindow::saveAs() {
    fileName = QFileDialog::getSaveFileName(this,
        tr("New JSON File"), "", tr("JSON Files (*.json)"));
    QFile jsonFile(fileName);
    if (!jsonFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }
    QJsonDocument jsonDoc(makeJsonObj());
    jsonFile.write(jsonDoc.toJson());
    jsonFile.close();
    setWindowTitle(fileName);
    dirty = false;
    opened = true;
    return true;
}

bool MainWindow::close() {
    if (dirty) {
        auto reply = QMessageBox::question(this, "?", "Do you want to save before closing?",
                                           QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        if (reply == QMessageBox::Cancel) {
            return false;
        } else {
            if (reply == QMessageBox::Yes) {
                save();
            }
            setWindowTitle("Untitled");
            dirty = false;
        }
    }
    for (State* state : states) {
        delete state;
    }
    model->clear();
    states.clear();
    opened = false;
    return true;
}

void MainWindow::appendState(State* state) {
    states << state;
    QList<QStandardItem*> row;
    row.reserve(71);
    auto delayAfter = new QStandardItem(QString("%1").arg(state->delayAfter));
    delayAfter->setEditable(false);
    row << delayAfter;
    for (int i = 0; i < 55; ++i) {
        auto item = new QStandardItem(QString("%1").arg(state->digital[i] ? 1 : 0));
        item->setEditable(false);
        item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        row << item;
    }
    for (int i = 0; i < 15; ++i) {
        auto item = new QStandardItem(QString("%1").arg(state->analog[i]));
        item->setEditable(false);
        item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        row << item;
    }
    model->appendRow(row);
}

void MainWindow::addState() {
    State* state = new State;
    if (EditModal(this, state).exec() == QDialog::Accepted) {
        appendState(state);
        if (!dirty) {
            dirty = true;
            if (opened) {
                setWindowTitle(fileName + "*");
            } else {
                setWindowTitle("New Unsaved File*");
            }
        }
    } else {
        delete state;
    }
}

void MainWindow::editState(const QModelIndex& index) {
    int row = index.row();
    State* state = states[row];
    if (EditModal(this, state, true).exec() == QDialog::Accepted) {
        model->item(row, 0)->setText(QString("%1").arg(state->delayAfter));
        for (int i = 0; i < 55; ++i) {
            model->item(row, i + 1)->setText(QString("%1").arg(state->digital[i]));
        }
        for (int i = 0; i < 15; ++i) {
            model->item(row, 56 + i)->setText(QString("%1").arg(state->analog[i]));
        }
        if (!dirty) {
            dirty = true;
            if (opened) {
                setWindowTitle(fileName + "*");
            }
        }
    }
}

void MainWindow::deleteState() {
    const QModelIndexList selectedList = ui->tableView->selectionModel()->selectedRows();
    if (selectedList.length() == 0) return;
    int row = selectedList[0].row();
    states.removeAt(row);
    model->removeRow(row);
}

QJsonObject MainWindow::makeJsonObj() {
    QJsonArray statesArr;
    for (auto pinsValue : states) {
        statesArr.append(pinsValue->makeJsonObj());
    }
    QJsonObject jsonObj;
    jsonObj.insert("states", statesArr);
    return jsonObj;
}

void MainWindow::closeEvent (QCloseEvent *event) {
    if (close()) {
        event->accept();
    } else {
        event->ignore();
    }
}
