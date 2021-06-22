#pragma once
#include "Model.h"
#include "OriginalState.h"
#include "Header.h"



class OriginalModel :
    public Model
{
private:
    vector<OriginalState> originalStates{};
    vector<int> initialStates{};

public:
    OriginalModel() {

        OriginalModel::originalStates = {};
        OriginalModel::initialStates = {};
    }

    OriginalModel(vector<OriginalState> original_states, vector<int> initial_states, int num_of_states)
        : originalStates(original_states), initialStates(initial_states)
    {
        Model{ num_of_states };
    }

    vector<int> getInitialStates();
    vector<OriginalState> getOriginalStates();
    void setInitialStates(vector<int> initial_states);
    void setOriginalStates(vector<OriginalState> original_states);
    void push_back_initialState(int stateIndex);
    void push_back_AP(int stateIndex, string ap);
    void pushBackStatesOut_index(int stateIndex, int toState);
    void pushBackStatesIn_index(int stateIndex, int fromState);
    void originalStatesPushBack(OriginalState state);
};
