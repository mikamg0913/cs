#include "Data.hpp"

Data::Data() {
	mt = std::mt19937(rd());
	score_int = std::uniform_int_distribution<int>();
	score = std::uniform_real_distribution<double>(0, 1);
	phi = std::uniform_real_distribution<double>(0, 1);
}


Data::Data(double minn, double maxx) {
	mt = std::mt19937(rd());
	score_int = std::uniform_int_distribution<int>();
	max = maxx, min = minn;
	score = std::uniform_real_distribution<double>(min, max);
	phi = std::uniform_real_distribution<double>(-1.0, 1.0);
}

Data::Data(std::pair<double, double> min_max) {
	mt = std::mt19937(rd());
	score_int = std::uniform_int_distribution<int>();
	min = min_max.first, max = min_max.second;
	score = std::uniform_real_distribution<double>(min_max.first, min_max.second);
	phi = std::uniform_real_distribution<double>(0, 1.0);
}

double Data::rd_make() {
	return score(mt);
}

double Data::rd_make_phi() {
	return phi(mt);
}

void Data::rd_init_free(double max) {
	rand_free = std::uniform_real_distribution<double>(0, max);
}

double Data::rd_make_free() {
	return rand_free(mt);
}

int Data::rd_make_int() {
	return score_int(mt);
}

int Data::rd_make_int(int nn) {
	return score_int(mt) % nn;
}