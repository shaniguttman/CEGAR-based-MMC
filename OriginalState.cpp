#include "OriginalState.h"

vector<int> OriginalState::getStatesIn_index()
{
    return statesIn_index;
}

vector<int> OriginalState::getStatesOut_index()
{
    return statesOut_index;
}

void OriginalState::setStatesIn_index(vector<int> statesIn)
{
    statesIn_index = statesIn;
}

void OriginalState::setStatesOut_index(vector<int> statesOut)
{
    statesOut_index = statesOut;
}

void OriginalState::pushBackStatesIn_index(int index)
{
    statesIn_index.push_back(index);
}

void OriginalState::pushBackStatesOut_index(int index)
{
    statesOut_index.push_back(index);
}