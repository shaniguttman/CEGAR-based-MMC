#include "In_Out_Line.h"


bool In_Out_Line::setAnotherOriginalState(int originalState_index)
{
    if (originalState_index == -1)
        return false;
    for (int i = 0; i < originalStatesIndex.size(); i++)
        if (originalStatesIndex[i] == originalState_index) // In case the original state has been added already
            return false;
    originalStatesIndex.push_back(originalState_index);
    return true;
}


//function to add new original state index 
int In_Out_Line::getAbstractStateIndex()
{
    return abstractStateIndex;
}


vector<int> In_Out_Line::getOriginalStates()
{
    return originalStatesIndex;
}

void In_Out_Line::setAbstractStateIndex(int abstractState)
{
    abstractStateIndex = abstractState;
}


void In_Out_Line::delOriginalState(int indexInVector) // Deleting specific original state
{
    originalStatesIndex.erase(originalStatesIndex.begin() + indexInVector);
}