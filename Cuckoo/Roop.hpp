#pragma once
#include "Cuckoo.hpp"

class Roop {
private:
	Cuckoo cs;
	int n, sn,func_num,roop_num,try_num;
	double beta, sigma;
	Data data;
	double best, all_best;
	std::vector<double> num;
public:
	Roop(int N, int SN, Data& DATA,double BETA, double SIGMA,int tryy);

	void update();
};