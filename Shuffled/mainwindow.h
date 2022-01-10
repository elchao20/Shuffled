#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <vector>
#include "AdjList.h"
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_songSearchButton_clicked();
    QString returnLink(string);
    void on_shuffleButton_clicked();

    void on_compareButton_clicked();

private:
    Ui::MainWindow *ui;
    AdjList g;
};
#endif // MAINWINDOW_H
