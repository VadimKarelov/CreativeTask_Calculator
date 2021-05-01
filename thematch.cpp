#include "thematch.h"

TheMatch::TheMatch(string command1, string command2, int score1, int score2)
{
    _command1 = command1;
    _command2 = command2;
    _score1 = score1;
    _score2 = score2;
}

// get
string TheMatch::GetCommand1()
{
    return _command1;
}

string TheMatch::GetCommand2()
{
    return _command2;
}

int TheMatch::GetScore1()
{
    return _score1;
}

int TheMatch::GetScore2()
{
    return _score2;
}
