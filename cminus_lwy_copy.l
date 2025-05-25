%option noyywrap

%{
    #include <string>
    #include <memory>
    #include "main.hpp"
    #include "cminus_lwy.tab.h"
    using namespace std;

    extern std::shared_ptr<SyntaxTree> syntaxTree;
    extern bool analysisSuccessful;
    int currentLine = 1;

    // 错误处理器
    class LexicalErrorHandler {
    public:
        static void reportError(const char* lexeme, const char* type, int line) {
            analysisSuccessful = false;
            printf("Error type A at Line %d: \"%s\" is not a valid %s\n", 
                   line, lexeme, type);
        }
    };

    // 数值转换器
    class NumericConverter {
    public:
        static int toInteger(const char* str, int base = 10) {
            try {
                size_t pos = 0;
                int result = std::stoi(str, &pos, base);
                if (pos != strlen(str)) {
                    throw std::invalid_argument("Invalid characters in input");
                }
                return result;
            } catch (const std::exception&) {
                LexicalErrorHandler::reportError(str, 
                    base == 10 ? "decimal integer" : 
                    base == 8 ? "octal integer" : "hexadecimal integer", currentLine);
                return 0;
            }
        }

        static float toFloat(const char* str) {
            try {
                size_t pos = 0;
                float result = std::stof(str, &pos);
                if (pos != strlen(str)) {
                    throw std::invalid_argument("Invalid characters in input");
                }
                return result;
            } catch (const std::exception&) {
                LexicalErrorHandler::reportError(str, "floating-point number", currentLine);
                return 0.0f;
            }
        }
    };

    // 创建Token节点
    void createTokenNode(TreeNode*& node, const char* tokenName, NodeType type) {
        node = TreeNode::createTokenNode(tokenName, currentLine, type);
    }

    void createTokenNode(TreeNode*& node, const char* tokenName, int intValue) {
        node = TreeNode::createIntValueNode(tokenName, currentLine, intValue);
    }

    void createTokenNode(TreeNode*& node, const char* tokenName, float floatValue) {
        node = TreeNode::createFloatValueNode(tokenName, currentLine, floatValue);
    }

    void createTokenNode(TreeNode*& node, const char* tokenName, string* idValue) {
        node = TreeNode::createIdentifierNode(tokenName, currentLine, idValue);
    }
%}

/* 字符类定义 */
LETTER      [a-zA-Z]
DIGIT       [0-9]
OCTDIGIT    [0-7]
HEXDIGIT    [0-9a-fA-F]
IDENTIFIER  [_a-zA-Z][_a-zA-Z0-9]*

/* 整数定义 */
DECIMAL     0|[1-9]{DIGIT}*
OCTAL       0{OCTDIGIT}+
HEXADECIMAL 0[xX]{HEXDIGIT}+
BAD_OCTAL   0{OCTDIGIT}*[89]{DIGIT}*
BAD_HEX     0[xX]{HEXDIGIT}*[g-zG-Z][_a-zA-Z0-9]*

/* 浮点数定义 */
FRACTION    {DECIMAL}\.{DECIMAL}?|\.{DECIMAL}
EXPONENT    [eE][+-]?{DECIMAL}
FLOAT       {FRACTION}{EXPONENT}?|{DECIMAL}{EXPONENT}

/* 运算符和分隔符 */
ASSIGN      =
COMPARE     >|<|>=|<=|==|!=
ARITHMETIC  \+|\-|\*|\/
LOGICAL     &&|\|\||!
SEPARATOR   ;|,|\.|[\(\)\[\]\{\}]

%x COMMENT

%%

 /* 空白符和注释处理 */
[ \t\r\v\f]     { /* 忽略空白符 */ }
\n              { currentLine++; }
"//".*          { /* 单行注释 */ }
"/*"            { BEGIN(COMMENT); }
<COMMENT>"*/"   { BEGIN(INITIAL); }
<COMMENT>\n     { currentLine++; }
<COMMENT>.      { /* 忽略注释内容 */ }

 /* 关键字 */
