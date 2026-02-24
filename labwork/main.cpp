#include <iostream>
#include <random>

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
	int* prototipe = new int[10];
	prototipe=generateArray(10,20);
	for (int i = 0; i < 10; i++) {
		printf("%d ",prototipe[i]);
	}
	return 0;}