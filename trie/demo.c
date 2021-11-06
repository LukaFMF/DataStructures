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

	u32 linecount = 0;
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
			case '\r':
			case '\"':
			{
				if(curr_char == '\n' || curr_char == '\r')
					linecount++;
				file_contents[i] = '\0';
				if(verify_word(str_start))
				{
					if(strcmp(str_start,"ed") == 0)
					 	printf("%d",linecount);
					//printf("%s -- ",str_start);
					trie_insert(t,str_start);
					//printf("%s\n",str_start);
				}
				str_start = file_contents + i + 1;
				break;
			}
		}
		if(linecount == 10702)
			printf("%c",curr_char);
		// convert to lowercase
		if(curr_char >= 'A' && curr_char <= 'Z')
			file_contents[i] += 32;
	}
	free(file_contents);
}

i32 main(void)
{
	FILE *file = fopen("TheSorcerersStone.txt","rw");

	char curr;
	while((curr = fgetc(file)) != EOF)
	{
		if(curr == '\r')
		{
			fseek(file,SEEK_CUR,-1);
			fwrite("\r",1,1,file);
			printf("replaced!\n");
		}
	}
	fclose(file);

	trie t;

	trie_init(&t);

	fill_trie(&t,"TheSorcerersStone.txt");
	trie_write(&t,"TheSorcerersStoneWords.txt");
	//fill_trie(&t,"TheHungerGames.txt");
	//trie_write(&t,"TheHungerGamesWords.txt");

	trie_cleanup(&t);
	printf("good");
	
	return 0;
}