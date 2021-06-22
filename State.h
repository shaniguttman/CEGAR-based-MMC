#pragma once
#include "Header.h"

class State {
protected:
	vector<string> APlist;
	int index;

public:
		State(vector<string> apList, int Index) : APlist(apList), index(Index)
		{
		}

		State() 
		{
			APlist = {};
			index = -1;
		};

		void push_back_AP(string ap);
		vector<string> getAPlist();
		void setAPlist(vector<string> ap);
		int getIndex();
		void setIndex(int i);
};
