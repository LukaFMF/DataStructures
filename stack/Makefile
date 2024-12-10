std = -std=c99
wrn = -Wall -Wextra -pedantic
opt = -O0

build: bin/stack_demo.exe

# compilation
bin/stack_demo.exe: obj/stack_demo.o | bin/ obj/
	gcc $(std) $(wrn) $(opt) -o bin/stack_demo.exe obj/stack_demo.o 

obj/stack_demo.o: stack_demo.c stack.h | obj/
	gcc $(std) $(wrn) $(opt) -o obj/stack_demo.o -c stack_demo.c 

# folders
bin/:
	mkdir -p bin/

obj/:
	mkdir -p obj/

.PHONY: clean

clean: 
	rm -rf obj/
	rm -rf bin/