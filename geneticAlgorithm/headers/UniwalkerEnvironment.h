/*
 * UniwalkerEnvironment.h
 *
 *  Created on: Oct 19, 2013
 *      Author: dstuck
 */

#ifndef UNIWALKERENVIRONMENT_H_
#define UNIWALKERENVIRONMENT_H_

#include "AbstractEnvironment.h"
#include <vector>
#include <iostream>
#include <ostream>
using namespace std;

class UniwalkerEnvironment: public AbstractEnvironment {
public:
	UniwalkerEnvironment();
	UniwalkerEnvironment(vector< vector<double> >);
	virtual ~UniwalkerEnvironment();
	virtual void PrintInfo();
	virtual void WriteInfo(ostream&);
	virtual void Debug(double);
	vector<vector<double> > GetMap();
	void SetMap(vector<vector<double> >);

	int lenSide;
	vector<vector<double> > map;	//map[row][column]
};

#endif /* UNIWALKERENVIRONMENT_H_ */
