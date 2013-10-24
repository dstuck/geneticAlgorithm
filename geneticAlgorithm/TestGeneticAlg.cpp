/*
 * TestGeneticAlg.cpp
 *
 *  Created on: Oct 21, 2013
 *      Author: dstuck
 */

#include "headers/TestGeneticAlg.h"

TestGeneticAlg::TestGeneticAlg() {
	idum = new int;
	*idum = -time(0);
	generationNum=0;
}

TestGeneticAlg::TestGeneticAlg(AbstractEcosystem* theEcosystem, string outName) {
	idum = new int;
	*idum = -time(0);
	ecosys = theEcosystem;
	generationNum=0;
	outFile.open(outName.c_str());
}

TestGeneticAlg::TestGeneticAlg(string inName, string outName) {
	idum = new int;
	*idum = -time(0);
	generationNum=0;
	outFile.open(outName.c_str());

//******************************
//	Set defaults
//******************************
	simType = "uniwalker";
	int mazeSize = 3;
	int * mazeSeed = new int(-10);
	double mazeRange = 20;
	numSpecimen = 12;
	selectionPressure = 20;
	muteRate = 3;
	crossRate = 0.2;
	maxStep = 1000;
	writeFreq = 1;
//******************************


//******************************
//	Read in from input file
//******************************
	ifstream input;
	input.open(inName.c_str());
	string lineRead;
	while(std::getline(input, lineRead)) {		// Reads next line until it reaches end of file
//		Read in parameters from $params section in .gin file
		if(lineRead.find("$params") != std::string::npos) {
			while(!(std::getline(input, lineRead).eof()) && (lineRead.find("$end") == std::string::npos)) {
				if(lineRead.find("!") != std::string::npos) {
				}
				else {
					vector<string> lineTokens;
					Tokenize(lineRead, lineTokens);
					if(lineTokens.size() != 2) {
						cout << "Error in input file: $params" << endl;
						cout << "Found line: " << lineRead << endl;
						exit(-1);
					}
					if(lineTokens[0].find("simType") != std::string::npos) {
						simType = lineTokens[1];
					}
					else if(lineTokens[0].find("numSpecimen") != std::string::npos) {
						numSpecimen = atoi(lineTokens[1].c_str());
					}
					else if(lineTokens[0].find("mazeSize") != std::string::npos) {
						mazeSize = atoi(lineTokens[1].c_str());
					}
					else if(lineTokens[0].find("mazeRange") != std::string::npos) {
						mazeRange = atoi(lineTokens[1].c_str());
					}
					else if(lineTokens[0].find("mazeSeed") != std::string::npos) {
						*mazeSeed = atoi(lineTokens[1].c_str());
					}
					else if(lineTokens[0].find("muteRate") != std::string::npos) {
						muteRate = atof(lineTokens[1].c_str());
					}
					else if(lineTokens[0].find("crossRate") != std::string::npos) {
						crossRate = atof(lineTokens[1].c_str());
					}
					else if(lineTokens[0].find("selectionPressure") != std::string::npos) {
						selectionPressure = atof(lineTokens[1].c_str());
					}
					else if(lineTokens[0].find("maxStep") != std::string::npos) {
						maxStep = atoi(lineTokens[1].c_str());
					}
					else if(lineTokens[0].find("writeFreq") != std::string::npos) {
						writeFreq = atoi(lineTokens[1].c_str());
					}
				}
			}
		}
	}
	if(!simType.compare("uniwalker")) {
		vector<vector<double> > map;
		vector<double> mapPiece;
//		int mazeSize = 3;
//		int mazeSize = 17;
//		int mazeSize = 30;
		for(int i=0; i<mazeSize; i++){
			for(int j=0; j<mazeSize; j++) {
				mapPiece.push_back(RandomNum::rand3(mazeSeed)*mazeRange);
			}
			map.push_back(mapPiece);
			mapPiece.clear();
		}
//		Correct answer for ms=17 seed=-10 is 413.054
		UniwalkerEnvironment * uniMap = new UniwalkerEnvironment(map);
		ecosys = new UniwalkerEcosystem(uniMap);
	}
	else {
		cout << "ERROR: Only uniwalker sim type implemented!!!" << endl;
		cout << simType << " is unimplemented!" << endl;
		exit(-1);
	}
}

TestGeneticAlg::~TestGeneticAlg() {
	outFile.close();
	// TODO Auto-generated destructor stub
}

void TestGeneticAlg::Initialize(int numSpecimen) {
	ecosys->AddRandomSpecimen(numSpecimen);
	generationNum=0;
	fitData.clear();
	maxFit.clear();
}

void TestGeneticAlg::SaveGen() {
	fitData.push_back(ecosys->GetFitness());
}

vector<int> TestGeneticAlg::SelectWinners() {
//	Pick (int)((numSpecimen+3)/4)*2
//	vector<double> tempFit = ecosys->GetFitness();
	vector<double> tempFit;
	double weight;
	for(int i=0; i<ecosys->GetFitness().size(); i++) {
		weight = exp(ecosys->GetFitness()[i]/selectionPressure);
		tempFit.push_back(weight);
	}
	int numSpecimen = ecosys->GetSpecimen().size();
	int numMates = (int)((numSpecimen+3)/4)*2;
	double totalFit = 0;
	bool picked = false;
//	vector<UniwalkerSpecimen> mates;
	vector<int> mateIndex;
	double sumFit=0;
	for(int i=0; i<numSpecimen; i++) {
		totalFit += tempFit[i];
	}
	vector<double> pick;
	for(int i=0; i<numMates; i++) {
		pick.push_back(RandomNum::rand3(idum));
	}
	sort(pick.begin(), pick.end());
	for(int i=0; i<numMates; i++) {
		sumFit=0;
		picked=false;
		for(int j=0; !picked; j++ ) {
			sumFit += tempFit[j];
			if(pick[i]*totalFit<sumFit) {
				mateIndex.push_back(j);
				totalFit -= tempFit[j];
				tempFit[j] = 0;
				picked=true;
			}
		}
	}
	return mateIndex;
}

