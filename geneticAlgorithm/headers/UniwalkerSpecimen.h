/*
 * UniwalkerSpecimen.h
 *
 *  Created on: Oct 18, 2013
 *      Author: dstuck
 */

#ifndef UNIWALKERSPECIMEN_H_
#define UNIWALKERSPECIMEN_H_

#include "AbstractSpecimen.h"
#include "Random.h"
#include <time.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <ostream>
using namespace std;

class UniwalkerSpecimen: public AbstractSpecimen {
public:
	UniwalkerSpecimen();
	UniwalkerSpecimen(vector<int>, int*);
	virtual ~UniwalkerSpecimen();
	void Walk(vector<vector<double> >);
	void Mutate(double=0);
	vector<UniwalkerSpecimen*> Mate(vector<UniwalkerSpecimen*>, int, vector<double>);
	vector<UniwalkerSpecimen*> Mate(UniwalkerSpecimen*, int, vector<double>);
	UniwalkerSpecimen* Mate(UniwalkerSpecimen*, double);
	double GetFitness();
	vector<int> GetGenome();
	void SetGenome(vector<int>);
	void PrintGenome();
	void WriteGenome(ostream&);
	void Debug(double);

	double fitness;
	vector<int> genome;
	int genSize;
	int* idum;
};

#endif /* UNIWALKERSPECIMEN_H_ */
