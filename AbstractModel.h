#pragma once
#include "Model.h"
#include "AbstractState.h"
#include "OriginalModel.h"
#include "Header.h"

class AbstractModel :
    public Model
{
 private:
    vector<AbstractState> abstractStates;
    vector<int> initialStates;
    void changeTables(OriginalModel originalModel, vector<int> statesForNewAbstractState, AbstractState newAbstractState); // Sub of the update Tables
    void updateTables(OriginalModel originalModel, vector<int> statesForNewAbstractState, AbstractState newAbstractState);
    vector<int> removeOriginals(OriginalModel originalModel, vector<int> statesOut, int stateToSplit, int stateIn, vector<int> statesIn, int outTable_line_index);

public:
    vector<AbstractState> getAbstractStates();
    vector<int> getInitialStates();
    void setAbstractStatesList(vector<AbstractState> list);
    void setInitialStates(vector<int> initialStatesList);
    void init_InTable(OriginalModel originalModel);
    void init_OutTable(OriginalModel originalModel);
    void statesDivision(OriginalModel originalModel, int stateToSplit, int stateIn);
    

    AbstractModel() 
    {
        AbstractModel::abstractStates = {};
        AbstractModel::initialStates = {};
    }
    

    AbstractModel(vector<AbstractState> abstract_states, vector<int> initial_states, int num_of_states)
        : abstractStates(abstract_states), initialStates(initial_states)
    {
        Model{ num_of_states };
    }
};