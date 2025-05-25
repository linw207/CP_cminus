%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <limits.h>
    #include "main.h"
    
    extern FILE* yyin;
    extern int yylex();
    extern int currentLine;
    extern char* yytext;
    
    // 全局变量
    extern SyntaxTree* syntaxTree;
    extern int analysisSuccessful;
    
    // 函数声明
    void yyerror(const char* msg);
    void reportSyntaxError(const char* msg, int line);
    TreeNode* createSyntaxNode(const char* name, int line);
    void addSyntaxChild(TreeNode* parent, TreeNode* child);
    int updateSyntaxNodeLine(TreeNode* node);
    
    // 报告语法错误
    void reportSyntaxError(const char* msg, int line) {
        if (strstr(msg, "Missing") != NULL || strstr(msg, "Unexpected") != NULL) {
            fprintf(stderr, "Error type B at Line %d: %s\n", line, msg);
        } else if (strstr(msg, "syntax error") != NULL) {
            // 提供更具体的错误消息
            if (yytext != NULL) {
                if (strcmp(yytext, "else") == 0) {
                    fprintf(stderr, "Error type B at Line %d: Missing ';' before 'else'\n", line);
                } else if (strcmp(yytext, ",") == 0) {
                    fprintf(stderr, "Error type B at Line %d: Unexpected ',' in array indexing\n", line);
                } else {
                    fprintf(stderr, "Error type B at Line %d: syntax error near '%s'\n", line, yytext);
                }
            } else {
                fprintf(stderr, "Error type B at Line %d: %s\n", line, msg);
            }
        } else {
            fprintf(stderr, "Error type B at Line %d: %s\n", line, msg);
        }
    }
    
    // 创建语法节点
    TreeNode* createSyntaxNode(const char* name, int line) {
        return createNonTerminalNode(name, line);
    }
    
    // 添加子节点
    void addSyntaxChild(TreeNode* parent, TreeNode* child) {
        addChild(parent, child);
    }
    
    // 将updateSyntaxNodeLine函数改为：
   int updateSyntaxNodeLine(TreeNode* node) {
      if (!node) return INT_MAX;
      
      // 直接调用main.c中的函数
      return node->line;
   }
%}

/* 定义语法分析器的值类型 */
%union {
    TreeNode* node;
}

/* 终结符定义 */
%token <node> INT FLOAT ID
%token <node> TYPE STRUCT RETURN IF ELSE WHILE
%token <node> SEMI COMMA ASSIGNOP RELOP PLUS MINUS STAR DIV
%token <node> AND OR NOT DOT LP RP LB RB LC RC

/* 运算符优先级和结合性 */
%right ASSIGNOP
%left OR
%left AND
%left RELOP
%left PLUS MINUS
%left STAR DIV
%right NOT
%left LP RP LB RB DOT
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

/* 非终结符定义 */
%type <node> Program ExtDefList ExtDef ExtDecList
%type <node> Specifier StructSpecifier OptTag Tag
%type <node> VarDec FunDec VarList ParamDec
%type <node> CompSt StmtList Stmt
%type <node> DefList Def DecList Dec
%type <node> Exp Args

/* 错误处理非终结符 */
%type <node> ErrorSemi ErrorRP ErrorRB ErrorRC

/* 开始符号 */
%start Program

%%

/* 错误恢复规则 */
ErrorSemi    : error SEMI 
             { 
                reportSyntaxError("Missing or invalid token before ';'", currentLine);
                $$ = $2; 
             }
             | SEMI 
             { 
                $$ = $1; 
             }
             ;

ErrorRP      : error RP 
             { 
                reportSyntaxError("Missing or invalid expression in parentheses", currentLine);
                $$ = $2; 
             }
             | RP 
             { 
                $$ = $1; 
             }
             ;

ErrorRB      : error RB 
             { 
                reportSyntaxError("Missing or invalid expression in square brackets", currentLine);
                $$ = $2; 
             }
             | RB 
             { 
                $$ = $1; 
             }
             ;

