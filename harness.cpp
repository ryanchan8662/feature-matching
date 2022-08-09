#include "reader.h"
#include <iostream>

int main(int argc, char** argv) {
    if (read_file() == nullptr) std::cout << "File was not found.\n";
    else std::cout << "File was found and loaded successfully.\n";

}