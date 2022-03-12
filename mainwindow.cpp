#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    data.region = allocateString(STRING_SCALE);
    data.name = allocateString(STRING_SCALE);
    data.fileExists = false;
    ui->setupUi(this);
    connect(ui->pushButtonAddFile, &QPushButton::clicked, this, &MainWindow::openWindowFile);
    connect(ui->pushButtonLoadData, &QPushButton::clicked, this, &MainWindow::loadData);
    connect(ui->pushButtonCalc, &QPushButton::clicked, this, &MainWindow::calc);
}

MainWindow::~MainWindow()
{
    freeString(data.region);
    freeString(data.name);
    if (data.fileExists){
        freeMatrix(data.info, data.size, data.countColumn);
        freeArr(data.nameColumn, data.countColumn);
    }
    delete ui;
}


void MainWindow::showErrorWindow(char* nameError){
    if(nameError = NULL){
        return;
    }
    QMessageBox::warning(this, "ERROR", nameError);
}


void MainWindow::calc(){
    QString colunm = ui->lineColumn->text();
    if (colunm.isEmpty() || !data.fileExists){
        error = Read;
        errorsReturn(error);
    } else {
        double numCol = colunm.toDouble() - 1;
        if (numCol < MIN_NUM_COL|| numCol > data.countColumn){
            error = ColumnNum;
            errorsReturn(error);
        } else {
            doOperation(Calculate, data, numCol, data.fileExists, error);
            ui->textIntermediate->setText(QString::number(data.intermediate));
            ui->textMax->setText(QString::number(data.max));
            ui->textMin->setText(QString::number(data.min));
        }
    }
}


void MainWindow::loadData(){
    QString region = ui->lineRegion->text();
    if(ui->labelFileName->text().isEmpty()){
        error = File;
        errorsReturn(error);
        return;
    }
    if (region.isEmpty()){
        error = Region;
        errorsReturn(error);
    } else {
        data.region = QstringToCharArray(region);
        doOperation(LoadData, data, NULL, data.fileExists, error);
        errorsReturn(error);
        showData(data);
    }
}


void MainWindow::openWindowFile(){
    QString pathFileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", "CSV File (*.csv)");
    data.name = QstringToCharArray(pathFileName);
    ui->labelFileName->setText(pathFileName);
}


char* MainWindow::QstringToCharArray(QString qstr){
    char *str = (char*)malloc(sizeof(char)*(qstr.size() + 1));
    int i;
    for (i = 0; i < qstr.size(); i++){
        str[i] = qstr.at(i).unicode();
    }
    str[i] = 0;
    return str;
}


QStringList MainWindow::ConvertRowToQTFormat(char **row, size_t size){
    QStringList qsl = {};
    for(size_t i = 0; i < size; i++){
        qsl.append(QString::fromUtf8(row[i]));
    }
    return qsl;
}


void MainWindow::showData(Data& data){
    ui->tableWidget->setColumnCount(data.countColumn);
    QStringList QColumns = ConvertRowToQTFormat(data.nameColumn, data.countColumn);
    ui->tableWidget->setHorizontalHeaderLabels(QColumns);
    ui->tableWidget->setRowCount(0);
    for (int i = 0; i < data.size - 1; i++){
        QStringList currentRow = ConvertRowToQTFormat(data.info[i], data.countColumn);
        ui->tableWidget->setRowCount(i + 1);
        for (int j = 0; j < currentRow.count(); j++){
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setData(Qt::EditRole, currentRow.at(j).toInt());
            item->setText(currentRow.at(j));
            ui->tableWidget->setItem(i, j, item);
        }
    }
}

void MainWindow::errorsReturn(Errors errors){
    switch(errors){
    case Read:
        showErrorWindow("Can't read data");
        break;
    case ColumnNum:
        showErrorWindow("Broke column number");
        break;
    case Region:
        showErrorWindow("No region");
        break;
    case File:
        showErrorWindow("No file");
        break;
    case Success:
        break;
    }
}
