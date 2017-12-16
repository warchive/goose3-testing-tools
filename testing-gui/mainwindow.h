#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "state.h"
#include <QList>
#include <QFile>
#include <QJsonObject>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QCloseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QList<State*> states;
    QStandardItemModel* model;
    bool opened;
    bool dirty;
    QString fileName;
    QJsonObject makeJsonObj();
    void loadState(QJsonObject& jsonObj);
    void closeEvent (QCloseEvent *event);

 public slots:
    bool open();
    bool save();
    bool saveAs();
    bool close();
    void addState();
    void editState(const QModelIndex& index);
    void deleteState();
    void appendState(State* state);
};

#endif // MAINWINDOW_H
