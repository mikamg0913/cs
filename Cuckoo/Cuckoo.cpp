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
	double step=0.01*Make()*(best-x);
	//return step*Make();
	//return step;
	return step*n_d_v(eng);
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
	for (int i = 0; i < sn; i++) 
		x_dm.push_back(xx[i]);
	

	
	
	//wnest‚Ì‰Šú‰»
	for (int i = 0; i < sn; i++) {
		std::vector<bool> dm;
		for (int j = 0; j < n; j++) {
			dm.push_back(0);
		}
		wnest.push_back(dm);
	}

	for (int i = 0; i < sn; i++) {
		sh_num.push_back(i);
		sh_num2.push_back(i);
	}

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
	x_update_s(data->rd_make_int(sn));
}

void Cuckoo::x_update_s(int s) {
	//int x_rand = 1;
	//int x_rand = data->rd_make_int(sn);
	int x_rand = s;
	
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
	/*for (int i = 0; i < sn*pa; i++)
		xx.pop_back();
	for (int i = 0; i < sn*pa; i++) {
		xx.push_back(x_make());
	}*/


	//wnest¶¬
	for (int i = 0; i < sn; i++) {
		for (int j = 0; j < n; j++) {
			if(data->rd_make_phi()>pa)
				wnest[i][j] = 1;
			else 
				wnest[i][j] = 0;
		}
	}
	
	//F
	double _F = data->rd_make_phi();

	
	for (int i = 0; i < sn; i++) {
		for (int j = 0; j < n; j++) {
			x_dm[i].x[j] = xx[i].x[j];
		}
	}

	std::random_device rd;
	std::mt19937 mt(rd());

	std::shuffle(sh_num.begin(), sh_num.end(),mt);
	std::shuffle(sh_num2.begin(), sh_num2.end(), mt);


	//dm=nest+F*wnest›(nest_per-nest_per)
	Bird dammy;
	for (int j = 0; j < sn; j++) {
		for (int i = 0; i < n; i++) {

			dammy.x.push_back(xx[j].x[i]+_F*wnest[j][i]*(x_dm[sh_num[j]].x[i] - x_dm[sh_num2[j]].x[i]));

			//Ü‚è•Ô‚µ
			if (dammy.x[i] > data->max || dammy.x[i] < data->min) {
				double am = (dammy.x[i] - data->min) - (int)((dammy.x[i] - data->min) / (data->max - data->min))*(data->max - data->min);
				am = (dammy.x[i] > data->max ? data->max : data->min) - am;
				dammy.x[i] = am;
			}
		}
		dammy.f = func.ff[func_num](dammy.x);
		std::cout << "Œ³:" << xx[j].f << " dm:" << dammy.f << std::endl;
		if (xx[j].f > dammy.f) {
			for (int i = 0; i < n; i++) {
				xx[j].x[i] = dammy.x[i];
			}
			xx[j].f = dammy.f;
		}
	}

}

void Cuckoo::update() {
	for (int i = 0; i < sn; i++) {
		//x_update();
		x_update_s(i);
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


