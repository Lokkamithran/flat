#include <bits/stdc++.h>
using namespace std;

enum class Direction
{
    LEFT,
    RIGHT
};

enum class Status
{
    ONGOING,
    ACCEPTED,
    REJECTED
};

struct Rule
{
    char inputSymbol, outputSymbol;
    Direction direction;
    Rule(char input, char output, Direction direction)
    {
        inputSymbol = input;
        outputSymbol = output;
        this->direction = direction;
    }

    bool const operator<(const Rule &o) const
    {
        return inputSymbol < o.inputSymbol;
    }
};

struct State
{
    string name;
    map<Rule, State *> transition;
};

struct TuringMachine
{
    State q0, qa, qr, currentState;
    vector<State> states;
    vector<char> input;
    vector<char> tape;

    TuringMachine(State q0, State qa, State qr, vector<State> states, vector<char> input, vector<char> tape)
    {
        this->q0 = q0;
        this->qa = qa;
        this->qr = qr;
        this->states = states;
        this->input = input;
        this->tape = tape;
        currentState = q0;
    }

    Status processInputString(string inputString)
    {
        size_t currentIndex = 0;
        Status result = Status::ONGOING;
        while (result == Status::ONGOING)
        {
            handleCurrentChar(&inputString, &currentIndex);
            printCurrentConfig(inputString, currentIndex);
            if (currentState.name == qa.name)
                result = Status::ACCEPTED;
            else if (currentState.name == qr.name)
                result = Status::REJECTED;
        }
        return result;
    }

    void handleCurrentChar(string *inputString, size_t *currentIndex)
    {
        char &head_symbol = (*inputString)[*currentIndex];
        for (pair<Rule, State *> trans : currentState.transition)
        {
            if (trans.first.inputSymbol == head_symbol)
            {
                head_symbol = trans.first.outputSymbol;
                *currentIndex = (trans.first.direction == Direction::LEFT) ? *currentIndex - 1 : *currentIndex + 1;
                currentState.name = (*(trans.second)).name;
                currentState.transition = (*(trans.second)).transition;
                return;
            }
        }
    }

    void printCurrentConfig(string inputString, size_t currentIndex)
    {
        string s1 = "", s2 = "";
        s1.append(inputString, 0, currentIndex);
        s2.append(inputString, currentIndex, inputString.length() - currentIndex);
        cout << s1 << " " << currentState.name << " " << s2 << endl;
    }
};

int main()
{

    // Equal Number Of one's and zero's
    Rule r1('0', 'B', Direction::RIGHT);
    Rule r2('0', '0', Direction::RIGHT);
    Rule r3('0', 'X', Direction::LEFT);
    Rule r4('0', '0', Direction::LEFT);

    Rule r5('1', 'B', Direction::RIGHT);
    Rule r6('1', 'X', Direction::LEFT);
    Rule r7('1', '1', Direction::RIGHT);
    Rule r8('1', '1', Direction::LEFT);

    Rule r9('X', 'B', Direction::RIGHT);
    Rule r10('X', 'X', Direction::RIGHT);
    Rule r11('X', 'X', Direction::LEFT);

    Rule r12('B', 'B', Direction::RIGHT);

    State q0;
    q0.name = "q0";
    State q1;
    q1.name = "q1";
    State q2;
    q2.name = "q2";
    State q3;
    q3.name = "q3";
    State qa;
    qa.name = "qa";
    State qr;
    qr.name = "qr";

    q0.transition.emplace(r1, &q1);
    q0.transition.emplace(r5, &q2);
    q0.transition.emplace(r9, &q0);
    q0.transition.emplace(r12, &qa);

    q1.transition.emplace(r2, &q1);
    q1.transition.emplace(r6, &q3);
    q1.transition.emplace(r10, &q1);
    q1.transition.emplace(r12, &qr);

    q2.transition.emplace(r3, &q3);
    q2.transition.emplace(r7, &q2);
    q2.transition.emplace(r10, &q2);
    q2.transition.emplace(r12, &qr);

    q3.transition.emplace(r4, &q3);
    q3.transition.emplace(r8, &q3);
    q3.transition.emplace(r11, &q3);
    q3.transition.emplace(r12, &q0);

    TuringMachine tm(q0, qa, qr, {q0, q1, q2, q3, qa, qr}, {'0', '1', 'X'}, {'0', '1', 'X', 'B'});

    Rule a1('0', 'B', Direction::RIGHT);
    Rule a2('0', '0', Direction::RIGHT);
    Rule a3('0', 'B', Direction::LEFT);
    Rule a4('0', '0', Direction::LEFT);

    Rule a5('1', 'B', Direction::RIGHT);
    Rule a6('1', '1', Direction::RIGHT);
    Rule a7('1', '1', Direction::LEFT);
    Rule a8('1', 'B', Direction::LEFT);

    Rule a9('B', 'B', Direction::RIGHT);
    Rule a10('B', 'B', Direction::LEFT);

    State b0;
    b0.name = "q0";
    State b1;
    b1.name = "q1";
    State b2;
    b2.name = "q2";
    State b3;
    b3.name = "q3";
    State b4;
    b4.name = "q4";
    State b5;
    b5.name = "q5";
    State ba;
    ba.name = "qa";
    State br;
    br.name = "qr";

    b0.transition.emplace(a1, &b1);
    b0.transition.emplace(a5, &b4);
    b0.transition.emplace(a9, &ba);

    b1.transition.emplace(a2, &b1);
    b1.transition.emplace(a6, &b1);
    b1.transition.emplace(a10, &b2);

    b2.transition.emplace(a3, &b3);
    b2.transition.emplace(a5, &br);
    b2.transition.emplace(a9, &br);

    b3.transition.emplace(a4, &b3);
    b3.transition.emplace(a7, &b3);
    b3.transition.emplace(a9, &b0);

    b4.transition.emplace(a2, &b4);
    b4.transition.emplace(a6, &b4);
    b4.transition.emplace(a10, &b5);

    b5.transition.emplace(a1, &br);
    b5.transition.emplace(a8, &b3);
    b5.transition.emplace(a9, &br);

    TuringMachine tm1(b0, ba, br, {b0, b1, b2, b3, b4, b5, ba, br}, {'0', '1'}, {'0', '1', 'B'});

    int Choice = 0;
    cout << "0 -> Check for equal number Of 0's and 1's" << endl;
    cout << "1 -> Check if its palindrome" << endl;
    cout << "Enter the choice: ";
    cin >> Choice;
    cout << "Enter the input string: ";
    string input;
    cin >> input;
    Status result = (Choice == 1) ? tm1.processInputString(input) : tm.processInputString(input);
    if (result == Status::ACCEPTED)
        cout << "The input string is accepted." << endl;
    else if (result == Status::REJECTED)
        cout << "The input string is rejected." << endl;

    return 0;
}