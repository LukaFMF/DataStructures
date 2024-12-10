std = -std=c99
wrn = -Wall -Wextra -pedantic
opt = -O0

build: bin/dyn_array_demo.exe

# compilation
bin/dyn_array_demo.exe: obj/dyn_array_demo.o | bin/ obj/
	gcc $(std) $(wrn) $(opt) -o bin/dyn_array_demo.exe obj/dyn_array_demo.o 

obj/dyn_array_demo.o: dyn_array_demo.c dyn_array.h | obj/
	gcc $(std) $(wrn) $(opt) -o obj/dyn_array_demo.o -c dyn_array_demo.c 

# folders
bin/:
	mkdir -p bin/

obj/:
	mkdir -p obj/

.PHONY: clean

clean: 
	rm -rf obj/
	rm -rf bin/