/*
   HW01_01.cpp
   ��өҺӤ@ P46091204 ���ӿo  Copyright (C) 2020
												   */

#include <iostream>
#include <ctime>
#include <cstring>

using namespace std;

void swap(int &p1, int &p2) {
	int temp = p1;
	p1 = p2;
	p2 = temp;
}

template <typename T>						// �Q��Template + Class�ѡA�ʸ˥B�x�Ϊ�����
class Maximum {
private:
	T * a;
	int l;
public:
	Maximum() {
		l = 8;
		a = new T[l];						// ��O����n�@�q�Ŷ�
	}
	void RandomNum() {						// ���Ͷüư}�C
		a = new T[l];
		srand(time(0));						// �]�w�üƺ�
		cout << "���Ƨǫe: ";
		for (int i = 0; i < l; i++) {
			a[i] = (T)rand();
		}
		for (int i = 0; i < l; i++) {
			cout << a[i] << " ";
		}
		cout << endl;
	};
	void Shellsort() {						// �o�̦]���}�C�ӼƸ��p�A�G���Shellsort (Pseudocode ���b�ĤG�D)
		int Gap = l / 2;					// ���ձƧǪk �����ɶ�������O(nlogn) �ΨӴ�ִ��J�ƧǪk�������h�������ơA�W�ֳt��
		while (Gap > 0) {
			for (int k = 0; k < Gap; k++) {
				for (int i = k + Gap; i < l; i += Gap) {
					for (int j = i - Gap; j >= k; j -= Gap) {
						if (a[j] > a[j + Gap]) {
							swap(a[j], a[j + Gap]);
						}
						else
							break;
					}
				}
			}
			Gap /= 2;
		}
	};
	void PrintSort() {						// �C�L�X���G
		cout << "�w�Ƨǫ�: ";
		for (int i = 1; i < l; i++) {
			cout << a[i] << " ";
		}
		cout << endl;
		cout << "�G�ҨD�̤j�Ȭ�: " << a[l - 1] << endl;
		delete[] a;							// ����O���� �קKMemory leak
											// C++ -> new delete  C-> malloc free
	};
};

template<>									// �˪O�S�s�ƴ���
class Maximum<char> {
public:
	void MaxStr(char ** pt) {				// �p��̪��r�ꪺindex�æ^�Ǧ�}
		int max = strlen(pt[0]);
		int index = 0;
		for (int i = 1; i < 8; i++) {
			if (strlen(pt[i]) > max) {
				max = strlen(pt[i]);
				index++;
			}
		}
		cout << endl;
		cout << pt[index] << " ���׬�: " << max << " �a�}��: " << &pt[index] << endl;
	}
};



int main() {
	cout << "----------------" << endl;
	cout << "|  ��M�̤j��  |" << endl;
	cout << "----------------" << endl;
	cout << "Short���A���}�C" << endl;
	Maximum<short>test1;
	test1.RandomNum();
	test1.Shellsort();
	test1.PrintSort();

	cout << endl;

	cout << "Double���A���}�C" << endl;
	Maximum<double>test2;
	test2.RandomNum();
	test2.Shellsort();
	test2.PrintSort();
	cout << endl;

	cout << "--------------------" << endl;
	cout << "| �M��̪��r��a�} |" << endl;
	cout << "--------------------" << endl;
	cout << "���դ@" << endl;						// �o�̧ڨϥγs�򪺰O����Ŷ�������
	char **pt = new char*[8];						// const * char pt = "string" �@�� (�Ҧp : printf(const * char) �A print���޼ƥ��ӴN�O��})
	pt[0] = new char[2]{ "h" };						// const ** char pt = {"string1", "string2"} �G��
	pt[1] = new char[3]{ "he" };
	pt[2] = new char[4]{ "hel" };
	pt[3] = new char[5]{ "hell" };
	pt[4] = new char[6]{ "hello" };
	pt[5] = new char[7]{ "helloo" };
	pt[6] = new char[8]{ "hellooo" };
	pt[7] = new char[8]{ "hellooo" };
	for (int i = 0; i < 8; i++) {
		cout << pt[i] << " : " << &pt[i] << endl;
	}
	Maximum<char>test3;
	test3.MaxStr(pt);
	for (int i = 0; i < 8; i++) {
		delete[] pt[i];
	}
	delete[] pt;

	cout << "���դG" << endl;
	char **pt1 = new char*[8];
	pt1[0] = new char[2]{ "h" };
	pt1[1] = new char[3]{ "he" };
	pt1[2] = new char[4]{ "hel" };
	pt1[3] = new char[5]{ "hell" };
	pt1[4] = new char[6]{ "hello" };
	pt1[5] = new char[7]{ "helloo" };
	pt1[6] = new char[8]{ "hellooo" };
	pt1[7] = new char[8]{ "hellooo" };
	for (int i = 0; i < 8; i++) {
		cout << pt1[i] << " : " << &pt1[i] << endl;
	}
	Maximum<char>test4;
	test4.MaxStr(pt1);
	for (int i = 0; i < 8; i++) {
		delete[] pt1[i];
	}
	delete[] pt1;
	system("pause");
	return 0;
}

/* ��r����� (��ƪ���k)
int String_len(char *a) {
int i = 0;
while (a[i] != '\0') { i++; }
return i;
}
*/