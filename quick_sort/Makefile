std = -std=c99
wrn = -Wall -Wextra -pedantic
opt = -O0

build: bin/quick_sort_demo.exe

# compilation
bin/quick_sort_demo.exe: obj/quick_sort_demo.o | bin/ obj/
	gcc $(std) $(wrn) $(opt) -o bin/quick_sort_demo.exe obj/quick_sort_demo.o 

obj/quick_sort_demo.o: quick_sort_demo.c quick_sort.h | obj/
	gcc $(std) $(wrn) $(opt) -o obj/quick_sort_demo.o -c quick_sort_demo.c 

# folders
bin/:
	mkdir -p bin/

obj/:
	mkdir -p obj/

.PHONY: clean

clean: 
	rm -rf obj/
	rm -rf bin/