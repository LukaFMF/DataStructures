#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../utils/types.h"
#include "../dyn_array/dyn_array.h"

// forward declaration for trie node
typedef struct trie_node trie_node;

// definition for all the generic dyn_array things
def_dyn_array(t_node,trie_node*)

typedef struct trie_node
{
	char character;
	bool word_mark;
	dyn_array_t_node next_nodes;
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
	dyn_array_t_node_init(&t->empty_str->next_nodes);
}

void trie_insert(trie *t,const char *str)
{
	trie_node *curr_node = t->empty_str;

	u32 curr_depth = 0u;
	for(u32 i = 0u;i < strlen(str);i++)
	{
		u32 insert_inx;
		bool found = false;
		bool insert_to_last = true;
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
			{
				insert_to_last = false;
				break;
			}
		}

		// if character has no barnch yet we create it
		if(!found)
		{
			trie_node *new = malloc(sizeof(trie_node));
			new->character = curr_char;
			new->word_mark = false;
			dyn_array_t_node_init(&new->next_nodes);

			if(insert_to_last)
				dyn_array_t_node_append(&curr_node->next_nodes,new);
			else
				dyn_array_t_node_insert(&curr_node->next_nodes,insert_inx,new);
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

void trie_cleanup_rec(trie_node *curr)
{
	for(u32 i = 0u;i < curr->next_nodes.size;i++)
		trie_cleanup_rec(curr->next_nodes.data[i]);

	dyn_array_t_node_cleanup(&curr->next_nodes);
	free(curr);
} 

void trie_cleanup(trie *t)
{
	trie_cleanup_rec(t->empty_str);
	t->size = 0u;
	t->max_str_len = 0u;
}

void trie_sort_to_file_rec(trie_node *curr,char *str,u32 depth,FILE *file)
{
	if(depth > 0)
		str[depth-1] = curr->character;

	// we found a complete
	if(curr->word_mark)
	{
		str[depth] = '\0';
		fprintf(file,"%s\n",str);
	}

	for(u32 i = 0u;i < curr->next_nodes.size;i++)
		trie_sort_to_file_rec(curr->next_nodes.data[i],str,depth + 1,file);
}

void trie_sort_to_file(trie *t,const char *filename)
{
	char *s = malloc(t->max_str_len + 1);
	FILE *file = fopen(filename,"w");

	trie_sort_to_file_rec(t->empty_str,s,0u,file);

	fclose(file);
	free(s);
}