#include <iostream>
#include <random>
#include <fstream> 
#include <string>
#include "lib.h"
using uint = unsigned int;

bool createFileWithRandomNumbers(const std::string& fileName, int numbersCount, int maxNumberValue) {
	std::ofstream outFile(fileName);
	if (!outFile.is_open()) {
		return false;
	}
	if (numbersCount < 0) {
		numbersCount = -numbersCount;
	}
	if (maxNumberValue < 0) {
		maxNumberValue = -maxNumberValue;
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
	int currentNumber, nextNumber;

	if (!(fin >> currentNumber)) {
		fin.close();
		fout1.close();
		fout2.close();
		return;
	}

	while (fin >> nextNumber) {
		if (toggle) {
			fout1 << currentNumber << " ";
		}
		else {
			fout2 << currentNumber << " ";
		}
		if (currentNumber > nextNumber) {
			toggle = !toggle;
		}

		currentNumber = nextNumber;
	}
	if (toggle) {
		fout1 << currentNumber << " ";
	}
	else {
		fout2 << currentNumber << " ";
	}

	fin.close();
	fout1.close();
	fout2.close();
}
void PrintFile(const std::string& inputFile) {
	std::ifstream fin1(inputFile);
	if (!fin1.is_open()) {
		std::cerr << "Error opening files for splitting.\n";
		return;
	}
	std::string num;
	while (fin1 >> num) {
		std::cout << num << " ";
	}
	std::cout << std::endl;
	fin1.close();
}
void mergeFiles(const std::string& inFile1, const std::string& inFile2,
	const std::string& outFile1, const std::string& outFile2) {
	std::ifstream fin1(inFile1);
	std::ifstream fin2(inFile2);
	std::ofstream fout1(outFile1);
	std::ofstream fout2(outFile2);
	if (!fin1.is_open() || !fin2.is_open() || !fout1.is_open() || !fout2.is_open()) {
		std::cerr << "Error opening files for merging.\n";
		return;
	}
	bool toggle = true;
	bool has1 = false, has2 = false;
	int aCurrentNumber, bCurrentNumber;
	if (fin1 >> aCurrentNumber) has1 = true;
	if (fin2 >> bCurrentNumber) has2 = true;
	int next1, next2;
	while (has1 && has2) {
		if (aCurrentNumber <= bCurrentNumber) {
			if (toggle) { fout1 << aCurrentNumber << " "; }
			else { fout2 << aCurrentNumber << " "; }
			if (fin1 >> next1) {
				if (next1 >= aCurrentNumber) { aCurrentNumber = next1; }
				else {
					aCurrentNumber = next1;
					if (toggle) { fout1 << bCurrentNumber << " "; }
					else { fout2 << bCurrentNumber << " "; }

					if (fin2 >> next2) {
						if (next2 >= bCurrentNumber) {
							while (1) {
								if (next2 >= bCurrentNumber) {
									bCurrentNumber = next2;
									if (toggle) { fout1 << bCurrentNumber << " "; }
									else { fout2 << bCurrentNumber << " "; }
									if (!(fin2 >> next2)) { has2 = !has2; break; }
								}
								break;
							}
							bCurrentNumber = next2;
							toggle = !toggle;
						}
						else { toggle = !toggle; bCurrentNumber = next2; }
					}
					else { toggle = !toggle; has2 = !has2; break; }
				}
			}
			else { has1 = !has1; break; }
		}
		else {
			if (toggle) { fout1 << bCurrentNumber << " "; }
			else { fout2 << bCurrentNumber << " "; }
			if (fin2 >> next2) {
				if (next2 >= bCurrentNumber) { bCurrentNumber = next2; }
				else {
					bCurrentNumber = next2;
					if (toggle) { fout1 << aCurrentNumber << " "; }
					else { fout2 << aCurrentNumber << " "; }
					if (fin1 >> next1) {
						if (next1 >= aCurrentNumber) {
							while (1) {
								if (next1 >= aCurrentNumber) {
									aCurrentNumber = next1;
									if (toggle) { fout1 << aCurrentNumber << " "; }
									else { fout2 << aCurrentNumber << " "; }
									if (!(fin1 >> next1)) { has1 = !has1; break; }
								}
								break;
							}
						}
						else { toggle = !toggle; aCurrentNumber = next1; }
					}
					else { has1 = !has1; break; }
				}
			}
			else { has2 = !has2; break; }
		}
	}

	if (!has1 || !has2) {
		if (!has2) {
			while (has1) {
				if (toggle) { fout1 << aCurrentNumber << " "; }
				else { fout2 << aCurrentNumber << " "; }
				if (!(fin1 >> next1)) {
					has1 = !has1;
				}
				if (aCurrentNumber > next1) { toggle = !toggle; }
				aCurrentNumber = next1;
			}
		}
		else {
			while (has2) {
				if (toggle) { fout1 << bCurrentNumber << " "; }
				else { fout2 << bCurrentNumber << " "; }
				if (!(fin2 >> next2)) {
					has2 = !has2;
				}
				if (bCurrentNumber > next2) { toggle = !toggle; }
				bCurrentNumber = next2;
			}
		}
	}
	fin1.close(); fin2.close(); fout1.close(); fout2.close();
}