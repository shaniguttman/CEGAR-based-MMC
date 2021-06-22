#pragma once
#include "Model.h"
#include "OriginalModel.h"
#include "AbstractModel.h"


class System
{
private:
    OriginalModel M1;
    OriginalModel M2;
    AbstractModel A; //The abstract is for M1 - all the abstract versions
    int isExistInAbstractModel(vector<AbstractState> abstractStates, vector<string> ap);
    bool containTheSame(vector<string> ap1, vector<string>ap2);
    bool SubRecourseIsRealCex(vector<vector<string>> trace, int traceIndex, int stateIndex, vector<int> stateList, int* maxTraceIndex);
    
public:
    void setAbstractModelStates(vector<AbstractState> abstractStates);
    OriginalModel getM1();
    AbstractModel getA();
    void initialize();
    bool MMC(vector<vector<string>>* cex, int probability);
    bool isRealCex(vector<vector<string>> trace, int* max);
    void refine(vector<vector<string>> cex, int maxTraceIndex); //Change the input and output of func
    void setAInitialStates(vector<int> initialStatesList);
    void statesGrouping();
    bool recursiveFindAbstractStateToSplit(vector<vector<string>> trace, int traceIndex, int stateIndex, vector<In_Out_Line> stateList, int maxTraceIndex, int* firstState, int* secondState);
    bool findAbstractStateToSplit(vector<vector<string>> trace, int maxTraceIndex, int* firstState, int* secondState);
   

    // Initialize a system
    System(OriginalModel m1, OriginalModel m2, AbstractModel a)
        : M1(m1), M2(m2), A(a)
    {
    }
};