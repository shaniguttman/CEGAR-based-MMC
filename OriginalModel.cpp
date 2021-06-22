#include "OriginalModel.h"

vector<int> OriginalModel::getInitialStates()
{
    return initialStates;
}

vector<OriginalState> OriginalModel::getOriginalStates()
{
    return originalStates;
}


void OriginalModel::setInitialStates(vector<int> initial_states)
{
    initialStates = initial_states;
}


void OriginalModel::setOriginalStates(vector<OriginalState> original_states)
{
    originalStates = original_states;
}

void OriginalModel::push_back_initialState(int stateIndex)
{
    initialStates.push_back(stateIndex);
}

void OriginalModel::push_back_AP(int stateIndex, string ap)
{
    originalStates[stateIndex].push_back_AP(ap);
}

void OriginalModel::pushBackStatesOut_index(int stateIndex, int toState)
{
    originalStates[stateIndex].pushBackStatesOut_index(toState);
}
void OriginalModel::pushBackStatesIn_index(int stateIndex, int fromState)
{
    originalStates[stateIndex].pushBackStatesIn_index(fromState);
}

void OriginalModel::originalStatesPushBack(OriginalState state)
{
    originalStates.push_back(state);
}
