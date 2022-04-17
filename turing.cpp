#include <iostream>
#include <vector>
#include <map> 
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
    State q0, qa, qr;
    vector<State> states;
    vector<char> input;
    vector<char> tape;

    TuringMachine();

    Result processInputString(string inputString){
        size_t currentIndex = 0;
        State currentState = q0;
        Result result = Result::ONGOING;
        printCurrentConfig(inputString, currentIndex, currentState);
        while(result == Result::ONGOING){
            handleCurrentChar(inputString, currentIndex, currentState);
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
                head_symbol = transition.first.outputSymbol;
                currentIndex = (transition.first.direction == Direction::LEFT)? 
                            currentIndex -= 1 : currentIndex+=1;
                currentState = transition.second;
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

int main(){
    Rule r1('0', 'B', Direction::RIGHT);
    Rule r2('1', 'B', Direction::RIGHT);
    Rule r3('B', 'B', Direction::RIGHT);
    
    State q0("q0");
    State q1("q1");
    State q2("q2");
    State qa("qa");
    State qr("qr");
    
    q0.transition.emplace(r1, q1);
    q0.transition.emplace(r2, qr);
    
    q1.transition.emplace(r1, q2);
    q1.transition.emplace(r2, q1);
    q1.transition.emplace(r3, qr);

    q2.transition.emplace(r3, qa);
    q2.transition.emplace(r1, qr);
    q2.transition.emplace(r2, qr);

    TuringMachine tm;
    tm.q0 = q0;
    tm.qa = qa;
    tm.qr = qr;
    tm.states = {q0, q1, q2, qa, qr};
    //Input symbols are for overwriting tape symbols
    tm.input = {'0', '1'};
    tm.tape = {'0', '1', 'B'};
    
    //cout << "Enter the input string: ";
    // string input;
    // cin >> input;
    Result result = tm.processInputString("01111110BBBB");
    if(result == Result::ACCEPTED)
        cout << "The input string is accepted." << endl;
    else
        cout << "The input string is rejected." << endl;

    return 0;
}