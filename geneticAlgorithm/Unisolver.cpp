/*
 * Unisolver.cpp
 *
 *  Created on: Oct 22, 2013
 *      Author: dstuck
 */

#include "headers/Unisolver.h"

Unisolver::Unisolver() {
}

Unisolver::Unisolver(UniwalkerEnvironment * env) {
	enviro = env;
}

Unisolver::~Unisolver() {
}

void Unisolver::Solve() {
	map = enviro->map;
	sideLen = map.size()-1;
	int numPaths = tgamma(sideLen*2+1)/tgamma(sideLen+1)/tgamma(sideLen+1);
	cout << "Testing all " << numPaths << " paths." << endl;
	bestScore=0;
	RecurStep(0,0,0);
	cout << "Best score is " << bestScore << endl;
}

void Unisolver::RecurStep(int right, int down, double score) {
	if((right==sideLen)&&(down==sideLen)){
		score += map[down][right];
		if (score > bestScore) {
			bestScore = score;
		}
		return;
	}
	if(right>sideLen){
		return;
	}
	if(down>sideLen){
		return;
	}
	score += map[down][right];
	RecurStep(right+1, down, score);
	RecurStep(right, down+1, score);
}
