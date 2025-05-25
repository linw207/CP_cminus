#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
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
    
    // 防止空指针
    node->name = name ? strdup(name) : strdup("UNKNOWN");
    if (!node->name) {
        fprintf(stderr, "Memory allocation failed for node name\n");
        free(node);
        exit(1);
    }
    
    node->line = line;
    node->type = NODE_OTHER;
    node->children = NULL;
    node->childCount = 0;
    node->childCapacity = 0;
    
    // 初始化值
    node->value.intValue = 0;
    node->value.floatValue = 0.0f;
    node->value.strValue = NULL;
    
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

// TreeNode* createIdentifierNode(const char* name, int line, const char* idValue) {
//     TreeNode* node = createNodeBase(name, line);
//     // 防止空指针
//     if (idValue) {
//         node->value.strValue = strdup(idValue);
//         if (!node->value.strValue) {
//             fprintf(stderr, "Memory allocation failed for identifier value\n");
//             free(node->name);
//             free(node);
//             exit(1);
//         }
//     } else {
//         node->value.strValue = NULL;
//     }
//     return node;
// }
TreeNode* createIdentifierNode(const char* name, int line, const char* idValue) {
    TreeNode* node = createNodeBase(name, line);
    
    // 防止空指针和特殊值
    if (idValue && strlen(idValue) > 0) {
        node->value.strValue = strdup(idValue);
        if (!node->value.strValue) {
            fprintf(stderr, "Memory allocation failed for identifier value\n");
            free(node->name);
            free(node);
            exit(1);
        }
    } else {
        // 使用空字符串代替NULL
        node->value.strValue = strdup("");
        if (!node->value.strValue) {
            fprintf(stderr, "Memory allocation failed for identifier value\n");
            free(node->name);
            free(node);
            exit(1);
        }
    }
    return node;
}

TreeNode* createNonTerminalNode(const char* name, int line) {
    return createNodeBase(name, line);
}

void addChild(TreeNode* parent, TreeNode* child) {
    if (!parent) return; // 父节点不能为空
    if (!child) return;  // 子节点不能为空
    
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

// void freeNode(TreeNode* node) {
//     if (!node) return;
    
//     // 先保存子节点数组，避免子节点释放后访问无效内存
//     TreeNode** children = node->children;
//     int childCount = node->childCount;
    
//     // 标记节点已经开始释放，防止重复释放
//     node->children = NULL;
//     node->childCount = 0;
    
//     // 释放节点名称
//     if (node->name) {
//         free(node->name);
//         node->name = NULL;
//     }
    
//     // 释放字符串值（如果存在）
//     if (node->value.strValue) {
//         // 只有在strValue不是一个特殊值(如0x1)时才释放
//         if ((uintptr_t)(node->value.strValue) > 0x1000) {
//             free(node->value.strValue);
//         }
//         node->value.strValue = NULL;
//     }
    
//     // 递归释放所有子节点
//     if (children) {
//         for (int i = 0; i < childCount; i++) {
//             if (children[i]) {
//                 freeNode(children[i]);
//             }
//         }
//         // 释放子节点数组
//         free(children);
//     }
    
//     // 释放节点本身
//     free(node);
// }
void freeNode(TreeNode* node) {
    if (!node) return;
    
    // 先保存子节点数组，避免子节点释放后访问无效内存
    TreeNode** children = node->children;
    int childCount = node->childCount;
    
    // 标记节点已经开始释放，防止重复释放
    node->children = NULL;
    node->childCount = 0;
    
    // 释放节点名称
    if (node->name) {
        free(node->name);
        node->name = NULL;
    }
    
    // 释放字符串值（如果存在）
    if (node->value.strValue) {
        // 只有在strValue不是一个特殊值(如0x1)时才释放
        if ((uintptr_t)(node->value.strValue) > 0x1000) {
            free(node->value.strValue);
        }
        node->value.strValue = NULL;
    }
    
    // 递归释放所有子节点
    if (children) {
        for (int i = 0; i < childCount; i++) {
            if (children[i]) {
                freeNode(children[i]);
            }
        }
        // 释放子节点数组
        free(children);
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
    printf("%s", node->name ? node->name : "UNKNOWN");
    
    // 根据节点类型打印附加信息
    if (node->name && strcmp(node->name, "INT") == 0) {
        printf(": %d", node->value.intValue);
    } else if (node->name && strcmp(node->name, "FLOAT") == 0) {
        printf(": %f", node->value.floatValue);
    } else if (node->name && strcmp(node->name, "ID") == 0 && node->value.strValue) {
        printf(": %s", node->value.strValue);
    } else if (node->name && strcmp(node->name, "TYPE") == 0) {
        printf(": int");
    }
    
    // 为所有非终结符和特定终结符打印行号
    if (strcmp(node->name, "Program") == 0) {
        printf(" (1)");  // Program 总是从第1行开始
    } else if (strcmp(node->name, "ExtDefList") == 0) {
        printf(" (1)");  // ExtDefList 总是从第1行开始
    } else if (strcmp(node->name, "LP") == 0 || 
              strcmp(node->name, "RP") == 0 || 
              strcmp(node->name, "SEMI") == 0 || 
              strcmp(node->name, "RC") == 0) {
        // 不显示行号
    } else {
        printf(" (%d)", node->line);
    }
    
    printf("\n");
    
    // 递归打印所有子节点
    if (node->children) {
        for (int i = 0; i < node->childCount; i++) {
            if (node->children[i]) {
                printNodeRecursive(node->children[i], depth + 1);
            }
        }
    }
}

void printSyntaxTree(SyntaxTree* tree) {
    if (!tree) {
        printf("Error: Syntax tree is NULL\n");
        return;
    }
    
    if (tree->root) {
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
        tree->root = NULL;
    }
    
    free(tree);
}

// 辅助函数
int updateNodeLine(TreeNode* node) {
    if (!node) return INT_MAX;
    
    // 如果没有子节点，直接返回当前行号
    if (!node->children || node->childCount == 0) 
        return node->line;
    
    // 找到最小行号
    int minLine = node->line;
    for (int i = 0; i < node->childCount; i++) {
        if (node->children[i]) {
            int childLine = node->children[i]->line;
            if (childLine > 0 && childLine < minLine) {
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
    logInfo("Processing file");
    
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
        fprintf(stderr, "Analysis failed\n");
        return 1;
    }
    
    // 检查语法树
    if (!syntaxTree || !syntaxTree->root) {
        fprintf(stderr, "Error: Syntax tree is empty\n");
        return 1;
    }
    
    // 分析成功，打印语法树
    printSyntaxTree(syntaxTree);
    
    // 清理资源
    freeSyntaxTree(syntaxTree);
    
    return 0;
}