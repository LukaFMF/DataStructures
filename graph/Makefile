std = -std=c99
wrn = -Wall -Wextra -pedantic
opt = -O0

# example graphs
graphs = $(notdir $(wildcard example_graphs/*.grph))
bin_graphs = $(addprefix bin/,$(graphs))

build: bin/graph_demo.exe $(bin_graphs)

# compilation
bin/graph_demo.exe: obj/graph_demo.o | bin/ obj/
	gcc $(std) $(wrn) $(opt) -o bin/graph_demo.exe obj/graph_demo.o 

obj/graph_demo.o: graph_demo.c graph.h | obj/
	gcc $(std) $(wrn) $(opt) -o obj/graph_demo.o -c graph_demo.c

# copy example graphs
define cp-graph =
bin/$(1): example_graphs/$(1) | bin/
	cp example_graphs/$(1) bin/$(1)
endef 

# generate rules to copy each individual file, 
# if it changes or it's missing
$(foreach file,$(graphs),$(eval $(call cp-graph,$(file))))

# folders
bin/:
	mkdir -p bin/

obj/:
	mkdir -p obj/

.PHONY: clean

clean: 
	rm -rf obj/
	rm -rf bin/