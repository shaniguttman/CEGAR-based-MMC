#include "AbstractModel.h"


vector<AbstractState> AbstractModel::getAbstractStates()
{
	return abstractStates;
}

vector<int> AbstractModel::getInitialStates()
{
	return initialStates;
}
void AbstractModel::setAbstractStatesList(vector<AbstractState> list)
{
	abstractStates = list;
}

void AbstractModel::setInitialStates(vector<int> initialStatesList)
{
	initialStates = initialStatesList;
}

// Getting the original model
// Initializing the in table of the abstract states using the original states and their edges after they have been grouped.
void AbstractModel::init_InTable(OriginalModel originalModel) {

	vector<int> originalStates_index;
	vector<int> originalStates_index2;
	vector<OriginalState> originalStates;
	OriginalState originalState;
	int originalIndex;
	int stateToAdd = -1;
	int tempOriginalState;
	int abstractStateToAdd = -1;
	In_Out_Line newLine;
	int indexInTable;

	// For each abstract state
		// For each original state
			// Check which original states have an edge that goes into this state
			// Check whether the other abstract state has the out edge for this original state - if there is, add this original state as causing the edge, otherwise add another line in the table
			// Add every abstract state that has an edge into this abstract state and the original states causing the edge.
	for (int i = 0; i < abstractStates.size(); i++) // For each abstract state
	{
		originalStates_index = abstractStates[i].getOriginalStates_index();
		for (int j = 0; j < originalStates_index.size(); j++) // For each original state
		{
			originalIndex = originalStates_index[j]; // Getting the actual index of the j's original state in the abstract
			originalStates = originalModel.getOriginalStates(); // Getting all of the original states from the original model
			originalState = originalStates[originalIndex]; // Getting the original state which has the originalIndex
			for (int k = 0; k < originalState.getStatesIn_index().size(); k++) // All the states which have an edge that goes into the original state
			{
				tempOriginalState = originalState.getStatesIn_index()[k];
				for (int l = 0; l < abstractStates.size(); l++) // For each abstract state
				{
					originalStates_index2 = abstractStates[l].getOriginalStates_index();
					for (int m = 0; m < originalStates_index2.size(); m++) // For each original state
					{
						if (originalStates_index2[m] == tempOriginalState)
						{
							abstractStateToAdd = l;
							stateToAdd = originalIndex;

							if (abstractStates[i].getInTable().searchForAbstractStateIndex(abstractStateToAdd) == -1) // Search for an abstract state index
							{
								// In case the abstract state was not found in the InTable, add a new line for it
								newLine = In_Out_Line(abstractStateToAdd, stateToAdd);  
								abstractStates[i].pushBackInTable(newLine);
							}

							else // In case the abstract state was found in the InTable, add another original state causing the edge
							{
								indexInTable = abstractStates[i].getInTable().searchForAbstractStateIndex(abstractStateToAdd);
								abstractStates[i].setAnotherOriginalState(stateToAdd, indexInTable, true);
							}

						}
					}

				}

			}
		}
	}

}


// Getting the original model
// Initializing the out table of the abstract states using the original states and their edges after they have been grouped.
void AbstractModel::init_OutTable(OriginalModel originalModel) {
	vector<int> originalStates_index;
	vector<int> originalStates_index2;
	vector<OriginalState> originalStates;
	OriginalState originalState;
	int originalIndex;
	int stateToAdd = -1;
	int tempOriginalState;
	int abstractStateToAdd = -1;
	In_Out_Line newLine;
	int indexOutTable;



	// For each abstract state
		// For each original state
			// Check which original states have an edge that goes out of this state
			// Check whether the other abstract state has the in edge for this original state - if there is, add this original state as causing the edge, otherwise add another line in the table
			// Add every abstract state that has an edge out of this abstract state and the original states causing the edge.
	for (int i = 0; i < abstractStates.size(); i++) // For each abstract state
	{
		originalStates_index = abstractStates[i].getOriginalStates_index();
		for (int j = 0; j < originalStates_index.size(); j++)
		{// For each original state
			originalIndex = originalStates_index[j];
			originalStates = originalModel.getOriginalStates();
			originalState = originalStates[originalIndex];

			for (int k = 0; k < originalState.getStatesOut_index().size(); k++) // All the states go out of the original state
			{
				tempOriginalState = originalState.getStatesOut_index()[k];
				for (int l = 0; l < abstractStates.size(); l++) // For each abstract state
				{
					originalStates_index2 = abstractStates[l].getOriginalStates_index();
					for (int m = 0; m < originalStates_index2.size(); m++) // For each original state
					{
						if (originalStates_index2[m] == tempOriginalState)
						{
							abstractStateToAdd = l;
							stateToAdd = originalIndex;


							if (abstractStates[i].getOutTable().searchForAbstractStateIndex(abstractStateToAdd) == -1) // Search for an abstract state index
							{
								// In case the abstract state was not found in the OutTable, add a new line for it
								newLine = In_Out_Line(abstractStateToAdd, stateToAdd);
								abstractStates[i].pushBackOutTable(newLine);
							}

							else // In case the abstract state was found in the OutTable, add another original state causing the edge
							{
								indexOutTable = abstractStates[i].getOutTable().searchForAbstractStateIndex(abstractStateToAdd);
								abstractStates[i].setAnotherOriginalState(stateToAdd, indexOutTable, false);
							}
						}
					}
				}
			}
		}
	}

}


