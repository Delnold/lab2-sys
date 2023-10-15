#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <fstream>

using namespace std;

class DFA {
public:
    int alphabetCount;
    int statesCount;
    int startState;
    int finalStatesCount;

    struct StateTransition {
        int currentState;
        char transitionSymbol;
        int nextState;
    };
    vector<int> finalStates;
    vector<StateTransition> statesTransition;

    DFA(int alphabetCount, int statesCount, int startState,
        int finalStatesCount, vector<int> finalStates,
        vector<StateTransition> statesTransition) {
        this->alphabetCount = alphabetCount;
        this->statesCount = statesCount;
        this->startState = startState;
        this->finalStatesCount = finalStatesCount;
        this->finalStates = finalStates;
        this->statesTransition = statesTransition;
    }

    bool canReachEndFromStart(int start, int finish, set<int>& visited) {
        visited.insert(start); 

        if (start == finish) {
            return true; 
        }

        for (const StateTransition& transition : statesTransition) {
            if (transition.currentState == start) {
                int nextState = transition.nextState;
                if (visited.find(nextState) == visited.end()) {
                    if (canReachEndFromStart(nextState, finish, visited)) {
                        return true;
                    }
                }
            }
        }

        return false; 
    }
    vector<char> dfsForAll(){
        vector<char> resultSymbols;
        for (auto transition : statesTransition){
            set<int> visitedStart;
            if (canReachEndFromStart(startState, transition.currentState, visitedStart)){
                for (auto state : finalStates){
                    set<int> visitedEnd;
                    if (canReachEndFromStart(transition.nextState, state, visitedEnd)){
                        resultSymbols.push_back(transition.transitionSymbol);
                        break; 
                    }
                } 
            }
        }
        return resultSymbols;
    }
    void printResults(){
        vector<char> output = this->dfsForAll();
        cout << "Letters which can`t reach final states: " << endl;
        for (char symbol : output) {
            cout << symbol << endl;
        }

    }
};
int main() {

    int alphabetCount;
    int statesCount;
    int startState;
    int finalStatesCount;
    vector<int> finalStates;
    vector<DFA::StateTransition> statesTransition;

    std::ifstream file("text.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    file >> alphabetCount >> statesCount >> startState >> finalStatesCount;

    for (int i = 0; i < finalStatesCount; i++) {
        int finalState;
        file >> finalState;
        finalStates.push_back(finalState);
    }
    int state, nextState;
    char inputSymbol;
    while (file >> state >> inputSymbol >> nextState) {
        DFA::StateTransition transition;
        transition.currentState = state;
        transition.transitionSymbol = inputSymbol;
        transition.nextState = nextState;
        statesTransition.push_back(transition);
    }
    DFA dfa1 (alphabetCount, statesCount, startState, finalStatesCount,
        finalStates, statesTransition);
        
    DFA dfa2(3, 3, 0, 1, {2}, {
        {0, 'a', 1},
        {1, 'b', 2},
        {2, 'c', 4},
    });
    DFA dfa3(3, 3, 0, 1, {}, {
        {1, 'a', 2},
        {2, 'd', 3},
        {3, 'e', 1},
    });
    dfa1.printResults();
    dfa2.printResults();
    dfa3.printResults();

}