ErrorRC      : error RC 
             { 
                reportSyntaxError("Missing or invalid declaration in block", currentLine);
                $$ = $2; 
             }
             | RC 
             { 
                $$ = $1; 
             }
             ;

/* 程序结构 */
Program      : ExtDefList
             {
                $$ = createSyntaxNode("Program", currentLine);
                addSyntaxChild($$, $1);
                updateSyntaxNodeLine($$);
                setSyntaxTreeRoot(syntaxTree, $$);
             }
             ;

ExtDefList   : ExtDef ExtDefList
             {
                $$ = createSyntaxNode("ExtDefList", currentLine);
                addSyntaxChild($$, $1);
                addSyntaxChild($$, $2);
                updateSyntaxNodeLine($$);
             }
             | /* empty */
             {
                $$ = NULL;
             }
             ;

ExtDef       : Specifier ExtDecList ErrorSemi
             {
                $$ = createSyntaxNode("ExtDef", currentLine);
                addSyntaxChild($$, $1);
                addSyntaxChild($$, $2);
                addSyntaxChild($$, $3);
                updateSyntaxNodeLine($$);
             }
             | Specifier ErrorSemi
             {
                $$ = createSyntaxNode("ExtDef", currentLine);
                addSyntaxChild($$, $1);
                addSyntaxChild($$, $2);
                updateSyntaxNodeLine($$);
             }
             | Specifier FunDec CompSt
             {
                $$ = createSyntaxNode("ExtDef", currentLine);
                addSyntaxChild($$, $1);
                addSyntaxChild($$, $2);
                addSyntaxChild($$, $3);
                updateSyntaxNodeLine($$);
             }
             ;

ExtDecList   : VarDec
             {
                $$ = createSyntaxNode("ExtDecList", currentLine);
                addSyntaxChild($$, $1);
                updateSyntaxNodeLine($$);
             }
             | VarDec COMMA ExtDecList
             {
                $$ = createSyntaxNode("ExtDecList", currentLine);
                addSyntaxChild($$, $1);
                addSyntaxChild($$, $2);
                addSyntaxChild($$, $3);
                updateSyntaxNodeLine($$);
             }
             ;

/* 类型说明符 */
Specifier    : TYPE
             {
                $$ = createSyntaxNode("Specifier", currentLine);
                addSyntaxChild($$, $1);
                updateSyntaxNodeLine($$);
             }
             | StructSpecifier
             {
                $$ = createSyntaxNode("Specifier", currentLine);
                addSyntaxChild($$, $1);
                updateSyntaxNodeLine($$);
             }
             ;

StructSpecifier : STRUCT OptTag LC DefList ErrorRC
                {
                   $$ = createSyntaxNode("StructSpecifier", currentLine);
                   addSyntaxChild($$, $1);
                   addSyntaxChild($$, $2);
                   addSyntaxChild($$, $3);
                   addSyntaxChild($$, $4);
                   addSyntaxChild($$, $5);
                   updateSyntaxNodeLine($$);
                }
                | STRUCT Tag
                {
                   $$ = createSyntaxNode("StructSpecifier", currentLine);
                   addSyntaxChild($$, $1);
                   addSyntaxChild($$, $2);
                   updateSyntaxNodeLine($$);
                }
                ;

OptTag       : ID
             {
                $$ = createSyntaxNode("OptTag", currentLine);
                addSyntaxChild($$, $1);
                updateSyntaxNodeLine($$);
             }
             | /* empty */
             {
                $$ = NULL;
             }
             ;

Tag          : ID
             {
                $$ = createSyntaxNode("Tag", currentLine);
                addSyntaxChild($$, $1);
                updateSyntaxNodeLine($$);
             }
             ;

/* 变量声明 */
VarDec       : ID
             {
                $$ = createSyntaxNode("VarDec", currentLine);
                addSyntaxChild($$, $1);
                updateSyntaxNodeLine($$);
             }
             | VarDec LB INT ErrorRB
             {
                $$ = createSyntaxNode("VarDec", currentLine);
                addSyntaxChild($$, $1);
                addSyntaxChild($$, $2);
                addSyntaxChild($$, $3);
                addSyntaxChild($$, $4);
                updateSyntaxNodeLine($$);
             }
             ;

