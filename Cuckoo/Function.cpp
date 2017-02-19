#include "Function.hpp"
#define _USE_MATH_DEFINES
#include <math.h>

Func::Func() {
	min_max.push_back({ -5.12,5.12 });//0
	min_max.push_back({ -512,512 });//1
	min_max.push_back({ -2.048,2.048 });//2
	min_max.push_back({ -512,512 });//3
	min_max.push_back({ -64,64 });//4
	min_max.push_back({ -32.768,32.768 });//5
	min_max.push_back({ -10000000,10000000 });//6
	min_max.push_back({ -100,100 });//7
	min_max.push_back({ -M_PI * 2,M_PI * 2 });//8
	min_max.push_back({ 0,M_PI });//9
	min_max.push_back({ -512,512 });//10
	ff.push_back(rastrigin);//0
	ff.push_back(schwefel);//1
	ff.push_back(rosenbrock);//2
	ff.push_back(griewank);//3
	ff.push_back(ridge);//4
	ff.push_back(ackley);//5
	ff.push_back(sphere);//6
	ff.push_back(easom);//7
	ff.push_back(xin_she_yang);//8
	ff.push_back(michalewicz);//9
	ff.push_back(eggholder);//10
}


double fit_calc(double f) {
	if (f < 0)
		return 1 + fabs(f);
	else
		return 1 / (1 + fabs(f));
}


double rastrigin(const std::vector<double> xx) {
	int A = 10, n = 0;
	double ans = 0;
	for (auto&& x : xx) {
		ans += x*x - A*cos(2 * M_PI*x);
		n++;
	}
	ans += A*n;
	return ans;
}

double schwefel(const std::vector<double> xx) {
	double ans = 0;
	int i = 0;
	for (auto&& x : xx) {
		ans -= x*sin(pow(fabs(x), 0.5));
		i++;
	}
	return ans + i*418.9829;
}

double rosenbrock(const std::vector<double> xx) {
	double ans = 0;
	auto x = xx.begin();
	x++;
	if (x == xx.end())
		ans += 100 * pow(-pow(*x, 2), 2) + pow(1 - *x, 2);
	for (; x != xx.end(); x++) {
		double t = *(x--);
		ans += 100 * pow(*(x++) - pow(t, 2), 2) + pow(1 - t, 2);
	}
	return ans;
}

double griewank(const std::vector<double> xx) {
	double ans = 1, dm = 1;
	int i = 1;
	for (auto&& x : xx) {
		ans += pow(x, 2) / 4000.0;
		dm *= cos(x / pow(i, 0.5));
	}
	return ans - dm;
}

double ridge(const std::vector<double> xx) {
	double ans = 0;
	int i = 1;
	for (auto&& x : xx) {
		auto dx = xx.begin();
		for (int j = 1; j <= i; j++) {
			ans += pow(*dx, 2);
			dx++;
		}
		i++;
	}
	return ans;
}

double ackley(const std::vector<double> xx) {
	double ans = 20, x1 = 0, x2 = 0;
	int n = 0;
	for (auto&& x : xx) {
		x1 += x*x;
		x2 += cos(2 * M_PI*x);
		n++;
	}
	return ans - 20 * exp(-0.2*pow(x1 / n*1.0, 0.5)) + exp(1) - exp(x2 / n);
}

double sphere(const std::vector<double> xx) {
	double ans = 0;
	for (auto&& x : xx) {
		ans += x*x;
	}
	return ans;
}

double easom(const std::vector<double> xx) {
	double ans = (-1.0)*cos(xx[0])*cos(xx[1])*exp(-pow(xx[0] - M_PI, 2.0) - pow(xx[1] - M_PI, 2.0));
	return ans;
}

double xin_she_yang(const std::vector<double> xx) {
	double ans = 0, x0 = 0;
	for (auto&& x : xx) {
		ans += abs(x);
		x0 += sin(x*x);
	}
	ans *= exp(-x0);
	return ans;
}


double michalewicz(const std::vector<double> xx) {
	double x0 = 0;
	int i = 1;
	for (auto&& x : xx) {
		x0 += sin(x)*pow(sin(i*x*x / M_PI), 20);
		i++;
	}
	return -x0;
}

double eggholder(const std::vector<double> xx) {

	return -(xx[1] + 47)*sin(pow(abs(xx[1] + xx[0] / 2.0 + 47), 0.5)) - xx
		[0] * sin(pow(abs(xx[0] - (xx[1] + 47)), 0.5));
}



