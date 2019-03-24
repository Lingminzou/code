
# 输出标目名称
BINNAME = test 

# 设置 .o 文件输出路径
OBJDIR = ./obj

# 配置工具链 CC
CC = g++

# 配置编译选项
CC_OPTS := -Wall -Werror

# 配置链接选项
LD_OPTS :=

# 指定编译时依赖的头文件目录，然后放进编译选项
INC_DIR := ./src/inc

CC_OPTS += -I$(INC_DIR)

# 指出源文件存放路径
SRC_DIR := ./src
SRC_DIR += ./src/src

# 指定依赖文件搜索路径，即我们的源文件路径
VPATH = $(SRC_DIR)

# 找出所有需要编译的 cpp 类型文件，注意 find 默认是会循环找子目录的，
# 由于我们子目录的路径也需要写进 VPATH 所以这里把 find 的查找深度设置为了 1
SRC = $(shell find $(SRC_DIR) -maxdepth 1 -name '*.cpp')

# 生成需要输出的 .o 文件名
OBJ_0  = $(notdir $(patsubst %.cpp, %.o, $(SRC)))

# 加上 .o 文件存放路径前缀
OBJ    = $(foreach file, $(OBJ_0), $(OBJDIR)/$(file))

.PHONY: all setup bin clean

all: setup bin

setup:
	@echo $(SRC)
	@echo $(OBJ_0)
	@echo $(OBJ)
	mkdir -p $(OBJDIR)

bin: $(OBJ)
	$(CC) $(OBJ) $(LD_OPTS) -o $(BINNAME)

$(OBJ): $(OBJDIR)/%.o : %.cpp
	$(CC) $(CC_OPTS) -o $@ -c $<

clean:
	rm -rf $(OBJDIR)
	rm -rf $(BINNAME)

