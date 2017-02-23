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

// �Ȃ�, ������,0
double rastrigin(const std::vector<double> x);//0

//�Ȃ�, ������,-418.98*D
double schwefel(const std::vector<double> x);//1

//����, �P����,0
double rosenbrock(const std::vector<double> x);//2

//����, ������,0
double griewank(const std::vector<double> x);//3

//����, �P����,0
double ridge(const std::vector<double> xx);//4

//�������֐��B���I�œK���̎��ӂɑ����̋Ǐ��������B,0
double ackley(const std::vector<double> xx);//5

//��{�I�Ȋ֐�,0
double sphere(const std::vector<double> xx);//6

//2�ϐ�,-1
double easom(const std::vector<double> xx);//7

//�Ȃ�,����,0
double xin_she_yang(const std::vector<double> xx);//8

//����,�����ɂ��œK���̈ʒu���Ⴄ,(2,-1.8013)(5,-4.687658),(10,-9.66015)
double michalewicz(const std::vector<double> xx);//9

//2�ϐ�,����,����,-1
double eggholder(const std::vector<double> xx);//10


