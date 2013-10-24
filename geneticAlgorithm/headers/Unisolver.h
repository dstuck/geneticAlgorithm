/*
 * Unisolver.h
 *
 *  Created on: Oct 22, 2013
 *      Author: dstuck
 */

#ifndef UNISOLVER_H_
#define UNISOLVER_H_
#include "UniwalkerEnvironment.h"
#include <string>
#include <cmath>
#include <fstream>
#include <ostream>
#include <vector>
#include "Random.h"
#include "debug.h"
using namespace std;

class Unisolver {
public:
	Unisolver();
	Unisolver(UniwalkerEnvironment *);
	virtual ~Unisolver();
	void Solve();
	void RecurStep(int,int,double);

	UniwalkerEnvironment * enviro;
	vector<vector<double> > map;
	int sideLen;
	vector<double> bestPath;
	double bestScore;
};

#endif /* UNISOLVER_H_ */
