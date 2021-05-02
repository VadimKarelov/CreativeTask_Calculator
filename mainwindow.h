#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QString>
#include <string>
#include <vector>
#include <set>
#include "match.h"
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
    void on_pushButton_Add_clicked();

    void on_pushButton_Edit_clicked();

private:
    Ui::MainWindow *ui;
    vector<Match> _matches;
    int editElement = -1;

private:
    // checking
    bool CheckFields();

    int GetInt(string s, string source);

    // gui
    void UpdateInformation();

    // computing places in standings
    set<pair<int, string>> ComputeStandings(vector<Match> m);

    string CommandStat(string name, vector<Match> m, int &score);

    int IndexOfMatch(vector<Match> m, string item);
};
#endif // MAINWINDOW_H
