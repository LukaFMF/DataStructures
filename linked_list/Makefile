std = -std=c99
wrn = -Wall -Wextra -pedantic
opt = -O0

build: bin/linked_list_demo.exe

# compilation
bin/linked_list_demo.exe: obj/linked_list_demo.o | bin/ obj/
	gcc $(std) $(wrn) $(opt) -o bin/linked_list_demo.exe obj/linked_list_demo.o 

obj/linked_list_demo.o: linked_list_demo.c linked_list.h | obj/
	gcc $(std) $(wrn) $(opt) -o obj/linked_list_demo.o -c linked_list_demo.c 

# folders
bin/:
	mkdir -p bin/

obj/:
	mkdir -p obj/

.PHONY: clean

clean: 
	rm -rf obj/
	rm -rf bin/