#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../utils/types.h"
#include "../dyn_array/dyn_array.h"

// define dynamic array of strings
def_dyn_array(char_ptr,char*)
typedef struct trie_result
{
	bool is_empty; // signals if the trie contains no records of this result type
	dyn_array_char_ptr words; // array of char pointers (strings)
} trie_result;

void trie_result_init(trie_result *tr)
{
	tr->is_empty = true;
	dyn_array_char_ptr_init(&tr->words,0);
}

void trie_result_cleanup(trie_result *tr)
{
	// first we need to free memory occupied by strings in array
	for(u32 i = 0u;i < tr->words.size;i++)
		free(tr->words.data[i]);

	dyn_array_char_ptr_cleanup(&tr->words);
}

void trie_result_reset(trie_result *tr)
{
	trie_result_cleanup(tr);
	trie_result_init(tr);
}

// writes trie result into a file, each line contains one word
void trie_result_to_file(trie_result *tr,const char *filename)
{
	if(tr->is_empty)
	{
		printf("Write attempt of empty trie_result to file \"%s\". No file will be created!\n",filename);
		return;
	}

	FILE *file = fopen(filename,"w");
	if(!file)
	{
		printf("Attempted write to file \"%s\", because it could not be opened."
		" Exiting!\n",filename);
		exit(1);
	}

	for(u32 i = 0u;i < tr->words.size;i++)
		fprintf(file,"%s\n",tr->words.data[i]);

	fclose(file);
}


// forward declaration for trie node
typedef struct trie_node trie_node;

// definition for all the generic dyn_array things
def_dyn_array(t_node_ptr,trie_node*)
typedef struct trie_node
{
	char character;
	bool word_mark;
	dyn_array_t_node_ptr next_nodes; // array of pointers to next nodes
} trie_node;

typedef struct trie
{
	u32 size;
	u32 max_str_len;
	trie_node *empty_str;
} trie;

void trie_init(trie *t)
{
	t->size = 0u;
	t->max_str_len = 0u; 
	t->empty_str = malloc(sizeof(trie_node));
	t->empty_str->character = '\0';
	t->empty_str->word_mark = false;
	dyn_array_t_node_ptr_init(&t->empty_str->next_nodes,0);
}

void trie_insert(trie *t,const char *str)
{
	trie_node *curr_node = t->empty_str;

	u32 curr_depth = 0u;
	for(u32 i = 0u;i < strlen(str);i++)
	{
		u32 insert_inx;
		bool found = false;
		const char curr_char = str[i];
		for(insert_inx = 0u;insert_inx < curr_node->next_nodes.size;insert_inx++)
		{
			const char possible_next_char = curr_node->next_nodes.data[insert_inx]->character;
			if(curr_char == possible_next_char)
			{
				found = true;
				break;
			}
			else if(curr_char < possible_next_char)
				break;
		}

		// if character has no barnch yet we create it
		if(!found)
		{
			trie_node *new = malloc(sizeof(trie_node));
			new->character = curr_char;
			new->word_mark = false;
			dyn_array_t_node_ptr_init(&new->next_nodes,0);

			dyn_array_t_node_ptr_insert(&curr_node->next_nodes,insert_inx,new);
		}
		curr_node = curr_node->next_nodes.data[insert_inx];
		curr_depth++;
	}

	// we should only increment size, if the word is not yet contained  
	if(!curr_node->word_mark)
	{
		curr_node->word_mark = true;
		t->size++;
	}

	if(curr_depth > t->max_str_len)
		t->max_str_len = curr_depth;
}

void trie_sort_rec(trie_node *curr,trie_result *tr,char *str,u32 depth)
{
	if(depth > 0)
		str[depth-1] = curr->character;

	// we found a complete word
	if(curr->word_mark)
	{
		str[depth] = '\0';
		const u32 len = strlen(str); 
		char *word = malloc(len + 1);
		memcpy(word,str,len + 1);

		dyn_array_char_ptr_append(&tr->words,word);
	}

	for(u32 i = 0u;i < curr->next_nodes.size;i++)
		trie_sort_rec(curr->next_nodes.data[i],tr,str,depth + 1);
}

void trie_sort(trie *t,trie_result *tr)
{
	char *s = malloc(t->max_str_len + 1);
	trie_sort_rec(t->empty_str,tr,s,0u);
	tr->is_empty = false;
	free(s);
}

void trie_query(trie *t,trie_result *tr,const char *str)
{
	trie_node *curr_node = t->empty_str;

	u32 depth = 0u;
	const u32 len = strlen(str);
	for(u32 i = 0u;i < len;i++)
	{
		u32 next_inx;
		bool char_not_found = true;
		const char curr_char = str[i];
		for(next_inx = 0u;next_inx < curr_node->next_nodes.size;next_inx++)
		{
			if(curr_char == curr_node->next_nodes.data[next_inx]->character)
			{
				char_not_found = false;
				break;
			}
		}

		if(char_not_found) // no such string exists in trie
		{
			tr->is_empty = true;
			return;
		}

		curr_node = curr_node->next_nodes.data[next_inx];
		depth++;
	}

	char *word = malloc(t->max_str_len + 1);
	memcpy(word,str,len);

	trie_sort_rec(curr_node,tr,word,depth);
	tr->is_empty = false;

	free(word);
}

void trie_cleanup_rec(trie_node *curr)
{
	for(u32 i = 0u;i < curr->next_nodes.size;i++)
		trie_cleanup_rec(curr->next_nodes.data[i]);

	dyn_array_t_node_ptr_cleanup(&curr->next_nodes);
	free(curr);
} 

void trie_cleanup(trie *t)
{
	trie_cleanup_rec(t->empty_str);
	t->size = 0u;
	t->max_str_len = 0u;
}

void trie_reset(trie *t)
{
	trie_cleanup(t);
	trie_init(t);
}