#include "Cuckoo.hpp"
#include <algorithm>

Levy::Levy() {
	Levy(1.5);
}

Levy::Levy(double _beta) {
	roop_num = 1;
	std::random_device seed;
	//std::cout << seed() << std::endl;
	eng = std::default_random_engine(seed());
	mt = std::mt19937(seed());
	mt2 = std::mt19937(seed());
	beta = _beta;
	sigma = pow(tgamma(beta + 1)*sin(std::_Pi*beta / 2) /
		tgamma((beta + 1) / 2)*beta*pow(2, (beta - 1) / 2), 1 / beta);

	n_d_u = std::normal_distribution<>(0, sigma*sigma);
	n_d_v = std::normal_distribution<>(0, 1.0);

}

double Levy::Make() {
	//return pow(roop_num, -beta);
	//return (n_d_u(eng)*sigma)/ pow(abs(n_d_v(eng)), 1 / beta);
	return (n_d_u(mt)*sigma) / pow(abs(n_d_v(mt2)), 1 / beta);
	//return n_d_u(eng);
	return 0.1;
}

double Levy::Make_s(double x, double best) {
	double step=0.01*Make()*(x-best);
	//return step*Make();
	return step;
	//return step*n_d_v(eng);
	//return 0.1;
}

Cuckoo::Cuckoo() {
	levy = Levy(1.5);
}


Cuckoo::Cuckoo(int N, int SN, Data& dataa, double betaa,int funcc) {
	//levy = Levy(betaa);
	beta=betaa,func_num=funcc;
	n = N, sn = SN,roop_num=0;
	alpha = 1,pa=0.25;
	data = new Data(func.min_max[func_num]);
	func_num = funcc;

	for (int i = 0; i < sn; i++) 
		xx.push_back(x_make());
	
	std::sort(xx.begin(),xx.end(), [](const Bird& a, const Bird& b) {return a.f < b.f; });
	for (int i = 0; i < n; i++)best.x.push_back(xx[0].x[i]);
	best_f= xx[0].f;
	best.f = best_f;
}

Bird Cuckoo::x_make() {
	Bird b;
	for(int i=0;i<n;i++)
		b.x.push_back(data->rd_make());
	b.f = func.ff[func_num](b.x);
	return b;
}

Bird Cuckoo::x_make_levy(int j) {
	Bird b;
	for (int i = 0; i<n; i++)
		b.x.push_back(xx[j].x[i]+alpha*levy.Make());
	b.f = func.ff[func_num](b.x);
	return b;
}

void Cuckoo::x_update() {
	int x_rand = 1;
	//int x_rand = data->rd_make_int(sn);

	int j_rand = 1;
	//int j_rand = data->rd_make_int(sn);
	
	//x_rand = 0;
	Bird dammy;
	for (int i = 0; i < n;i++) {
		//double lv = 0.1;
		double lv = levy.Make();
		dammy.x.push_back(xx[x_rand].x[i] +alpha* lv);
		//Ü‚è•Ô‚µ
		if (dammy.x[i] > data->max || dammy.x[i] < data->min) {
			double am = (dammy.x[i] - data->min) - (int)((dammy.x[i] - data->min) / (data->max - data->min))*(data->max - data->min);
			am = (dammy.x[i] > data->max ? data->max : data->min) - am;
			dammy.x[i] = am;
		}
	}
	dammy.f=func.ff[func_num](dammy.x);
	if (xx[j_rand].f > dammy.f) {
		for (int i = 0; i < n;i++) {
			xx[j_rand].x[i] = dammy.x[i];
		}
		xx[j_rand].f = dammy.f;
	}
}

void Cuckoo::x_update_s() {
	//int x_rand = 1;
	int x_rand = data->rd_make_int(sn);
	//int k = 1;
	int k = data->rd_make_int(sn);
	
	//x_rand = 0;
	
	Bird dammy;
	for (int i = 0; i < n; i++) {
		//alpha = 0.1;
		alpha = levy.Make_s(xx[x_rand].x[i], best.x[i]);
		//alpha = levy.Make();
		dammy.x.push_back(xx[x_rand].x[i] + alpha);
		//Ü‚è•Ô‚µ
		if (dammy.x[i] > data->max || dammy.x[i] < data->min) {
			double am = (dammy.x[i] - data->min) - (int)((dammy.x[i] - data->min) / (data->max - data->min))*(data->max - data->min);
			am = (dammy.x[i] > data->max ? data->max : data->min) - am;
			dammy.x[i] = am;
		}
	}
	dammy.f = func.ff[func_num](dammy.x);
	if (xx[x_rand].f > dammy.f) {
		for (int i = 0; i < n; i++) {
			xx[x_rand].x[i] = dammy.x[i];
		}
		xx[x_rand].f = dammy.f;
	}
	//std::sort(xx.begin(), xx.end(), [](const Bird& a, const Bird& b) {return a.f < b.f; });
}

void Cuckoo::sort_update() {
	std::sort(xx.begin(), xx.end(), [](const Bird& a, const Bird& b) {return a.f < b.f; });
	for (int i = 0; i < n; i++)best.x[i] = xx[0].x[i];
	best_f = xx[0].f;
	best.f = best_f;
}

void Cuckoo::worst_update() {
	for (int i = 0; i < sn*pa; i++)
		xx.pop_back();
	for (int i = 0; i < sn*pa; i++) {
		xx.push_back(x_make());
	}

	//for (int i = 0; i < sn*pa; i++) {
	//	for (int j = 0; j < n; j++) {
	//		//xx[sn-i-1].x[j] += alpha*levy.Make();
	//		xx[sn - i - 1].x[j] += levy.Make_s(xx[sn-i-1].x[j], best.x[j]);
	//		//xx[sn - i - 1].x[j] =xx[0].x[j]+ alpha*levy.Make();
	//		if (xx[sn-i-1].x[j] > data->max || xx[sn-i-1].x[j] < data->min) {
	//			double am = (xx[sn-i-1].x[j] - data->min) - (int)((xx[sn-i-1].x[j] - data->min) / (data->max - data->min))*(data->max - data->min);
	//			am = (xx[sn-i-1].x[j] > data->max ? data->max : data->min) - am;
	//			xx[sn-i-1].x[j] = am;
	//		}
	//	}
	//	xx[sn-i-1].f = func.ff[func_num](xx[sn-i-1].x);
	//}

}

void Cuckoo::update() {
	for (int i = 0; i < sn; i++) {
		//x_update();
		x_update_s();
	}
	//x_update();
	sort_update();
	worst_update();
	roop_num++;
	levy.roop_num = roop_num;
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
	double x=0, y=0;
	std::ofstream out("move.txt");
	out << x << " " << y << std::endl;
	for (int i = 0; i < 200; i++) {
		x += levy.Make(), y += levy.Make();
		out << x << " " << y << std::endl;
	}
}


