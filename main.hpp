#ifndef _MAIN_HPP_
#define _MAIN_HPP_

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <climits>
#include <algorithm>

// 节点类型枚举
enum class NodeType {
    NON_TERMINAL,  // 非终结符
    INT_TYPE,      // int类型
    FLOAT_TYPE,    // float类型
    ID_VALUE,      // 标识符
    INT_VALUE,     // 整数值
    FLOAT_VALUE,   // 浮点数值
    OTHER          // 其他终结符
};

// 节点值联合体
union NodeValue {
    std::string* idValue;
    int intValue;
    float floatValue;
    
    NodeValue() : idValue(nullptr) {}
    ~NodeValue() {} // 不在此处释放资源，由TreeNode析构函数处理
};

// 语法树节点
class TreeNode {
public:
    NodeType type;
    const char* tokenName;
    int line;
    NodeValue value;
    std::vector<TreeNode*> children;
    
    // 修改构造函数初始化列表，使其与成员声明顺序一致
    TreeNode(NodeType type, int line, const char* name)
        : type(type), tokenName(name), line(line) {}
    
    // 析构函数
    ~TreeNode() {
        // 释放子节点
        for (auto child : children) {
            delete child;
        }
        
        // 释放标识符值
        if (type == NodeType::ID_VALUE && value.idValue) {
            delete value.idValue;
        }
    }
    
    // 添加子节点
    void addChild(TreeNode* child) {
        if (child) {
            children.push_back(child);
            // 更新行号
            if (child->line < line) {
                line = child->line;
            }
        }
    }
    
    // 创建非终结符节点
    static TreeNode* createNonTerminalNode(const char* name, int line) {
        return new TreeNode(NodeType::NON_TERMINAL, line, name);
    }
    
    // 创建标识符节点
    static TreeNode* createIdentifierNode(const char* name, int line, std::string* value) {
        TreeNode* node = new TreeNode(NodeType::ID_VALUE, line, name);
        node->value.idValue = value;
        return node;
    }
    
    // 创建整数值节点
    static TreeNode* createIntValueNode(const char* name, int line, int value) {
        TreeNode* node = new TreeNode(NodeType::INT_VALUE, line, name);
        node->value.intValue = value;
        return node;
    }
    
    // 创建浮点值节点
    static TreeNode* createFloatValueNode(const char* name, int line, float value) {
        TreeNode* node = new TreeNode(NodeType::FLOAT_VALUE, line, name);
        node->value.floatValue = value;
        return node;
    }
    
    // 创建终结符节点
    static TreeNode* createTokenNode(const char* name, int line, NodeType type) {
        return new TreeNode(type, line, name);
    }
};

// 语法树类
class SyntaxTree {
private:
    TreeNode* root;
    
public:
    SyntaxTree() : root(nullptr) {}
    
    ~SyntaxTree() {
        if (root) {
            delete root;
        }
    }
    
    void setRoot(TreeNode* node) {
        root = node;
    }
    
    TreeNode* getRoot() const {
        return root;
    }
    
    // 打印语法树
    void print() const {
        if (root) {
            printNode(root);
        }
    }
    
private:
    // 打印节点
    void printNode(const TreeNode* node, int level = 0) const {
        if (!node) return;
        
        // 缩进
        for (int i = 0; i < level; ++i) {
            std::cout << "  ";
        }
        
        // 打印节点名称
        std::cout << node->tokenName;
        
        // 根据节点类型打印额外信息
        switch (node->type) {
            case NodeType::NON_TERMINAL:
                std::cout << " (" << node->line << ")" << std::endl;
                break;
            case NodeType::ID_VALUE:
                std::cout << ": " << *(node->value.idValue) << std::endl;
                break;
            case NodeType::INT_TYPE:
                std::cout << ": int" << std::endl;
                break;
            case NodeType::FLOAT_TYPE:
                std::cout << ": float" << std::endl;
                break;
            case NodeType::INT_VALUE:
                std::cout << ": " << node->value.intValue << std::endl;
                break;
            case NodeType::FLOAT_VALUE:
                std::cout << ": " << node->value.floatValue << std::endl;
                break;
            case NodeType::OTHER:
                std::cout << std::endl;
                break;
        }
        
        // 递归打印子节点
        for (const auto& child : node->children) {
            printNode(child, level + 1);
        }
    }
};

#endif // _MAIN_HPP_