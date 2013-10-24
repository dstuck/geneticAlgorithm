/*
 * UniwalkerEnvironment.cpp
 *
 *  Created on: Oct 19, 2013
 *      Author: dstuck
 */

#include "headers/UniwalkerEnvironment.h"

UniwalkerEnvironment::UniwalkerEnvironment() {
	// TODO Auto-generated constructor stub

}

UniwalkerEnvironment::UniwalkerEnvironment(vector<vector<double> > newMap) {
	map = newMap;
	lenSide = map.size();
	if(lenSide != map[0].size()) {
		cout << "ERROR: map is not square!!!" << endl;
	}
}

UniwalkerEnvironment::~UniwalkerEnvironment() {
	// TODO Auto-generated destructor stub
}

void UniwalkerEnvironment::WriteInfo(ostream & outFile) {
	outFile << "Map is:" << endl;
//	cout << "lenSide is " << lenSide << endl;
	for(int i=0; i<lenSide; i++) {
		for(int j=0; j<lenSide; j++) {
			outFile << map[i][j] << " ";
		}
		outFile << endl;
	}
}

void UniwalkerEnvironment::PrintInfo() {
//	cout << "Map is:" << endl;
////	cout << "lenSide is " << lenSide << endl;
//	for(int i=0; i<lenSide; i++) {
//		for(int j=0; j<lenSide; j++) {
//			cout << map[i][j] << " ";
//		}
//		cout << endl;
//	}
	WriteInfo(cout);
}

void UniwalkerEnvironment::Debug(double double1) {
}

vector<vector<double> > UniwalkerEnvironment::GetMap() {
	return map;
}

void UniwalkerEnvironment::SetMap(vector<vector<double> > newMap) {
	map = newMap;
	lenSide = map.size();
	if(lenSide != map[0].size()) {
		cout << "ERROR: map is not square!!!" << endl;
	}
}
