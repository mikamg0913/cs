#include "Roop.hpp"



Roop::Roop(int N,int SN,Data& dataa,int _func,int _roop,int tryy) {
	n = N, sn = SN, data = dataa, func_num = _func;
	roop_num = _roop, try_num = tryy;
	beta = 1;
	//sigma = 1;

	for (int i = 0; i < _roop; i++)num.push_back(0);
}

void Roop::update() {
	std::ofstream out("out.txt");
	std::ofstream b_out("best.txt");
	for (int i = 0; i < try_num; i++) {
		cs=Cuckoo(n, sn, data, beta,func_num);
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