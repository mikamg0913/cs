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

	//�l
	std::vector<Bird> xx;
	Bird best;
	std::vector<Bird> x_dm;


	std::vector<std::vector<bool>> wnest;
	std::vector<int> sh_num,sh_num2;


	Levy levy{1.5};
	//Levy levy;
public:

	double best_f;
	
	//���̐���
	Bird x_make();

	//���̐���(�����B)
	Bird x_make_levy(int);

	Cuckoo();
	Cuckoo(int N,int SN,Data& dataa,double betaa,int funcc);

	//�����_���E�H�[�N�܂߂��X�V
	void x_update();
	void x_update_s();
	void x_update_s(int);

	//�\�[�g���邾��
	void sort_update();
	//������r���A�V�����̍��
	void worst_update();

	//�S�̂̍X�V
	void update();


	void test();
	void n_test();
	void move_test();
};