FunDec       : ID LP VarList ErrorRP
             {
                $$ = createSyntaxNode("FunDec", currentLine);
                addSyntaxChild($$, $1);
                addSyntaxChild($$, $2);
                addSyntaxChild($$, $3);
                addSyntaxChild($$, $4);
                updateSyntaxNodeLine($$);
             }
             | ID LP ErrorRP
             {
                $$ = createSyntaxNode("FunDec", currentLine);
                addSyntaxChild($$, $1);
                addSyntaxChild($$, $2);
                addSyntaxChild($$, $3);
                updateSyntaxNodeLine($$);
             }
             ;

VarList      : ParamDec COMMA VarList
             {
                $$ = createSyntaxNode("VarList", currentLine);
                addSyntaxChild($$, $1);
                addSyntaxChild($$, $2);
                addSyntaxChild($$, $3);
                updateSyntaxNodeLine($$);
             }
             | ParamDec
             {
                $$ = createSyntaxNode("VarList", currentLine);
                addSyntaxChild($$, $1);
                updateSyntaxNodeLine($$);
             }
             ;

ParamDec     : Specifier VarDec
             {
                $$ = createSyntaxNode("ParamDec", currentLine);
                addSyntaxChild($$, $1);
                addSyntaxChild($$, $2);
                updateSyntaxNodeLine($$);
             }
             ;

/* 语句 */
CompSt       : LC DefList StmtList ErrorRC
             {
                $$ = createSyntaxNode("CompSt", currentLine);
                addSyntaxChild($$, $1);
                addSyntaxChild($$, $2);
                addSyntaxChild($$, $3);
                addSyntaxChild($$, $4);
                updateSyntaxNodeLine($$);
             }
             ;

StmtList     : Stmt StmtList
             {
                $$ = createSyntaxNode("StmtList", currentLine);
                addSyntaxChild($$, $1);
                addSyntaxChild($$, $2);
                updateSyntaxNodeLine($$);
             }
             | /* empty */
             {
                $$ = NULL;
             }
             ;

Stmt         : Exp ErrorSemi
             {
                $$ = createSyntaxNode("Stmt", currentLine);
                addSyntaxChild($$, $1);
                addSyntaxChild($$, $2);
                updateSyntaxNodeLine($$);
             }
             | CompSt
             {
                $$ = createSyntaxNode("Stmt", currentLine);
                addSyntaxChild($$, $1);
                updateSyntaxNodeLine($$);
             }
             | RETURN Exp ErrorSemi
             {
                $$ = createSyntaxNode("Stmt", currentLine);
                addSyntaxChild($$, $1);
                addSyntaxChild($$, $2);
                addSyntaxChild($$, $3);
                updateSyntaxNodeLine($$);
             }
             | IF LP Exp ErrorRP Stmt %prec LOWER_THAN_ELSE
             {
                $$ = createSyntaxNode("Stmt", currentLine);
                addSyntaxChild($$, $1);
                addSyntaxChild($$, $2);
                addSyntaxChild($$, $3);
                addSyntaxChild($$, $4);
                addSyntaxChild($$, $5);
                updateSyntaxNodeLine($$);
             }
             | IF LP Exp ErrorRP Stmt ELSE Stmt
             {
                $$ = createSyntaxNode("Stmt", currentLine);
                addSyntaxChild($$, $1);
                addSyntaxChild($$, $2);
                addSyntaxChild($$, $3);
                addSyntaxChild($$, $4);
                addSyntaxChild($$, $5);
                addSyntaxChild($$, $6);
                addSyntaxChild($$, $7);
                updateSyntaxNodeLine($$);
             }
             | WHILE LP Exp ErrorRP Stmt
             {
                $$ = createSyntaxNode("Stmt", currentLine);
                addSyntaxChild($$, $1);
                addSyntaxChild($$, $2);
                addSyntaxChild($$, $3);
                addSyntaxChild($$, $4);
                addSyntaxChild($$, $5);
                updateSyntaxNodeLine($$);
             }
             | IF LP Exp ErrorRP Stmt error Stmt
             {
                analysisSuccessful = 0;
                reportSyntaxError("Missing ';' before 'else'", currentLine);
                
                $$ = createSyntaxNode("Stmt", currentLine);
                addSyntaxChild($$, $1);
                addSyntaxChild($$, $2);
                addSyntaxChild($$, $3);
                addSyntaxChild($$, $4);
                addSyntaxChild($$, $5);
                addSyntaxChild($$, $7);
                updateSyntaxNodeLine($$);
             }
             ;

