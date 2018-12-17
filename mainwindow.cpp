#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include <iostream>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    readFromFile("proverbs.txt");
}

void MainWindow::on_lineEdit_returnPressed()
{
    QString qsTemp = ui->lineEdit->text();
    ui->plainTextEdit->appendPlainText(qsTemp);
    ui->lineEdit->clear();
    writeToFile(qsTemp, "output.txt");
}

void MainWindow::writeToFile(QString writeLine, QString fileName)
{
    QFile outFile(fileName);
    if (!outFile.open(QIODevice::Append | QIODevice::Text)){
        qDebug() << "Cannot write to file.";
    }
    outFile.write(qPrintable(writeLine + "\n"));
    outFile.close();
}

void MainWindow::readFromFile(QString fileName) {
    char buf[1024];
    QFile inputFile(fileName);
    ui->label_5->setText("Reading proverbs from file: " + fileName + " and writing them to file output.txt");
    if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Can't open file" ;
    }
    while (!inputFile.atEnd()) {
        inputFile.readLine(buf, 1024);
        ui->plainTextEdit->appendPlainText(buf);
        writeToFile(buf, "output.txt");
    }
}

void MainWindow::on_pushButton_Sort_clicked()
{
    sortList("proverbs.txt");
}

void MainWindow::sortList(QString fileName){
    int p = 0;
    char phrase[1024];
    QString proverbs[1024];
    int proverbNumber[1024] = {0};
    int countLetters [1024] = {0};
    QFile inputFile(fileName);
    if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Can't open file " + fileName;
    }
    while (!inputFile.atEnd()) {
        int count = 0;
        for (int i = 0; i < 1024; i++){
            if (phrase[i] == '\n') break;
            count = i;
            countLetters[p] = i;
        }
        inputFile.readLine(phrase, 1024);
        for (int j = 0; j < 1024; j++){
            proverbs [p] = phrase;
            proverbNumber[p] = p;
        }
//        writeToFile(proverbs[p], "sortedList.txt");
        if (count == 0) continue;
        qDebug() << "Number of letters in proverb No" << proverbNumber[p] << " is " << count + 1;
        p++;
    }
    countLetters[0] = 0;
    int max = *std::max_element(std::begin(countLetters), std::end(countLetters));
    qDebug() << "The longest proverbs are: ";
    int longestLines = 5;
    for (int j = max; j > 0; j--){
        bool yes = false;
        for (int i = 0; i < 1024; i++){
            if (countLetters[i] == max){
                yes = true;
                qDebug() << "Proverb of" << countLetters[i] << "letters long is No" << proverbNumber[i];
       //         ui->plainTextEdit->appendPlainText(phrase);
            }
        }
        max--;
        if (yes == true){longestLines--; qDebug();}
        if (longestLines <= 0) break;
    }
    writeToFile(proverbs[p], "sortedList.txt");
}
