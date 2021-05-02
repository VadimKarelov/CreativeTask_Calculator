#include "mainwindow.h"
#include "ui_mainwindow.h"

// constructor and destructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // add background image
    QPixmap bkgnd("D:\\Projects\\Qt\\C++\\Creative_Task_Calculator\\Resources\\background_image.jfif");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
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

            // check edit mod
            if (editElement != -1)
            {
                _matches.erase(_matches.begin() + editElement);
                editElement = -1;
                ui->pushButton_Edit->setStyleSheet("QPushButton { background-color: grey; }\n"
                                                   "QPushButton:enabled { background-color: rgb(85,255,255);"
                                                   "border-radius: 8px; }\n");
            }

            UpdateInformation();
        }
    }
}

void MainWindow::on_pushButton_Edit_clicked()
{
    if (ui->listWidget_Matches->selectedItems().size() > 0)
    {
        // get element
        QListWidgetItem *el = *(ui->listWidget_Matches->selectedItems().begin());
        int ind = IndexOfMatch(_matches, el->text().toStdString());

        // set data to fields to change information
        ui->lineEdit_name1->setText(QString::fromStdString(_matches[ind].GetCommand1()));
        ui->lineEdit_name2->setText(QString::fromStdString(_matches[ind].GetCommand2()));
        ui->lineEdit_score1->setText(QString::number(_matches[ind].GetScore1()));
        ui->lineEdit_score2->setText(QString::number(_matches[ind].GetScore2()));

        // set flag to edit mod
        editElement = ind;
        ui->pushButton_Edit->setStyleSheet("QPushButton { background-color: grey; }\n"
                                           "QPushButton:enabled { background-color: rgb(200,0,0);"
                                           "border-radius: 8px; }\n");
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
    set<pair<int, string>>::iterator it = table.end();
    --it;
    for (int i = 0; i < table.size(); i++, it--)
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
        // check command 1
        bool f = true;
        for (int j = 0; j < commands.size() && f; j++)
        {
            f = m[i].GetCommand1() != commands[j];
        }
        if (f)
        {
            commands.push_back(m[i].GetCommand1());
        }
        // command 2
        f = true;
        for (int j = 0; j < commands.size() && f; j++)
        {
            f = m[i].GetCommand2() != commands[j];
        }
        if (f)
        {
            commands.push_back(m[i].GetCommand2());
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

// count stat for one command
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

// find index of match in table
int MainWindow::IndexOfMatch(vector<Match> m, string item)
{
    int res = -1;
    for (int i = 0; i < m.size() && res == -1; i++)
    {
        if (item == m[i].ToString())
            res = i;
    }
    return res;
}
