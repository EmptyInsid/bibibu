#include <iostream>
#include <fstream>
#include "DoubleList.h"

const std::string failName = "text.txt";

int main() {

	std::cout << "Creat and output empty list:\n";
	DoubleList test;
	test.outAll();

	std::fstream in;
	/*std::string fileName;
	std::cout << "\nEnter failName: ";
	std::cin >> fileName;*/
	in.open(failName);
	if (!in.is_open()) {
		throw std::exception("failed open the fail");
	}
	if (in.peek() == EOF) {
		throw std::exception("fail is empty");
	}
	while (!in.eof()) {
		int data;
		in >> data;
		if (!in) {
			throw std::exception("uncorrect data in fail");
		}
		test.insertEnd(data);
	}
	in.close();
	std::cout << "\nList from fail:\n";
	test.outAll();
	std::cout << "\n" << test.getSize();
	std::cout << "\n";
	test.reverse();
	test.outAll();
	std::cout << "\n" << test.getSize();

	std::cout << "\n";
	test.replaceByAvarage();
	test.outAll();
	std::cout << "\n" << test.getSize();


}
