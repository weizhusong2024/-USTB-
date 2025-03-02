<<<<<<< HEAD
// struct.h
#ifndef STRUCT_H
#define STRUCT_H

#include <string>
#include <map>
#include <vector>

// ����Token�ṹ
enum TokenType {
    IDENFR, INTCON, CHARCON, STRCON, CONSTTK, INTTK, CHARTK, VOIDTK, MAINTK, IFTK,
    ELSETK, SWITCHTK, CASETK, DEFAULTTK, WHILETK, FORTK, SCANFTK, PRINTFTK, RETURNTK,
    PLUS, MINU, MULT, DIV, ASSIGN, LSS, LEQ, GRE, GEQ, EQL, NEQ, COLON,
    SEMICN, COMMA, LPARENT, RPARENT, LBRACK, RBRACK, LBRACE, RBRACE,
    MOD, OR, AND, NOT, GETINTTK, BREAKTK, CONTINUETK
};

struct Token {
    TokenType type;
    std::string value;
    int line;
};

// �������ƺ������ӳ���
extern std::map<std::string, TokenType> keywords;

// ���ַ�������ӳ���
extern std::map<char, TokenType> singleCharTokens;

#endif // STRUCT_H

=======
// struct.h
#ifndef STRUCT_H
#define STRUCT_H

#include <string>
#include <map>
#include <vector>

// ����Token�ṹ
enum TokenType {
    IDENFR, INTCON, CHARCON, STRCON, CONSTTK, INTTK, CHARTK, VOIDTK, MAINTK, IFTK,
    ELSETK, SWITCHTK, CASETK, DEFAULTTK, WHILETK, FORTK, SCANFTK, PRINTFTK, RETURNTK,
    PLUS, MINU, MULT, DIV, ASSIGN, LSS, LEQ, GRE, GEQ, EQL, NEQ, COLON,
    SEMICN, COMMA, LPARENT, RPARENT, LBRACK, RBRACK, LBRACE, RBRACE,
    MOD, OR, AND, NOT, GETINTTK, BREAKTK, CONTINUETK
};

struct Token {
    TokenType type;
    std::string value;
    int line;
};

// �������ƺ������ӳ���
extern std::map<std::string, TokenType> keywords;

// ���ַ�������ӳ���
extern std::map<char, TokenType> singleCharTokens;

#endif // STRUCT_H

>>>>>>> b28ca46fce9fee58e781a2df68b64b37fbc5ae75
