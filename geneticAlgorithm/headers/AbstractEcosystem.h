/*
 * AbstractEcosystem.h
 *
 *  Created on: Oct 18, 2013
 *      Author: dstuck
 */

#ifndef ABSTRACTECOSYSTEM_H_
#define ABSTRACTECOSYSTEM_H_
#include "AbstractSpecimen.h"
#include "AbstractEnvironment.h"
#include <vector>
using namespace std;

class AbstractEcosystem {
public:
	AbstractEcosystem();
	virtual ~AbstractEcosystem();
	virtual void CompeteOne(AbstractSpecimen*) = 0;
	virtual void Compete(vector<int>);
	virtual void Compete();
	virtual vector<double> GetFitness() = 0;
	virtual void Reproduce(vector<int>, int, vector<double>) = 0;
	virtual void Mutate(int, double=1) = 0;
	virtual void Cull(vector<int>) = 0;
	virtual void Cull(int) = 0;
	virtual vector<AbstractSpecimen *> GetSpecimen() = 0;
	virtual void AddSpecimen(AbstractSpecimen *) = 0;
	virtual void AddSpecimen(vector<AbstractSpecimen *>) = 0;
	virtual void AddRandomSpecimen(int) = 0;
	virtual AbstractEnvironment * GetEnvironment() = 0;
	virtual void SetEnvironment(AbstractEnvironment *) = 0;
	virtual int GetGeneSize() = 0;
	virtual void Debug(double) = 0;
};

#endif /* ABSTRACTECOSYSTEM_H_ */
