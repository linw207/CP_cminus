%{
    #include <iostream>
    #include <memory>
    #include <string>
    #include <vector>
    #include <cstring>
    #include "main.hpp"
    
    extern FILE* yyin;
    extern int yylex();
    extern int currentLine;
    
    // 全局变量
    std::shared_ptr<SyntaxTree> syntaxTree;
    bool analysisSuccessful = true;
    
    // 前向声明
    void yyerror(const char* msg);
    
    // 错误处理工具
    class SyntaxErrorHandler {
    private:
        static const int MAX_ERROR_MSG = 256;
        
    public:
        static void reportError(const char* msg, int line) {
            if (strstr(msg, "Missing") != nullptr || strstr(msg, "Unexpected") != nullptr) {
                fprintf(stderr, "Error type B at Line %d: %s\n", line, msg);
            } else if (strstr(msg, "syntax error") != nullptr) {
                // 提供更具体的错误消息
                extern char* yytext;
                if (yytext != nullptr) {
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
    };
    
    // 节点构建器
    class NodeBuilder {
    public:
        static TreeNode* createNonTerminalNode(const char* name, int line) {
            return TreeNode::createNonTerminalNode(name, line);
        }
        
        static void addChild(TreeNode* parent, TreeNode* child) {
            if (parent && child) {
                parent->addChild(child);
            }
        }
        
        static int updateNodeLine(TreeNode* node) {
            if (!node) return INT_MAX;
            if (node->children.empty()) return node->line;
            
            int minLine = node->line;
            for (auto child : node->children) {
                if (child) {
                    minLine = std::min(minLine, child->line);
                }
            }
            node->line = minLine;
            return minLine;
        }
    };
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
                SyntaxErrorHandler::reportError("Missing or invalid token before ';'", currentLine);
                $$ = $2; 
             }
             | SEMI 
             { 
                $$ = $1; 
             }
             ;

ErrorRP      : error RP 
             { 
                SyntaxErrorHandler::reportError("Missing or invalid expression in parentheses", currentLine);
                $$ = $2; 
             }
             | RP 
             { 
                $$ = $1; 
             }
             ;

ErrorRB      : error RB 
             { 
                SyntaxErrorHandler::reportError("Missing or invalid expression in square brackets", currentLine);
                $$ = $2; 
             }
             | RB 
             { 
                $$ = $1; 
             }
             ;

ErrorRC      : error RC 
             { 
                SyntaxErrorHandler::reportError("Missing or invalid declaration in block", currentLine);
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
                $$ = NodeBuilder::createNonTerminalNode("Program", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::updateNodeLine($$);
                syntaxTree->setRoot($$);
             }
             ;

ExtDefList   : ExtDef ExtDefList
             {
                $$ = NodeBuilder::createNonTerminalNode("ExtDefList", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::addChild($$, $2);
                NodeBuilder::updateNodeLine($$);
             }
             | /* empty */
             {
                $$ = nullptr;
             }
             ;

ExtDef       : Specifier ExtDecList ErrorSemi
             {
                $$ = NodeBuilder::createNonTerminalNode("ExtDef", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::addChild($$, $2);
                NodeBuilder::addChild($$, $3);
                NodeBuilder::updateNodeLine($$);
             }
             | Specifier ErrorSemi
             {
                $$ = NodeBuilder::createNonTerminalNode("ExtDef", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::addChild($$, $2);
                NodeBuilder::updateNodeLine($$);
             }
             | Specifier FunDec CompSt
             {
                $$ = NodeBuilder::createNonTerminalNode("ExtDef", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::addChild($$, $2);
                NodeBuilder::addChild($$, $3);
                NodeBuilder::updateNodeLine($$);
             }
             ;

ExtDecList   : VarDec
             {
                $$ = NodeBuilder::createNonTerminalNode("ExtDecList", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::updateNodeLine($$);
             }
             | VarDec COMMA ExtDecList
             {
                $$ = NodeBuilder::createNonTerminalNode("ExtDecList", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::addChild($$, $2);
                NodeBuilder::addChild($$, $3);
                NodeBuilder::updateNodeLine($$);
             }
             ;

/* 类型说明符 */
Specifier    : TYPE
             {
                $$ = NodeBuilder::createNonTerminalNode("Specifier", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::updateNodeLine($$);
             }
             | StructSpecifier
             {
                $$ = NodeBuilder::createNonTerminalNode("Specifier", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::updateNodeLine($$);
             }
             ;

StructSpecifier : STRUCT OptTag LC DefList ErrorRC
                {
                   $$ = NodeBuilder::createNonTerminalNode("StructSpecifier", currentLine);
                   NodeBuilder::addChild($$, $1);
                   NodeBuilder::addChild($$, $2);
                   NodeBuilder::addChild($$, $3);
                   NodeBuilder::addChild($$, $4);
                   NodeBuilder::addChild($$, $5);
                   NodeBuilder::updateNodeLine($$);
                }
                | STRUCT Tag
                {
                   $$ = NodeBuilder::createNonTerminalNode("StructSpecifier", currentLine);
                   NodeBuilder::addChild($$, $1);
                   NodeBuilder::addChild($$, $2);
                   NodeBuilder::updateNodeLine($$);
                }
                ;

OptTag       : ID
             {
                $$ = NodeBuilder::createNonTerminalNode("OptTag", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::updateNodeLine($$);
             }
             | /* empty */
             {
                $$ = nullptr;
             }
             ;

Tag          : ID
             {
                $$ = NodeBuilder::createNonTerminalNode("Tag", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::updateNodeLine($$);
             }
             ;

/* 变量声明 */
VarDec       : ID
             {
                $$ = NodeBuilder::createNonTerminalNode("VarDec", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::updateNodeLine($$);
             }
             | VarDec LB INT ErrorRB
             {
                $$ = NodeBuilder::createNonTerminalNode("VarDec", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::addChild($$, $2);
                NodeBuilder::addChild($$, $3);
                NodeBuilder::addChild($$, $4);
                NodeBuilder::updateNodeLine($$);
             }
             ;

FunDec       : ID LP VarList ErrorRP
             {
                $$ = NodeBuilder::createNonTerminalNode("FunDec", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::addChild($$, $2);
                NodeBuilder::addChild($$, $3);
                NodeBuilder::addChild($$, $4);
                NodeBuilder::updateNodeLine($$);
             }
             | ID LP ErrorRP
             {
                $$ = NodeBuilder::createNonTerminalNode("FunDec", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::addChild($$, $2);
                NodeBuilder::addChild($$, $3);
                NodeBuilder::updateNodeLine($$);
             }
             ;

VarList      : ParamDec COMMA VarList
             {
                $$ = NodeBuilder::createNonTerminalNode("VarList", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::addChild($$, $2);
                NodeBuilder::addChild($$, $3);
                NodeBuilder::updateNodeLine($$);
             }
             | ParamDec
             {
                $$ = NodeBuilder::createNonTerminalNode("VarList", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::updateNodeLine($$);
             }
             ;

ParamDec     : Specifier VarDec
             {
                $$ = NodeBuilder::createNonTerminalNode("ParamDec", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::addChild($$, $2);
                NodeBuilder::updateNodeLine($$);
             }
             ;

/* 语句 */
CompSt       : LC DefList StmtList ErrorRC
             {
                $$ = NodeBuilder::createNonTerminalNode("CompSt", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::addChild($$, $2);
                NodeBuilder::addChild($$, $3);
                NodeBuilder::addChild($$, $4);
                NodeBuilder::updateNodeLine($$);
             }
             ;

StmtList     : Stmt StmtList
             {
                $$ = NodeBuilder::createNonTerminalNode("StmtList", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::addChild($$, $2);
                NodeBuilder::updateNodeLine($$);
             }
             | /* empty */
             {
                $$ = nullptr;
             }
             ;

Stmt         : Exp ErrorSemi
             {
                $$ = NodeBuilder::createNonTerminalNode("Stmt", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::addChild($$, $2);
                NodeBuilder::updateNodeLine($$);
             }
             | CompSt
             {
                $$ = NodeBuilder::createNonTerminalNode("Stmt", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::updateNodeLine($$);
             }
             | RETURN Exp ErrorSemi
             {
                $$ = NodeBuilder::createNonTerminalNode("Stmt", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::addChild($$, $2);
                NodeBuilder::addChild($$, $3);
                NodeBuilder::updateNodeLine($$);
             }
             | IF LP Exp ErrorRP Stmt %prec LOWER_THAN_ELSE
             {
                $$ = NodeBuilder::createNonTerminalNode("Stmt", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::addChild($$, $2);
                NodeBuilder::addChild($$, $3);
                NodeBuilder::addChild($$, $4);
                NodeBuilder::addChild($$, $5);
                NodeBuilder::updateNodeLine($$);
             }
             | IF LP Exp ErrorRP Stmt ELSE Stmt
             {
                $$ = NodeBuilder::createNonTerminalNode("Stmt", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::addChild($$, $2);
                NodeBuilder::addChild($$, $3);
                NodeBuilder::addChild($$, $4);
                NodeBuilder::addChild($$, $5);
                NodeBuilder::addChild($$, $6);
                NodeBuilder::addChild($$, $7);
                NodeBuilder::updateNodeLine($$);
             }
             | WHILE LP Exp ErrorRP Stmt
             {
                $$ = NodeBuilder::createNonTerminalNode("Stmt", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::addChild($$, $2);
                NodeBuilder::addChild($$, $3);
                NodeBuilder::addChild($$, $4);
                NodeBuilder::addChild($$, $5);
                NodeBuilder::updateNodeLine($$);
             }
             | IF LP Exp ErrorRP Stmt error Stmt
             {
                analysisSuccessful = false;
                SyntaxErrorHandler::reportError("Missing ';' before 'else'", currentLine);
                
                $$ = NodeBuilder::createNonTerminalNode("Stmt", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::addChild($$, $2);
                NodeBuilder::addChild($$, $3);
                NodeBuilder::addChild($$, $4);
                NodeBuilder::addChild($$, $5);
                NodeBuilder::addChild($$, $7);
                NodeBuilder::updateNodeLine($$);
             }
             ;

/* 局部定义 */
DefList      : Def DefList
             {
                $$ = NodeBuilder::createNonTerminalNode("DefList", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::addChild($$, $2);
                NodeBuilder::updateNodeLine($$);
             }
             | /* empty */
             {
                $$ = nullptr;
             }
             ;

Def          : Specifier DecList ErrorSemi
             {
                $$ = NodeBuilder::createNonTerminalNode("Def", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::addChild($$, $2);
                NodeBuilder::addChild($$, $3);
                NodeBuilder::updateNodeLine($$);
             }
             ;

DecList      : Dec
             {
                $$ = NodeBuilder::createNonTerminalNode("DecList", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::updateNodeLine($$);
             }
             | Dec COMMA DecList
             {
                $$ = NodeBuilder::createNonTerminalNode("DecList", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::addChild($$, $2);
                NodeBuilder::addChild($$, $3);
                NodeBuilder::updateNodeLine($$);
             }
             ;

Dec          : VarDec
             {
                $$ = NodeBuilder::createNonTerminalNode("Dec", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::updateNodeLine($$);
             }
             | VarDec ASSIGNOP Exp
             {
                $$ = NodeBuilder::createNonTerminalNode("Dec", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::addChild($$, $2);
                NodeBuilder::addChild($$, $3);
                NodeBuilder::updateNodeLine($$);
             }
             ;

/* 表达式 */
Exp          : Exp ASSIGNOP Exp
             {
                $$ = NodeBuilder::createNonTerminalNode("Exp", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::addChild($$, $2);
                NodeBuilder::addChild($$, $3);
                NodeBuilder::updateNodeLine($$);
             }
             | Exp AND Exp
             {
                $$ = NodeBuilder::createNonTerminalNode("Exp", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::addChild($$, $2);
                NodeBuilder::addChild($$, $3);
                NodeBuilder::updateNodeLine($$);
             }
             | Exp OR Exp
             {
                $$ = NodeBuilder::createNonTerminalNode("Exp", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::addChild($$, $2);
                NodeBuilder::addChild($$, $3);
                NodeBuilder::updateNodeLine($$);
             }
             | Exp RELOP Exp
             {
                $$ = NodeBuilder::createNonTerminalNode("Exp", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::addChild($$, $2);
                NodeBuilder::addChild($$, $3);
                NodeBuilder::updateNodeLine($$);
             }
             | Exp PLUS Exp
             {
                $$ = NodeBuilder::createNonTerminalNode("Exp", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::addChild($$, $2);
                NodeBuilder::addChild($$, $3);
                NodeBuilder::updateNodeLine($$);
             }
             | Exp MINUS Exp
             {
                $$ = NodeBuilder::createNonTerminalNode("Exp", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::addChild($$, $2);
                NodeBuilder::addChild($$, $3);
                NodeBuilder::updateNodeLine($$);
             }
             | Exp STAR Exp
             {
                $$ = NodeBuilder::createNonTerminalNode("Exp", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::addChild($$, $2);
                NodeBuilder::addChild($$, $3);
                NodeBuilder::updateNodeLine($$);
             }
             | Exp DIV Exp
             {
                $$ = NodeBuilder::createNonTerminalNode("Exp", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::addChild($$, $2);
                NodeBuilder::addChild($$, $3);
                NodeBuilder::updateNodeLine($$);
             }
             | LP Exp ErrorRP
             {
                $$ = NodeBuilder::createNonTerminalNode("Exp", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::addChild($$, $2);
                NodeBuilder::addChild($$, $3);
                NodeBuilder::updateNodeLine($$);
             }
             | MINUS Exp
             {
                $$ = NodeBuilder::createNonTerminalNode("Exp", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::addChild($$, $2);
                NodeBuilder::updateNodeLine($$);
             }
             | NOT Exp
             {
                $$ = NodeBuilder::createNonTerminalNode("Exp", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::addChild($$, $2);
                NodeBuilder::updateNodeLine($$);
             }
             | ID LP Args ErrorRP
             {
                $$ = NodeBuilder::createNonTerminalNode("Exp", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::addChild($$, $2);
                NodeBuilder::addChild($$, $3);
                NodeBuilder::addChild($$, $4);
                NodeBuilder::updateNodeLine($$);
             }
             | ID LP ErrorRP
             {
                $$ = NodeBuilder::createNonTerminalNode("Exp", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::addChild($$, $2);
                NodeBuilder::addChild($$, $3);
                NodeBuilder::updateNodeLine($$);
             }
             | Exp LB Exp ErrorRB
             {
                $$ = NodeBuilder::createNonTerminalNode("Exp", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::addChild($$, $2);
                NodeBuilder::addChild($$, $3);
                NodeBuilder::addChild($$, $4);
                NodeBuilder::updateNodeLine($$);
             }
             | Exp DOT ID
             {
                $$ = NodeBuilder::createNonTerminalNode("Exp", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::addChild($$, $2);
                NodeBuilder::addChild($$, $3);
                NodeBuilder::updateNodeLine($$);
             }
             | ID
             {
                $$ = NodeBuilder::createNonTerminalNode("Exp", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::updateNodeLine($$);
             }
             | INT
             {
                $$ = NodeBuilder::createNonTerminalNode("Exp", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::updateNodeLine($$);
             }
             | FLOAT
             {
                $$ = NodeBuilder::createNonTerminalNode("Exp", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::updateNodeLine($$);
             }
             | Exp LB Exp COMMA Exp RB
             {
                analysisSuccessful = false;
                SyntaxErrorHandler::reportError("Unexpected ',' in array indexing, did you mean '][' ?", currentLine);
                
                $$ = NodeBuilder::createNonTerminalNode("Exp", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::addChild($$, $2);
                NodeBuilder::addChild($$, $3);
                NodeBuilder::updateNodeLine($$);
             }
             ;

Args         : Exp COMMA Args
             {
                $$ = NodeBuilder::createNonTerminalNode("Args", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::addChild($$, $2);
                NodeBuilder::addChild($$, $3);
                NodeBuilder::updateNodeLine($$);
             }
             | Exp
             {
                $$ = NodeBuilder::createNonTerminalNode("Args", currentLine);
                NodeBuilder::addChild($$, $1);
                NodeBuilder::updateNodeLine($$);
             }
             ;

%%

void yyerror(const char* msg) {
    // 由SyntaxErrorHandler处理具体错误报告
    analysisSuccessful = false;
    SyntaxErrorHandler::reportError(msg, currentLine);
}