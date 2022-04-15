#include <bits/stdc++.h> 
using namespace std;

enum class Direction{
    LEFT, RIGHT
};

enum class Result{
    ONGOING, ACCEPTED, REJECTED
};

struct Rule{
    char inputSymbol, outputSymbol;
    Direction direction;
};

struct State{
    string name;
    map<Rule, State> transition;
    State(string name){
        this->name = name;
    }
};

struct TuringMachine
{
    State q0 = {q0}, qa = {qa}, qr = {qr};
    vector<State> states;
    vector<char> input;
    vector<char> tape;

    Result processInputString(string inputString){
        size_t currentIndex = 0;
        State currentState = q0;
        Result result = Result::ONGOING;
        printCurrentConfig(inputString, currentIndex, currentState);
        while(result == Result::ONGOING){
            // handleCurrentChar(inputString, currentIndex, currentState);
            printCurrentConfig(inputString, currentIndex, currentState);
            if(currentState.name == qa.name) result = Result::ACCEPTED;
            else if(currentState.name == qr.name) result = Result::REJECTED;
        }
        return result;
    }

    void handleCurrentChar(string &inputString, size_t &currentIndex, State &currentState){
        char &head_symbol = inputString[currentIndex];
        for(pair<Rule,State> transition : currentState.transition){
            if(transition.first.inputSymbol == head_symbol){
                head_symbol =transition.first.outputSymbol;
                currentIndex=(transition.first.direction ==Direction::LEFT)?currentIndex-=1:currentIndex+=1;
                currentState =transition.second;
                return;
            }
        }
    }

    void printCurrentConfig(string inputString, size_t currentIndex, State currentState){
        string s1 = "", s2 = "";
        s1.append(inputString, 0, currentIndex);
        s2.append(inputString, currentIndex, inputString.length()-currentIndex);
        cout << s1 << " " << currentState.name << " " << s2 << endl;
    }
};