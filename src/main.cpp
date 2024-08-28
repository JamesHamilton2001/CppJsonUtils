#include <iostream>
#include <vector>
#include <string>

#include "JsonTokeniser.hpp"

using namespace std;


int main()
{
    JsonTokeniser tokeniser;

    // string testFilePaths[2] = {
    //     "test/testy1.json",
    //     "test/testy2.json"
    // };

    vector<string> testFilePaths = {
        "test/testy1.json",
        "test/testy2.json"
    };

    for (string testFilePath : testFilePaths) {
        cout << "================================================================================" << endl;
        cout << "Tokenising " << testFilePath << endl;
        cout << "================================================================================" << endl;
        tokeniser.tokenise(testFilePath);
    }
    cout << "================================================================================" << endl;
    cout << "================================================================================" << endl;

    return EXIT_SUCCESS;
}