/* 局部定义 */
DefList      : Def DefList
             {
                $$ = createSyntaxNode("DefList", currentLine);
                addSyntaxChild($$, $1);
                addSyntaxChild($$, $2);
                updateSyntaxNodeLine($$);
             }
             | /* empty */
             {
                $$ = NULL;
             }
             ;

Def          : Specifier DecList ErrorSemi
             {
                $$ = createSyntaxNode("Def", currentLine);
                addSyntaxChild($$, $1);
                addSyntaxChild($$, $2);
                addSyntaxChild($$, $3);
                updateSyntaxNodeLine($$);
             }
             ;

DecList      : Dec
             {
                $$ = createSyntaxNode("DecList", currentLine);
                addSyntaxChild($$, $1);
                updateSyntaxNodeLine($$);
             }
             | Dec COMMA DecList
             {
                $$ = createSyntaxNode("DecList", currentLine);
                addSyntaxChild($$, $1);
                addSyntaxChild($$, $2);
                addSyntaxChild($$, $3);
                updateSyntaxNodeLine($$);
             }
             ;

Dec          : VarDec
             {
                $$ = createSyntaxNode("Dec", currentLine);
                addSyntaxChild($$, $1);
                updateSyntaxNodeLine($$);
             }
             | VarDec ASSIGNOP Exp
             {
                $$ = createSyntaxNode("Dec", currentLine);
                addSyntaxChild($$, $1);
                addSyntaxChild($$, $2);
                addSyntaxChild($$, $3);
                updateSyntaxNodeLine($$);
             }
             ;