"int"           { createTokenNode(yylval.node, "TYPE", NodeType::INT_TYPE); return TYPE; }
"float"         { createTokenNode(yylval.node, "TYPE", NodeType::FLOAT_TYPE); return TYPE; }
"void"          { createTokenNode(yylval.node, "TYPE", NodeType::OTHER); return TYPE; }
"if"            { createTokenNode(yylval.node, "IF", NodeType::OTHER); return IF; }
"else"          { createTokenNode(yylval.node, "ELSE", NodeType::OTHER); return ELSE; }
"while"         { createTokenNode(yylval.node, "WHILE", NodeType::OTHER); return WHILE; }
"return"        { createTokenNode(yylval.node, "RETURN", NodeType::OTHER); return RETURN; }
"struct"        { createTokenNode(yylval.node, "STRUCT", NodeType::OTHER); return STRUCT; }

 /* 错误的数字表示 */
{BAD_OCTAL}     { 
                  LexicalErrorHandler::reportError(yytext, "octal integer", currentLine); 
                  createTokenNode(yylval.node, "INT", 0); 
                  return INT; 
                }
{BAD_HEX}       { 
                  LexicalErrorHandler::reportError(yytext, "hexadecimal integer", currentLine); 
                  createTokenNode(yylval.node, "INT", 0); 
                  return INT; 
                }

 /* 有效数字 */
{DECIMAL}       { createTokenNode(yylval.node, "INT", NumericConverter::toInteger(yytext, 10)); return INT; }
{OCTAL}         { createTokenNode(yylval.node, "INT", NumericConverter::toInteger(yytext, 8)); return INT; }
{HEXADECIMAL}   { createTokenNode(yylval.node, "INT", NumericConverter::toInteger(yytext, 16)); return INT; }
{FLOAT}         { createTokenNode(yylval.node, "FLOAT", NumericConverter::toFloat(yytext)); return FLOAT; }

 /* 运算符 */
{ASSIGN}        { createTokenNode(yylval.node, "ASSIGNOP", NodeType::OTHER); return ASSIGNOP; }
{COMPARE}       { createTokenNode(yylval.node, "RELOP", NodeType::OTHER); return RELOP; }
"+"             { createTokenNode(yylval.node, "PLUS", NodeType::OTHER); return PLUS; }
"-"             { createTokenNode(yylval.node, "MINUS", NodeType::OTHER); return MINUS; }
"*"             { createTokenNode(yylval.node, "STAR", NodeType::OTHER); return STAR; }
"/"             { createTokenNode(yylval.node, "DIV", NodeType::OTHER); return DIV; }
"&&"            { createTokenNode(yylval.node, "AND", NodeType::OTHER); return AND; }
"||"            { createTokenNode(yylval.node, "OR", NodeType::OTHER); return OR; }
"!"             { createTokenNode(yylval.node, "NOT", NodeType::OTHER); return NOT; }

 /* 分隔符 */
";"             { createTokenNode(yylval.node, "SEMI", NodeType::OTHER); return SEMI; }
","             { createTokenNode(yylval.node, "COMMA", NodeType::OTHER); return COMMA; }
"."             { createTokenNode(yylval.node, "DOT", NodeType::OTHER); return DOT; }
"("             { createTokenNode(yylval.node, "LP", NodeType::OTHER); return LP; }
")"             { createTokenNode(yylval.node, "RP", NodeType::OTHER); return RP; }
"["             { createTokenNode(yylval.node, "LB", NodeType::OTHER); return LB; }
"]"             { createTokenNode(yylval.node, "RB", NodeType::OTHER); return RB; }
"{"             { createTokenNode(yylval.node, "LC", NodeType::OTHER); return LC; }
"}"             { createTokenNode(yylval.node, "RC", NodeType::OTHER); return RC; }

 /* 标识符 */
{IDENTIFIER}    { 
                  std::string* idName = new std::string(yytext);
                  createTokenNode(yylval.node, "ID", idName);
                  return ID; 
                }

 /* 未识别的字符 */
.               { 
                  LexicalErrorHandler::reportError(yytext, "character", currentLine);
                  analysisSuccessful = false;
                }

%%.in