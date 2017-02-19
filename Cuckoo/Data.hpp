#pragma once
#include <random>
#include <iostream>

class Data {
private:
	std::random_device rd;
	std::mt19937 mt;
	std::uniform_int_distribution<int> score_int;
	std::uniform_real_distribution<double> score;
	std::uniform_real_distribution<double> phi;
	std::uniform_real_distribution<double> rand_free;
public:
	double max, min;
	Data();
	Data(double, double);
	Data(std::pair<double, double>);
	double rd_make();
	double rd_make_phi();
	void rd_init_free(double);
	double rd_make_free();
	int rd_make_int();
	int rd_make_int(int);

	Data& Data::operator=(const Data&) {
		return *this;
	}
};