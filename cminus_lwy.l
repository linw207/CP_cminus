%option noyywrap

%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <errno.h>
    #include "main.h"
    #include "cminus_lwy.tab.h"

    extern SyntaxTree* syntaxTree;
    extern int analysisSuccessful;
    int currentLine = 1;

    // 报告词法错误
    void reportLexicalError(const char* lexeme, const char* type, int line) {
        analysisSuccessful = 0;
        printf("Error type A at Line %d: \"%s\" is not a valid %s\n", 
               line, lexeme, type);
    }

    // 数值转换函数
    int toInteger(const char* str, int base) {
        char* endptr;
        errno = 0;
        long val = strtol(str, &endptr, base);
        
        if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
            || (errno != 0 && val == 0)) {
            reportLexicalError(str, 
                base == 10 ? "decimal integer" : 
                base == 8 ? "octal integer" : "hexadecimal integer", currentLine);
            return 0;
        }

        if (endptr == str || *endptr != '\0') {
            reportLexicalError(str, 
                base == 10 ? "decimal integer" : 
                base == 8 ? "octal integer" : "hexadecimal integer", currentLine);
            return 0;
        }
        
        return (int)val;
    }

    float toFloat(const char* str) {
        char* endptr;
        errno = 0;
        float val = strtof(str, &endptr);
        
        if ((errno == ERANGE) || (errno != 0 && val == 0)) {
            reportLexicalError(str, "floating-point number", currentLine);
            return 0.0f;
        }

        if (endptr == str || *endptr != '\0') {
            reportLexicalError(str, "floating-point number", currentLine);
            return 0.0f;
        }
        
        return val;
    }

    // 创建Token节点的辅助函数
    void createToken(YYSTYPE* yylval, const char* tokenName, NodeType type) {
        yylval->node = createTokenNode(tokenName, currentLine, type);
    }

    void createIntToken(YYSTYPE* yylval, const char* tokenName, int intValue) {
        yylval->node = createIntValueNode(tokenName, currentLine, intValue);
    }

    void createFloatToken(YYSTYPE* yylval, const char* tokenName, float floatValue) {
        yylval->node = createFloatValueNode(tokenName, currentLine, floatValue);
    }

    void createIdToken(YYSTYPE* yylval, const char* tokenName, const char* idValue) {
        yylval->node = createIdentifierNode(tokenName, currentLine, idValue);
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
"int"           { createToken(&yylval, "TYPE", NODE_INT_TYPE); return TYPE; }
"float"         { createToken(&yylval, "TYPE", NODE_FLOAT_TYPE); return TYPE; }
"void"          { createToken(&yylval, "TYPE", NODE_OTHER); return TYPE; }
"if"            { createToken(&yylval, "IF", NODE_OTHER); return IF; }
"else"          { createToken(&yylval, "ELSE", NODE_OTHER); return ELSE; }
"while"         { createToken(&yylval, "WHILE", NODE_OTHER); return WHILE; }
"return"        { createToken(&yylval, "RETURN", NODE_OTHER); return RETURN; }
"struct"        { createToken(&yylval, "STRUCT", NODE_OTHER); return STRUCT; }

 /* 错误的数字表示 */
{BAD_OCTAL}     { 
                  reportLexicalError(yytext, "octal integer", currentLine); 
                  createIntToken(&yylval, "INT", 0); 
                  return INT; 
                }
{BAD_HEX}       { 
                  reportLexicalError(yytext, "hexadecimal integer", currentLine); 
                  createIntToken(&yylval, "INT", 0); 
                  return INT; 
                }

 /* 有效数字 */
{DECIMAL}       { createIntToken(&yylval, "INT", toInteger(yytext, 10)); return INT; }
{OCTAL}         { createIntToken(&yylval, "INT", toInteger(yytext, 8)); return INT; }
{HEXADECIMAL}   { createIntToken(&yylval, "INT", toInteger(yytext, 16)); return INT; }
{FLOAT}         { createFloatToken(&yylval, "FLOAT", toFloat(yytext)); return FLOAT; }

 /* 运算符 */
{ASSIGN}        { createToken(&yylval, "ASSIGNOP", NODE_OTHER); return ASSIGNOP; }
{COMPARE}       { createToken(&yylval, "RELOP", NODE_OTHER); return RELOP; }
"+"             { createToken(&yylval, "PLUS", NODE_OTHER); return PLUS; }
"-"             { createToken(&yylval, "MINUS", NODE_OTHER); return MINUS; }
"*"             { createToken(&yylval, "STAR", NODE_OTHER); return STAR; }
"/"             { createToken(&yylval, "DIV", NODE_OTHER); return DIV; }
"&&"            { createToken(&yylval, "AND", NODE_OTHER); return AND; }
"||"            { createToken(&yylval, "OR", NODE_OTHER); return OR; }
"!"             { createToken(&yylval, "NOT", NODE_OTHER); return NOT; }

 /* 分隔符 */
";"             { createToken(&yylval, "SEMI", NODE_OTHER); return SEMI; }
","             { createToken(&yylval, "COMMA", NODE_OTHER); return COMMA; }
"."             { createToken(&yylval, "DOT", NODE_OTHER); return DOT; }
"("             { createToken(&yylval, "LP", NODE_OTHER); return LP; }
")"             { createToken(&yylval, "RP", NODE_OTHER); return RP; }
"["             { createToken(&yylval, "LB", NODE_OTHER); return LB; }
"]"             { createToken(&yylval, "RB", NODE_OTHER); return RB; }
"{"             { createToken(&yylval, "LC", NODE_OTHER); return LC; }
"}"             { createToken(&yylval, "RC", NODE_OTHER); return RC; }

 /* 标识符 */
{IDENTIFIER}    { 
                  createIdToken(&yylval, "ID", yytext);
                  return ID; 
                }

 /* 未识别的字符 */
.               { 
                  reportLexicalError(yytext, "character", currentLine);
                  analysisSuccessful = 0;
                }

%%