#include <iostream>
#include <string>

//#pragma pack(4)
using namespace std;

int main()
{
    string str("The quick brown fox jumps over the lazy dog.");

    str.replace(10, 5, "red"); // (4)

    str.replace(str.begin(), str.begin() + 3, 3, '<'); // (5)

    cout << str << '\n';
}