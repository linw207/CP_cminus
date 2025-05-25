# 编译器和编译选项
CC = gcc
CFLAGS = -std=gnu99 -Wall -I. -g

# 目标和依赖
TARGET = cminus_lwy
SRCS = main.c
OBJS = lex.yy.o cminus_lwy.tab.o $(SRCS:.c=.o)

# 默认目标
all: $(TARGET)

# 构建可执行文件
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# 生成词法分析器
lex.yy.c: cminus_lwy.l cminus_lwy.tab.h
	flex cminus_lwy.l

# 生成语法分析器
cminus_lwy.tab.c cminus_lwy.tab.h: cminus_lwy.y
	bison -d cminus_lwy.y

# 编译C源文件
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 编译从Flex和Bison生成的C文件
lex.yy.o: lex.yy.c
	$(CC) $(CFLAGS) -c $< -o $@

cminus_lwy.tab.o: cminus_lwy.tab.c
	$(CC) $(CFLAGS) -c $< -o $@

# 定义伪目标
.PHONY: clean debugbuild run

# 调试构建
debugbuild: CFLAGS += -DDEBUG_MODE
debugbuild: clean all

# 运行项目
run: $(TARGET)
	./$(TARGET) $(FILE)

# 清理构建产物
clean:
	rm -f $(TARGET) $(OBJS) lex.yy.c cminus_lwy.tab.c cminus_lwy.tab.h *.o