// Gets the original model, the index of the state to split and the state that has the problematic edge in 
// Halving the abstract state to split (the original states that causes the counterexample will be moved to a new abstract state)
void AbstractModel::statesDivision(OriginalModel originalModel, int stateToSplit, int stateIn) 
{
	Table inTable, outTable;
	vector<int> statesForNewAbstractState;
	AbstractState newAbstractState;
	bool isInitialState = false;
	vector<int> statesIn, statesOut;
	int outTable_line_index = -1;


	// Initializing statesIn +
	// Initializing outTable_line_index
	// The line with the original states of the state to be split, and saving them
	for (int i = 0; i < abstractStates[stateToSplit].getOutTable().getTable().size(); i++)
	{
		if (abstractStates[stateToSplit].getOutTable().getTable()[i].getAbstractStateIndex() == stateIn)
		{
			outTable_line_index = i; // The index of the line in OutTable of the stateToSplit that describes the problematic edge
		}

		else
		{
			// Adding the states that have an edge into from the state to split
			statesIn.push_back(abstractStates[stateToSplit].getOutTable().getTable()[i].getAbstractStateIndex());
		}

	}

	// Initializing statesOut
	for (int i = 0; i < abstractStates[stateToSplit].getInTable().getTable().size(); i++)
	{
		// Adding the states that have an edge out to the state to split
		statesOut.push_back(abstractStates[stateToSplit].getInTable().getTable()[i].getAbstractStateIndex());
	}


	// Removing the edges that are connected to the original states that will be moved to the new state
	statesForNewAbstractState = removeOriginals(originalModel, statesOut, stateToSplit, stateIn, statesIn, outTable_line_index);
	newAbstractState = AbstractState(inTable, outTable, statesForNewAbstractState, abstractStates.size()); // Creating a new abstract state

	// Setting the AP list of the new abstract state
	newAbstractState.setAPlist(abstractStates[stateToSplit].getAPlist());

	abstractStates.push_back(newAbstractState); // Adding the new abstract state to the abstraction

	// Checking whether the new abstract state should be an initial state
	for (int i = 0; i < statesForNewAbstractState.size(); i++)
		for (int j = 0; j < originalModel.getInitialStates().size(); j++)
			if (statesForNewAbstractState[i] == originalModel.getInitialStates()[j]) // Checking whether any of the original states is an initial state
			{
				isInitialState = true;
				break;
			}

	if (isInitialState) // In case that one of the original states that are included in this abstract state is an initial state
		initialStates.push_back(newAbstractState.getIndex()); // Adding the new abstract state to the initial states

	isInitialState = false;

	// Checking whether the abstract state which was split should still be an initial state
	for (int i = 0; i < abstractStates[stateToSplit].getOriginalStates_index().size(); i++)
		for (int j = 0; j < originalModel.getInitialStates().size(); j++)
			if (abstractStates[stateToSplit].getOriginalStates_index()[i] == originalModel.getInitialStates()[j]) // Checking whether any of the original states is an initial state
			{
				isInitialState = true;
				break;
			}

	if (!isInitialState) // In case none of the original states which are included in this abstract state is an initial state
	{
		// Deleting the abstract state from the initial states
		for (int i = 0; i < initialStates.size(); i++) // Searching for the index of the abstract state
		{
			if (initialStates[i] == stateToSplit)
				initialStates.erase(initialStates.begin() + i);
		}
	}

	updateTables(originalModel, statesForNewAbstractState, newAbstractState); // Adding the new state edges to the other states

}

