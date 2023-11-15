
cpp_srcs := $(shell find src -name *.cpp)
cpp_i := $(patsubst src/%.cpp,src/%.i,$(cpp_srcs))
cpp_s := $(patsubst src/%.cpp,src/%.s,$(cpp_srcs))
cpp_objs := $(patsubst src/%.cpp,objs/%.o,$(cpp_srcs))

src/%.i : src/%.cpp
	@g++ -E $< -o $@

src/%.s : src/%.cpp
	@g++ -S $< -o $@

objs/%.o : src/%.cpp
	@mkdir -p $(dir $@)
	@g++ -c $< -o $@

preprocess : $(cpp_i)

assemble : $(cpp_s)

objects : $(cpp_objs)

workspace/exec : $(cpp_objs)
	@mkdir -p $(dir $@)
	@g++ $^ -o $@

run : workspace/exec
	@./$<

debug:
	@echo $(cpp_i)

clean : 
	@rm -rf src/*.i src/*.s objs 

.PHONY: debug preprocess assemble objects