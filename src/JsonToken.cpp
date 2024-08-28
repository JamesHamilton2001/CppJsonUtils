#include "JsonToken.hpp"

#include <iostream>



ostream& operator <<(ostream& os, const JsonToken& token)
{
    switch (token)
    {
        case STRING:
            os << "STRING";
            break;
        case NUMBER:
            os << "NUMBER";
            break;
        case TRUE:
            os << "TRUE";
            break;
        case FALSE:
            os << "FALSE";
            break;
        case NUL:
            os << "NUL";
            break;
        case COLON:
            os << "COLON";
            break;
        case COMMA:
            os << "COMMA";
            break;
        case OPEN_OBJECT:
            os << "OPEN_OBJECT";
            break;
        case CLOSE_OBJECT:
            os << "CLOSE_OBJECT";
            break;
        case OPEN_ARRAY:
            os << "OPEN_ARRAY";
            break;
        case CLOSE_ARRAY:
            os << "CLOSE_ARRAY";
            break;
    }
    return os;
}