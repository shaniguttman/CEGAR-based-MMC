#include "System.h"

// Setting the abstract states of the abstract model
void System::setAbstractModelStates(vector<AbstractState> abstractStates)
{
	A.setAbstractStatesList(abstractStates);
}

OriginalModel System::getM1()
{
	return M1;
}

AbstractModel System::getA()
{
	return A;
}

// Setting the initial states of the abstract
void System::setAInitialStates(vector<int> initialStatesList)
{
	A.setInitialStates(initialStatesList);
}

// The simulator which returns whether the system satisfies the formula or not
bool System::MMC(vector<vector<string>>* cex, int probability) {

	int i = rand() % 100; // Randomizing numbers from 0 to 99

	if (i <= probability) 
		return true; // In case the system satisfies the formula - return true
	
	int indexOfOutTable = -1;
	vector<vector<string>> trace = {}; // Create an empty trace
	vector<int> initialStates = A.getInitialStates(); // Get the initial states of the abstract state
	
	// Choose a random index from the initialstates and put it in randomIndexIntialState
	int size = initialStates.size();
	int randomIndexIntialState = rand() % size;

	// The index of the abstract state is initialStates[randomIndexIntialState]
	// Get the abstractState
	AbstractState state = A.getAbstractStates()[initialStates[randomIndexIntialState]];
	vector<string> nextAP = state.getAPlist();
	trace.push_back(nextAP); // Add the AP to the trace
	vector < In_Out_Line >stateslist = state.getOutTable().getTable(); // Getting the OutTable

	i = rand() % 20 + 1; // Ranging from 0 to 20 - choose random length for the future trace;

	while (i - 1) 
	{
		size = stateslist.size();
		if (!size) 
			break; // If there is no next edge then stop creating the trace
		indexOfOutTable = rand() % size; // Choose a random index from the table
		int nextState = stateslist[indexOfOutTable].getAbstractStateIndex(); // Get the abstractstate index that is presented in the table 
		state = A.getAbstractStates()[nextState]; // Get the abstractstate with the index "nextState"
		nextAP = state.getAPlist(); // Get the AP list
		trace.push_back(nextAP); // Add the AP to the trace
		stateslist = state.getOutTable().getTable(); // Get the outTtable of the abstractState
		i--;
	}

	*cex = trace; // Return the counterexample
	return false;
}

//update two int pointers the index of tthw state that have the illegal esge, return true if succeded
bool System::findAbstractStateToSplit(vector<vector<string>> trace, int maxTraceIndex, int* firstState, int* secondState)
{ 
	for (int i = 0; i < A.getInitialStates().size(); i++)
	{
		//set all first variables
		int index = A.getInitialStates()[i];//find the first fitting state of the path
		vector<string> ap = A.getAbstractStates()[index].getAPlist();
		if (A.getAbstractStates()[index].getAPlist() == trace[0])
		{
			//set variables and call recursive function after done wth intial state
			int stateIndex = A.getInitialStates()[i];
			AbstractState state = A.getAbstractStates()[stateIndex];
			vector<In_Out_Line> outLineList = state.getOutTable().getTable();
			if (recursiveFindAbstractStateToSplit(trace, 1, stateIndex, outLineList, maxTraceIndex, firstState, secondState))
				return true;
		}
	}
	return false;
}
 bool System ::recursiveFindAbstractStateToSplit(vector<vector<string>> trace, int traceIndex, int stateIndex, vector<In_Out_Line> stateList, int maxTraceIndex, int* firstState, int* secondState)
{
	{      
			if ((traceIndex - 1) == maxTraceIndex)//if it is the last state in the maximal path
				*firstState = stateIndex;
			if ((traceIndex - 1) == maxTraceIndex + 1)
			{
				*secondState = stateIndex;
				//return true;
			}
			if ((traceIndex) == trace.size()) return true; //maxTraceIndex)
		 for (int i = 0; i < stateList.size(); i++) //check each state of an out-edge
		 {
			 bool val = -1;
			 int nextStateIndex = stateList[i].getAbstractStateIndex(); //index of the state in the out-edge
			 if (containTheSame(trace[traceIndex], A.getAbstractStates()[nextStateIndex].getAPlist() )) // if the state's ap are equal to the current ap in the tace cell
			 {
				 val= recursiveFindAbstractStateToSplit(trace, traceIndex + 1, nextStateIndex,A.getAbstractStates()[nextStateIndex].getOutTable().getTable(), maxTraceIndex, firstState, secondState); //keep go in this direction and check next trace cell
				 if (val) //the rest of the trace was completed properly, we can end the search
				 {

					 return true;
				 }
			 }

		 }
		 return false; // no trace like this was found int the model
	 }

}

 // Refining the abstract model
void System::refine(vector<vector<string>> cex,int maxTraceIndex) {
	int stateToSplit = -1, stateIn = -1;

	findAbstractStateToSplit(cex, maxTraceIndex, &stateToSplit, &stateIn); //setting first variables Finding the abstract state to split

	A.statesDivision(M1, stateToSplit, stateIn); // Dividing the state to split
}

