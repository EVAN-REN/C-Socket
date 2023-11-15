
cpp_srcs := $(shell find src -name *.cpp)
cpp_objs := $(patsubst src/%.cpp,objs/%.o,$(cpp_srcs))

#头文件目录
include_paths := /Users/ren/Documents/GitHub/C-Socket/c_socket_practice/mf2/include

#编译头文件
I_flags := $(include_paths:%=-I%)

#加入编译选项
compile_options := -g -O3 -w $(I_flags)

#编译文件和头文件
objs/%.o : src/%.cpp
	@mkdir -p $(dir $@)
	@g++ -c $^ -o $@ $(compile_options)

workspace/exec : $(cpp_objs)
	@mkdir -p $(dir $@)
	@g++ $^ -o $@

run : workspace/exec
	@./$<

debug:
	@echo $(I_flags)
	@echo $(cpp_srcs)
	@echo $(cpp_objs)

clean : 
	@rm -rf objs workspace/exec

.PHOHY : run debug