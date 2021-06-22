#pragma once
#include "State.h"
#include "Table.h"
#include "Header.h"

 class AbstractState :
    public State
{    
private:
    Table inTable;
    Table outTable;
    vector<int> originalStates_index;
public:
    AbstractState(Table in_table, Table out_table, vector<int> original_states_index, int index) :
        inTable(in_table), outTable(out_table), originalStates_index(original_states_index), State{ {""}, index }
    {

    }

    AbstractState() {}

   
    vector<int> getOriginalStates_index();
    Table getInTable();
    Table getOutTable();
    void setAbstractStateIndex(bool isInTable, int line_index, int newAbstractIndex);
    void delOriginalStatesOutTable(int table_line_index);
    void delOriginalStatesInTable(int table_line_index);
    void removeOriginalStates(bool isInTable, vector<int> irrelevantStates);
    void pushBackInTable(In_Out_Line newLine);
    void pushBackOutTable(In_Out_Line newLine);
    void setAnotherOriginalState(int stateToAdd, int indexInTable, bool in);
    void originalStates_index_push_back(int i);
};