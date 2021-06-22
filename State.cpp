#include "State.h"


vector<string> State::getAPlist() {
	return APlist;
}

void State::setAPlist(vector<string> ap) {
	APlist = ap;
}

int State::getIndex()
{
	return index;
}

void State::setIndex(int i)
{
	index = i;
}

void State::push_back_AP(string ap)
{
	APlist.push_back(ap);
}