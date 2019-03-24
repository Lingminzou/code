### 一个Makefile示例

作为一个普通的搬砖码农来说，敲 make 的次数多，写 makefile 的机会却比较少，但掌握它是十分有必要的，毕竟读和改 makefile 的时候还是很多的嘛，特别是对于一个经常使用 c/c++ 的码农来说。

网上有一份关于 makefile 很好的资料叫做 《跟我一起写Makefile》，每每遇到不懂的地方我都会在里面找答案，非常的不错，需要的请到如下网盘路径下载：

	链接：https://pan.baidu.com/s/1OT-Hk3bzo070hjuWo39ASg
	提取码：sjfy

资料的内容还是比较多的，对于新手来说非常有必要通读，但读完以后要自己来写一个的时候通常也是一头雾水，不知如何下手，本文则展示一个 makefile 示例，帮助大家运用和理解它，也可把它作为构建一个应用的 makfile 模板。

开始之前还是选简单说下 makefile，它是由一系列规则组成的文件，一条基本的规则结构如下：

	<target> : <prerequisites> 
	[tab]  <commands>

即 target 依赖于 prerequisites，那怎么由 prerequisites 生成 target 的，那就定义在 commands，那何时会更新 target 呢，则只要 prerequisites 最后一次更新的时间早已 target，则 target 会发生更新，即 commands 会执行。

现假设我们有如下一个工程目录，需要我们使用 makefile 来构建出 bin 档，那我们应该做呢？

	.
	├── Makefile
	├── README.md
	└── src
		├── inc
		│   ├── test01.h
		│   └── test02.h
		├── main.cpp
		├── src
		│   └── test02.cpp
		└── test01.cpp

首先如果我们只需要构建 main.cpp 一个文件的时候我们可以这么做

	g++ main.cpp -o main

这里其实是一步到位，把编译和链接放到了一起，直接生产 bin 档 main

通常的做法是我们先把源文件先编译成 .o 文件，然后再一起链接成 bin 档，如下：

	g++ -o main.o -c main.cpp

	g++ main.o -o main

这是为什么呢？这是因为一步到位的做法，当源文件数量很多的时候非常的慢，它每次都要对所有文件进行编译，先编译生产中间文件的好处在于在一次全编译后，如果后续只更改一个文件的话，编译过程只会只编译更新过的文件，然后再一起链接输出可执行文件，速度比较快。

在编译链接过程有时往往还需要加入各种参数，如下两个常用的编译参数，则告诉编译器打开所有警告并遇到警告的地方也发出错误，这是十分好的习惯。

	-Wall -Werror

除了编译选项，我们有时还会有链接选项，如下常用的指定链接线程库动态库

	-lpthread

以上介绍的则是我们即将要用的 commands 啦，即怎么编译输出某文件，怎么链接生成某文件。

好的，那么我们再来理清楚一下我们的目标和依赖。

首先我们有一个终极目标就是生成可执行 bin 档，它依赖于源文件对应的 .o 文件，我们输入 .o 文件通过链接命令生成可执行文件，则这条规则可以这么写（伪代码）：

	可执行文件：所有源文件编译生成的 .o 文件
		一条链接命令，输入是所有 .o 文件，输出是可执行文件

那所有源文件编译生成的 .o 文件怎么生成呢，我们再写一条规则如下（伪代码）：

	所有源文件编译生成的 .o 文件：所有源文件
		一条编译命令，输入是源文件，输出是 .o 文件

那如果对于只有一个源文件的情况这个 makefile 文件就可以这么写了：

	main:main.o
		g++ main.o -o main

	main.o:main.cpp
		g++ -o main.o -c main.cpp

对于如上我们给出的工程目录实例存在多个源文件还遍布在不同的目录下，那我们应该怎么办呢？

那这里需要再介绍一个 makefile 的知识，模式规则。

模式规则是用于说明生一类文件的另一类文件是什么，和是怎么生成的。假设我们要说明 .o 文件是由 .cpp 文件生成的，那么我们可以这么写：

	%.o:%.cpp
		g++ -o $@ -c $<

假设我们要生产 a.o b.o c.o 那它就会知道我们需要 a.cpp b.cpp c.cpp，其中 $@ 和 $< 是两个自动化变量。

其中 $@ 表示目标文件集，$< 表示这一模式规则中所有符合的文件，注意这里多是一一取出的。

了解了这些后，我们基本就能写出适用我们示例工程的 makefile 了。

首先第一件事情我们要先写出两个目标，终极目标好办，我们把它叫做 bin，则它依赖所有的 .o 文件，我们把所有 .o 文件存在一个变量 $(OBJ) 中的话，那么我们的第一条规则就是这么样的：

	bin: $(OBJ)
		g++ $(OBJ) -o bin

那我们所有的 .o 文件怎么生成呢，按上面的写出由所有 .cpp 文件生成所有 .o 文件的规则如下：


	$(OBJ): %.o : %.cpp
		g++ -o $@ -c $<

那这里 $(OBJ) 还是一个变量呢，我们应该对它进行赋值，我们可以这样做，如下：
	
	# 找到所有源文件
	SRC = $(shell find ./src -name '*.cpp')

	# 把所有源文件名字的 cpp 换成 o，同时去掉前面的路径，就得到所有 .o 文件了
	OBJ  = $(notdir $(patsubst %.cpp, %.o, $(SRC)))

那这里还有最后一个问题是 make 过程中它怎么找到所有 cpp 文件呢？这里就还需要介绍 makefile 下的另一个变量了叫 VPATH，它指明了依赖文件的搜索路径，所以我们要指定它，如下：

	VPATH = ./src ./src/src

注意它是要指定到每一级路径的。

那到这里关于怎么写用于构建这个示例工程的 makefile 文件，基本就完成了，剩下的就是把他们组织起来即可了。

下面是一个完整的组织起来后的示例，里面也有详细的注释，可以参考，

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

感觉写的不是不是特别好，希望解释清楚了，怎么从零开始生产这样一个示例工程的 makefile 文件。欢迎提出你的建议或疑问，谢谢大家阅读。

扫码关注我了解更多有趣编程实例

![](http://wx1.sinaimg.cn/large/9e169b75gy1fqcisgsbd7j2076076q3e.jpg)

