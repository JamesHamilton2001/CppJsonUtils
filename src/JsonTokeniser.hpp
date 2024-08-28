#ifndef JSONTOKENISER_HPP
#define JSONTOKENISER_HPP

#include "JsonToken.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;



class JsonTokeniser
{
  public:

    vector<JsonToken> sequence;
    vector<string> values;

    JsonTokeniser();

    void tokenise(string jsonFilePath);
    void clear();

  private:

    string filePath;
    ifstream inputFile;

    string val;
    char chr;

    void handleWhitespace();

    void readString();
    void readNumber();
    void readTrue();
    void readFalse();
    void readNull();
    void readColon();
    void readComma();
    void readOpenObject();
    void readCloseObject();
    void readOpenArray();
    void readCloseArray();

};



#endif