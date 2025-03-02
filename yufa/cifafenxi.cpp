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
vector<Token> token;
ifstream inputFile("testfile.txt");
ofstream output("output.txt");
int q = 0;

void MatchToken(string expected);
void MatchCompUnit();
void MatchDecl();
void MatchConstDecl();
void MatchIntConst();
void MatchNumber();
void MatchBType();
void MatchConstDef();
void MatchConstInitVal();
void MatchVarDecl();
void MatchVarDef();
void MatchInitVal();
void MatchFuncDef();
void MatchMainFuncDef();
void MatchFuncType();
void MatchFuncFParams();
void MatchFuncFParam();
void MatchBlock();
void MatchBlockItem();
void MatchStmt();
void MatchExp();
void MatchCond();
void MatchLVal();
void MatchPrimaryExp();
void MatchUnaryOp();
void MatchFuncRParams();
void MatchMulExp();
void MatchMulExp2();
void MatchUnaryExp();
void MatchAddExp();
void MatchAddExp2();
void MatchRelExp();
void MatchRelExp2();
void MatchEqExp();
void MatchEqExp2();
void MatchLAndExp();
void MatchLAndExp2();
void MatchLOrExp();
void MatchLOrExp2();
void MatchConstExp();
void MatchPrint();
void MatchGetint();
void MatchReturn();

