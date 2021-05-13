#include "messagewindow.h"
#include "ui_messagewindow.h"

MessageWindow::MessageWindow(QWidget *parent, QString message) :
    QDialog(parent),
    ui(new Ui::MessageWindow)
{
    ui->setupUi(this);
    ui->textBrowser_message->setText(message);
}

MessageWindow::~MessageWindow()
{
    delete ui;
}

void MessageWindow::on_pushButton_ok_clicked()
{
    this->close();
}
