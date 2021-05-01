#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_Add_clicked()
{
    if (CheckFields())
    {
        if (GetInt(ui->lineEdit_score1->text().toStdString(), "cчет команды 1") != -1 &&
                GetInt(ui->lineEdit_score2->text().toStdString(), "cчет команды 2") != -1)
        {

        }
    }
}

bool MainWindow::CheckFields()
{
    if (ui->lineEdit_name1->text() == "")
    {
        QMessageBox::warning(this, "Ошибка","Не указано имя команды 1");
        return false;
    }
    if (ui->lineEdit_name2->text() == "")
    {
        QMessageBox::warning(this, "Ошибка","Не указано имя команды 2");
        return false;
    }
    if (ui->lineEdit_score1->text() == "")
    {
        QMessageBox::warning(this, "Ошибка","Не указаны очки команды 1");
        return false;
    }
    if (ui->lineEdit_score2->text() == "")
    {
        QMessageBox::warning(this, "Ошибка","Не указаны очки команды 2");
        return false;
    }
    return true;
}

int MainWindow::GetInt(string s, string source)
{
    int res = -1;
    try
    {
        res = stoi(s);
    }
    catch(...)
    {
        QString t = QString::fromStdString("Не удалось распарсить " + source);
        QMessageBox::warning(this, "Ошибка", t);
    }
    return res;
}
