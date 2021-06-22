// check what if it the number has 2 digits!!!
//delete all std!!

#include "Encoding.h"


string* AP;
int len;
System Encoding::initialize(string path) {

	std::string word;
	
	ifstream file(path);
	if (file.fail())error("The input file could not be found!\n");

	OriginalModel model1;
	OriginalModel model2;
	AbstractModel A;

	vector<string> APlist{};


	string fromFile;
	// Use a while loop together with the getline() function to read the file line by line
	for (int i = 0;i < 2; i++)
	{
		int lineCounter = 0;
		fromFile = "";
		//while (getline(file, fromFile)) {
		while (!fromFile.compare(""))
			{
			lineCounter++;
			if(lineCounter>10) error("Error with model encoding\n");
			getline(file, fromFile);
		}
			
		if (fromFile.compare("M;") == 0)//
		{
			APlist = createAP(file);
			if (i == 0)
			{
				model1 = createState(file);

				model1 = createEdges(file, model1);
			}
			else
			{
				model2 = createState(file);

				model2 = createEdges(file, model2);
			}

		}
		else(error("\nThe encoding of each model should start with the letter 'M'\n"));

	}
	file.close();

	System system(model1, model2, A);

	return system;
}
vector<string> Encoding::createAP(std::ifstream& file) {
	string word;
	vector<string> APlist{};
	file >> word;
	if (word.compare("AP"))
		error("encoding error");// if it is different than AP



	while (true)// read all AP
	{
		word = readAP(file);
		if (!word.compare("end")) break;
		APlist.push_back(word);
	}
	return APlist;
}
void Encoding::error(string output)
{
	cout << "\n";
	cout << output;
	cout << "\n";
	cout << "Press any key to close the program\n";
	_flushall();
	getchar();
	exit(1);// if it is different than AP
}
int Encoding::read_to_state(ifstream& file) {
	//read all digit until ) and convet to an init number
	bool oneDigitAccepted = 0, spaceAfteDigit = 0;
	string number = "";
	char c;
	while (true) {
		if (number.size() == 6) error("Edge encoding error");//if there is no ) right after the number // too loge number

		file.get(c);
		if (c == ' ') error("Edge encoding error-An unnecessary space whike defining edges");
		if (c == ')') return stoi(number); // end of edge
		if (isdigit(c)) number = number + c;
		else error("Edge encoding error-An unfamiliar character");// if not a digit
	}
}
int Encoding::read_from_state(ifstream& file) {
	//read up to 6 g=digits numer until comma
	bool oneDigitAccepted = 0, spaceAfteDigit = 0;
	string number = "";
	char c;
	while (true) {
		if (number.size() == 6) error("Edge encoding error");//if there is no comma right after the number 

		file.get(c);
		if (c == ' ') error("Edge encoding error - an unnecessary space while defining the edges");// not needed psace
		if (c == ',') return stoi(number);
		if (isdigit(c)) number = number + c;
		else error("Edge encoding error-An unfamiliar character");//if not  digit



	}
}
OriginalModel Encoding::readEdgeStates(ifstream& file, OriginalModel model) {

	int fromState, toState;//, intoState;
	//OriginalModel modell;

	char c;
	while (true)
	{//in case of double space
		file.get(c);

		if (c != ' ' && c != ';' && c != '(') error("Edge encoding error");
		if (c == ' ');
		// what if it is endless loop // read until first char after space
		if (c == '(')// get the state where the edge is going out from
		{

			fromState = read_from_state(file);// read thhe state the edge is going out from
			toState = read_to_state(file);// read the state the edge is going int to 


			model.pushBackStatesOut_index(fromState, toState);//update OutTable

			model.pushBackStatesIn_index(toState, fromState);//update InTable
		}
		if (c == ';') break;// end of line


	}
	return model;
}
OriginalModel Encoding::createEdges(ifstream& file, OriginalModel model) //when to add ENCODING::?
{
	//read encoded edges line and return an original model with the edges information 
	string word;
	file >> word;
	//cout << word;

	if (word.compare("E"))// check its an edges defifning line
		error("Encoding error");
	model = readEdgeStates(file, model);//start reading information

	return model;

};
char Encoding::nextAfterSpace(std::ifstream& file)
{
	char c;
	while (true)
	{//in case of double space
		file.get(c);
		if (c != ' ')// what if it is endless loop
			return c;//check if i exists
	}
}
string Encoding::readAP(std::ifstream& file) { 
	/*return the next letter(avoid spaces) as a string, 
	or returns "end" in case of ";" 
	or end the program after 5 sequatial spaces 
	or end the program in other cases.
	*/
	int spaceCounter = 0;
	char c;
	while (true) {//in case of double space
		file.get(c);// get next character
		if (c == ' ') {// skip on spaces or end program in case of 5seuential spaces
			spaceCounter++;
			if (spaceCounter >= 5) error("Too many sequential spaces\n");
		}
		if (c != ' ') {// what if it is endless loop
			if (c == ';') return "end";
			if (c == '\n') error("';' character is missing in AP encoding line\n");
			if(!isalpha(c))error("An unfamiliar character was detected\n");
			string str(1, c);// convert to string
			//cout << str;
			return str;
		}
	}
}
string Encoding::readStatesAP(ifstream& file) {
	//return "new state" in case of char ') -'in the in the end of previous state
	//reutnr end in case if eend line of state decoding - ';
	//end program if unfamiliar char'
	//return "initial" if 'i' detected not as AP
	char c;
	bool digitDetected = 0;
	while (true) {//in case of double space
		file.get(c);
		if (c != ' ' && c != '(') {// what if it is endless loop
			if (c == ';') return "end";
			if (c == ')') return "new state";
			if (isdigit(c)) digitDetected = 1;
			if (!isdigit(c) && !isalpha(c))//not number or letter
			{
				error("Error unfamiliar character\n");
			}
			if (!isdigit(c)) {
				if (digitDetected && c == 'i') return "initial";//if initial state
				//check if it is not a number
				string str(1, c);// convert to string
				//cout << str;
				return str;
			}
			
		}
	}
}
OriginalModel Encoding::createState(ifstream& file) {
	OriginalModel model;
	string word;
	file >> word;
	//cout << word;

	if (word.compare("S"))// check if it is a states enoding line
		error("Encoding error");
	file >> len; //check that thi is a number

	//model.setNumOfStates(len);

	for (int j = 0; j < len; j++)// create len states
	{
		OriginalState state;
		model.originalStatesPushBack(state);
	}

	vector<vector<string>> states(len);
	int i = 0;
	while (true)
	{
		string ret = readStatesAP(file);
		if (!ret.compare("end")) break; //end of liine done adding state
		if (!ret.compare("new state"))
		{
			model.getOriginalStates()[i].setIndex(i);

			i++;

			if (i == len)//check if there are number of states like t was defined
			{

				if (nextAfterSpace(file) != ';')
					error("The character ';' is missing in the end of state line or there are more states then defined to be");

				break;
			}

			if (isInitialState(file))//add state to initials list if needed
			{
				model.push_back_initialState(i);
			}


		}
		else// add *first state* if it is initial state,
		{
			if (!ret.compare("initial")) { model.push_back_initialState(i); }
			else
				model.push_back_AP(i, ret);
		}

	}
	return model;
}
bool Encoding::isInitialState(std::ifstream& file) //cehck if the state is initial state
{
	char c;
	while (true)
	{//in case of double space
		file.get(c);
		if (c != ' ' && !isdigit(c)) {//check if it is not state index or space
			if (!isalpha(c) && !isdigit(c) && c!= '(') error("Error unfamiliar character\n");//illegal char
			//file.get(c);//checl next char
			if (c == 'i')//if initial state
				return true;//check if i exists
			return false;
		}
	}
}

