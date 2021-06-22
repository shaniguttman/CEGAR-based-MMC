#pragma once
#include "In_Out_Line.h"
#include "Header.h"

class Table {
private:

public:
	vector<In_Out_Line> table;

	Table()
	{
		table = {};
	}

	vector<In_Out_Line> getTable();
	void setAnotherOriginalState(int stateToAdd, int indexInTable);
	void pushBack(In_Out_Line newLine);
	void setAbstractStateIndex(int line_index, int newAbstractIndex);
	void delOriginalStates(int table_line_index);
	// Removing all of the irrelavant original states from the table
	void removeOriginalStates(vector<int> irrelavantOriginalStates);
	// Searches for an abstract state index, if exists returns the index in table, else it returns -1
	int searchForAbstractStateIndex(int index);

};