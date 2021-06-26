#include <algorithm>
#include <conio.h>
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <list>
#include <vector>
#include <iterator>
#include <random>
#include <Windows.h>
#include <filesystem>

using namespace std;

int main()
{
    std::stringstream input;
    std::vector<std::string> result;
    string test;
    getline(cin, test);
    input << test;
    // extract substrings one-by-one
    while (!input.eof()) {
        std::string substring;
        input >> substring;
        result.push_back(substring);
    }

    // print all the extracted substrings
    for (const std::string& substring : result) {
        std::cout << substring << std::endl;
    }
}
// "Task 4.exe" C:\Users\PonchikCobaki\source\repos\Laba 3\Test\test.bin