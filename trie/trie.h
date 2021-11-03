#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../utils/types.h"

typedef struct trie_node
{
	char character;
	bool end_of_word;
	u32 num_next_nodes;
	struct trie_node **next_nodes;
} trie_node;


typedef struct trie
{
	u32 max_depth;
	trie_node *empty_str;
} trie;

void trie_init(trie *t)
{
	t->max_depth = 0u;
	t->empty_str = malloc(sizeof(trie_node));
	t->empty_str->character = '\0';
	t->empty_str->end_of_word = false;
	t->empty_str->num_next_nodes = 0u;
}

void trie_inset(trie *t,const char *str)
{
	trie_node *curr_node = t->empty_str;

	u32 curr_depth = 0u;
	for(u32 i = 0u;i < strlen(str);i++)
	{
		u32 insert_inx = 0u;
		bool found = false;
		char curr_char = str[i];
		for(u32 j = 0u;j < curr_node->num_next_nodes;j++)
		{
			char possible_next_char = curr_node->next_nodes[j]->character;
			if(curr_char == possible_next_char)
			{
				found = true;
				break;
			}
			else if(j == 0u && curr_char < possible_next_char)
			{
				insert_inx = j;
				break;
			}
			else if(curr_char > curr_node->next_nodes[j-1]->character && curr_char < possible_next_char)
			{
				insert_inx = j;
				break;
			}

		}
		// if character has no barnch yet we create it
		if(!found)
		{
			if(curr_node->num_next_nodes == 0u)
			{
				curr_node->num_next_nodes = 1u;
				curr_node->next_nodes = malloc(sizeof(trie_node*));
				curr_node->next_nodes[0] = malloc(sizeof(trie_node));
			}
			else
			{
				// TODO alloc space at pointers also, not just pointer array !!!!!!!!!!!!
				curr_node->num_next_nodes++;
				curr_node->next_nodes = realloc(curr_node->next_nodes,curr_node->num_next_nodes*sizeof(trie_node*));

				// make space for new element
				trie_node **move_src = curr_node->next_nodes + insert_inx;
				const u32 bytes_to_move = (curr_node->num_next_nodes - insert_inx - 1)*sizeof(trie_node*);
				memmove(move_src + 1,move_src,bytes_to_move);
			}
			trie_node *next_node = curr_node->next_nodes[insert_inx];
			next_node->character = curr_char;
			next_node->end_of_word = false;
			next_node->num_next_nodes = 0u;
		}
		curr_node = curr_node->next_nodes[insert_inx];
	}
	curr_node->end_of_word = true;
}

void trie_cleanup(trie *t)
{
	
}