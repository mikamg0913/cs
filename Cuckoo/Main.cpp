#include "Cuckoo.hpp"
#include "Roop.hpp"

using namespace std;

int func_num = 0;//�g���֐�

int main(void) {

	int N;//������
	int try_num = 10;//���s��
	int roop_num = 20;//���[�v��
	int SN;//
	cout << "�֐�:";
	cin >> func_num;
	cout << "������:";
	cin >> N;
	cout << "�̐�:";
	cin >> SN;
	cout << "�C�e���[�V����:";
	cin >> roop_num;
	cout << "���s��:";
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