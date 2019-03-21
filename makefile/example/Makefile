
# 输出标目名称
BINNAME = test 

# 配置工具链 CC
#CC = gcc
CC = g++

# 配置编译选项
CC_OPTS := -Wall -Werror

# 配置链接选项
LD_OPTS :=

INC_DIR := ./src/inc

CC_OPTS += -I$(INC_DIR)

SRC_DIR := ./src
SRC_DIR += ./src/src

VPATH = $(SRC_DIR)

SRC = $(shell find $(SRC_DIR) -maxdepth 1 -name '*.cpp')

OBJ_0  = $(notdir $(patsubst %.cpp, %.o, $(SRC)))
OBJ    = $(foreach file, $(OBJ_0), $(OBJDIR)/$(file))

OBJDIR = ./obj

.PHONY: all

all: setup bin

setup:
	@echo $(SRC)
	@echo $(OBJ_0)
	@echo $(OBJ)
	mkdir -p $(OBJDIR)

bin: $(OBJ)
	$(CC) $(OBJ) $(CC_OPTS) -o $(BINNAME)

$(OBJ): $(OBJDIR)/%.o : %.cpp
	$(CC) $(CC_OPTS) -o $@ -c $<


