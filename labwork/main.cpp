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
void PrintFile(const std::string& inputFile){
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
	while (has1&& has2) {
		if (aCurrentNumber <= bCurrentNumber) {
			if (toggle) { fout1 << aCurrentNumber << " "; }
			else { fout2 << aCurrentNumber << " "; }
			if (fin1 >> next1) {
				if (next1 >= aCurrentNumber) {aCurrentNumber = next1;}
				else {
					aCurrentNumber = next1;
					if (toggle) { fout1 << bCurrentNumber << " "; }
					else { fout2 << bCurrentNumber << " "; }

					if (fin2 >> next2) {
						if (next2 >= bCurrentNumber) {
							while (next2 >= bCurrentNumber) {
								bCurrentNumber = next2;
								if (toggle) { fout1 << bCurrentNumber << " "; }
								else { fout2 << bCurrentNumber << " "; }
								if (!(fin2 >> next2)) { has2 = !has2; break; }
							}
							bCurrentNumber = next2;
							toggle = !toggle;
						}
						else {toggle = !toggle; bCurrentNumber = next2;}
					}
					else { has2 = !has2; break;}
				}
			}
			else { has1 = !has1; break;}
		}
		else{
			if (toggle) { fout1 << bCurrentNumber << " "; }
			else { fout2 << bCurrentNumber << " "; }
			if (fin2 >> next2) {
				if (next2 >= bCurrentNumber) { bCurrentNumber = next2;}
				else{
					bCurrentNumber = next2;
					if (toggle) { fout1 << aCurrentNumber << " "; }
					else { fout2 << aCurrentNumber << " "; }
					if (fin1 >> next1) {
						if (next1 >= aCurrentNumber) {
							while (next1 >= aCurrentNumber) {
								aCurrentNumber = next1;
								if (toggle) { fout1 << aCurrentNumber << " "; }
								else { fout2 << aCurrentNumber << " "; }
								if (!(fin2 >> next2)) { has2 = !has2; break; }
							}
						}
						else { toggle = !toggle; aCurrentNumber = next1;}
					}
					else { has1 = !has1; break;}
				}
			}
			else { has2 = !has2; break;}
		}
	}
	if (!has1|| !has2) { 
		if (!has2) {
			while(has1) {
				if (toggle) { fout1 << aCurrentNumber << " "; }
			else { fout2 << aCurrentNumber << " "; }
			if (!(fin1 >> next1)) {
				has1 = !has1;
			}
			if (aCurrentNumber >= next1) { toggle = !toggle; }
			aCurrentNumber = next1;
		}
		}
		else{
			while (has2) {
				if (toggle) { fout1 << bCurrentNumber << " "; }
				else { fout2 << bCurrentNumber << " "; }
				if (!(fin2 >> next2)) {
					has2 = !has2;
				}
				if (bCurrentNumber >= next2) { toggle = !toggle; }
				bCurrentNumber = next2;
			}
		}
	}
	fin1.close(); fin2.close(); fout1.close(); fout2.close();
}
int main() {
	/*if (createFileWithRandomNumbers("f0.txt", 10, 100)) {
		std::cout << "file f0 create:\n";

		
		std::ifstream f0("f0.txt");
		if (!f0.is_open()) {
			std::cerr << "Eror with open file for read.\n";
			return -1;
		}
		std::string number;
		while (f0 >> number) {
			std::cout << number << " ";
		}
		std::cout << std::endl;
		f0.close();
	}
	else {
		std::cerr << "problem with create main file.\n";
		return -1;
	}*/

	splitFileF0toF1F2("f0.txt", "f1.txt", "f2.txt");
	std::cout << "File f1.txt and f2.txt create and  not empty.\n";

	std::cout << " f1.txt: ";
	PrintFile("f1.txt");

	std::cout << " f2.txt: ";
	PrintFile("f2.txt");

	std::ifstream f1("f1.txt"), f2("f2.txt"), f3("f3.txt"), f4("f4.txt");
	while (f2.is_open()|| f4.is_open()) {
		f1.close(), f2.close(), f3.close(), f4.close();
		mergeFiles("f1.txt", "f2.txt", "f3.txt", "f4.txt");
		std::cout << " f3.txt: ";
		PrintFile("f3.txt"); 
		std::cout << " f4.txt: ";
		PrintFile("f4.txt");
		mergeFiles("f3.txt", "f4.txt", "f1.txt", "f2.txt");
		std::cout << " f1.txt: ";
		PrintFile("f1.txt");
		std::cout << " f2.txt: ";
		PrintFile("f2.txt");
	}

	return 0;
}