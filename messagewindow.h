#ifndef MESSAGEWINDOW_H
#define MESSAGEWINDOW_H

#include <QDialog>
#include <QString>

namespace Ui {
class MessageWindow;
}

class MessageWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MessageWindow(QWidget *parent = nullptr, QString message = "");
    ~MessageWindow();

private slots:
    void on_pushButton_ok_clicked();

private:
    Ui::MessageWindow *ui;
};

#endif // MESSAGEWINDOW_H
