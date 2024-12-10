std = -std=c99
wrn = -Wall -Wextra -pedantic
opt = -O0

build: bin/queue_demo.exe

# compilation
bin/queue_demo.exe: obj/queue_demo.o | bin/ obj/
	gcc $(std) $(wrn) $(opt) -o bin/queue_demo.exe obj/queue_demo.o 

obj/queue_demo.o: queue_demo.c queue.h | obj/
	gcc $(std) $(wrn) $(opt) -o obj/queue_demo.o -c queue_demo.c 

# folders
bin/:
	mkdir -p bin/

obj/:
	mkdir -p obj/

.PHONY: clean

clean: 
	rm -rf obj/
	rm -rf bin/