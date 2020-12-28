/*
HW05_01.cpp
��өҺӤ@ P46091204 ���ӿo  Copyright (C) 2020
Lambda expression => �٥h�t�~�w�q��ƪ��·�
*/

#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>

int main(){
	auto outint = [=](int n) -> void{std::cout << n << " "; };			// [=]: �Ҧ����ܼƳ��H�ǭ�(by vallue)���覡���
	auto cutoff = [&](int v) -> bool{return v > 100; };  // [&]�G�Ҧ����ܼƳ��H�ǰѦҡ]by reference�^���覡���
																		// ��lamda expression ���� f100
	int vals[10] = { 50, 100, 90, 180, 60, 210, 415, 88, 188, 201 };
	std::list<int> yadayada(vals, vals + 10); // range constructor
	std::list<int> etcetera(vals, vals + 10); 

	std::cout << "Original lists:\n";
	for_each(yadayada.begin(), yadayada.end(), outint);          
	std::cout << std::endl;
	for_each(etcetera.begin(), etcetera.end(), outint);        
	std::cout << std::endl; 
	
	yadayada.erase(std::remove_if(yadayada.begin(), yadayada.end(), cutoff), yadayada.end());
	etcetera.erase(std::remove_if(etcetera.begin(), etcetera.end(), [&](int v) {return v > 200; }), etcetera.end());
	std::cout << "Trimmed lists:\n";
	for_each(yadayada.begin(), yadayada.end(), outint);        
	std::cout << std::endl;
	for_each(etcetera.begin(), etcetera.end(), outint);          
	std::cout << std::endl;
	std::cin.get();

	system("pause");
	return 0;
}
