#include "Cuckoo.hpp"
#include <algorithm>

Levy::Levy() {
	Levy(1.0);
}

Levy::Levy(double _beta) {
	std::random_device seed;
	//std::cout << seed() << std::endl;
	eng = std::default_random_engine(seed());
	mt = std::mt19937(seed());
	mt2 = std::mt19937(seed());
	beta = _beta;
	sigma = pow(tgamma(beta + 1)*sin(std::_Pi*beta / 2) /
		tgamma((beta + 1) / 2)*beta*pow(2, (beta - 1) / 2), 1 / beta);

	n_d_u = std::normal_distribution<double>(0.0, sigma*sigma);
	n_d_v = std::normal_distribution<double>(0.0, 1.0);

}

double Levy::Make() {
	return n_d_u(eng) / pow(abs(n_d_v(eng)), 1 / beta);
	//return n_d_u(eng);
}


Cuckoo::Cuckoo() {
	levy = Levy(1.8);
}


Cuckoo::Cuckoo(int N, int SN, Data& dataa, double betaa, double sigmaa,int funcc) {
	levy = Levy(betaa),beta=betaa,sigma=sigmaa;
	n = N, sn = SN, data = Data(func.min_max[func_num]);
	func_num = funcc;

	for (int i = 0; i < sn; i++) {
		//Bird bird;
		/*for (int j = 0; j < n; j++) 
			bird.x.push_back(data.rd_make());

		bird.f = func.ff[func_num](bird.x);*/

		xx.push_back(x_make());
	}
	std::sort(xx.begin(),xx.end(), [](const Bird& a, const Bird& b) {return a.f < b.f; });
	best_num = xx[0].f;
}

Bird& Cuckoo::x_make() {
	Bird b;
	for(int i=0;i<n;i++)
		b.x.push_back(data.rd_make());
	b.f = func.ff[func_num](b.x);
	return b;
}

void Cuckoo::x_update() {
	int x_rand = data.rd_make_int(n);
	Bird dammy;
	for (int i = 0; i < n;i++) {
		dammy.x.push_back(xx[x_rand].x[i] + levy.Make());
		//�܂�Ԃ�
		//�l-�����������{*�������l
		double am=dammy.x[i]-(int)(dammy.x[i] / (data.max-data.min))*(data.max-data.min);
		dammy.x[i] = am;
	}
	dammy.f=func.ff[func_num](dammy.x);
	if (xx[x_rand].f > dammy.f) {
		int i = 0;
		for (auto&& v : dammy.x) {
			xx[x_rand].x[i] = dammy.x[i];
			i++;
		}
		xx[x_rand].f = dammy.f;
	}
}

void Cuckoo::worst_update() {
	for (int i = 0; i < n*pa; i++) 
		xx.pop_back();
	for (int i = 0; i < n*pa; i++)
		xx.push_back(x_make());
}

void Cuckoo::update() {
	x_update();
	worst_update();

}


void Cuckoo::n_test() {
	std::ofstream out("n_out.txt");
	for (int i = 0; i < 100; i++) {
		out << levy.Make() << std::endl;
	}


}

void Cuckoo::test() {
	std::ofstream out("out2.txt");

	for (int i = 0; i < 100000; i++) {
		//out <<(int)(levy.Make()/0.001)*0.001<<std::endl;
		out << levy.Make() << std::endl;
	}
}

void Cuckoo::move_test() {
	double x=50, y=50;
	std::ofstream out("move.txt");
	out << x << " " << y << std::endl;
	for (int i = 0; i < 100; i++) {
		x += levy.Make()*10, y += levy.Make()*10;
		out << x << " " << y << std::endl;
	}
}