// Initializing the first abstract model
void System::initialize() {
	statesGrouping(); // Grouping the original states that have the same APs
	A.init_InTable(M1); // Initializing the in table
	A.init_OutTable(M1); // Initializing the out table
}


//eturn the index of abstract state that has same ap list
int System::isExistInAbstractModel(vector<AbstractState> abstractStates, vector<string> ap)
{

	for (int j = 0; j < abstractStates.size();j++)
	{
		if (containTheSame(abstractStates[j].getAPlist(), ap)) return j;
	}
	return -1;
}

//check if the vectors are exqual
bool System::containTheSame(vector<string> ap1, vector<string>ap2)
{
	sort(ap1.begin(), ap1.end());
	sort(ap2.begin(), ap2.end());
	return ap1 == ap2;
}


// Grouping the states with the same APs
void System::statesGrouping() {
	vector<AbstractState> abstractStates;
	vector<int> abstractInitialStateIndex; // Initial state of abstract state by index
	vector<AbstractState> initialState; // Initial state of abstract state by absractstate object

	for (int i = 0; i < M1.getOriginalStates().size();i++)
	{
		vector<string> AP = M1.getOriginalStates()[i].getAPlist(); // Get AP list of the original state

		int index = isExistInAbstractModel(abstractStates, AP); // Check if there already exists an abstract state with the same AP like in the original state
		if (index >= 0)
		{
			abstractStates[index].originalStates_index_push_back(i); // Add the i-th state to the abstract state
			vector<int> originalInitialStates = getM1().getInitialStates();
			if (find(originalInitialStates.begin(), originalInitialStates.end(), i) != originalInitialStates.end()) // Check if the current original state is an initial state
				if(!(find(abstractInitialStateIndex.begin(), abstractInitialStateIndex.end(), index) != abstractInitialStateIndex.end())) // Check if the current abstract state already exists in the initial states
					abstractInitialStateIndex.push_back(index); // Adding the index to the initial states
		}
		else
		{
			AbstractState element; 
			element.originalStates_index_push_back(i); // Adding the state to a new abstract state
			element.setAPlist(AP); // Setting the APs of the abstract state
			abstractStates.push_back(element); // Adding the state to the abstract states of the model
			vector<int> originalInitialStates = getM1().getInitialStates();
			if (find(originalInitialStates.begin(), originalInitialStates.end(), i) != originalInitialStates.end()) // Check if the current original state is an initial state
					abstractInitialStateIndex.push_back(abstractStates.size()-1); // Add the abstract state to the initial abstract states list
		}
	}

	setAInitialStates(abstractInitialStateIndex);
	setAbstractModelStates(abstractStates);
	A.setNumOfStates(abstractStates.size());;
}
/// **Recursive function**
// trace - the trace we want to find in the model
// traceIndex - the index of the current cell for the trace that we want to check
// stateIndex - the current selected state
// stateList - all the states of the out-edges
// maxTraceIndex - the maximal equal trace(length) we have found in the model

//check if the cex exist in the original model
bool System::isRealCex(vector<vector<string>> trace, int* max)
{
	bool value=SubRecourseIsRealCex(trace, 0, -1, M1.getInitialStates(), max);//setting initial variables
	if (value)
	{
		cout << "\n A counter example was found:\n";
		for (int i = 0; i < trace.size(); i++)
		{
			cout << "(";
			for(int j = 0; j < trace[i].size(); j++)
			{ 
				cout << trace[i][j];
			}
			cout << ")";
		}
		cout << "\n";
	}

	return value;
}

//check if the cex exist in the original model, set maiximal fitiing path length initial states and other parameters.l
bool System::SubRecourseIsRealCex(vector<vector<string>> trace, int traceIndex, int stateIndex, vector<int> stateList, int* maxTraceIndex)
{
	if (traceIndex - 1 > *maxTraceIndex)*maxTraceIndex = traceIndex - 1; // If we arrived to the maximal index of the trace so far then save it
	if (traceIndex == trace.size()) // If the whole trace was found
	{
		return true;
	}

	for (int i = 0; i < stateList.size(); i++) // Check each state of an out-edge
	{
		bool val = -1;
		int nextStateIndex = stateList[i]; // Index of the state in the out-edge
		if (containTheSame(trace[traceIndex], (M1.getOriginalStates())[nextStateIndex].getAPlist())) // If the APs of the state are equal to the current AP in the trace cell
		{
			
			val = SubRecourseIsRealCex(trace, traceIndex + 1, nextStateIndex, M1.getOriginalStates()[nextStateIndex].getStatesOut_index(), maxTraceIndex); // Keep moving in this direction and check the next trace cell
			if (val) // The rest of the trace was completed properly, so we can end the search
			{
				
				return true;
			}
		}

	}
	return false; // No trace like this was found in the model
}