//main.cpp
#define _GLIBCXX_USE_CXX11_ABI 0

#include <iostream>
#include <fstream>
#include <string>
#include "tokenscanner.cpp"

int main(int argc, char *argv[]) {
    std::string file = "../for_parse/source.c";
    std::ifstream ifn(file.c_str(), std::ifstream::in);

    if (ifn.is_open()) {
        TokenScanner scanner(ifn);
        bool isEnd;
        std::cout << "START PARSING FILE: " << file << std::endl;

        do {
            isEnd = scanner.nextToken();
        } while (!isEnd);

        std::cout << "END PARSING FILE: " << file << std::endl;
    } else {
        std::cout << "ERROR OPENING FILE: " << file << std::endl;
    }

    ifn.close();
};