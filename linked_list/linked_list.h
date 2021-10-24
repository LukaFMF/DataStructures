#include <stdlib.h>
#include <stdio.h>
#include "../utils/types.h"

typedef struct link_node
{
	i32 data;
	struct link_node *next;
} link_node;

typedef struct linked_list
{
	link_node *head;
	u32 size;
} linked_list;

void linked_list_init(linked_list *l)
{
	l->head = NULL;
	l->size = 0u;
}

void linked_list_insert(linked_list *l,i32 value,u32 index)
{
	if(index > l->size)
	{
		printf("Cannot insert to index %d, because it exceeds size of the list. Exiting!",index);
		exit(-1);
	}
	
	if(index == 0)
	{
		link_node *new = malloc(sizeof(link_node));
		new->data = value;

		link_node *next = l->head;
		l->head = new;
		new->next = next;
	}
	else
	{
		link_node *prev = l->head;
		link_node *next = prev->next;
		for(u32 i = 1u;i < index;i++)
		{
			prev = next;
			next = next->next;
		}

		link_node *new = malloc(sizeof(link_node));
		new->data = value;

		prev->next = new;
		new->next = next;
	}
	l->size++;
}

void linked_list_delete(linked_list *l,u32 index)
{
	if(l->size == 0u || index > l->size - 1)
	{
		printf("Cannot delete from index %d, because it exceeds (size of the list) - 1. Exiting!",index);
		exit(-1);
	}

	if(index == 0)
	{
		link_node *to_delete = l->head;
		l->head = to_delete->next;
		free(to_delete);
	}
	else
	{
		link_node *prev = l->head;
		link_node *to_delete = prev->next;
		for(u32 i = 1u;i < index;i++)
		{
			prev = to_delete;
			to_delete = to_delete->next;
		}

		prev->next = to_delete->next;
		free(to_delete);
	}
	l->size--;
}

void linked_list_cleanup(linked_list *l)
{
	link_node *curr = l->head;
	link_node *next = NULL;
	while(curr != NULL)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}

	l->head = NULL;
	l->size = 0u;
}

void linked_list_print(linked_list l)
{
	printf("HEAD ");
	link_node *curr = l.head;
	while(curr != NULL)
	{
		printf("--> %d ",curr->data);
		curr = curr->next;
	}
	printf("--> NULL\n");
}