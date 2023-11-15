#编译连接静态库

#filter-out去掉前面的
lib_srcs := $(filter-out src/main.cpp,$(shell find src -name *.cpp))
lib_objs := $(patsubst src/%.cpp,objs/%.o,$(lib_srcs))

include_paths := ./include

library_paths := ./lib

linking_libs := xxx

I_option := $(include_paths:%=-I%)
#静态库名和位置
l_option := $(linking_libs:%=-l%)
L_option := $(library_paths:%=-L%)

compile_flags := -g -O3 -std=c++11 $(I_option)
linking_flags := $(l_option) $(L_option)

objs/%.o : src/%.cpp
	@mkdir -p $(dir $@)
	@g++ -c $^ -o $@ $(compile_flags)

#编译成静态库
lib/libxxx.a : $(lib_objs)
	@mkdir -p $(dir $@)
	@ar -r $@ $^

static_lib : lib/libxxx.a

#链接静态库
objs/main.o : src/main.cpp
	@mkdir -p $(dir $@)
	@g++ -c $^ -o $@ $(compile_flags)

workspace/exec : objs/main.o
	@mkdir -p $(dir $@)
	@g++ $^ -o $@ $(linking_flags)

run : workspace/exec
	@./$<

debug :
	@echo $(lib_srcs)
	@echo $(lib_objs)

clean :
	@rm -rf objs

.PHONY : debug static_lib