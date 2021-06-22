#pragma once
class Model
{
protected:
	int NumOfStates;
public:
	Model(int num_of_states = 0)
		: NumOfStates(num_of_states)
	{}

	void setNumOfStates(int num_of_states = 0);
};