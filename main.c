#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

// 全局变量
SyntaxTree* syntaxTree = NULL;
int analysisSuccessful = 1;  // 使用int代替bool，1为真，0为假

// 日志记录函数
void logDebug(const char* message) {
    #ifdef DEBUG_MODE
    fprintf(stderr, "[DEBUG] %s\n", message);
    #endif
}

void logInfo(const char* message) {
    #ifdef DEBUG_MODE
    fprintf(stderr, "[INFO] %s\n", message);
    #endif
}

void logWarning(const char* message) {
    #ifdef DEBUG_MODE
    fprintf(stderr, "[WARNING] %s\n", message);
    #endif
}

void logError(const char* message) {
    #ifdef DEBUG_MODE
    fprintf(stderr, "[ERROR] %s\n", message);
    #endif
}

// 文件处理函数
FILE* openFile(const char* filename, const char* mode) {
    FILE* file = fopen(filename, mode);
    if (!file) {
        fprintf(stderr, "Cannot open file: %s\n", filename);
    }
    return file;
}

void closeFile(FILE* file) {
    if (file) {
        fclose(file);
    }
}

// 树节点结构实现
TreeNode* createNodeBase(const char* name, int line) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    
    node->name = strdup(name);
    node->line = line;
    node->type = NODE_OTHER;
    node->children = NULL;
    node->childCount = 0;
    node->childCapacity = 0;
    
    return node;
}

TreeNode* createTokenNode(const char* name, int line, NodeType type) {
    TreeNode* node = createNodeBase(name, line);
    node->type = type;
    return node;
}

TreeNode* createIntValueNode(const char* name, int line, int value) {
    TreeNode* node = createNodeBase(name, line);
    node->value.intValue = value;
    return node;
}

TreeNode* createFloatValueNode(const char* name, int line, float value) {
    TreeNode* node = createNodeBase(name, line);
    node->value.floatValue = value;
    return node;
}

TreeNode* createIdentifierNode(const char* name, int line, const char* idValue) {
    TreeNode* node = createNodeBase(name, line);
    node->value.strValue = strdup(idValue);
    return node;
}

TreeNode* createNonTerminalNode(const char* name, int line) {
    return createNodeBase(name, line);
}

void addChild(TreeNode* parent, TreeNode* child) {
    if (!parent || !child) return;
    
    // 需要扩展子节点数组
    if (parent->childCount >= parent->childCapacity) {
        int newCapacity = parent->childCapacity == 0 ? 4 : parent->childCapacity * 2;
        TreeNode** newChildren = (TreeNode**)realloc(parent->children, 
                                               sizeof(TreeNode*) * newCapacity);
        if (!newChildren) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        parent->children = newChildren;
        parent->childCapacity = newCapacity;
    }
    
    parent->children[parent->childCount++] = child;
}

void freeNode(TreeNode* node) {
    if (!node) return;
    
    // 释放节点名称
    free(node->name);
    
    // 释放字符串值（如果是标识符节点）
    if (node->type == NODE_OTHER && node->value.strValue) {
        free(node->value.strValue);
    }
    
    // 递归释放所有子节点
    for (int i = 0; i < node->childCount; i++) {
        freeNode(node->children[i]);
    }
    
    // 释放子节点数组
    if (node->children) {
        free(node->children);
    }
    
    // 释放节点本身
    free(node);
}

// 语法树实现
SyntaxTree* createSyntaxTree() {
    SyntaxTree* tree = (SyntaxTree*)malloc(sizeof(SyntaxTree));
    if (!tree) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    tree->root = NULL;
    return tree;
}

void setSyntaxTreeRoot(SyntaxTree* tree, TreeNode* node) {
    if (tree) {
        tree->root = node;
    }
}

// 递归打印语法树的辅助函数
void printNodeRecursive(TreeNode* node, int depth) {
    if (!node) return;
    
    // 打印缩进
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    
    // 打印节点信息
    printf("%s", node->name);
    
    // 根据节点类型打印附加信息
    if (strcmp(node->name, "INT") == 0) {
        printf(": %d", node->value.intValue);
    } else if (strcmp(node->name, "FLOAT") == 0) {
        printf(": %f", node->value.floatValue);
    } else if (strcmp(node->name, "ID") == 0) {
        printf(": %s", node->value.strValue);
    }
    
    printf(" (line: %d)\n", node->line);
    
    // 递归打印所有子节点
    for (int i = 0; i < node->childCount; i++) {
        printNodeRecursive(node->children[i], depth + 1);
    }
}

void printSyntaxTree(SyntaxTree* tree) {
    if (tree && tree->root) {
        printf("Syntax Tree:\n");
        printNodeRecursive(tree->root, 0);
    } else {
        printf("Empty syntax tree\n");
    }
}

void freeSyntaxTree(SyntaxTree* tree) {
    if (!tree) return;
    
    if (tree->root) {
        freeNode(tree->root);
    }
    
    free(tree);
}

// 辅助函数
int updateNodeLine(TreeNode* node) {
    if (!node) return INT_MAX;
    if (node->childCount == 0) return node->line;
    
    int minLine = node->line;
    for (int i = 0; i < node->childCount; i++) {
        if (node->children[i]) {
            int childLine = node->children[i]->line;
            if (childLine < minLine) {
                minLine = childLine;
            }
        }
    }
    node->line = minLine;
    return minLine;
}

// 程序入口
int main(int argc, char** argv) {
    // 初始化语法树
    syntaxTree = createSyntaxTree();
    
    // 处理命令行参数
    const char* filename;
    if (argc < 2) {
        printf("Usage: ./cminus_lwy <filename>\n");
        return 1;
    }
    
    filename = argv[1];
    
    // 打开输入文件
    yyin = openFile(filename, "r");
    if (!yyin) {
        return 1;
    }
    
    // 执行语法分析
    int parseResult = yyparse();
    closeFile(yyin);
    
    // 检查分析结果
    if (parseResult != 0 || !analysisSuccessful) {
        logError("Analysis failed");
        return 1;
    }
    
    // 分析成功，打印语法树
    logInfo("Analysis successful");
    printSyntaxTree(syntaxTree);
    
    // 清理资源
    freeSyntaxTree(syntaxTree);
    
    return 0;
}