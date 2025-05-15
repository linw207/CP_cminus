# 编译器和编译选项
CXX = g++
CXXFLAGS = -std=c++11 -Wall -I.

# 目标和依赖
TARGET = cminus_lwy
SRCS = main.cpp
OBJS = lex.yy.o cminus_lwy.tab.o $(SRCS:.cpp=.o)

# 默认目标
all: $(TARGET)

# 构建可执行文件
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# 生成词法分析器
lex.yy.c: cminus_lwy.l cminus_lwy.tab.h
	flex cminus_lwy.l

# 生成语法分析器
cminus_lwy.tab.c cminus_lwy.tab.h: cminus_lwy.y
	bison -d cminus_lwy.y

# 编译C++源文件
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 编译C源文件
lex.yy.o: lex.yy.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

cminus_lwy.tab.o: cminus_lwy.tab.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 定义伪目标
.PHONY: clean debugbuild run

# 调试构建
debugbuild: CXXFLAGS += -DDEBUG_MODE -g
debugbuild: clean all

# 运行项目
run: $(TARGET)
	./$(TARGET) $(FILE)

# 清理构建产物
clean:
	rm -f $(TARGET) $(OBJS) lex.yy.c cminus_lwy.tab.c cminus_lwy.tab.h *.o