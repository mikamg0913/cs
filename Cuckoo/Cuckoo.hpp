#pragma once
#include "Data.hpp"
#include "Function.hpp"
#include <functional>
#include <fstream>

class Levy {
private:
	double beta, sigma;
	
	std::normal_distribution<> n_d_u, n_d_v;
	
	std::default_random_engine eng;
	std::mt19937 mt,mt2;
public:
	int roop_num;
	Levy();
	Levy(double beta);
	double Make();
	double Make_s(double ,double);

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
	int n, sn, func_num, try_num,roop_num;
	double beta, sigma,pa,alpha;
	Func func;
	Data *data;

	//値
	std::vector<Bird> xx;
	Bird best;
	std::vector<Bird> x_dm;


	std::vector<std::vector<bool>> wnest;
	std::vector<int> sh_num,sh_num2;


	Levy levy{1.5};
	//Levy levy;
public:

	double best_f;
	
	//巣の生成
	Bird x_make();

	//巣の生成(レヴィ)
	Bird x_make_levy(int);

	Cuckoo();
	Cuckoo(int N,int SN,Data& dataa,double betaa,int funcc);

	//ランダムウォーク含めた更新
	void x_update();
	void x_update_s();
	void x_update_s(int);

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