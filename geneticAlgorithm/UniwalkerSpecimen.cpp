/*
 * UniwalkerSpecimen.cpp
 *
 *  Created on: Oct 18, 2013
 *      Author: dstuck
 */

#include "headers/UniwalkerSpecimen.h"

UniwalkerSpecimen::UniwalkerSpecimen() {
	idum = new int;
	*idum = -time(0);
}

UniwalkerSpecimen::UniwalkerSpecimen(vector<int> genes, int* iseed) {
	idum = iseed;
	genome = genes;
	genSize = genes.size();
}

UniwalkerSpecimen::~UniwalkerSpecimen() {
	// TODO Auto-generated destructor stub
}

vector<UniwalkerSpecimen*> UniwalkerSpecimen::Mate(vector<UniwalkerSpecimen*> mates, int numOffspring, vector<double> crossRate) {
//	CrossRate determines the percentage of genes selected from self for each offspring
//	CrossRate must be in [0,1]
	int numMates = mates.size();
	vector<UniwalkerSpecimen*> children;
	vector<int> kidGenes;
	vector<int> comboGenes;			//Mates' genes
	vector<int> tempGenes;			//Self's genes
	double crossPercent;
	for(int i=0; i<numOffspring; i++){
		crossPercent = crossRate[i%(crossRate.size())];
		tempGenes.assign(genome.begin(),genome.end());
		for(int j=0; j<numMates; j++) {
			for(int k=0; k<genSize; k++) {
				comboGenes.push_back(mates[j]->GetGenome()[k]);
			}
		}
//		Select random genes from parents
		int pick;
		for(int k=0; k<genSize; k++) {
			if(RandomNum::rand3(idum)<crossPercent) {
				pick = tempGenes.size()*RandomNum::rand3(idum);
				double picked = tempGenes[pick];
				kidGenes.push_back(picked);
//				Remove selected values to avoid double picking
				for (vector<int>::iterator iter = comboGenes.begin(); iter != comboGenes.end();) {
					if (*iter == picked) {
						iter = comboGenes.erase(iter);
					}
					else {
						iter++;
					}
				}
				for (vector<int>::iterator iter = tempGenes.begin(); iter != tempGenes.end();) {
					if (*iter == picked) {
						iter = tempGenes.erase(iter);
					}
					else {
						iter++;
					}
				}
			}
			else {
				pick = comboGenes.size()*RandomNum::rand3(idum);
				double picked = comboGenes[pick];
				kidGenes.push_back(picked);
//				Remove selected values to avoid double picking
				for (vector<int>::iterator iter = comboGenes.begin(); iter != comboGenes.end();) {
					if (*iter == picked) {
						iter = comboGenes.erase(iter);
					}
					else {
						iter++;
					}
				}
				for (vector<int>::iterator iter = tempGenes.begin(); iter != tempGenes.end();) {
					if (*iter == picked) {
						iter = tempGenes.erase(iter);
					}
					else {
						iter++;
					}
				}
			}
		}
		sort(kidGenes.begin(), kidGenes.end());
		children.push_back(new UniwalkerSpecimen(kidGenes, idum));
		kidGenes.clear();
	}
//	abstractChildren.assign(children.begin(), children.end());
	return children;
}

vector<UniwalkerSpecimen*> UniwalkerSpecimen::Mate(UniwalkerSpecimen* mate, int numOffspring, vector<double> crossRate) {
	vector<UniwalkerSpecimen*> mates;
	mates.push_back(mate);
	return Mate(mates, numOffspring, crossRate);
}

UniwalkerSpecimen* UniwalkerSpecimen::Mate(UniwalkerSpecimen* mate, double crossRate) {
	vector<double> crossVec;
	crossVec.push_back(crossRate);
	return Mate(mate,1, crossVec)[0];
}

double UniwalkerSpecimen::GetFitness() {
	return fitness;
}

vector<int> UniwalkerSpecimen::GetGenome() {
	return genome;
}

void UniwalkerSpecimen::SetGenome(vector<int> newGenes) {
	genome = newGenes;
}

void UniwalkerSpecimen::Walk(vector<vector<double> > map) {
	double score=0;
	int right = 0;
	int down = 0;
	sort(genome.begin(), genome.end());
	vector<int> tempGene;
	for(vector<int>::iterator iter=genome.begin(); iter!=genome.end(); iter++) {
		tempGene.push_back(*iter);
	}
	for(int i=0; i<2*genSize; i++) {
		if((i+1)==tempGene[0]) {
			right++;
			tempGene.erase(tempGene.begin());
		}
		else {
			down++;
		}
//		cout << "Map is " << map[down][right] << endl;
		score += map[down][right];
	}
	fitness = score;
//	cout << "fitness is " << fitness << endl;
}

void UniwalkerSpecimen::Mutate(double muteRate) {
	double tempMute = muteRate;
	for(int i=0; i<(muteRate+1); i++) {
//		cout << "tempMute = "<< tempMute << endl;
		if(tempMute<1) {
			if(RandomNum::rand3(idum)>tempMute){
				return;
			}
		}
		int randoStep = (int)((2*genSize)*RandomNum::rand3(idum)) + 1;
		//	cout << "RandoStep is " << randoStep << endl;
		int flip = 2*RandomNum::rand3(idum);
		//	cout << "Flip is " << flip << endl;
		sort(genome.begin(), genome.end());
		bool found = false;
		if(flip) {
			for(int i=0; !found; i++) {
				if(genome[i]>=randoStep) {
					genome[i]=randoStep;
					found=true;
				}
				else if(i==(genSize-1)) {
					genome.erase(genome.begin());
					genome.push_back(randoStep);
					found=true;
				}
			}
		}
		else {
			for(int i=genSize; !found; i--) {
				if(genome[i]<=randoStep) {
					genome[i]=randoStep;
					found=true;
				}
				else if(i==0) {
					genome[genSize]=randoStep;
					found=true;
				}
			}
		}
		tempMute -= 1;
	}
}

void UniwalkerSpecimen::WriteGenome(ostream& outFile) {
	for(vector<int>::iterator iter = genome.begin(); iter != genome.end(); iter++) {
		if(iter!=genome.begin()){
			outFile << ", ";
		}
		outFile << *iter;
	}
	outFile << endl;
}

void UniwalkerSpecimen::PrintGenome() {
//	for(vector<int>::iterator iter = genome.begin(); iter != genome.end(); iter++) {
//		if(iter!=genome.begin()){
//			cout << ", ";
//		}
//		cout << *iter;
//	}
//	cout << endl;
	WriteGenome(cout);
}

void UniwalkerSpecimen::Debug(double debugVar) {

}
