// function.h
#ifndef FUNCTION_H
#define FUNCTION_H

#include <string>
#include <vector>
#include "struct.h"

// �ж��Ƿ�Ϊ��ʶ��
bool isIdentifier(const std::string& str);

// ���һ���ʷ���Ԫ�����
void addToken(std::vector<Token>& tokens, TokenType type, const std::string& value, int line);

// �ʷ���������
void lexicalAnalysis(std::vector<Token>& tokens, const std::string& code);

// ӳ�� TokenType ���ַ���
std::string tokenTypeToString(TokenType type);

#endif // FUNCTION_H
