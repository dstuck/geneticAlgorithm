/*
 * AbstractEcosystem.cpp
 *
 *  Created on: Oct 18, 2013
 *      Author: dstuck
 */

#include "headers/AbstractEcosystem.h"

AbstractEcosystem::AbstractEcosystem() {
	// TODO Auto-generated constructor stub

}

AbstractEcosystem::~AbstractEcosystem() {
	// TODO Auto-generated destructor stub
}

void AbstractEcosystem::Compete(vector<int> index) {
	vector<AbstractSpecimen*> specs = GetSpecimen();
	for (vector<int>::iterator iter=index.begin(); iter!=index.end();iter++) {
		CompeteOne(specs[*iter]);
	}
}

void AbstractEcosystem::Compete() {
	vector<AbstractSpecimen*> specs = GetSpecimen();
	for (vector<AbstractSpecimen*>::iterator iter=specs.begin(); iter!=specs.end();iter++) {
		CompeteOne(*iter);
	}
}



