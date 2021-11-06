#include <stdio.h>
#include <stdlib.h>
#include "trie.h"


bool verify_word(const char *str)
{
	const u32 len = strlen(str);
	if(len == 0u || str[0] == '-')
		return false;
	
	for(u32 i = 0u;i < len;i++)
		if(str[i] >= 'a' && str[i] <= 'z')
			return true;

	return false;
}

void fill_trie(trie *t,const char *filename)
{
	FILE *file = fopen(filename,"r");
	fseek(file,0u,SEEK_END);
	const u64 file_size = ftell(file);
	rewind(file);

	char *file_contents = malloc(file_size);
	fread(file_contents,file_size,1u,file);
	fclose(file);

	char *str_start = file_contents;
	for(u32 i = 0u;i < file_size;i++)
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
				{
					//printf("%s -- ",str_start);
					trie_insert(t,str_start);
					//printf("%s\n",str_start);
				}
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

	fill_trie(&t,"TheSorcerersStone.txt");
	trie_write(&t,"TheSorcerersStoneWords.txt");

	trie_cleanup(&t);
	
	return 0;
}