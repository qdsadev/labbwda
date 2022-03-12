#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "entrypoint.h"
#include "filemanager.h"
#include "logic.h"

#define MIN_NUM_COL 2

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Data data;
    Errors error = Success;
    QStringList ConvertRowToQTFormat(char **row, size_t size);
    char* QstringToCharArray(QString qstr);
    void showData(Data& data);
    void errorsReturn(Errors errors);
    void showErrorWindow(char* nameError);
    void loadData();
    void openWindowFile();
    void calc();
};
#endif // MAINWINDOW_H
