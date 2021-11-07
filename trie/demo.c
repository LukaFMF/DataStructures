#include <stdio.h>
#include <stdlib.h>
#include "trie.h"


bool verify_word(const char *str)
{
	const u32 len = strlen(str);
	if(len == 0u)
		return false;

	// first character filter
	switch(str[0])
	{
		case '-':
		case '*':
			return false;

	}

	// last character filter
	switch(str[len-1])
	{
		case '-':
		case '*':
			return false;
	}		
	
	// valid word must contain at least one letter
	for(u32 i = 0u;i < len;i++)
		if(str[i] >= 'a' && str[i] <= 'z')
			return true;

	return false;
}

void read_file_into_trie(trie *t,const char *filename)
{
	FILE *file = fopen(filename,"r");
	fseek(file,0u,SEEK_END);
	const u64 file_size = ftell(file);
	rewind(file);

	char *file_contents = malloc(file_size);
	fread(file_contents,file_size,1u,file);
	fclose(file);

	char *str_start = file_contents;
	for(u64 i = 0u;i < file_size;i++)
	{
		const char curr_char = file_contents[i];
		switch(curr_char)
		{
			case ' ':
			case ',':
			case '.':
			case '?':
			case '!':
			case ':':
			case ';':
			case '(':
			case ')':
			case '\n':
			case '\r':
			case '\"':
			{
				file_contents[i] = '\0';
				if(verify_word(str_start))
					trie_insert(t,str_start);

				str_start = file_contents + i + 1;
				break;
			}
		}
		// convert to lowercase
		if(curr_char >= 'A' && curr_char <= 'Z')
			file_contents[i] += 32;
	}
	free(file_contents);
}

void trie_sorted_print(trie_node *curr,char *str,u32 depth)
{
	if(depth > 0)
		str[depth-1] = curr->character;

	if(curr->word_mark)
	{
		str[depth] = '\0';
		printf("%s\n",str);
	}

	for(u32 i = 0u;i < curr->next_nodes.size;i++)
		trie_sorted_print(curr->next_nodes.data[i],str,depth + 1);
}

i32 main(void)
{
	trie t;

	trie_init(&t);

	// downloader from: https://sites.google.com/site/the74thhungergamesbyced/download-the-hunger-games-trilogy-e-book-txt-file
	read_file_into_trie(&t,"TheHungerGames.txt");
	trie_sort_to_file(&t,"TheHungerGamesWords.txt");

	trie_cleanup(&t);

	return 0;
}