/* 表达式 */
Exp          : Exp ASSIGNOP Exp
             {
                $$ = createSyntaxNode("Exp", currentLine);
                addSyntaxChild($$, $1);
                addSyntaxChild($$, $2);
                addSyntaxChild($$, $3);
                updateSyntaxNodeLine($$);
             }
             | Exp AND Exp
             {
                $$ = createSyntaxNode("Exp", currentLine);
                addSyntaxChild($$, $1);
                addSyntaxChild($$, $2);
                addSyntaxChild($$, $3);
                updateSyntaxNodeLine($$);
             }
             | Exp OR Exp
             {
                $$ = createSyntaxNode("Exp", currentLine);
                addSyntaxChild($$, $1);
                addSyntaxChild($$, $2);
                addSyntaxChild($$, $3);
                updateSyntaxNodeLine($$);
             }
             | Exp RELOP Exp
             {
                $$ = createSyntaxNode("Exp", currentLine);
                addSyntaxChild($$, $1);
                addSyntaxChild($$, $2);
                addSyntaxChild($$, $3);
                updateSyntaxNodeLine($$);
             }
             | Exp PLUS Exp
             {
                $$ = createSyntaxNode("Exp", currentLine);
                addSyntaxChild($$, $1);
                addSyntaxChild($$, $2);
                addSyntaxChild($$, $3);
                updateSyntaxNodeLine($$);
             }
             | Exp MINUS Exp
             {
                $$ = createSyntaxNode("Exp", currentLine);
                addSyntaxChild($$, $1);
                addSyntaxChild($$, $2);
                addSyntaxChild($$, $3);
                updateSyntaxNodeLine($$);
             }
             | Exp STAR Exp
             {
                $$ = createSyntaxNode("Exp", currentLine);
                addSyntaxChild($$, $1);
                addSyntaxChild($$, $2);
                addSyntaxChild($$, $3);
                updateSyntaxNodeLine($$);
             }
             | Exp DIV Exp
             {
                $$ = createSyntaxNode("Exp", currentLine);
                addSyntaxChild($$, $1);
                addSyntaxChild($$, $2);
                addSyntaxChild($$, $3);
                updateSyntaxNodeLine($$);
             }
             | LP Exp ErrorRP
             {
                $$ = createSyntaxNode("Exp", currentLine);
                addSyntaxChild($$, $1);
                addSyntaxChild($$, $2);
                addSyntaxChild($$, $3);
                updateSyntaxNodeLine($$);
             }
             | MINUS Exp
             {
                $$ = createSyntaxNode("Exp", currentLine);
                addSyntaxChild($$, $1);
                addSyntaxChild($$, $2);
                updateSyntaxNodeLine($$);
             }
             | NOT Exp
             {
                $$ = createSyntaxNode("Exp", currentLine);
                addSyntaxChild($$, $1);
                addSyntaxChild($$, $2);
                updateSyntaxNodeLine($$);
             }
             | ID LP Args ErrorRP
             {
                $$ = createSyntaxNode("Exp", currentLine);
                addSyntaxChild($$, $1);
                addSyntaxChild($$, $2);
                addSyntaxChild($$, $3);
                addSyntaxChild($$, $4);
                updateSyntaxNodeLine($$);
             }
             | ID LP ErrorRP
             {
                $$ = createSyntaxNode("Exp", currentLine);
                addSyntaxChild($$, $1);
                addSyntaxChild($$, $2);
                addSyntaxChild($$, $3);
                updateSyntaxNodeLine($$);
             }
             | Exp LB Exp ErrorRB
             {
                $$ = createSyntaxNode("Exp", currentLine);
                addSyntaxChild($$, $1);
                addSyntaxChild($$, $2);
                addSyntaxChild($$, $3);
                addSyntaxChild($$, $4);
                updateSyntaxNodeLine($$);
             }
             | Exp DOT ID
             {
                $$ = createSyntaxNode("Exp", currentLine);
                addSyntaxChild($$, $1);
                addSyntaxChild($$, $2);
                addSyntaxChild($$, $3);
                updateSyntaxNodeLine($$);
             }
             | ID
             {
                $$ = createSyntaxNode("Exp", currentLine);
                addSyntaxChild($$, $1);
                updateSyntaxNodeLine($$);
             }
             | INT
             {
                $$ = createSyntaxNode("Exp", currentLine);
                addSyntaxChild($$, $1);
                updateSyntaxNodeLine($$);
             }
             | FLOAT
             {
                $$ = createSyntaxNode("Exp", currentLine);
                addSyntaxChild($$, $1);
                updateSyntaxNodeLine($$);
             }
             | Exp LB Exp COMMA Exp RB
             {
                analysisSuccessful = 0;
                reportSyntaxError("Unexpected ',' in array indexing, did you mean '][' ?", currentLine);
                
                $$ = createSyntaxNode("Exp", currentLine);
                addSyntaxChild($$, $1);
                addSyntaxChild($$, $2);
                addSyntaxChild($$, $3);
                updateSyntaxNodeLine($$);
             }
             ;

Args         : Exp COMMA Args
             {
                $$ = createSyntaxNode("Args", currentLine);
                addSyntaxChild($$, $1);
                addSyntaxChild($$, $2);
                addSyntaxChild($$, $3);
                updateSyntaxNodeLine($$);
             }
             | Exp
             {
                $$ = createSyntaxNode("Args", currentLine);
                addSyntaxChild($$, $1);
                updateSyntaxNodeLine($$);
             }
             ;

%%

void yyerror(const char* msg) {
    // 由reportSyntaxError函数处理具体错误报告
    analysisSuccessful = 0;
    reportSyntaxError(msg, currentLine);
}