// Adding the new state edges to the other states and calling the funtion changeTables to initialize the tables of the new abtract state
void AbstractModel::updateTables(OriginalModel originalModel, vector<int> statesForNewAbstractState, AbstractState newAbstractState) 
{
	vector<int> originalStatesOut;
	vector<int> originalStatesIn;
	OriginalState originalState;
	int stateOut, stateIn;
	In_Out_Line newLine;
	bool lineExists = false;

	// Initializing the inTable of the new abstract state
	// Initializing the outTable of the new abstract state
	changeTables(originalModel, statesForNewAbstractState, newAbstractState);

	// Updating the outTable of the abstract states that have original states which go into the new abstract state original states
	// Collecting the original states that have an edge into the statesForNewAbstractState
	// For each abstract state checking whether it has original states that go into the statesForNewAbstractState
	// Adding the line in the table for the abstract state
	// Adding the relevant original states to this line

	// Passing on the original states of states out, if they have an edge to the new state then create a new line in outTable for the new state
	// Adding all of the original states that have an edge into the new state
	for (int i = 0; i < abstractStates.size(); i++) // For each abstract state
		for (int j = 0; j < abstractStates[i].getOriginalStates_index().size(); j++) // For each original state in this abstract state
		{
			originalState = originalModel.getOriginalStates()[abstractStates[i].getOriginalStates_index()[j]];
			for (int k = 0; k < originalState.getStatesOut_index().size(); k++) 
			{
				stateOut = originalState.getStatesOut_index()[k];
				for (int l = 0; l < statesForNewAbstractState.size(); l++)
				{
					if (stateOut == statesForNewAbstractState[l])
					{

						for (int m = 0; m < abstractStates[i].getOutTable().getTable().size(); m++)
						{
							// In case there is a line with the new abstract state already
							if (abstractStates[i].getOutTable().getTable()[m].getAbstractStateIndex() == newAbstractState.getIndex()) 
							{
								// Adding another original state to an existing line of OutTable
								abstractStates[i].setAnotherOriginalState(originalState.getIndex(), m, false); 
								lineExists = true;
								break;
							}
						}

						// In case there is no line with the new abstract state
						if (lineExists == false)
						{
							// Creating a new line to add to the table
							originalState.getIndex();
							newLine.setAbstractStateIndex(newAbstractState.getIndex()); 
							newLine.setAnotherOriginalState(originalState.getIndex());
							abstractStates[i].pushBackOutTable(newLine); // Adding the new line to the table
						}

						lineExists = false;
					}
				}

			}
		}


	// Updating the inTable of the abstract states that have original states with edges in from the new abstract state original states
	// The abstract state had the problematic edge in - is not included
	// Collecting the original states that have an edge from the statesForNewAbstractState
	// For each abstract state checking whether it has original states from the statesForNewAbstractState
	// Adding the line of the new abstract state
	// Adding the relevant original states to this line
	for (int i = 0; i < abstractStates.size(); i++)
		for (int j = 0; j < abstractStates[i].getOriginalStates_index().size(); j++)
		{
			originalState = originalModel.getOriginalStates()[abstractStates[i].getOriginalStates_index()[j]];
			for (int k = 0; k < originalState.getStatesIn_index().size(); k++)
			{
				stateIn = originalState.getStatesIn_index()[k]; 
				for (int l = 0; l < statesForNewAbstractState.size(); l++)
				{
					if (stateIn == statesForNewAbstractState[l])
					{

						for (int m = 0; m < abstractStates[i].getInTable().getTable().size(); m++)
						{
							// In case there is a line with the new abstract state already
							if (abstractStates[i].getInTable().getTable()[m].getAbstractStateIndex() == newAbstractState.getIndex()) 
							{
								// Adding another original state to an existing line of InTable
								abstractStates[i].setAnotherOriginalState(originalState.getIndex(), m, true);
								lineExists = true;
								break;
							}
						}

						// In case there is no a line with the new abstract state
						if (lineExists == false)
						{
							// Creating a new line to add to the table
							originalState.getIndex();
							newLine.setAbstractStateIndex(newAbstractState.getIndex());
							newLine.setAnotherOriginalState(originalState.getIndex());
							abstractStates[i].pushBackInTable(newLine); // Adding the new line to the table
						}
						lineExists = false;
					}
				}

			}
		}
}
// Updating the edges to the new abstract state
void AbstractModel::changeTables(OriginalModel originalModel, vector<int> statesForNewAbstractState, AbstractState newAbstractState)  
{
	vector<int> originalStates_index;
	vector<int> originalStates_index2;
	vector<OriginalState> originalStates;
	OriginalState originalState;
	int originalIndex;
	int stateToAdd = -1;
	int tempOriginalState;
	int abstractStateToAdd = -1;
	In_Out_Line newLineIn;
	int indexInTable;

	// Updating inTable, outTable of the new abstract state	

	// Updating inTable
	originalStates_index = newAbstractState.getOriginalStates_index();
	for (int j = 0; j < originalStates_index.size(); j++) // For each original state
	{
		originalIndex = originalStates_index[j]; // Getting the actual index of the j's original state in the abstract
		originalStates = originalModel.getOriginalStates(); // Getting all of the original states from the original model
		originalState = originalStates[originalIndex]; // Getting the original state which has the originalIndex
		for (int k = 0; k < originalState.getStatesIn_index().size(); k++) // All the states go into the original state
		{
			tempOriginalState = originalState.getStatesIn_index()[k];
			for (int l = 0; l < abstractStates.size(); l++) // For each abstract state
			{
				originalStates_index2 = abstractStates[l].getOriginalStates_index();
				for (int m = 0; m < originalStates_index2.size(); m++) // For each original state
				{
					if (originalStates_index2[m] == tempOriginalState)
					{
						abstractStateToAdd = l;
						stateToAdd = originalIndex;

						// Search for an abstract state index
						if (newAbstractState.getInTable().searchForAbstractStateIndex(abstractStateToAdd) == -1) 
						{
							// In case there is no line for this abstract state
							newLineIn = In_Out_Line(abstractStateToAdd, stateToAdd);
							abstractStates[abstractStates.size() - 1].pushBackInTable(newLineIn);
						}

						else
						{
							// In case the line for this abstract state is already exists
							// Searching for the line for this abstract state in the table
							indexInTable = newAbstractState.getInTable().searchForAbstractStateIndex(abstractStateToAdd); 
							// Adding another original model to this line
							abstractStates[abstractStates.size() - 1].setAnotherOriginalState(stateToAdd, indexInTable, true);
						}

					}
				}

			}

		}
	}

	// Updating outTable
	stateToAdd = -1;
	abstractStateToAdd = -1;
	In_Out_Line newLineOut;
	int indexOutTable;


	originalStates_index = newAbstractState.getOriginalStates_index();
	for (int j = 0; j < originalStates_index.size(); j++) // For each original state
	{
		originalIndex = originalStates_index[j]; // Getting the actual index of the j's original state in the abstract
		originalStates = originalModel.getOriginalStates(); // Getting all of the original states from the original model
		originalState = originalStates[originalIndex]; // Getting the original state which has the originalIndex

		for (int k = 0; k < originalState.getStatesOut_index().size(); k++) // All the states go out of the original state
		{
			tempOriginalState = originalState.getStatesOut_index()[k];
			for (int l = 0; l < abstractStates.size(); l++) // For each abstract state
			{
				originalStates_index2 = abstractStates[l].getOriginalStates_index();
				for (int m = 0; m < originalStates_index2.size(); m++) // For each original state
				{
					if (originalStates_index2[m] == tempOriginalState) 
					{
						abstractStateToAdd = l;
						stateToAdd = originalIndex;


						if (newAbstractState.getOutTable().searchForAbstractStateIndex(abstractStateToAdd) == -1) // Search for an abstract state index
						{
							// In case there is no line for this abstract state
							newLineOut = In_Out_Line(abstractStateToAdd, stateToAdd);
							abstractStates[abstractStates.size() - 1].pushBackOutTable(newLineOut);
						}

						else
						{
							// In case the line for this abstract state is already exists
							// Searching for the line for this abstract state in the table
							indexOutTable = newAbstractState.getOutTable().searchForAbstractStateIndex(abstractStateToAdd);
							// Adding another original model to this line
							abstractStates[abstractStates.size() - 1].setAnotherOriginalState(stateToAdd, indexOutTable, false);
						}
					}
				}
			}
		}
	}
}

