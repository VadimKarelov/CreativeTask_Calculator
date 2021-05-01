#include "mainwindow.h"
#include "ui_mainwindow.h"

// constructor and destructor
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

// slots
void MainWindow::on_pushButton_Add_clicked()
{
    if (CheckFields())
    {
        if (GetInt(ui->lineEdit_score1->text().toStdString(), "cчет команды 1") != -1 &&
                GetInt(ui->lineEdit_score2->text().toStdString(), "cчет команды 2") != -1)
        {
            // add new match
            string c1 = ui->lineEdit_name1->text().toStdString();
            string c2 = ui->lineEdit_name2->text().toStdString();
            int s1 = stoi(ui->lineEdit_score1->text().toStdString());
            int s2 = stoi(ui->lineEdit_score2->text().toStdString());
            _matches.push_back(Match(c1, c2, s1, s2));
            UpdateInformation();
        }
    }
}

// methods to checking fields
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

// update information on gui
void MainWindow::UpdateInformation()
{
    // update matches list
    ui->listWidget_Matches->clear();

    for (int i = 0; i < _matches.size(); i++)
    {
        ui->listWidget_Matches->addItem(QString::fromStdString(_matches[i].ToString()));
    }

    // update standings
    ui->listWidget_Standings->clear();
    set<pair<int, string>> table = ComputeStandings(_matches);

    // add title row
    ui->listWidget_Standings->addItem("Имя (победы/ничьи/проигрыши)(голы/пропуски) (очки)");
    set<pair<int, string>>::iterator it = table.begin();
    for (int i = 0; i < table.size(); i++, it++)
    {
         ui->listWidget_Standings->addItem(
                     QString::fromStdString(
                         to_string(i + 1) + " - " + it->second + " (" + to_string(it->first) + ")"));
    }
}

set<pair<int, string>> MainWindow::ComputeStandings(vector<Match> m)
{
    set<pair<int, string>> res;

    // find names of commands
    vector<string> commands;
    for (int i = 0; i < m.size(); i++)
    {
        bool f = true;
        for (int j = 0; j < commands.size() && f; j++)
        {
            if (commands[j] == m[i].GetCommand1())
            {
                commands.push_back(m[i].GetCommand1());
                f = false;
            }
            if (commands[j] == m[i].GetCommand2())
            {
                commands.push_back(m[i].GetCommand2());
                f = false;
            }
        }
    }

    // compute stat and add command to table
    for (int i = 0; i < commands.size(); i++)
    {
        int score = 0;
        string t = CommandStat(commands[i], m, score);
        res.insert(make_pair(score, t));
    }

    return res;
}

string MainWindow::CommandStat(string name, vector<Match> m, int &score)
{
    int wins = 0, draws = 0, looses = 0, goals = 0, omissions = 0;
    for (int i = 0; i < m.size(); i++)
    {
        Match cur = m[i];
        if (cur.GetCommand1() == name)
        {
            goals += cur.GetScore1();
            omissions += cur.GetScore2();

            if (cur.GetScore1() > cur.GetScore2())
            {
                wins++;
            }
            else if (cur.GetScore1() == cur.GetScore2())
            {
                draws++;
            }
            else
            {
                looses++;
            }
        }
        else if (cur.GetCommand2() == name)
        {
            goals += cur.GetScore2();
            omissions += cur.GetScore1();

            if (cur.GetScore2() > cur.GetScore1())
            {
                wins++;
            }
            else if (cur.GetScore2() == cur.GetScore1())
            {
                draws++;
            }
            else
            {
                looses++;
            }
        }
    }

    //(wins - looses) * 10 + goals - omissions;
    score = wins * 3;

    return name + "(" + to_string(wins) + "/" + to_string(draws) + "/" + to_string(looses) + ")("
            + to_string(goals) + "/" + to_string(omissions) + ")";
}
