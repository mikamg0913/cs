#include "Cuckoo.hpp"
#include "Roop.hpp"

using namespace std;

int func_num = 0;//�g���֐�
int cross_num = 0;//�������@

int main(void) {
	cout << "�֐�:" << func_num << endl;
	int N;//������
	int try_num = 10;//���s��
	int roop_num = 20;//���[�v��
	int SN;//
	cout << "������:";
	cin >> N;
	cout << "�̐�:";
	cin >> SN;
	cout << "�C�e���[�V����:";
	cin >> roop_num;
	cout << "���s��:";
	cin >> try_num;

	Data data;
	Roop roop(N, SN, data, func_num, roop_num,try_num);

	roop.update();

	cout << "end";
	return 0;
}