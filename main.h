#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// 节点类型枚举
typedef enum {
    NODE_OTHER,
    NODE_INT_TYPE,
    NODE_FLOAT_TYPE
} NodeType;

// 前置声明树节点结构
struct TreeNode;

// 树节点结构定义
typedef struct TreeNode {
    char* name;          // 节点名称
    int line;            // 行号
    NodeType type;       // 节点类型
    
    // 节点值（联合体）
    union {
        int intValue;        // 整型值
        float floatValue;    // 浮点值
        char* strValue;      // 字符串值（用于标识符）
    } value;
    
    // 子节点
    struct TreeNode** children;  // 子节点数组
    int childCount;              // 子节点数量
    int childCapacity;           // 子节点数组容量
} TreeNode;

// 语法树结构
typedef struct {
    TreeNode* root;  // 根节点
} SyntaxTree;

// 树节点函数声明
TreeNode* createTokenNode(const char* name, int line, NodeType type);
TreeNode* createIntValueNode(const char* name, int line, int value);
TreeNode* createFloatValueNode(const char* name, int line, float value);
TreeNode* createIdentifierNode(const char* name, int line, const char* idValue);
TreeNode* createNonTerminalNode(const char* name, int line);
void addChild(TreeNode* parent, TreeNode* child);
void freeNode(TreeNode* node);

// 语法树函数声明
SyntaxTree* createSyntaxTree();
void setSyntaxTreeRoot(SyntaxTree* tree, TreeNode* node);
void printSyntaxTree(SyntaxTree* tree);
void freeSyntaxTree(SyntaxTree* tree);

// 外部定义引用
extern FILE* yyin;
extern int yyparse();
extern SyntaxTree* syntaxTree;
extern int analysisSuccessful;

#endif /* MAIN_H */