void TestGeneticAlg::ProduceYoung(vector<int> matingPool, int muteRate) {
//	Randomly match up mating individuals to produce 3 young apiece (except last pair) and then add randos to fill it up.
//	Special cases to consider are populations of 3 and 5
	int numParents = matingPool.size();
	int oldPopSize = ecosys->GetSpecimen().size();
	int pick;
	vector<int> couple;
	vector<int> tempPool = matingPool;
	vector<double> crossRate;
	crossRate.push_back(0.2);
	crossRate.push_back(0.8);
	crossRate.push_back(0.5);
//	For each pass, mate the first in the list with a random spec from the list.
//	The broken symmetry only matters for small populations so ignore it.
	for(int i=0; i<(numParents/2)-1; i++) {
		couple.push_back(tempPool[0]);
		tempPool.erase(tempPool.begin());
		pick = tempPool.size()*RandomNum::rand3(idum);
		couple.push_back(tempPool[pick]);
		tempPool.erase(tempPool.begin()+pick);
		ecosys->Reproduce(couple, 3, crossRate);
		couple.clear();
	}
	if(tempPool.size()!=2) {
		cout << "Error: tempPool has too many parents left: " << tempPool.size() << endl;
	}
	int remaining = oldPopSize - (numParents/2-1)*3;
//	Mutation rate is once per 10 steps
//	In case population is 3 or 5
	if(remaining <= 3) {		//Edge Case
		ecosys->Reproduce(tempPool, remaining, crossRate);
		for(int i=0; i<(oldPopSize-remaining); i++) {
			ecosys->Mutate(oldPopSize+i,muteRate);
		}
	}
	else {		//Normal Case
//		cout << "tempPool is ";
//		for(int i=0; i<tempPool.size(); i++) cout << tempPool[i] << " ";
//		cout << endl;
		ecosys->Reproduce(tempPool, 3, crossRate);
		ecosys->AddRandomSpecimen(remaining-3);
	}
}

void TestGeneticAlg::NewGeneration() {
	int popSize = ecosys->GetSpecimen().size();
	vector<int> oldGen;
//	Update fitness values for the population
	ecosys->Compete();
//	Implement elitism
	double maxF = 0;
	int fittest = 0;
	for(int i=0; i<popSize; i++) {
		oldGen.push_back(i);
		if(ecosys->GetSpecimen()[i]->GetFitness() > maxF) {
			fittest = i;
			maxF = ecosys->GetSpecimen()[i]->GetFitness();
		}
	}
	maxFit.push_back(maxF);
//	Save fitness
	SaveGen();
//	Select for parents and produce the next generation 3/4 kids 1/4 randos.
//	Mutation rate is 3 for every 10 steps
	double muteRate = ecosys->GetGeneSize()*3/5+1;
//	double muteRate = 5;
	ProduceYoung( SelectWinners() , muteRate);
	ecosys->AddSpecimen(ecosys->GetSpecimen()[fittest]);
//	Kill the old generation
	ecosys->Cull(oldGen);
	ecosys->Cull(ecosys->GetSpecimen().size()-2);
	oldGen.clear();
	generationNum++;
}


//******************************
//	Run Sim
//******************************
//void TestGeneticAlg::RunSimulation(int numSpecimen, int maxStep, double press, int writeFreq) {
void TestGeneticAlg::RunSimulation() {
	Initialize(numSpecimen);
	for(int i=0; i<maxStep; i++) {
		NewGeneration();
	}
	ecosys->Compete();
	WriteData(outFile, writeFreq);
}
//******************************





void TestGeneticAlg::WriteGen(ostream& outFile) {
	for(int i=0; i<ecosys->GetSpecimen().size(); i++) {
		outFile << "Specimen " << i << ":\t";
		ecosys->GetSpecimen()[i]->WriteGenome(outFile);
	}
}

void TestGeneticAlg::PrintGen() {
	WriteGen(cout);
}

void TestGeneticAlg::WriteFit(ostream& outFile) {
	outFile << "Fitness" << endl;
	for(int i=0; i<ecosys->GetSpecimen().size(); i++) {
		outFile << ecosys->GetSpecimen()[i]->GetFitness() << "\t";
	}
	outFile << endl;
//		outFile << "Fitness " << i << ":\t" << ecosys->GetSpecimen()[i]->GetFitness() << endl;
}

void TestGeneticAlg::PrintFit() {
	WriteFit(cout);
}


void TestGeneticAlg::WriteData(ostream& outFile, int freq) {
	outFile << "Generation\tFitness" << endl;
	for(int i=0; i<fitData.size(); i+=freq) {
		outFile << i << "\t";
		for(int j=0; j<fitData[i].size(); j++) {
			outFile << fitData[i][j] << "\t";
		}
		outFile << endl;
	}
}

void TestGeneticAlg::PrintData(int freq) {
	WriteData(cout, freq);
}

//	Utility function stolen from http://www.oopweb.com/CPP/Documents/CPPHOWTO/Volume/C++Programming-HOWTO-7.html
void TestGeneticAlg::Tokenize(const string& str, vector<string>& tokens, const string& delimiters) {
    // Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}
