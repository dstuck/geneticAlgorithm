/*
 * UniwalkerEcosystem.h
 *
 *  Created on: Oct 19, 2013
 *      Author: dstuck
 */

#ifndef UNIWALKERECOSYSTEM_H_
#define UNIWALKERECOSYSTEM_H_

#include "AbstractEcosystem.h"
#include "UniwalkerSpecimen.h"
#include "UniwalkerEnvironment.h"
#include "debug.h"
#include <vector>
#include <time.h>
using namespace std;


class UniwalkerEcosystem: public AbstractEcosystem {
public:
	UniwalkerEcosystem();
	UniwalkerEcosystem(UniwalkerEnvironment *);
	UniwalkerEcosystem(vector<UniwalkerSpecimen *>,UniwalkerEnvironment *);
	virtual ~UniwalkerEcosystem();
	virtual void CompeteOne(AbstractSpecimen*);
	virtual vector<double> GetFitness();
	virtual void Reproduce(vector<int>, int, vector<double>);
	virtual void Mutate(int, double=1);
	virtual void Cull(vector<int>);
	virtual void Cull(int);
	virtual vector<AbstractSpecimen *> GetSpecimen();
	virtual void AddSpecimen(AbstractSpecimen *);
	virtual void AddSpecimen(vector<AbstractSpecimen *>);
	virtual void AddRandomSpecimen(int=1);
	virtual AbstractEnvironment * GetEnvironment();
	virtual void SetEnvironment(AbstractEnvironment *);
	virtual int GetGeneSize();
	virtual void Debug(double);

	int * idum;
	int numSpecimen;
	int geneSize;
	vector<UniwalkerSpecimen*> specimen;
	UniwalkerEnvironment * environment;
	vector<double> fitnessPop;
	bool updateFit;
};

#endif /* UNIWALKERECOSYSTEM_H_ */
