/*
 * TestGeneticAlg.h
 *
 *  Created on: Oct 21, 2013
 *      Author: dstuck
 */

#ifndef TESTGENETICALG_H_
#define TESTGENETICALG_H_
#include "AbstractEcosystem.h"
#include <UniwalkerEnvironment.h>
#include <UniwalkerEcosystem.h>
#include "Random.h"
#include "debug.h"
#include <iostream>
#include <math.h>
#include <string>
#include <fstream>
#include <ostream>
#include <vector>
using namespace std;

class TestGeneticAlg {
public:
	TestGeneticAlg();
	TestGeneticAlg(AbstractEcosystem *, string);
	TestGeneticAlg(string, string);
	virtual ~TestGeneticAlg();
	void Initialize(int);
	void NewGeneration();
	void SaveGen();
	vector<int> SelectWinners();
	void ProduceYoung(vector<int>, int);
	void RunSimulation();

	void WriteGen(ostream&);
	void PrintGen();
	void WriteFit(ostream&);
	void PrintFit();
	void WriteData(ostream&, int=1);
	void PrintData(int=1);
	void Tokenize(const string&, vector<string>&, const string& = " ");

	int * idum;
	int generationNum;
	int maxStep;
	string simType;
	int numSpecimen;
	double selectionPressure;
	double muteRate;
	double crossRate;
	int writeFreq;
	AbstractEcosystem * ecosys;
	vector<vector<double> > fitData;
	vector<double> maxFit;
	string outFileName;
	ofstream outFile;
};

#endif /* TESTGENETICALG_H_ */
