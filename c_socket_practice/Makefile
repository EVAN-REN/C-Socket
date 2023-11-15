#
# 'make'        build executable file 'main'
# 'make clean'  removes all .o and executable files
#

# define the Cpp compiler to use
CXX = g++

# define any compile-time flags
CXXFLAGS	:= -std=c++17 -Wall -Wextra -g

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS =

# define output directory
OUTPUT	:= output

# define source directory
SRC		:= src

# define include directory
INCLUDE	:= include

# define lib directory
LIB		:= lib

ifeq ($(OS),Windows_NT)
MAIN	:= main.exe
SOURCEDIRS	:= $(SRC)
INCLUDEDIRS	:= $(INCLUDE)
LIBDIRS		:= $(LIB)
FIXPATH = $(subst /,\,$1)
RM			:= del /q /f
MD	:= mkdir
else
MAIN	:= main
SOURCEDIRS	:= $(shell find $(SRC) -type d)
INCLUDEDIRS	:= $(shell find $(INCLUDE) -type d)
LIBDIRS		:= $(shell find $(LIB) -type d)
FIXPATH = $1
RM = rm -f
MD	:= mkdir -p
endif

# define any directories containing header files other than /usr/include
INCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))

# define the C libs
LIBS		:= $(patsubst %,-L%, $(LIBDIRS:%/=%))

# define the C source files
SOURCES		:= $(wildcard $(patsubst %,%/*.cpp, $(SOURCEDIRS)))

# define the C object files
OBJECTS		:= $(SOURCES:.cpp=.o)

# define the dependency output files
DEPS		:= $(OBJECTS:.o=.d)

#
# The following part of the makefile is generic; it can be used to
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

OUTPUTMAIN	:= $(call FIXPATH,$(OUTPUT)/$(MAIN))

all: $(OUTPUT) $(MAIN)
	@echo Executing 'all' complete!

$(OUTPUT):
	$(MD) $(OUTPUT)

$(MAIN): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(OUTPUTMAIN) $(OBJECTS) $(LFLAGS) $(LIBS)

# include all .d files
-include $(DEPS)

# this is a suffix replacement rule for building .o's and .d's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file)
# -MMD generates dependency output files same name as the .o file
# (see the gnu make manual section about automatic variables)
.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -MMD $<  -o $@

.PHONY: clean
clean:
	$(RM) $(OUTPUTMAIN)
	$(RM) $(call FIXPATH,$(OBJECTS))
	$(RM) $(call FIXPATH,$(DEPS))
	@echo Cleanup complete!

run: all
	./$(OUTPUTMAIN)
	@echo Executing 'run: all' complete!


################################################################
# preprocessing - generating assembly language - source file to object file - single source to executable - 装入（将指令装入内存运行）
# .c - .i - .s - .o
# g++ -E / g++ -S /g++ -c
# 静态库（链接时将其他库全部加载一起）：ar -r libxxx.a / g++ .c .a -o xxx 
# 动态库（在装入或运行时加载）：g++ -c -fpic / g++ -shared / g++ .c -o xxx -lxxx -Lxxxx
# 静态链接/装载时动态链接/运行时动态链接
# 绝对装入/可重定位装入/动态运行时装入

# 在terminal对应makefile目录下输入make+target
# make指令会在当前目录下寻找makefile或Makefile文件，并执行对应target，若没有加target默认执行文件里第一个target，若有依赖迭代找最内层target
# echo是Linux打印命令
# 默认还会打印出命令本身，在命令前加上@就可以取消打印
debug :
	@echo $(cpp)
	@echo $(obj)

#定义变量：:=变量的值立即展开，单纯的将字符串赋值过去
# = 变量的值是延迟展开
# ?= 默认赋值运算符，若变量定义则不进行操作，否则赋值
# += 等于在后面继续加入值（然后等于重新赋值）
# \ 是续行符，可以允许换行写
cpp := src/main.cpp
obj := output/main.o
HOST_ARCH = arrch64
HOST_ARCH ?= amd64
HOST_ARCH += $(cpp)
HOST_ARCH := aaaa \
			ccccc

#变量引用：$()/${}
# $@：目标target的完整名称
# $<：第一个依赖文件的名称
# $^：所有依赖文件，以空格分来，不包含重复依赖文件
# obj依赖于cpp
$(obj) : $(cpp)
	@g++ -c $(cpp) -o $(obj)
#	@g++ -c $< -o $@
#	@g++ -c $^ -o $@


#compile依赖于obj
compile : $(obj)

clean:
	@rm -rf output

#makefile function
# 函数调用 $(fn, arguments) or ${fn, arguments}
# shell命令函数：$(shell <command> <arguments>)
# shell find xxx -name *.cpp 表示查找xxx目录下名字以.cpp结尾的文件 
cpp_srcs := $(shell find ./src -name *.cpp)

# subst命令函数将text中的from字符串替换为to：$(subst <from>,<to>,<text>)
cpp_objs := $(subst src/,output/,$(cpp_srcs))
cpp_objs := $(subst .cpp,.o,$(cpp_objs))

# patsubst是按格式替换函数，通配符%表示任意长度的字串，从text中提取pattern并替换为replacement：$(patsubst <pattern>,<replacement>,<text>)
cpp_objsp := $(patsubst src/%.cpp,output/%.o,$(cpp_srcs))

#foreach循环函数，把字串<list>中的元素逐个取出来，执行<text>包含的表达式：$(foreach <var>,<list>,<text>)
include_path := /user/include \
				/user/include/opencv2
include_path := $(foreach item,$(include_path),-I$(item))
# I_flag := $(include_path:%=-I%) 同等于上面效果 

# 编译所有src下文件到ouput，这里还自动创建output文件夹
# dir去目录函数，取回最后/之前的所有文件目录：$(dir <names..>)
output/%.o : src/%.cpp
	@mkdir -p $(dir $@)
	@g++ -c $^ -o $@

compile2 : $(cpp_objs)

#处理静态库动态库
# $(notdir <names..>)去掉路径只保留文件
libs := $(notdir $(shell find /user/lib -name lib*))

# $(filter <pattern>,<names..>)过滤
# $(basename <names..>)去掉后缀
a_libs := $(subst lib,,$(basename $(filter %.a,$(libs))))
so_libs := $(subst lib,,$(basename $(filter %.so,$(libs))))




test :
	@echo $(cpp_srcs)
	@echo $(cpp_objs)
	@echo $(cpp_objsp)

# 若出现与target重名的文件，需要将target名字加入到.PHONY中
.PHONY : debug clean test

#编译选项
# -m64 指定编译为64位应用程序
# -std= 指定编译标准，如c++11
# -g 包含调试信息
# -w 不显示警告
# -O 优化等级，通常是-O3
# -I 加在头文件路径前
# fPIC 产生的没有绝对地址，全是相对地址

#链接选项
# -l 加在库名前面
# -L 加载库路径前面
# -wl,<选项> 将逗号分隔的<选项>传递给链接器
# -rpath= 运行时候，去找目录，运行的时候，要找.so文件，会从这个选项里指定的地方去找

