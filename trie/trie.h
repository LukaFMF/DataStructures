#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../utils/types.h"

typedef struct trie_node
{
	char character;
	bool word_mark;
	u32 num_next_nodes;
	struct trie_node **next_nodes;
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
	t->empty_str->num_next_nodes = 0u;
}

void trie_insert(trie *t,const char *str)
{
	//printf("INSERTING: %s\n",str);
	trie_node *curr_node = t->empty_str;

	u32 curr_depth = 0u;
	for(u32 i = 0u;i < strlen(str);i++)
	{
		u32 insert_inx = 0u;
		bool found = false;
		bool insert_to_last = true;
		const char curr_char = str[i];
		for(u32 j = 0u;j < curr_node->num_next_nodes;j++)
		{
			const char possible_next_char = curr_node->next_nodes[j]->character;
			if(curr_char == possible_next_char)
			{
				found = true;
				insert_inx = j;
				break;
			}
			else if(curr_char < possible_next_char)
			{
				insert_to_last = false;
				insert_inx = j;
				break;
			}
		}

		// if character has no barnch yet we create it
		if(!found)
		{
			if(curr_node->num_next_nodes == 0u)
			{
				//printf("first insert %c\n",curr_char);
				curr_node->num_next_nodes = 1u;
				curr_node->next_nodes = malloc(sizeof(trie_node*));
				curr_node->next_nodes[0] = malloc(sizeof(trie_node));
			}
			else if(insert_to_last)
			{
				//printf("insert to last: %c\n",curr_char);
				curr_node->num_next_nodes++;
				curr_node->next_nodes = realloc(curr_node->next_nodes,curr_node->num_next_nodes*sizeof(trie_node*));

				insert_inx = curr_node->num_next_nodes - 1;
				curr_node->next_nodes[insert_inx] = malloc(sizeof(trie_node));
			}
			else
			{
				//printf("insert to %d: %c\n",insert_inx,curr_char);
				curr_node->num_next_nodes++;
				curr_node->next_nodes = realloc(curr_node->next_nodes,curr_node->num_next_nodes*sizeof(trie_node*));

				// make space for new element
				trie_node **move_src = curr_node->next_nodes + insert_inx;
				const u32 bytes_to_move = (curr_node->num_next_nodes - insert_inx - 1)*sizeof(trie_node*);
				memmove(move_src + 1,move_src,bytes_to_move);
				curr_node->next_nodes[insert_inx] = malloc(sizeof(trie_node));
			}
			trie_node *next_node = curr_node->next_nodes[insert_inx];
			next_node->character = curr_char;
			next_node->word_mark = false;
			next_node->num_next_nodes = 0u;
		}
		curr_node = curr_node->next_nodes[insert_inx];
		curr_depth++;
	}

	// if word already exists in trie
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
	for(u32 i = 0u;i < curr->num_next_nodes;i++)
	{
		trie_cleanup_rec(curr->next_nodes[i]);
		free(curr->next_nodes[i]);
	}
	if(curr->num_next_nodes > 0)
		free(curr->next_nodes);
	free(curr);
} 

void trie_cleanup(trie *t)
{
	trie_cleanup_rec(t->empty_str);
	t->size = 0u;
	t->max_str_len = 0u; 
}

void trie_write_rec(trie_node *curr,char *str,u32 depth,FILE *file)
{
	//printf("%c - %s\n",curr->character,curr->word_mark ? "true" : "false");
	if(depth > 0)
		str[depth-1] = curr->character;

	if(curr->word_mark)
	{
		str[depth] = '\0';
		fprintf(file,"%s\n",str);
	}

	for(u32 i = 0u;i < curr->num_next_nodes;i++)
	{
		trie_write_rec(curr->next_nodes[i],str,depth + 1,file);
	}
}

void trie_write(trie *t,const char *filename)
{
	char *s = malloc(t->max_str_len + 1);
	FILE *file = fopen(filename,"w");
	trie_write_rec(t->empty_str,s,0u,file);
	free(s);
}