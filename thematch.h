#ifndef THEMATCH_H
#define THEMATCH_H
#include <string>
using namespace std;

class TheMatch
{
private:
    string _command1, _command2;
    int _score1, _score2;

public:
    // constructor
    TheMatch(string command1, string command2, int score1, int score2);

    // get
    string GetCommand1();

    string GetCommand2();

    int GetScore1();

    int GetScore2();
};

#endif // THEMATCH_H
