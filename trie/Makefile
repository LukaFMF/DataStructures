std = -std=c99
wrn = -Wall -Wextra -pedantic
opt = -O0

# example texts
texts = $(notdir $(wildcard example_texts/*.txt))
bin_texts = $(addprefix bin/,$(texts))

build: bin/trie_demo.exe $(bin_texts)

# compilation
bin/trie_demo.exe: obj/trie_demo.o | bin/ obj/
	gcc $(std) $(wrn) $(opt) -o bin/trie_demo.exe obj/trie_demo.o 

obj/trie_demo.o: trie_demo.c trie.h | obj/
	gcc $(std) $(wrn) $(opt) -o obj/trie_demo.o -c trie_demo.c

# copy example texts
define cp-text =
bin/$(1): example_texts/$(1) | bin/
	cp example_texts/$(1) bin/$(1)
endef 

# generate rules to copy each individual file, 
# if it changes or it's missing
$(foreach file,$(texts),$(eval $(call cp-text,$(file))))

# folders
bin/:
	mkdir -p bin/

obj/:
	mkdir -p obj/

.PHONY: clean

clean: 
	rm -rf obj/
	rm -rf bin/