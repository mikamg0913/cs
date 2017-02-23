#pragma once
#include <vector>
#include <functional>

class Func {
public:
	Func();
	std::vector<std::function<double(const std::vector<double>)>> ff;
	std::vector<std::pair<double, double>> min_max;

};

double fit_calc(double);

// なし, 多峰性,0
double rastrigin(const std::vector<double> x);//0

//なし, 多峰性,-418.98*D
double schwefel(const std::vector<double> x);//1

//あり, 単峰性,0
double rosenbrock(const std::vector<double> x);//2

//あり, 多峰性,0
double griewank(const std::vector<double> x);//3

//あり, 単峰性,0
double ridge(const std::vector<double> xx);//4

//多峰性関数。大域的最適解の周辺に多数の局所解をもつ。,0
double ackley(const std::vector<double> xx);//5

//基本的な関数,0
double sphere(const std::vector<double> xx);//6

//2変数,-1
double easom(const std::vector<double> xx);//7

//なし,多峰,0
double xin_she_yang(const std::vector<double> xx);//8

//多峰,次元により最適解の位置が違う,(2,-1.8013)(5,-4.687658),(10,-9.66015)
double michalewicz(const std::vector<double> xx);//9

//2変数,あり,多峰,-1
double eggholder(const std::vector<double> xx);//10


