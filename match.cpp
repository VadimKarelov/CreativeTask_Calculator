#include "match.h"

Match::Match(string command1, string command2, int score1, int score2)
{
    _command1 = command1;
    _command2 = command2;
    _score1 = score1;
    _score2 = score2;
}

// get
string Match::GetCommand1()
{
    return _command1;
}

string Match::GetCommand2()
{
    return _command2;
}

int Match::GetScore1()
{
    return _score1;
}

int Match::GetScore2()
{
    return _score2;
}

string Match::ToString()
{
    return (_command1 + " " + to_string(_score1) + ":" + to_string(_score2) + " " + _command2);
}
