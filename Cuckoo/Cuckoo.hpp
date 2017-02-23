#pragma once
#include "Data.hpp"
#include "Function.hpp"
#include <functional>
#include <fstream>

class Levy {
private:
	double beta=1, sigma;
	std::normal_distribution<> n_d_u, n_d_v;
	
	std::default_random_engine eng;
	std::mt19937 mt,mt2;
public:
	Levy();
	Levy(double beta);
	double Make();

	Levy& operator=(const Levy& copy) {
		return *this;
	}
};

class Bird {
public:
	std::vector<double> x;
	double f;
};

class Cuckoo {
private:
	int n, sn, func_num, try_num;
	double beta, sigma,pa=0.1;
	double best, all_best;
	Func func;
	Data *data;

	//値
	std::vector<Bird> xx;

	//Levy levy{1.8};
	Levy levy;
public:

	double best_f;
	
	//巣の生成
	Bird x_make();

	Cuckoo();
	Cuckoo(int N,int SN,Data& dataa,double betaa,int funcc);

	//ランダムウォーク含めた更新
	void x_update();
	//ソートするだけ
	void sort_update();
	//悪巣を排除、新しいの作る
	void worst_update();
	//全体の更新
	void update();


	void test();
	void n_test();
	void move_test();
};