// Removes the irrelevant edges/Updating the edges to have an edge to/from the new abstract state
vector<int> AbstractModel::removeOriginals(OriginalModel originalModel, vector<int> statesOut, int stateToSplit, int stateIn, vector<int> statesIn, int outTable_line_index)  
{
	vector<int> statesForNewAbstractState;
	vector<int> statesIn_index;
	vector<int> statesOut_index;


	statesForNewAbstractState = abstractStates[stateToSplit].getOutTable().getTable()[outTable_line_index].getOriginalStates(); // Get all the original states that cause the problematic edge
	for (int i = 0; i < statesForNewAbstractState.size(); i++) // For each original state that causes the problematic edge
	{
		for (int j = 0; j < originalModel.getOriginalStates()[i].getStatesIn_index().size(); j++) // For each state that has an edge into this original state
		{
			// If the state is the state to split, do not add it to statesIn
			if (originalModel.getOriginalStates()[i].getStatesIn_index()[j] != stateToSplit) 
				statesIn_index.push_back(originalModel.getOriginalStates()[i].getStatesIn_index()[j]);
		}

		for (int k = 0; k < originalModel.getOriginalStates()[i].getStatesOut_index().size(); k++) // For each state that has an edge into from this original state
		{
			// If the state is the state to split, do not add it to statesOut
			if (originalModel.getOriginalStates()[i].getStatesOut_index()[k] != stateToSplit)
				statesOut_index.push_back(originalModel.getOriginalStates()[i].getStatesOut_index()[k]);
		}
	}

	// Sorting the vectors for the simplicity
	sort(statesIn_index.begin(), statesIn_index.end());
	sort(statesOut_index.begin(), statesOut_index.end());
	sort(statesForNewAbstractState.begin(), statesForNewAbstractState.end());

	// Updating the outTable of the states that have an edge out to the state to be split
	for (int i = 0; i < statesOut.size(); i++) // For every state goes into the state to be split
	{
		abstractStates[statesOut[i]].removeOriginalStates(false, statesIn_index);
	}

	// Updating the inTable of the state to be split
	// Deleting the original states in the table
	abstractStates[stateToSplit].removeOriginalStates(true, statesForNewAbstractState);

	// Updating the outTable of the state to be split - deleting the outTable_line creates the problematic edge
	// Saving the original states that has the problematic edges from the original states to be split
	for (int i = 0; i < abstractStates[stateToSplit].getOutTable().getTable().size(); i++)
	{
		if (abstractStates[stateToSplit].getOutTable().getTable()[i].getAbstractStateIndex() == stateIn)
		{
			outTable_line_index = i; 
		}
	}

	// Deleting the original states of the state to be split and saving them
	abstractStates[stateToSplit].delOriginalStatesOutTable(outTable_line_index); 
	// Deleting the other original states in the table
	abstractStates[stateToSplit].removeOriginalStates(false, statesForNewAbstractState);



	// Updating the inTable of the state that has an edge in from the state to be split
	for (int i = 0; i < abstractStates[stateIn].getInTable().getTable().size(); i++)
	{
		if (abstractStates[stateIn].getInTable().getTable()[i].getAbstractStateIndex() == abstractStates[stateToSplit].getIndex())
		{
			abstractStates[stateIn].setAbstractStateIndex(true, i, abstractStates.size()); // Changing the abstract state index to be the new abstract state index 
		}
	}

	// Updating the inTable of the states that have an edge in from the state to be split
	for (int i = 0; i < statesIn.size(); i++) // For every state that has an edge goes out from the state to be split
	{
		abstractStates[statesIn[i]].removeOriginalStates(true, statesOut_index); // Remove the originals that we move to the new abstract state
	}


	// Only the state that has an edge in from the state to be split is updated fully on this function

	return statesForNewAbstractState;
}