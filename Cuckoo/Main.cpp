#include "Cuckoo.hpp"
#include "Roop.hpp"

using namespace std;

int func_num = 0;//使う関数

int main(void) {

	int N;//次元数
	int try_num = 10;//試行回数
	int roop_num = 20;//ループ回数
	int SN;//
	cout << "関数:";
	cin >> func_num;
	cout << "次元数:";
	cin >> N;
	cout << "個体数:";
	cin >> SN;
	cout << "イテレーション:";
	cin >> roop_num;
	cout << "試行回数:";
	cin >> try_num;
	
	Func func;
	Data data(func.min_max[func_num]);
	
	Roop roop(N, SN, data, func_num, roop_num,try_num);

	roop.update();
	/*Cuckoo cs;
	cs.move_test();*/


	cout << "end";
	return 0;
}