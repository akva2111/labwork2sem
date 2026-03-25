#include <iostream>
#include <fstream> 
#include "lib.h"

int main() {
    int numbersCount, maxNumberValue, actions = 0;
    std::cout << "input len and max: ";
    std::cin >> numbersCount >> maxNumberValue;

    if (numbersCount != 0) {
        if (createFileWithRandomNumbers("f0.txt", numbersCount, maxNumberValue)) {
            std::cout << "file f0 create:\n";

            std::ifstream f0("f0.txt");
            if (!f0.is_open()) {
                std::cerr << "Error with open file for read.\n";
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
        }

        splitFileF0toF1F2("f0.txt", "f1.txt", "f2.txt");
        std::cout << "File f1.txt and f2.txt create and not empty.\n";

        std::cout << "f1.txt: ";
        PrintFile("f1.txt");

        std::cout << "f2.txt: ";
        PrintFile("f2.txt");
        std::cout << "\n\n";

        int number = 0;
        while (true) {
            std::ifstream f2("f2.txt");
            if (f2.peek() == EOF) {
                number = 2;
                f2.close();
                break;
            }
            f2.close();

            mergeFiles("f1.txt", "f2.txt", "f3.txt", "f4.txt");
            std::cout << "f3.txt: ";
            PrintFile("f3.txt");
            std::cout << "f4.txt: ";
            PrintFile("f4.txt");
            actions += 1;
            std::cout << "\n\n";
            std::ifstream f41("f4.txt");
            if (f41.peek() == EOF) {
                f41.close();
                break;
            }
            f41.close();

            mergeFiles("f3.txt", "f4.txt", "f1.txt", "f2.txt");
            std::cout << "f1.txt: ";
            PrintFile("f1.txt");
            std::cout << "f2.txt: ";
            PrintFile("f2.txt");
            actions += 1;
            std::cout << "\n\n";
            std::ifstream f21("f1.txt");
            if (f21.peek() == EOF) {
                number = 2;
                f21.close();
                break;
            }
            f21.close();
        }

        std::cout << "We do " << actions << " actions for ";
        std::cout << "final sorted file: ";
        if (number == 2) {
            PrintFile("f1.txt");
        }
        else {
            PrintFile("f3.txt");
        }
    }
    else {
        std::cout << "lenfile=0 so it doesn't need to be sorted\n";
    }

    return 0;
}