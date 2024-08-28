#ifndef JSONTOKEN_HPP
#define JSONTOKEN_HPP

#include <iostream>

using namespace std;



constexpr unsigned short int JSON_TOKEN_TYPE_COUNT = 11;

enum JsonToken
{
    STRING, NUMBER, TRUE, FALSE, NUL, COLON, COMMA, OPEN_OBJECT, CLOSE_OBJECT, OPEN_ARRAY, CLOSE_ARRAY
};

ostream& operator <<(ostream& os, const JsonToken& token);




#endif