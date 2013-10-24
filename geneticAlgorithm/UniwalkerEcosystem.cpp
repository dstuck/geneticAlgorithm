/*
 * UniwalkerEcosystem.cpp
 *
 *  Created on: Oct 19, 2013
 *      Author: dstuck
 */

#include "headers/UniwalkerEcosystem.h"

UniwalkerEcosystem::UniwalkerEcosystem() {
	idum = new int;
	*idum = -time(0);
	updateFit = false;
}

UniwalkerEcosystem::UniwalkerEcosystem(UniwalkerEnvironment * seedEnvironment) {
	idum = new int;
	*idum = -time(0);
	environment = seedEnvironment;
	geneSize = seedEnvironment->map.size()-1;
	updateFit = false;
}

UniwalkerEcosystem::UniwalkerEcosystem(vector<UniwalkerSpecimen *> seedSpecimen, UniwalkerEnvironment * seedEnvironment) {
	idum = new int;
	*idum = -time(0);
	updateFit = false;
	specimen = seedSpecimen;
	environment = seedEnvironment;
	geneSize = seedEnvironment->map.size()-1;
	numSpecimen = specimen.size();
}

UniwalkerEcosystem::~UniwalkerEcosystem() {
}

void UniwalkerEcosystem::CompeteOne(AbstractSpecimen* competitor) {
	dynamic_cast<UniwalkerSpecimen*>(competitor)->Walk(environment->map);
	updateFit = false;
//	fitnessPop.push_back(specimen[i]->fitness);
}

vector<double> UniwalkerEcosystem::GetFitness() {
	if(!updateFit) {
		fitnessPop.clear();
		for(int i=0; i<specimen.size(); i++) {
			fitnessPop.push_back(specimen[i]->GetFitness());
		}
	}
	return fitnessPop;
}

void UniwalkerEcosystem::Reproduce(vector<int> index, int numOffspring, vector<double> crossoverRate) {
	vector<UniwalkerSpecimen*> mates;
	for(int i=0; i<(index.size()-1); i++) {
		mates.push_back(specimen[index[i+1]]);
	}
	vector<UniwalkerSpecimen*> kiddos = specimen[index[0]]->Mate(mates,numOffspring,crossoverRate);
	for(int i=0; i<kiddos.size(); i++) {
		specimen.push_back(kiddos[i]);
	}
	updateFit = false;
}

void UniwalkerEcosystem::Mutate(int index, double muteRate) {
	specimen[index]->Mutate(muteRate);
}

void UniwalkerEcosystem::Cull(vector<int> index) {
//	TODO: Make sure these specimen get deallocated
	sort(index.begin(), index.end());
	for(int i=index.size(); i>0; i--) {
//		cout << "erasing specimen " << index[i-1] << endl;
		specimen.erase(specimen.begin()+index[i-1]);
	}
}

void UniwalkerEcosystem::Cull(int index) {
	vector<int> fullIndex;
	fullIndex.push_back(index);
	Cull(fullIndex);
}

vector<AbstractSpecimen*> UniwalkerEcosystem::GetSpecimen() {
	vector<AbstractSpecimen*> absSpecimen;
	for(vector<UniwalkerSpecimen*>::iterator iter=specimen.begin(); iter!=specimen.end(); iter++) {
		absSpecimen.push_back(dynamic_cast<AbstractSpecimen*>(*iter));
	}
	return absSpecimen;
}

void UniwalkerEcosystem::AddSpecimen(AbstractSpecimen* newSpec) {
	specimen.push_back(dynamic_cast<UniwalkerSpecimen *>(newSpec));
	if(dynamic_cast<UniwalkerSpecimen *>(newSpec)->genome.size()!=geneSize) {
		cout << "Warning: New species does not match environment. Walker gene is: " << dynamic_cast<UniwalkerSpecimen *>(newSpec)->genome.size() << endl;
		cout << "Environment needs gene size: " << geneSize << endl;
		cout << "Maybe you didn't set an environment first." << endl;
//		geneSize = dynamic_cast<UniwalkerSpecimen *>(newSpec)->genome.size();
	}
}

void UniwalkerEcosystem::AddSpecimen(vector<AbstractSpecimen*> specVec) {
	for(int i=0; i<specVec.size(); i++) {
		AddSpecimen(specVec[i]);
	}
}


AbstractEnvironment* UniwalkerEcosystem::GetEnvironment() {
	return environment;
}

void UniwalkerEcosystem::SetEnvironment(AbstractEnvironment* newEnv) {
	environment = dynamic_cast<UniwalkerEnvironment *>(newEnv);
	geneSize = environment->map.size()-1;
}

void UniwalkerEcosystem::AddRandomSpecimen(int numSpecimen) {
	for(int i=0; i< numSpecimen; i++) {
//		cout << "idum is " << *idum << endl;
		vector<int> randoGenes;
		double numLeft = geneSize*2;
		int pick;
		vector<int> numbers;
		for(int i=0; i<geneSize*2; i++) {
			numbers.push_back(i+1);
		}
		for(int i=0; i<geneSize; i++) {
			pick = numLeft*RandomNum::rand3(idum);
			randoGenes.push_back(numbers[pick]);
			numLeft--;
			numbers.erase(numbers.begin()+pick);
		}
		sort(randoGenes.begin(), randoGenes.end());
		UniwalkerSpecimen * randoSpec = new UniwalkerSpecimen(randoGenes, idum);
		specimen.push_back(randoSpec);
		updateFit=false;
	}
}

int UniwalkerEcosystem::GetGeneSize() {
	return geneSize;
}

void UniwalkerEcosystem::Debug(double double1) {
}


