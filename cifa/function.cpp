<<<<<<< HEAD
// function.cpp
#include "function.h"
#include <iostream>
#include <cctype>
#include <map>
#include <vector>
#include <string>

using namespace std;

// �ж��Ƿ�Ϊ��ʶ��
bool isIdentifier(const string& str) {
    if (!isalpha(str[0]) && str[0] != '_') return false;
    for (char ch : str) {
        if (!isalnum(ch) && ch != '_') return false;
    }
    return true;
}

// ���һ���ʷ���Ԫ�����
void addToken(vector<Token>& tokens, TokenType type, const string& value, int line) {
    tokens.push_back({ type, value, line });
}

// �ʷ���������
void lexicalAnalysis(vector<Token>& tokens, const string& code) {
    int lineNumber = 1;
    size_t i = 0;
    while (i < code.length()) {
        char ch = code[i];

        if (isspace(ch)) {
            if (ch == '\n') lineNumber++;
            i++;
            continue;
        }

        if (ch == '/' && i + 1 < code.length() && code[i + 1] == '/') {  // ����//ע��
            while (i < code.length() && code[i] != '\n') {
                i++;
            }
            continue;
        }
        if (ch == '/' && i + 1 < code.length() && code[i + 1] == '*') {  // ����/*ע��
            while (i + 1 < code.length() && !(code[i] == '*' && code[i + 1] == '/')) {
                i++;
            }
            i += 2;
            continue;
        }

        if (isalpha(ch) || ch == '_') {  // �����ʶ���͹ؼ���
            string buffer;
            while (isalnum(ch) || ch == '_') {
                buffer += ch;
                ch = code[++i];
            }
            if (keywords.count(buffer)) {
                addToken(tokens, keywords[buffer], buffer, lineNumber);
            }
            else {
                addToken(tokens, IDENFR, buffer, lineNumber);
            }
        }
        else if (isdigit(ch)) {  // ������������
            string buffer;
            while (isdigit(ch)) {
                buffer += ch;
                ch = code[++i];
            }
            addToken(tokens, INTCON, buffer, lineNumber);
        }
        else if (ch == '"') {  // �����ַ���
            string buffer;
            ch = code[++i];
            while (ch != '"') {
                buffer += ch;
                ch = code[++i];
            }
            i++;
            addToken(tokens, STRCON, "\"" + buffer + "\"", lineNumber);  // ����˫����
        }
        else if (ch == '\'') {  // �����ַ�����
            string buffer;
            buffer += code[++i];
            i += 2;  // ������һ��'
            addToken(tokens, CHARCON, buffer, lineNumber);
        }
        else if (ch == '<' || ch == '>' || ch == '=' || ch == '!') {  // ������������˫�ַ�������
            string buffer = "";
            buffer += ch;

            // �����һ���ַ��Ƿ��� '='
            if (i + 1 < code.length() && code[i + 1] == '=') {
                buffer += '=';
                i++; // ���� '='
            }

            // ���� buffer ��ֵ��Ӷ�Ӧ�� Token
            if (buffer == "<") addToken(tokens, LSS, buffer, lineNumber);
            else if (buffer == "=") addToken(tokens, ASSIGN, buffer, lineNumber);
            else if (buffer == "<=") addToken(tokens, LEQ, buffer, lineNumber);
            else if (buffer == ">") addToken(tokens, GRE, buffer, lineNumber);
            else if (buffer == ">=") addToken(tokens, GEQ, buffer, lineNumber);
            else if (buffer == "==") addToken(tokens, EQL, buffer, lineNumber);
            else if (buffer == "!") addToken(tokens, NOT, buffer, lineNumber);
            else if (buffer == "!=") addToken(tokens, NEQ, buffer, lineNumber);
            else {
                cerr << "Error at line " << lineNumber << ": unrecognized operator '" << buffer << "'\n";
            }

            i++; // ����������һ���ַ�
        }
        else if (ch == '&' || ch == '|') {  // �����߼�����˫�ַ�������
            string buffer = "";
            buffer += ch;

            // �����һ���ַ��Ƿ���ch
            if (i + 1 < code.length() && code[i + 1] == ch) {
                buffer += ch;
                i++; // ����ch
            }
            // ���� buffer ��ֵ��Ӷ�Ӧ�� Token
            if (buffer == "&&") addToken(tokens, AND, buffer, lineNumber);
            else if (buffer == "||") addToken(tokens, OR, buffer, lineNumber);
            else {
                cerr << "Error at line " << lineNumber << ": unrecognized operator '" << buffer << "'\n";
            }

            i++; // ����������һ���ַ�
        }
        else if (singleCharTokens.count(ch)) {  // ���ַ��ʷ���Ԫ
            addToken(tokens, singleCharTokens[ch], string(1, ch), lineNumber);
            i++;
        }
        else {
            cerr << "Error at line " << lineNumber << ": unrecognized character '" << ch << "'\n";
            i++;
        }
    }
}

