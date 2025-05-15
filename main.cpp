#include <iostream>
#include <string>
#include <memory>
#include <cstdio>
#include "main.hpp"

// 外部定义
extern FILE* yyin;
extern int yyparse();
extern std::shared_ptr<SyntaxTree> syntaxTree;
extern bool analysisSuccessful;

// 日志记录类
class Logger {
public:
    enum class Level {
        DEBUG,
        INFO,
        WARNING,
        ERROR
    };
    
    static void log(Level level, const std::string& message) {
        #ifdef DEBUG_MODE
        const char* levelStr;
        switch (level) {
            case Level::DEBUG: levelStr = "DEBUG"; break;
            case Level::INFO: levelStr = "INFO"; break;
            case Level::WARNING: levelStr = "WARNING"; break;
            case Level::ERROR: levelStr = "ERROR"; break;
        }
        std::cerr << "[" << levelStr << "] " << message << std::endl;
        #endif
    }
};

// 文件处理类
class FileProcessor {
public:
    static FILE* openFile(const char* filename, const char* mode) {
        FILE* file = fopen(filename, mode);
        if (!file) {
            std::cerr << "Cannot open file: " << filename << std::endl;
        }
        return file;
    }
    
    static void closeFile(FILE* file) {
        if (file) {
            fclose(file);
        }
    }
};

// 程序入口
int main(int argc, char** argv) {
    // 初始化语法树
    syntaxTree = std::make_shared<SyntaxTree>();
    
    // 处理命令行参数
    const char* filename;
    if (argc < 2) {
        std::cout << "Usage: ./cminus_lwy <filename>" << std::endl;
        return 1;
    }
    
    filename = argv[1];
    Logger::log(Logger::Level::INFO, "Processing file: " + std::string(filename));
    
    // 打开输入文件
    yyin = FileProcessor::openFile(filename, "r");
    if (!yyin) {
        return 1;
    }
    
    // 执行语法分析
    int parseResult = yyparse();
    FileProcessor::closeFile(yyin);
    
    // 检查分析结果
    if (parseResult != 0 || !analysisSuccessful) {
        Logger::log(Logger::Level::ERROR, "Analysis failed");
        return 1;
    }
    
    // 分析成功，打印语法树
    Logger::log(Logger::Level::INFO, "Analysis successful");
    syntaxTree->print();
    
    return 0;
}