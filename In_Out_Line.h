#pragma once
#include "Header.h"

class In_Out_Line {

private:
    int abstractStateIndex;
    vector<int> originalStatesIndex;

public:
    In_Out_Line()
    {
        abstractStateIndex = 0;
        originalStatesIndex = {};
    }


    In_Out_Line(int abstractState_index, int originalState_index)
        : abstractStateIndex(abstractState_index)
    {
        originalStatesIndex.push_back(originalState_index);
    }


    bool setAnotherOriginalState(int originalState_index);
    //function to add new original state index 
    int getAbstractStateIndex();
    vector<int> getOriginalStates();
    void setAbstractStateIndex(int abstractState);
    void delOriginalState(int indexInVector); // Deleting specific original state
};