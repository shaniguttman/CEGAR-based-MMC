#include "AbstractState.h"

vector<int> AbstractState::getOriginalStates_index() {
    return originalStates_index;
}

Table AbstractState::getInTable()
{
    return inTable;
}

Table AbstractState::getOutTable()
{
    return outTable;
}

void AbstractState::setAbstractStateIndex(bool isInTable, int line_index, int newAbstractIndex)
{
    if (isInTable)
    {
        inTable.setAbstractStateIndex(line_index, newAbstractIndex);
    }

    else
    {
        outTable.setAbstractStateIndex(line_index, newAbstractIndex);
    }
}

void AbstractState::delOriginalStatesOutTable(int table_line_index)
{
    outTable.delOriginalStates(table_line_index);
}

void AbstractState::delOriginalStatesInTable(int table_line_index)
{
    inTable.delOriginalStates(table_line_index);
}

void AbstractState::removeOriginalStates(bool isInTable, vector<int> irrelevantStates)
{
    if (isInTable)
    {
        inTable.removeOriginalStates(irrelevantStates);
    }

    else
    {
        outTable.removeOriginalStates(irrelevantStates);
    }
}

void AbstractState::pushBackInTable(In_Out_Line newLine)
{
    inTable.pushBack(newLine);
}


void AbstractState::pushBackOutTable(In_Out_Line newLine)
{
    outTable.pushBack(newLine);
}

void AbstractState::setAnotherOriginalState(int stateToAdd, int indexInTable, bool in)
{
    if (in == true)
        inTable.setAnotherOriginalState(stateToAdd, indexInTable);
    else
        outTable.setAnotherOriginalState(stateToAdd, indexInTable);
}
void AbstractState::originalStates_index_push_back(int i)
{

    originalStates_index.push_back(i);
}