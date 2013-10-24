/*
 * AbstractSpecimen.h
 *
 *  Created on: Oct 18, 2013
 *      Author: dstuck
 */

#ifndef ABSTRACTSPECIMEN_H_
#define ABSTRACTSPECIMEN_H_
#include <vector>
#include <ostream>
using namespace std;

class AbstractSpecimen {
public:
	AbstractSpecimen();
	virtual ~AbstractSpecimen();
//	virtual vector<AbstractSpecimen*> MateVec(vector<AbstractSpecimen*>, int) = 0;
//	vector<AbstractSpecimen*> Mate(AbstractSpecimen*, int);
	virtual double GetFitness() = 0;
	virtual void PrintGenome() = 0;
	virtual void WriteGenome(ostream&) = 0;
//	TODO: Make this a Genome type object
//	virtual vector<double> GetGenome() = 0;
//	virtual void SetGenome(vector<double>) = 0;
	virtual void Debug(double) = 0;
};

#endif /* ABSTRACTSPECIMEN_H_ */
