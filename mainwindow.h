#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QDebug>
//#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    struct Proverbs
    {
        int provNumber[1024];
        QString proverbText[1024];
        int letterCount[1024];
    };
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_lineEdit_returnPressed();
    void on_pushButton_Sort_clicked();

private:
    void writeToFile(QString writeLine, QString fileName);
    void readFromFile(QString fileName);
    void sortList(QString fileName);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
