/*
 * main.C
 *
 *  Created on: Oct 18, 2013
 *      Author: dstuck
 */

#include <UniwalkerSpecimen.h>
#include <UniwalkerEnvironment.h>
#include <UniwalkerEcosystem.h>
#include <TestGeneticAlg.h>
#include "Unisolver.h"
#include <Random.h>
#include <iostream>
#include <vector>
using namespace std;


int main(int argc, char *argv[]){
//	Make sure only one input
	if(argc<2) {
		cout << "Error: Requires an input file!" << endl;
		exit(-1);
	}
//	Check if input exists
	string inFile(argv[1]);
	ifstream inp(inFile.c_str());
	if(!inp) {
		cout << "Error: File does not exist!" << endl;
		exit(-1);
	}
	std::string outFile;
	if(argc==3) {
		outFile = string(argv[2]);
	}
	else {
		string tempIn = inFile;
		int dot = inFile.find_last_of(".");
		outFile = tempIn.replace(dot,4,".out");
	}

//	Unisolver * solver = new Unisolver(uniMap);
//	solver->Solve();
	TestGeneticAlg * alg = new TestGeneticAlg(inFile, outFile);
	alg->RunSimulation();
	alg->PrintFit();


//	static const double arr[4][4] = {{0,1,4,7},{3,4,3,3},{3,2,1,4},{1,6,1,0}};
//	static const double arr[8][8] = {{0,1,4,71,44,71,1,9},{3,14,3,13,9,7,9,9},{3,2,9,14,9,8,6,4},{3,4,3,3,19,7,0,3},{3,2,9,4,4,81,6,4},{3,4,3,31,9,7,0,3},{3,2,1,4,4,8,6,4},{1,6,1,7,6,9,3,0}};
//	vector<vector<double> > map;
//	vector<double> mapPiece;
//	int * idum = new int(-10);
//	int mazeSize = 3;
////	int mazeSize = 17;
////	int mazeSize = 30;
//	double mazeRange = 20;
//	for(int i=0; i<mazeSize; i++){
//		for(int j=0; j<mazeSize; j++) {
////			mapPiece.push_back(arr[i][j]);
//			mapPiece.push_back(RandomNum::rand3(idum)*mazeRange);
//		}
//		map.push_back(mapPiece);
//		mapPiece.clear();
//	}
//	Correct answer for ms=17 seed=-10 is 413.054
//	UniwalkerEnvironment * uniMap = new UniwalkerEnvironment(map);
//	uniMap->PrintInfo();
//	vector<int> rturns;
//	rturns.push_back(1);
//	rturns.push_back(2);
//	rturns.push_back(4);
//	vector<int> rturns2;
//	rturns2.push_back(2);
//	rturns2.push_back(3);
//	rturns2.push_back(6);
//	vector<int> rturns3;
//	rturns3.push_back(1);
//	rturns3.push_back(3);
//	rturns3.push_back(5);
//	vector<int> rturns4;
//	rturns4.push_back(3);
//	rturns4.push_back(5);
//	rturns4.push_back(6);
//	UniwalkerSpecimen * walker1 = new UniwalkerSpecimen(rturns);
//	UniwalkerSpecimen * walker2 = new UniwalkerSpecimen(rturns2);
//	UniwalkerSpecimen * walker3 = new UniwalkerSpecimen(rturns3);
//	UniwalkerSpecimen * walker4 = new UniwalkerSpecimen(rturns4);

//	vector<UniwalkerSpecimen *> species;
//	species.push_back(walker1);
//	species.push_back(walker2);
//	species.push_back(walker3);
//	species.push_back(walker4);
//	UniwalkerEcosystem * ecosys = new UniwalkerEcosystem(species, uniMap);
//	UniwalkerEcosystem * ecosys = new UniwalkerEcosystem(uniMap);
//	TestGeneticAlg * alg = new TestGeneticAlg(ecosys, "test.out");
//	alg->RunSimulation(12,2000,40,1);
//	alg->Initialize(4);
//	alg->ecosys->Compete();
//	alg->PrintGen();
//	alg->PrintFit();
//	vector<int> pool = alg->PickWinners();
//	cout << "Picked ";
//	for(int i=0; i<pool.size(); i++) {
//		cout << pool[i] << " ";
//	}
//	cout << endl;
//	ecosys->AddRandomSpecimen(4);
//	for(int i=0; i<ecosys->specimen.size(); i++) {
//		cout << "Walker " << i << " has genome ";
//		ecosys->specimen[i]->PrintGenome();
//	}
//	vector<int> index;
//	index.push_back(0);
//	index.push_back(3);
//	index.push_back(2);
//	cout << "There are " << ecosys->GetSpecimen().size() << " specimen" << endl;
//	ecosys->Reproduce(index,3);
//	ecosys->Compete();
//	cout << "There are " << ecosys->GetSpecimen().size() << " specimen" << endl;
//	ecosys->Cull(index);
//	cout << "There are " << ecosys->GetSpecimen().size() << " specimen" << endl;
//	cout << "Fitness is " << ecosys->GetFitness()[0] << ", " << ecosys->GetFitness()[1] << ", " << ecosys->GetFitness()[2] << ", " << ecosys->GetFitness()[3] << endl;

	return 0;
}
