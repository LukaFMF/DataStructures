std = -std=c99
wrn = -Wall -Wextra -pedantic
opt = -O0

build: bin/priority_queue_demo.exe

# compilation
bin/priority_queue_demo.exe: obj/priority_queue_demo.o | bin/ obj/
	gcc $(std) $(wrn) $(opt) -o bin/priority_queue_demo.exe obj/priority_queue_demo.o 

obj/priority_queue_demo.o: priority_queue_demo.c priority_queue.h | obj/
	gcc $(std) $(wrn) $(opt) -o obj/priority_queue_demo.o -c priority_queue_demo.c 

# folders
bin/:
	mkdir -p bin/

obj/:
	mkdir -p obj/

.PHONY: clean

clean: 
	rm -rf obj/
	rm -rf bin/