void GrammarAnalysis()
{
	q = 0;
	MatchCompUnit();
	output.close();
	return;
}
void MatchCompUnit()
{
	// 编译单元 CompUnit → {Decl} {FuncDef} MainFuncDef // 1.是否存在Decl 2.是否存在FuncDef
	// 常量声明
	while ((tokenTypeToString(token[q].type) == "INTTK" || tokenTypeToString(token[q].type) == "CHARTK")
		&& tokenTypeToString(token[q + 2].type) != "LPARENT" || tokenTypeToString(token[q].type) == "CONSTTK")
	{
		MatchDecl();
	}
	// 函数定义
	while ((tokenTypeToString(token[q].type) == "INTTK" || tokenTypeToString(token[q].type) == "CHARTK" || tokenTypeToString(token[q].type) == "VOIDTK")
		&& tokenTypeToString(token[q + 1].type) == "IDENFR" && tokenTypeToString(token[q + 2].type) == "LPARENT")
	{
		MatchFuncDef();
	}
	// 主函数
	if (tokenTypeToString(token[q].type) == "INTTK" && tokenTypeToString(token[q + 1].type) == "MAINTK")
	{
		MatchMainFuncDef();
	}
	output << "<CompUnit>\n";
}
void MatchDecl()
{
	// 声明Decl → ConstDecl | VarDecl // 覆盖两种声明
	if (tokenTypeToString(token[q].type) == "CONSTTK")
	{
		MatchConstDecl();
	}
	else
	{
		MatchVarDecl();
	}
	// output << "<Decl>\n";
}
void MatchConstDecl()
{
	// 常量声明 ConstDecl → 'const' BType ConstDef { ',' ConstDef } ';' // 1.花括号内重复0次 2.花括号内重复多次
	MatchToken("CONSTTK");
	MatchBType();
	MatchConstDef();
	while (tokenTypeToString(token[q].type) == "COMMA")
	{
		MatchToken("COMMA");
		MatchConstDef();
	}
	MatchToken("SEMICN");
	output << "<ConstDecl>\n";
}
void MatchIntConst()
{
	if (token[q].value[0] == '0' && token[q].value.length() > 1)
	{
		printf("error");
		exit(0);
	}
	else
		MatchToken("INTCON");
	// printf("<无符号整数>\n");
	output << "<Number>\n";
}
void MatchNumber()
{
	// 数值 Number → IntConst
	if (tokenTypeToString(token[q].type) == "PLUS")
		MatchToken("PLUS");
	else if (tokenTypeToString(token[q].type) == "MINU")
		MatchToken("MINU");
	MatchIntConst();
	// printf("<整数>\n");
	// output << "<整数>\n";
}
void MatchBType()
{
	// 基本类型 BType → 'int' // 存在即可
	if (tokenTypeToString(token[q].type) == "INTTK")
		MatchToken("INTTK");
	else if (tokenTypeToString(token[q].type) == "CHARTK")
		MatchToken("CHARTK");
}
void MatchConstDef()
{
	// 常数定义 ConstDef → Ident { '[' ConstExp ']' } '=' ConstInitVal // 包含普通变量、⼀维数组、⼆维数组共三种情况
	MatchToken("IDENFR");
	while (tokenTypeToString(token[q].type) == "LBRACK")
	{
		MatchToken("LBRACK");
		MatchConstExp();
		MatchToken("RBRACK");
	}
	MatchToken("ASSIGN");
	MatchConstInitVal();
	output << "<ConstDef>\n";
}
void MatchConstInitVal()
{
	// 常量初值 ConstInitVal → ConstExp | '{' [ ConstInitVal { ',' ConstInitVal } ] '}' // 1.常表达式初值 2.⼀维数组初值 3.⼆维数组初值
	if (tokenTypeToString(token[q].type) != "LBRACE")
	{
		MatchConstExp();
	}
	else
	{
		MatchToken("LBRACE");
		if (tokenTypeToString(token[q].type) != "RBRACE")
		{
			MatchConstInitVal();
			while (tokenTypeToString(token[q].type) == "COMMA")
			{
				MatchToken("COMMA");
				MatchConstInitVal();
			}
		}
		MatchToken("RBRACE");
	}
	output << "<ConstInitVal>\n";
}
void MatchVarDecl()
{
	// 变量声明 VarDecl → BType VarDef { ',' VarDef } ';' // 1.花括号内重复0次 2.花括号内重复多次
	MatchBType();
	MatchVarDef();
	while (tokenTypeToString(token[q].type) == "COMMA")
	{
		MatchToken("COMMA");
		MatchVarDef();
	}
	MatchToken("SEMICN");
	output << "<VarDecl>\n";
}
void MatchVarDef()
{
	// 变量定义 VarDef → Ident { '[' ConstExp ']' }  | Ident { '[' ConstExp ']' } '=' InitVal
	MatchToken("IDENFR");
	while (tokenTypeToString(token[q].type) == "LBRACK")
	{
		MatchToken("LBRACK");
		MatchConstExp();
		MatchToken("RBRACK");
	}
	if (tokenTypeToString(token[q].type) == "ASSIGN")
	{
		MatchToken("ASSIGN");
		MatchInitVal();
	}
	output << "<VarDef>\n";
}
void MatchInitVal()
{
	// 变量初值 InitVal → Exp | '{' [ InitVal { ',' InitVal } ] '}'// 1.表达式初值 2.⼀维数组初值 3.⼆维数组初值
	if (tokenTypeToString(token[q].type) != "LBRACE")
	{
		MatchExp();
	}
	else
	{
		MatchToken("LBRACE");
		if (tokenTypeToString(token[q].type) != "RBRACE")
		{
			MatchInitVal();
			while (tokenTypeToString(token[q].type) == "COMMA")
			{
				MatchToken("COMMA");
				MatchInitVal();
			}
		}
		MatchToken("RBRACE");
	}
	output << "<InitVal>\n";
}
void MatchFuncDef()
{
	// 函数定义 FuncDef → FuncType Ident '(' [FuncFParams] ')' Block // 1.⽆形参 2.有形参
	MatchFuncType();
	MatchToken("IDENFR");
	MatchToken("LPARENT");
	if (tokenTypeToString(token[q].type) != "RPARENT")
		MatchFuncFParams();
	MatchToken("RPARENT");
	MatchBlock();
	output << "<FuncDef>\n";
}
void MatchMainFuncDef()
{
	// 主函数定义 MainFuncDef → 'int' 'main' '(' ')' Block // 存在main函数
	MatchToken("INTTK");
	MatchToken("MAINTK");
	MatchToken("LPARENT");
	MatchToken("RPARENT");
	MatchBlock();
	// printf("<MainFuncDef>\n");
	output << "<MainFuncDef>\n";
}
void MatchFuncType()
{
	// 函数类型 FuncType → 'void' | 'int' // 覆盖两种类型的函数
	if (tokenTypeToString(token[q].type) == "INTTK")
		MatchToken("INTTK");
	else if (tokenTypeToString(token[q].type) == "VOIDTK")
		MatchToken("VOIDTK");
	output << "<FuncType>\n";
}
void MatchFuncFParams()
{
	// 函数形参表 FuncFParams → FuncFParam { ',' FuncFParam } // 1.花括号内重复0次 2.花括号内重复多次
	MatchFuncFParam();
	while (tokenTypeToString(token[q].type) == "COMMA")
	{
		MatchToken("COMMA");
		MatchFuncFParam();
	}
	output << "<FuncFParams>\n";
}
void MatchFuncFParam()
{
	// 函数形参 FuncFParam → BType Ident ['[' ']' { '[' ConstExp ']' }] // 1.普通变量 2.⼀维数组变量 3.⼆维数组变量
	MatchBType();
	MatchToken("IDENFR");
	// 数组
	if (tokenTypeToString(token[q].type) == "LBRACK")
	{
		MatchToken("LBRACK");
		MatchToken("RBRACK");
		while (tokenTypeToString(token[q].type) == "LBRACK")
		{
			MatchToken("LBRACK");
			MatchConstExp();
			MatchToken("RBRACK");
		}
	}
	output << "<FuncFParam>\n";
}
void MatchBlock()
{
	// 语句块 Block → '{' { BlockItem } '}' // 1.花括号内重复0次 2.花括号内重复多次
	MatchToken("LBRACE");
	while (tokenTypeToString(token[q].type) != "RBRACE")
		MatchBlockItem();
	MatchToken("RBRACE");
	// printf("<Block>\n");
	output << "<Block>\n";
}
void MatchBlockItem()
{
	// 语句块项 BlockItem → Decl | Stmt // 覆盖两种语句块项
	if (tokenTypeToString(token[q].type) == "INTTK" || tokenTypeToString(token[q].type) == "CHARTK" || tokenTypeToString(token[q].type) == "CONSTTK")
	{
		MatchDecl();
	}
	else
	{
		MatchStmt();
	}
	// output << "<BlockItem>\n";
}
void MatchStmt()
{
	// 语句 Stmt → LVal '=' Exp ';' // 每种类型的语句都要覆盖
	// | [Exp] ';' //有⽆Exp两种情况
	// | Block
	// | 'if' '(' Cond ')' Stmt [ 'else' Stmt ] // 1.有else 2.⽆else
	// | 'while' '(' Cond ')' Stmt
	// | 'break' ';' | 'continue' ';'
	// | 'return' [Exp] ';' // 1.有Exp 2.⽆Exp
	// | LVal '=' 'getint''('')'';'
	// | 'printf''('FormatString{','Exp}')'';' // 1.有Exp 2.⽆Exp
	if (tokenTypeToString(token[q].type) == "IDENFR")
	{
		// result[k]=1;的情况
		// a[1] - a[1];
		// a[2] = -+a[1] * a[0] / 1;
		// temp[0][2] = 4;
		if (((tokenTypeToString(token[q + 1].type) == "LBRACK" && tokenTypeToString(token[q + 4].type) == "LBRACK" && tokenTypeToString(token[q + 7].type) == "ASSIGN"))
			|| (tokenTypeToString(token[q + 1].type) == "LBRACK" && tokenTypeToString(token[q + 4].type) == "ASSIGN")
			|| tokenTypeToString(token[q + 1].type) == "ASSIGN")
		{
			MatchLVal();
			MatchToken("ASSIGN");
			if (tokenTypeToString(token[q].type) == "GETINTTK")
			{
				MatchGetint();
			}
			else
				MatchExp();
		}
		else
		{
			MatchExp();
		}
		MatchToken("SEMICN");
	}
	else if (tokenTypeToString(token[q].type) == "LBRACE")
	{
		MatchBlock();
	}
	else if (tokenTypeToString(token[q].type) == "IFTK")
	{
		MatchToken("IFTK");
		MatchToken("LPARENT");
		MatchCond();
		MatchToken("RPARENT");
		MatchStmt();
		if (tokenTypeToString(token[q].type) == "ELSETK")
		{
			MatchToken("ELSETK");
			MatchStmt();
		}
	}
	else if (tokenTypeToString(token[q].type) == "WHILETK")
	{
		MatchToken("WHILETK");
		MatchToken("LPARENT");
		MatchCond();
		MatchToken("RPARENT");
		MatchStmt();
	}
	else if (tokenTypeToString(token[q].type) == "BREAKTK" || tokenTypeToString(token[q].type) == "CONTINUETK")
	{
		MatchToken(tokenTypeToString(token[q].type));
		MatchToken("SEMICN");
	}
	else if (tokenTypeToString(token[q].type) == "RETURNTK")
	{
		MatchReturn();
		MatchToken("SEMICN");
	}
	else if (tokenTypeToString(token[q].type) == "PRINTFTK")
	{
		MatchPrint();
		MatchToken("SEMICN");
	}
	else if (tokenTypeToString(token[q].type) == "SEMICN")
		MatchToken("SEMICN");

	// printf("<Stmt>\n");
	output << "<Stmt>\n";
}
void MatchExp()
{
	// 表达式 Exp → AddExp
	MatchAddExp();
	// printf("<Exp>\n");
	output << "<Exp>\n";
}
void MatchCond()
{
	// 条件表达式 Cond → LOrExp
	MatchLOrExp();
	output << "<Cond>\n";
}
void MatchLVal()
{
	// 左值表达式 LVal → Ident {'[' Exp ']'}
	MatchToken("IDENFR");
	while (tokenTypeToString(token[q].type) == "LBRACK")
	{
		MatchToken("LBRACK");
		MatchExp();
		MatchToken("RBRACK");
	}
	output << "<LVal>\n";
}
void MatchPrimaryExp()
{
	// 基本表达式 PrimaryExp → '(' Exp ')' | LVal | Number
	if (tokenTypeToString(token[q].type) == "LPARENT")
	{
		MatchToken("LPARENT");
		MatchExp();
		MatchToken("RPARENT");
	}
	else if (tokenTypeToString(token[q].type) == "IDENFR")
	{
		MatchLVal();
	}
	else if (tokenTypeToString(token[q].type) == "INTCON" || tokenTypeToString(token[q].type) == "PLUS" || tokenTypeToString(token[q].type) == "MINU")
		MatchNumber();
	output << "<PrimaryExp>\n";
}
void MatchUnaryOp()
{
	// 单⽬运算符 UnaryOp → '+' | '−' | '!' 注：'!'仅出现在条件表达式中 // 三种均需覆盖
	if (tokenTypeToString(token[q].type) == "PLUS" || tokenTypeToString(token[q].type) == "MINU" || tokenTypeToString(token[q].type) == "NOT")
	{
		MatchToken(tokenTypeToString(token[q].type));
	}
	output << "<UnaryOp>\n";
}
void MatchFuncRParams()
{
	// 函数实参表 FuncRParams → Exp { ',' Exp }
	MatchExp();
	while (tokenTypeToString(token[q].type) == "COMMA")
	{
		MatchToken("COMMA");
		MatchExp();
	}
	output << "<FuncRParams>\n";
}
void MatchMulExp()
{
	// 乘除模表达式 MulExp → UnaryExp |  MulExp (*' | '/' | '%') UnaryExp
	MatchUnaryExp();
	MatchMulExp2();
}
void MatchMulExp2()
{
	output << "<MulExp>\n";
	if (tokenTypeToString(token[q].type) == "MULT" || tokenTypeToString(token[q].type) == "DIV" || tokenTypeToString(token[q].type) == "MOD")
	{
		if (tokenTypeToString(token[q].type) == "MULT")
			MatchToken("MULT");
		else if (tokenTypeToString(token[q].type) == "DIV")
			MatchToken("DIV");
		else if (tokenTypeToString(token[q].type) == "MOD")
			MatchToken("MOD");
		MatchUnaryExp();
		MatchMulExp2();
	}
}
void MatchUnaryExp()
{
	// ⼀元表达式 UnaryExp → PrimaryExp | Ident '(' [FuncRParams] ')' | UnaryOp UnaryExp

	// 首位带符号
	if (tokenTypeToString(token[q].type) == "PLUS" || tokenTypeToString(token[q].type) == "MINU" || tokenTypeToString(token[q].type) == "NOT")
	{
		MatchUnaryOp();
		MatchUnaryExp();
	}
	// 函数调用
	else if (tokenTypeToString(token[q + 1].type) == "LPARENT")
	{
		MatchToken("IDENFR");
		MatchToken("LPARENT");
		if (tokenTypeToString(token[q].type) != "RPARENT")
			MatchFuncRParams();
		MatchToken("RPARENT");
	}
	else
	{
		MatchPrimaryExp();
	}
	output << "<UnaryExp>\n";
}
void MatchAddExp()
{
	// 加减表达式 AddExp → MulExp | AddExp ('+' | '−') MulExp
	// 形式：A → Aa|b
	// 改写为：A → bA’ ，A’→ aA’|ε

	// if (tokenTypeToString(token[q].type) == "PLUS")MatchToken("PLUS");
	// else if (tokenTypeToString(token[q].type) == "MINU")MatchToken("MINU");
	// x+y;
	MatchMulExp();
	MatchAddExp2();
}
void MatchAddExp2()
{
	output << "<AddExp>\n";
	if (tokenTypeToString(token[q].type) == "PLUS" || tokenTypeToString(token[q].type) == "MINU")
	{
		if (tokenTypeToString(token[q].type) == "PLUS")
			MatchToken("PLUS");
		else if (tokenTypeToString(token[q].type) == "MINU")
			MatchToken("MINU");
		MatchMulExp();
		MatchAddExp2();
	}
}
void MatchRelExp()
{
	// 关系表达式 RelExp → AddExp | RelExp ('<' | '>' | '<=' | '>=') AddExp

	if (tokenTypeToString(token[q].type) == "LSS")
		MatchToken("LSS");
	else if (tokenTypeToString(token[q].type) == "LEQ")
		MatchToken("LEQ");
	else if (tokenTypeToString(token[q].type) == "GRE")
		MatchToken("GRE");
	else if (tokenTypeToString(token[q].type) == "GEQ")
		MatchToken("GEQ");
	MatchAddExp();
	MatchRelExp2();
}
void MatchRelExp2()
{
	output << "<RelExp>\n";
	if (tokenTypeToString(token[q].type) == "LSS" || tokenTypeToString(token[q].type) == "LEQ" || tokenTypeToString(token[q].type) == "GRE" || tokenTypeToString(token[q].type) == "GEQ")
	{
		if (tokenTypeToString(token[q].type) == "LSS")
			MatchToken("LSS");
		else if (tokenTypeToString(token[q].type) == "LEQ")
			MatchToken("LEQ");
		else if (tokenTypeToString(token[q].type) == "GRE")
			MatchToken("GRE");
		else if (tokenTypeToString(token[q].type) == "GEQ")
			MatchToken("GEQ");
		MatchAddExp();
		MatchRelExp2();
	}
}
void MatchEqExp()
{
	// 相等性表达式 EqExp → RelExp | EqExp ('==' | '!=') RelExp
	if (tokenTypeToString(token[q].type) == "EQL")
		MatchToken("EQL");
	else if (tokenTypeToString(token[q].type) == "NEQ")
		MatchToken("NEQ");
	MatchRelExp();
	MatchEqExp2();
}
void MatchEqExp2()
{
	output << "<EqExp>\n";
	if (tokenTypeToString(token[q].type) == "EQL" || tokenTypeToString(token[q].type) == "NEQ")
	{
		if (tokenTypeToString(token[q].type) == "EQL")
			MatchToken("EQL");
		else if (tokenTypeToString(token[q].type) == "NEQ")
			MatchToken("NEQ");
		MatchRelExp();
		MatchEqExp2();
	}
}
void MatchLAndExp()
{
	// 逻辑与表达式 LAndExp → EqExp | LAndExp '&&' EqExp
	if (tokenTypeToString(token[q].type) == "AND")
		MatchToken("AND");
	MatchEqExp();
	MatchLAndExp2();
}
void MatchLAndExp2()
{
	output << "<LAndExp>\n";
	if (tokenTypeToString(token[q].type) == "AND")
	{
		if (tokenTypeToString(token[q].type) == "AND")
			MatchToken("AND");
		MatchEqExp();
		MatchLAndExp2();
	}
}
void MatchLOrExp()
{
	// 逻辑或表达式 LOrExp → LAndExp | LOrExp '||' LAndExp
	if (tokenTypeToString(token[q].type) == "OR")
		MatchToken("OR");
	MatchLAndExp();
	MatchLOrExp2();
}
void MatchLOrExp2()
{
	output << "<LOrExp>\n";
	if (tokenTypeToString(token[q].type) == "OR")
	{
		if (tokenTypeToString(token[q].type) == "OR")
			MatchToken("OR");
		MatchLAndExp();
		MatchLOrExp2();
	}
}
void MatchConstExp()
{
	MatchAddExp();
	output << "<ConstExp>\n";
}
void MatchPrint()
{
	//'printf''('FormatString{','Exp}')'';' // 1.有Exp 2.⽆Exp
	MatchToken("PRINTFTK");
	MatchToken("LPARENT");
	if (tokenTypeToString(token[q].type) == "STRCON")
		MatchToken("STRCON");
	else
		MatchExp();
	while (tokenTypeToString(token[q].type) == "COMMA")
	{
		MatchToken("COMMA");
		MatchExp();
	}
	MatchToken("RPARENT");
}
void MatchGetint()
{
	// LVal '=' 'getint''('')'';'
	MatchToken("GETINTTK");
	MatchToken("LPARENT");
	MatchToken("RPARENT");
}
void MatchReturn()
{
	// 'return' [Exp] ';' // 1.有Exp 2.⽆Exp
	MatchToken("RETURNTK");
	// 有返回值
	if (tokenTypeToString(token[q].type) != "SEMICN")
		MatchExp();
}
void MatchToken(string expected)
{
	if (tokenTypeToString(token[q].type) == expected)
	{
		// cout << tokenTypeToString(token[q].type) << " " << token[q].value << endl;
		output << tokenTypeToString(token[q].type) << " " << token[q].value << endl;
		q++;
	}
	else
	{
		cout << tokenTypeToString(token[q].type) << " " << expected << endl;
		printf("shitbrofuckingerror_tm");
		exit(0);
	}
}
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
    if (!inputFile.is_open()) {
        cerr << "Failed to open file." << endl;
        return 1;
    }

    string code((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
    lexicalAnalysis(token, code);

	MatchCompUnit();
	inputFile.close();
	output.close();
    return 0;
}