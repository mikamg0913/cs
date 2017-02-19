#include "Roop.hpp"



Roop::Roop(int N,int SN,Data& dataa,double betaa, double sigmaa,int tryy) {
	n = N, sn = SN, data = dataa, beta = betaa, sigma = sigmaa,try_num=tryy;
}

void Roop::update() {
	std::ofstream out("out.txt");
	std::ofstream b_out("best.txt");
	for (int i = 0; i < try_num; i++) {
		cs=Cuckoo(n, sn, data, beta,sigma,func_num);
		for (int j = 0; j < roop_num; j++) {
			cs.update();
			num[j] += cs.best_f;
		}
		std::cout <<cs.best_f << std::endl << std::endl;
		if (i == 0)
			best =cs.best_f;
		else if (best > cs.best_f)
			best = cs.best_f;
	}
	for (int i = 0; i < roop_num; i++) {
		num[i] /= try_num;
		out << i + 1 << " " << num[i] << std::endl;
	}
	b_out << best << std::endl;
}