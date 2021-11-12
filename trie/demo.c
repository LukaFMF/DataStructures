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
	if(!file)
	{
		printf("File \"%s\" could not be opened. Exiting!\n",filename);
		exit(1);
	}

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

i32 main(void)
{
	trie t;
	trie_init(&t);

	// downloaded from: https://sites.google.com/site/the74thhungergamesbyced/download-the-hunger-games-trilogy-e-book-txt-file
	read_file_into_trie(&t,"TheHungerGames.txt");

	trie_result tr;
	trie_result_init(&tr);

	trie_sort(&t,&tr);
	trie_result_to_file(&tr,"TheHungerGamesWords.txt");

	trie_result_reset(&tr);

	trie_query(&t,&tr,"to"); // all words that begin with "to"
	trie_result_to_file(&tr,"TheHungerGamesWordsStartWithTo.txt");

	trie_result_reset(&tr);

	trie_query(&t,&tr,"bar"); // all words that begin with "bar"
	trie_result_to_file(&tr,"TheHungerGamesWordsStartWithBar.txt");

	trie_result_cleanup(&tr);
	trie_cleanup(&t);

	return 0;
}