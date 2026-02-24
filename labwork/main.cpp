#include <iostream>
#include <random>
#include <fstream> 

using uint = unsigned int;
int* generateArray(const int ArraySize, const uint UpperBound, const uint LowerBound = 0) {
	int* outputArray = new int[ArraySize];
	std::random_device randomDevice;
	std::mt19937_64 generator(randomDevice());
	std::uniform_int_distribution<uint> distribution(LowerBound, UpperBound);
	for (int i = 0; i < ArraySize; i++) {
		outputArray[i] = distribution(generator);
	}
	return outputArray;
}
int main() {
	int* prototipe = generateArray(10, 20);
	FILE* file = nullptr;
	errno_t err = fopen_s(&file, "textfile.txt", "wt");
	if (err != 0 || file == nullptr) {
		puts("File Open Error!");
		return -1;
	}
	for (int i = 0; i < 10; ++i)
		fprintf(file, "%d ", prototipe[i]);
	for (int i = 0; i < 10; i++) {
		printf("%d ", prototipe[i]);
	}
	delete[] prototipe;
	fclose(file);
	return 0;
}