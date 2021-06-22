#include "Header.h"
#include "OriginalModel.h"
#include "AbstractModel.h"
#include "System.h"
#include "Encoding.h"

#define P1 30
#define P2 50
#define P3 10
#define P4 90


int main()
{
	srand(time(NULL));
	int numOfStatesBeginning;
	int numOfNewAbstracts;
	char c;
	bool result;

	string path;
	cout << "Please enter a path of the encoding file:\n";
	getline(cin, path); 
	//path = "./Examples of inputs/system1.txt"; //
	Encoding encode;
	System system = encode.initialize(path);
	system.initialize();//create
	numOfStatesBeginning = system.getA().getAbstractStates().size();

	
	vector<vector<string>> counterExample = {};
	while (true)
	{
		result=system.MMC(&counterExample, P2);
		if (result == true)
		{
			numOfNewAbstracts = system.getA().getAbstractStates().size() - numOfStatesBeginning+1;

			cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
			cout << "\n\nThe system satisfies the formula!\n";
			cout << numOfNewAbstracts << " abstracts have been created.\n";
			if (system.getA().getAbstractStates().size() == system.getM1().getOriginalStates().size())
				cout << "We have returned to the original model.\n";
			else
				cout << "We have not returned to the original model.\n";
			cout << "\nPress any key to exit the program\n";
			cin >> c;
			return 0;
		}
		int maximalTraceLen=-1;
		if (system.isRealCex(counterExample,&maximalTraceLen))
		{
			numOfNewAbstracts = system.getA().getAbstractStates().size() - numOfStatesBeginning+1;

			cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
			cout << "\n\nThe system does not satisfy the formula!\n";
			cout << numOfNewAbstracts << " abstracts have been created.\n";
			if (system.getA().getAbstractStates().size() == system.getM1().getOriginalStates().size())
				cout << "We have returned to the original model.\n";
			else
				cout << "We have not returned to the original model.\n";
			cout << "\nPress any letter and then enter to exit the program\n";
			cin >> c;
			return 0;
		}

		system.refine(counterExample, maximalTraceLen);
	}
}