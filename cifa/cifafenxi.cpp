<<<<<<< HEAD
// main.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <map>
#include <vector>
#include <utility>
#include "struct.h"
#include "function.h"

using namespace std;

map<string, TokenType> keywords = {
    {"else", ELSETK}, {"switch", SWITCHTK}, {"case", CASETK}, {"default", DEFAULTTK},
    {"while", WHILETK}, {"for", FORTK}, {"scanf", SCANFTK}, {"printf", PRINTFTK},
    {"return", RETURNTK}, {"const", CONSTTK}, {"int", INTTK}, {"char", CHARTK},
    {"void", VOIDTK}, {"main", MAINTK}, {"if", IFTK}, {"getint", GETINTTK},
    {"continue", CONTINUETK},{"break", BREAKTK}
};

map<char, TokenType> singleCharTokens = {
    {'+', PLUS}, {'-', MINU}, {'*', MULT}, {'/', DIV}, {'=', ASSIGN},
    {'<', LSS}, {'>', GRE}, {'%', MOD}, {':', COLON}, {';', SEMICN}, {',', COMMA},
    {'(', LPARENT}, {')', RPARENT}, {'[', LBRACK}, {']', RBRACK}, {'{', LBRACE}, {'}', RBRACE},
    {'|', OR}, {'&', AND}, {'!', NOT} 
};

int main() {
    ifstream inputFile("testfile.txt");
    ofstream outputFile("output.txt");
    if (!inputFile.is_open()) {
        cerr << "Failed to open file." << endl;
        return 1;
    }

    // 定义Token结构
    vector<Token> tokens;
    string code((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
    lexicalAnalysis(tokens, code);

    for (const auto& token : tokens) {
        outputFile << tokenTypeToString(token.type) << " " << token.value << endl;
    }

    return 0;
=======
// main.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <map>
#include <vector>
#include <utility>
#include "struct.h"
#include "function.h"

using namespace std;

map<string, TokenType> keywords = {
    {"else", ELSETK}, {"switch", SWITCHTK}, {"case", CASETK}, {"default", DEFAULTTK},
    {"while", WHILETK}, {"for", FORTK}, {"scanf", SCANFTK}, {"printf", PRINTFTK},
    {"return", RETURNTK}, {"const", CONSTTK}, {"int", INTTK}, {"char", CHARTK},
    {"void", VOIDTK}, {"main", MAINTK}, {"if", IFTK}, {"getint", GETINTTK},
    {"continue", CONTINUETK},{"break", BREAKTK}
};

map<char, TokenType> singleCharTokens = {
    {'+', PLUS}, {'-', MINU}, {'*', MULT}, {'/', DIV}, {'=', ASSIGN},
    {'<', LSS}, {'>', GRE}, {'%', MOD}, {':', COLON}, {';', SEMICN}, {',', COMMA},
    {'(', LPARENT}, {')', RPARENT}, {'[', LBRACK}, {']', RBRACK}, {'{', LBRACE}, {'}', RBRACE},
    {'|', OR}, {'&', AND}, {'!', NOT} 
};

int main() {
    ifstream inputFile("testfile.txt");
    ofstream outputFile("output.txt");
    if (!inputFile.is_open()) {
        cerr << "Failed to open file." << endl;
        return 1;
    }

    // 定义Token结构
    vector<Token> tokens;
    string code((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
    lexicalAnalysis(tokens, code);

    for (const auto& token : tokens) {
        outputFile << tokenTypeToString(token.type) << " " << token.value << endl;
    }

    return 0;
>>>>>>> b28ca46fce9fee58e781a2df68b64b37fbc5ae75
}