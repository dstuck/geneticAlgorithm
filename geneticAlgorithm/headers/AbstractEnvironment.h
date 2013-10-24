/*
 * AbstractEnvironment.h
 *
 *  Created on: Oct 18, 2013
 *      Author: dstuck
 */

#ifndef ABSTRACTENVIRONMENT_H_
#define ABSTRACTENVIRONMENT_H_
#include <ostream>
#include <iostream>
using namespace std;

class AbstractEnvironment {
public:
	AbstractEnvironment();
	virtual ~AbstractEnvironment();
	virtual void PrintInfo() = 0;
	virtual void WriteInfo(ostream&) = 0;
	virtual void Debug(double) = 0;
};

#endif /* ABSTRACTENVIRONMENT_H_ */
