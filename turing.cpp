#include <iostream>
#include <vector>
#include <map> 
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
    Rule(char input, char output, Direction direction){
        inputSymbol = input;
        outputSymbol = output;
        this->direction = direction;
    }

    bool const operator<(const Rule &o) const {
        return inputSymbol < o.inputSymbol;
    }
};

struct State{
    string name;
    map<Rule,State *> transition;
};

struct TuringMachine
{
    State q0, qa, qr,currentState;
    vector<State> states;
    vector<char> input;
    vector<char> tape;

    TuringMachine(State q0, State qa, State qr, vector<State> states, vector<char> input, vector<char> tape){
        this->q0 = q0;
        this->qa = qa;
        this->qr = qr;
        this->states = states;
        this->input = input;
        this->tape = tape;
        currentState =q0;
    }

    Result processInputString(string inputString){
        size_t currentIndex = 0;
        Result result = Result::ONGOING;
        while(result == Result::ONGOING){
            handleCurrentChar(&inputString, &currentIndex);            
            printCurrentConfig(inputString, currentIndex);
            if(currentState.name == qa.name) 
                result = Result::ACCEPTED;
            else if(currentState.name == qr.name) result = Result::REJECTED;
        }
        return result;
    }

    void handleCurrentChar(string *inputString, size_t *currentIndex){
        char &head_symbol = (*inputString)[*currentIndex];
        for(pair<Rule,State *> trans : currentState.transition){
            if(trans.first.inputSymbol == head_symbol){
                head_symbol = trans.first.outputSymbol;
                *currentIndex = (trans.first.direction == Direction::LEFT)? 
                            *currentIndex -1 : *currentIndex+1;
                currentState.name = (*(trans.second)).name;
                currentState.transition = (*(trans.second)).transition;
                return;
            }
        }
    }

    void printCurrentConfig(string inputString, size_t currentIndex){
        string s1 = "", s2 = "";
        s1.append(inputString, 0, currentIndex);
        s2.append(inputString, currentIndex, inputString.length()-currentIndex);
        cout << s1 << " " << currentState.name << " " << s2 << endl;
    }
};

int main(){
    Rule r1('0', 'B', Direction::RIGHT);
    Rule r2('1', 'B', Direction::RIGHT);
    Rule r3('B', 'B', Direction::RIGHT);
    
    State q0; q0.name = "q0";
    State q1; q1.name = "q1";
    State q2; q2.name = "q2";
    State qa; qa.name = "qa";
    State qr; qr.name = "qr";
   
    q0.transition.emplace(r1, &q1);
    q0.transition.emplace(r2, &qr);
    
    q1.transition.emplace(r1, &q2);
    q1.transition.emplace(r2, &q1);
    q1.transition.emplace(r3, &qr);

    q2.transition.emplace(r3, &qa);
    q2.transition.emplace(r1, &qr);
    q2.transition.emplace(r2, &qr);

    TuringMachine tm(q0, qa, qr, {q0, q1, q2, qa, qr}, {'0', '1'}, {'0', '1', 'B'});
    
    // //cout << "Enter the input string: ";
    // // string input;
    // // cin >> input;
    Result result = tm.processInputString("01111110BBBB");
    if(result == Result::ACCEPTED)
        cout << "The input string is accepted." << endl;
    else if(result == Result::REJECTED)
        cout << "The input string is rejected." << endl;

    return 0;
}