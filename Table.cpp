#include "Table.h"


vector<In_Out_Line> Table::getTable()
{
	return table;
}

// Adding another original state to the line in the table
void Table::setAnotherOriginalState(int stateToAdd, int indexInTable)
{
	bool ans;
	ans = table[indexInTable].setAnotherOriginalState(stateToAdd);
}

// Adding a new line to the table (with a new abstract state)
void Table::pushBack(In_Out_Line newLine)
{
	table.push_back(newLine);
}

// Setting the abstract state index to the line in the table
void Table::setAbstractStateIndex(int line_index, int newAbstractIndex)
{
	table[line_index].setAbstractStateIndex(newAbstractIndex);
}

// Deleting a specific line from the table
void Table::delOriginalStates(int table_line_index)
{
	table.erase(table.begin() + table_line_index);
}


// Removing all of the irrelavant original states from the table
void Table::removeOriginalStates(vector<int> irrelavantOriginalStates)
{
	for (int i = 0; i < table.size(); i++)
	{
		for (int j = 0; j < table[i].getOriginalStates().size(); j++)
		{
			for (int k = 0; k < irrelavantOriginalStates.size(); k++)
			{
				if (i < table.size())
				{
					if (j < table[i].getOriginalStates().size())
					{
						if (irrelavantOriginalStates[k] == table[i].getOriginalStates()[j])
						{
							// Deleting the state
							table[i].delOriginalState(j);


							// Checking if the edge still remains
							if (table[i].getOriginalStates().size() == 0) // In case no original state remain - remove the edge of the abstract model
							{
								table.erase(table.begin() + i);
							}
						}

					}
				}

			}

			if (table.size() <= i)
			{
				break;
			}
		}
	}
}

// Searches for an abstract state index, if exists returns the index in table, else it returns -1
int Table::searchForAbstractStateIndex(int index)
{
	if (index == -1)
		return -1;
	for (int i = 0; i < table.size(); i++)
	{
		if (table[i].getAbstractStateIndex() == index)
			return i;
	}

	return -1;
}