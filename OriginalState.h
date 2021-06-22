#pragma once
#include "State.h"

class OriginalState :
    public State
{
private: 
    vector<int> statesIn_index{};
    vector<int> statesOut_index{};

public:
    OriginalState() {}


    OriginalState(vector<int> states_in_index, vector<int> states_out_index, int index) :
        statesIn_index(states_in_index), statesOut_index(states_out_index), State{ {""}, index}
    {
    }

    vector<int> getStatesIn_index();
    vector<int> getStatesOut_index();
    void setStatesIn_index(vector<int> statesIn);
    void setStatesOut_index(vector<int> statesOut);
    void pushBackStatesIn_index(int index);
    void pushBackStatesOut_index(int index);
};