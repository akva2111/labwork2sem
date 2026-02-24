#include <iostream>
#include <random>
#include <fstream> 

using uint = unsigned int;
#include <string>

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
int main() {
	std::ifstream f0;
	if (createFileWithRandomNumbers("mainFile", 10, 100)) {
		std::cout << "file f0 create:\n";
		f0.open("mainFile");
		if (!f0.is_open()) {
			std::cerr << "Eror with open file for read.\n";
			return -1;
		}
		std::string number;
		while (f0 >> number) {
			std::cout << number << " ";
		}
		std::cout << std::endl;
	}
	else {
		std::cerr << "problem with create main file.\n";
		return -1;
	}


	f0.close();
	return 0;
}