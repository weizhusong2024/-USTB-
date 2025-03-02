// function.h
#ifndef FUNCTION_H
#define FUNCTION_H

#include <string>
#include <vector>
#include "struct.h"

// 判断是否为标识符
bool isIdentifier(const std::string& str);

// 添加一个词法单元到结果
void addToken(std::vector<Token>& tokens, TokenType type, const std::string& value, int line);

// 词法分析函数
void lexicalAnalysis(std::vector<Token>& tokens, const std::string& code);

// 映射 TokenType 到字符串
std::string tokenTypeToString(TokenType type);

#endif // FUNCTION_H
