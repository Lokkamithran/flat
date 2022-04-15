#include <bits/stdc++.h> 
using namespace std;

enum class Direction{
    LEFT, RIGHT;
};

enum class Result{
    ONGOING, ACCEPTED, REJECTED;
}

struct Rule{
    char inputSymbol, outputSymbol;
    Direction direction;
};

struct State{
    string name;
    map<Rule, State> transition;
};

struct TuringMachine
{
    State q0, qa, qr;
    vector<State> states;
    vector<char> input;
    vector<char> tape;
};

