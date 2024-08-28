#include "JsonTokeniser.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "JsonToken.hpp"

using namespace std;



JsonTokeniser::JsonTokeniser()
{
    clear();
}



void JsonTokeniser::tokenise(string jsonFilePath)
{
    clear();

    inputFile.open(jsonFilePath);
    if (!inputFile.is_open()) {
        cerr << "Error: could not open file " << jsonFilePath << endl;
        return;
    }

    inputFile.get(chr);
    while (!inputFile.eof())
    {
        switch (chr)
        {
            case ' ':
            case '\t':
            case '\n':
                cout << chr;
                handleWhitespace();
                break;

            case '"':
                readString();
                cout << '"' << values.back() <<  '"';
                break;

            case '0' ... '9':
            case '-':
                readNumber();
                cout << values.back();
                break;

            case 't':
                readTrue();
                cout << "true";
                break;

            case 'f':
                readFalse();
                cout << "false";
                break;

            case 'n':
                readNull();
                cout << "null";
                break;

            case ':':
                readColon();
                cout << ':';
                break;

            case ',':
                readComma();
                cout << ',';
                break;

            case '{':
                readOpenObject();
                cout << '{';
                break;

            case '}':
                readCloseObject();
                cout << '}';
                break;

            case '[':
                readOpenArray();
                cout << '[';
                break;

            case ']':
                readCloseArray();
                cout << ']';
                break;

            default:
                throw invalid_argument("Error: invalid character in JSON file");
        }
    }
    inputFile.close();
}

void JsonTokeniser::clear()
{
    filePath.clear();
    inputFile.close();

    sequence.clear();
    values.clear();

    val.clear();
    chr = EOF;
}


void JsonTokeniser::handleWhitespace()
{
    inputFile.get(chr);
}


void JsonTokeniser::readString()
{
    inputFile.get(chr);
    while (chr != '"')
    {
        if (chr == '\\') {
            throw invalid_argument("Error: escape characters not supported");
        }
        if (chr == '\n' || chr == EOF) {
            throw invalid_argument("Error: newline reached before string terminated");
        }
        val += chr;
        inputFile.get(chr);
    }
    inputFile.get(chr);

    sequence.push_back(STRING);
    values.push_back(val);
    val.clear();
}

void JsonTokeniser::readNumber()
{
    bool hasDecimal = false;
    unsigned int digits = 0U;

    if (chr == '-') {
        val += '-';
        inputFile.get(chr);
    }

    while (true)
    {
        if (isdigit(chr)) {
            digits++;
            val += chr;
            inputFile.get(chr);
        }
        else if (chr == '.') {
            if (hasDecimal) {
                throw invalid_argument("Error: invalid number format");
            }
            digits = 0U;
            hasDecimal = true;
            val += chr;
            inputFile.get(chr);
        }
        else break;
    }

    if (!digits) {    // if no digits were read before or after decimal point
        throw invalid_argument("Error: invalid number format");
    }

    sequence.push_back(NUMBER);
    values.push_back(val);
    val.clear();
}

void JsonTokeniser::readTrue()
{
    while (isalpha(chr)) {
        val += chr;
        inputFile.get(chr);
    }
    if (val != "true") {
        throw invalid_argument("Error: invalid value for literal");
    }

    sequence.push_back(TRUE);
    val.clear();
}

void JsonTokeniser::readFalse()
{
    while (isalpha(chr))
    {
        val += chr;
        inputFile.get(chr);
    }
    if (val != "false") {
        throw invalid_argument("Error: invalid value for literal");
    }

    sequence.push_back(FALSE);
    val.clear();
}

void JsonTokeniser::readNull()
{
    while (isalpha(chr)) {
        val += chr;
        inputFile.get(chr);
    }
    if (val != "null") {
        throw invalid_argument("Error: invalid value for literal");
    }

    sequence.push_back(NUL);
    val.clear();
}

void JsonTokeniser::readColon()
{
    sequence.push_back(COLON);
    inputFile.get(chr);
}

void JsonTokeniser::readComma()
{
    sequence.push_back(COMMA);
    inputFile.get(chr);
}

void JsonTokeniser::readOpenObject()
{
    sequence.push_back(OPEN_OBJECT);
    inputFile.get(chr);
}

void JsonTokeniser::readCloseObject()
{
    sequence.push_back(CLOSE_OBJECT);
    inputFile.get(chr);
}

void JsonTokeniser::readOpenArray()
{
    sequence.push_back(OPEN_ARRAY);
    inputFile.get(chr);
}

void JsonTokeniser::readCloseArray()
{
    sequence.push_back(CLOSE_ARRAY);
    inputFile.get(chr);
}