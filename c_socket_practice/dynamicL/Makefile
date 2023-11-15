
cpp_srcs := $(shell find src -name *.cpp)
cpp_objs := $(patsubst src/%.cpp,objs/%.o,$(cpp_srcs))

so_objs := $(filter-out objs/main.o,$(cpp_objs))

include_dirs := ./include
library_dirs := ./lib

linking_libs := ddd

I_options := $(include_dirs:%=-I%)
l_options := $(linking_libs:%=-l%)
L_options := $(library_dirs:%=-L%)
#指代-Wl -rpath=[库路径]，mac可以不加rpath来搜索路径
r_options := $(library_dirs:%=-Wl,-rpath=%)

#动态编译要加入-fPIC
compile_options := -g -O3 -w -fPIC $(I_options)
linking_options := $(l_options) $(L_options)

objs/%.o : src/%.cpp
	@mkdir -p $(dir $@)
	@g++ -c $^ -o $@ $(compile_options)

compile : $(cpp_objs)

#编译动态库
lib/libddd.so : $(so_objs)
	@mkdir -p $(dir $@)
	@g++ -shared $^ -o $@

dynamic : lib/libddd.so

#链接动态库
#加入compile和dynamic可以一步运行
workspace/exec : objs/main.o compile dynamic
	@mkdir -p $(dir $@)
	@g++ $< -o $@ $(linking_options)

run : workspace/exec
	@./$<

clean :
	@rm -rf objs lib workspace/exec

debug :
	@echo $(cpp_srcs)
	@echo $(cpp_objs)
	@echo $(so_objs)

.PHONY : debug clean dynamic