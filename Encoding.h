#pragma once
#include "Header.h"
#include "OriginalModel.h"
#include "System.h"

class Encoding
{
private:
	/*void readWord();*/
	/*int checkStatesNumber(string str);*/
	vector<string> createAP(std::ifstream& file);// get all the exis ap in the model
	string readStatesAP(std::ifstream& file);
	bool isInitialState(std::ifstream& file);
	char nextAfterSpace(std::ifstream& file);
	OriginalModel createState(ifstream& file);
	OriginalModel createEdges(ifstream& file, OriginalModel model1);
	//createEdges(file, model1);
	void error(string output);
	int read_from_state(ifstream& file);
	int read_to_state(ifstream& file);
	string readAP(std::ifstream& file);
	OriginalModel readEdgeStates(ifstream& file, OriginalModel model);

public:
	 System initialize(string path);
	 
};