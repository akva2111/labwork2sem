#include <iostream>
#include <random>
#include <fstream> 
#include <string>
using uint = unsigned int;

bool createFileWithRandomNumbers(const std::string& fileName, const int numbersCount, const int maxNumberValue) {
	std::ofstream outFile(fileName);
	if (!outFile.is_open()) {
		return false;
	}
	std::random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_int_distribution<int> dist(0, maxNumberValue);
	const int bufferSize = 10000;
	int* buffer = new int[bufferSize];
	int remaining = numbersCount;
	while (remaining > 0) {
		int currentBatchSize = std::min(remaining, bufferSize);
		for (int i = 0; i < currentBatchSize; ++i) {
			buffer[i] = dist(gen);
		}
		for (int i = 0; i < currentBatchSize; ++i) {
			outFile << buffer[i] << " ";
		}
		remaining -= currentBatchSize;
	}

	delete[] buffer;
	outFile.close();
	return true;
}
void splitFileF0toF1F2(const std::string& inputFile, const std::string& fileF1, const std::string& fileF2) {
	std::ifstream fin(inputFile);
	std::ofstream fout1(fileF1);
	std::ofstream fout2(fileF2);
	if (!fin.is_open() || !fout1.is_open() || !fout2.is_open()) {
		std::cerr << "Error opening files for splitting.\n";
		return;
	}
	bool toggle = true;
	int currentNumber;

	while (fin >> currentNumber) {
		if (toggle) {
			fout1 << currentNumber << " ";
		}
		else {
			fout2 << currentNumber << " ";
		}
		toggle = !toggle;
	}
	fin.close();
	fout1.close();
	fout2.close();
}
int main() {
	if (createFileWithRandomNumbers("f0.txt", 10, 100)) {
		std::cout << "file f0 create:\n";

		
		std::ifstream fin0("f0.txt");
		if (!fin0.is_open()) {
			std::cerr << "Eror with open file for read.\n";
			return -1;
		}
		std::string number;
		while (fin0 >> number) {
			std::cout << number << " ";
		}
		std::cout << std::endl;
		fin0.close();
	}
	else {
		std::cerr << "problem with create main file.\n";
		return -1;
	}

	splitFileF0toF1F2("f0.txt", "f1.txt", "f2.txt");
	std::cout << "File f1.txt and f2.txt create and  not empty.\n";

	std::cout << " f1.txt: ";
	std::ifstream fin1("f1.txt");
	std::string num;
	while (fin1 >> num) {
		std::cout << num << " ";
	}
	std::cout << std::endl;

	std::cout << " f2.txt: ";
	std::ifstream fin2("f2.txt");
	while (fin2 >> num) {
		std::cout << num << " ";
	}
	std::cout << std::endl;
	fin1.close();
	fin2.close();
	return 0;
}