#include "Roop.hpp"



Roop::Roop(int N,int SN,Data& dataa,double betaa, double sigmaa,int tryy) {
	n = N, sn = SN, data = dataa, beta = betaa, sigma = sigmaa,try_num=tryy;
}

void Roop::update() {
	std::ofstream out("out.txt");
	std::ofstream b_out("best.txt");
	for (int i = 0; i < try_num; i++) {
		cs=Cuckoo(n, sn, data, beta,sigma);
		for (int j = 0; j < gene_num; j++) {
			ga.update();
			num[j] += ga.best_f;
		}
		std::cout << ga.best_f << std::endl << std::endl;
		if (i == 0)
			best = ga.best_f;
		else if (best > ga.best_f)
			best = ga.best_f;
	}
	for (int i = 0; i < gene_num; i++) {
		num[i] /= try_num;
		out << i + 1 << " " << num[i] << std::endl;
	}
	b_out << best << std::endl;
}