// tokenTypeToString �����Ķ���
std::string tokenTypeToString(TokenType type) {
    switch (type) {
    case IDENFR: return "IDENFR";
    case INTCON: return "INTCON";
    case CHARCON: return "CHARCON";
    case STRCON: return "STRCON";
    case CONSTTK: return "CONSTTK";
    case INTTK: return "INTTK";
    case CHARTK: return "CHARTK";
    case VOIDTK: return "VOIDTK";
    case MAINTK: return "MAINTK";
    case IFTK: return "IFTK";
    case ELSETK: return "ELSETK";
    case SWITCHTK: return "SWITCHTK";
    case CASETK: return "CASETK";
    case DEFAULTTK: return "DEFAULTTK";
    case WHILETK: return "WHILETK";
    case FORTK: return "FORTK";
    case SCANFTK: return "SCANFTK";
    case PRINTFTK: return "PRINTFTK";
    case RETURNTK: return "RETURNTK";
    case PLUS: return "PLUS";
    case MINU: return "MINU";
    case MULT: return "MULT";
    case DIV: return "DIV";
    case ASSIGN: return "ASSIGN";
    case LSS: return "LSS";
    case LEQ: return "LEQ";
    case GRE: return "GRE";
    case GEQ: return "GEQ";
    case EQL: return "EQL";
    case NEQ: return "NEQ";
    case COLON: return "COLON";
    case SEMICN: return "SEMICN";
    case COMMA: return "COMMA";
    case LPARENT: return "LPARENT";
    case RPARENT: return "RPARENT";
    case LBRACK: return "LBRACK";
    case RBRACK: return "RBRACK";
    case LBRACE: return "LBRACE";
    case RBRACE: return "RBRACE";
    case MOD: return "MOD";
    case OR: return "OR";
    case AND: return "AND";
    case NOT: return "NOT";
    case GETINTTK: return "GETINTTK";
    case BREAKTK: return "BREAKTK";
    case CONTINUETK: return "CONTINUETK";
    default: return "UNKNOWN";
    }
=======
// function.cpp
#include "function.h"
#include <iostream>
#include <cctype>
#include <map>
#include <vector>
#include <string>

using namespace std;

// �ж��Ƿ�Ϊ��ʶ��
bool isIdentifier(const string& str) {
    if (!isalpha(str[0]) && str[0] != '_') return false;
    for (char ch : str) {
        if (!isalnum(ch) && ch != '_') return false;
    }
    return true;
}

// ���һ���ʷ���Ԫ�����
void addToken(vector<Token>& tokens, TokenType type, const string& value, int line) {
    tokens.push_back({ type, value, line });
}

// �ʷ���������
void lexicalAnalysis(vector<Token>& tokens, const string& code) {
    int lineNumber = 1;
    size_t i = 0;
    while (i < code.length()) {
        char ch = code[i];

        if (isspace(ch)) {
            if (ch == '\n') lineNumber++;
            i++;
            continue;
        }

        if (ch == '/' && i + 1 < code.length() && code[i + 1] == '/') {  // ����//ע��
            while (i < code.length() && code[i] != '\n') {
                i++;
            }
            continue;
        }
        if (ch == '/' && i + 1 < code.length() && code[i + 1] == '*') {  // ����/*ע��
            while (i + 1 < code.length() && !(code[i] == '*' && code[i + 1] == '/')) {
                i++;
            }
            i += 2;
            continue;
        }

        if (isalpha(ch) || ch == '_') {  // �����ʶ���͹ؼ���
            string buffer;
            while (isalnum(ch) || ch == '_') {
                buffer += ch;
                ch = code[++i];
            }
            if (keywords.count(buffer)) {
                addToken(tokens, keywords[buffer], buffer, lineNumber);
            }
            else {
                addToken(tokens, IDENFR, buffer, lineNumber);
            }
        }
        else if (isdigit(ch)) {  // ������������
            string buffer;
            while (isdigit(ch)) {
                buffer += ch;
                ch = code[++i];
            }
            addToken(tokens, INTCON, buffer, lineNumber);
        }
        else if (ch == '"') {  // �����ַ���
            string buffer;
            ch = code[++i];
            while (ch != '"') {
                buffer += ch;
                ch = code[++i];
            }
            i++;
            addToken(tokens, STRCON, "\"" + buffer + "\"", lineNumber);  // ����˫����
        }
        else if (ch == '\'') {  // �����ַ�����
            string buffer;
            buffer += code[++i];
            i += 2;  // ������һ��'
            addToken(tokens, CHARCON, buffer, lineNumber);
        }
        else if (ch == '<' || ch == '>' || ch == '=' || ch == '!') {  // ������������˫�ַ�������
            string buffer = "";
            buffer += ch;

            // �����һ���ַ��Ƿ��� '='
            if (i + 1 < code.length() && code[i + 1] == '=') {
                buffer += '=';
                i++; // ���� '='
            }

            // ���� buffer ��ֵ��Ӷ�Ӧ�� Token
            if (buffer == "<") addToken(tokens, LSS, buffer, lineNumber);
            else if (buffer == "=") addToken(tokens, ASSIGN, buffer, lineNumber);
            else if (buffer == "<=") addToken(tokens, LEQ, buffer, lineNumber);
            else if (buffer == ">") addToken(tokens, GRE, buffer, lineNumber);
            else if (buffer == ">=") addToken(tokens, GEQ, buffer, lineNumber);
            else if (buffer == "==") addToken(tokens, EQL, buffer, lineNumber);
            else if (buffer == "!") addToken(tokens, NOT, buffer, lineNumber);
            else if (buffer == "!=") addToken(tokens, NEQ, buffer, lineNumber);
            else {
                cerr << "Error at line " << lineNumber << ": unrecognized operator '" << buffer << "'\n";
            }

            i++; // ����������һ���ַ�
        }
        else if (ch == '&' || ch == '|') {  // �����߼�����˫�ַ�������
            string buffer = "";
            buffer += ch;

            // �����һ���ַ��Ƿ���ch
            if (i + 1 < code.length() && code[i + 1] == ch) {
                buffer += ch;
                i++; // ����ch
            }
            // ���� buffer ��ֵ��Ӷ�Ӧ�� Token
            if (buffer == "&&") addToken(tokens, AND, buffer, lineNumber);
            else if (buffer == "||") addToken(tokens, OR, buffer, lineNumber);
            else {
                cerr << "Error at line " << lineNumber << ": unrecognized operator '" << buffer << "'\n";
            }

            i++; // ����������һ���ַ�
        }
        else if (singleCharTokens.count(ch)) {  // ���ַ��ʷ���Ԫ
            addToken(tokens, singleCharTokens[ch], string(1, ch), lineNumber);
            i++;
        }
        else {
            cerr << "Error at line " << lineNumber << ": unrecognized character '" << ch << "'\n";
            i++;
        }
    }
}

// tokenTypeToString �����Ķ���
std::string tokenTypeToString(TokenType type) {
    switch (type) {
    case IDENFR: return "IDENFR";
    case INTCON: return "INTCON";
    case CHARCON: return "CHARCON";
    case STRCON: return "STRCON";
    case CONSTTK: return "CONSTTK";
    case INTTK: return "INTTK";
    case CHARTK: return "CHARTK";
    case VOIDTK: return "VOIDTK";
    case MAINTK: return "MAINTK";
    case IFTK: return "IFTK";
    case ELSETK: return "ELSETK";
    case SWITCHTK: return "SWITCHTK";
    case CASETK: return "CASETK";
    case DEFAULTTK: return "DEFAULTTK";
    case WHILETK: return "WHILETK";
    case FORTK: return "FORTK";
    case SCANFTK: return "SCANFTK";
    case PRINTFTK: return "PRINTFTK";
    case RETURNTK: return "RETURNTK";
    case PLUS: return "PLUS";
    case MINU: return "MINU";
    case MULT: return "MULT";
    case DIV: return "DIV";
    case ASSIGN: return "ASSIGN";
    case LSS: return "LSS";
    case LEQ: return "LEQ";
    case GRE: return "GRE";
    case GEQ: return "GEQ";
    case EQL: return "EQL";
    case NEQ: return "NEQ";
    case COLON: return "COLON";
    case SEMICN: return "SEMICN";
    case COMMA: return "COMMA";
    case LPARENT: return "LPARENT";
    case RPARENT: return "RPARENT";
    case LBRACK: return "LBRACK";
    case RBRACK: return "RBRACK";
    case LBRACE: return "LBRACE";
    case RBRACE: return "RBRACE";
    case MOD: return "MOD";
    case OR: return "OR";
    case AND: return "AND";
    case NOT: return "NOT";
    case GETINTTK: return "GETINTTK";
    case BREAKTK: return "BREAKTK";
    case CONTINUETK: return "CONTINUETK";
    default: return "UNKNOWN";
    }
>>>>>>> b28ca46fce9fee58e781a2df68b64b37fbc5ae75
}