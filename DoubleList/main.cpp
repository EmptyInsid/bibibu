#include "DoubleList.h"
#include <iostream>
#include <fstream>

int main() {
	DoubleList test;

	try {
		std::fstream in;
		std::string fileName;
		std::cout << "Enter name of file: ";
		std::cin >> fileName;
		in.open(fileName);
		if (!in.is_open()) {
			throw std::exception("Failed open the file.");
		}
		else if (in.peek() == EOF) {
			throw std::exception("Fail is empty.");
		}
		int data;
		while (!in.eof()) {
			in >> data;
			if (!in)
			{
				throw std::exception("attempt to insert a key of the wrong type");
			}
			test.insertBegin(data);
		}
		in.close();

		test.output_all();
		std::cout << "\n";
		
		test.reverse();
		test.output_all();
		std::cout << "\n";

		DoubleList test2;
		if (test.del(4)) {
			test2.output_all();
		}

	}
	catch (std::exception e) {
		std::cerr << "Error: " << e.what();
		exit(-1);
	}
	return 0;
}