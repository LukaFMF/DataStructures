#include <stdlib.h>
#include <stdio.h>

#include "../utils/types.h"

#define DEF_LINKED_LIST(NAME,TYPE)											\
typedef struct link_node_##NAME link_node_##NAME;							\
typedef struct link_node_##NAME												\
{																			\
	TYPE data;																\
	link_node_##NAME *next;													\
} link_node_##NAME;															\
\
typedef struct linked_list_##NAME											\
{																			\
	u32 size;																\
	link_node_##NAME *head;													\
} linked_list_##NAME;														\
\
void linked_list_##NAME##_init(linked_list_##NAME *l)						\
{																			\
	l->size = 0u;															\
	l->head = NULL;															\
}																			\
\
void linked_list_##NAME##_insert(linked_list_##NAME *l,TYPE value,u32 index)\
{																			\
	if(index > l->size)														\
	{																		\
		printf("Cannot insert to index %d, because it "						\
		"exceeds size of the list. Exiting!",index);						\
		exit(-1);															\
	}																		\
																			\
	if(index == 0)															\
	{																		\
		link_node_##NAME *new = malloc(sizeof(link_node_##NAME));			\
		new->data = value;													\
																			\
		link_node_##NAME *next = l->head;									\
		l->head = new;														\
		new->next = next;													\
	}																		\
	else																	\
	{																		\
		link_node_##NAME *prev = l->head;									\
		link_node_##NAME *next = prev->next;								\
		for(u32 i = 1u;i < index;i++)										\
		{																	\
			prev = next;													\
			next = next->next;												\
		}																	\
																			\
		link_node_##NAME *new = malloc(sizeof(link_node_##NAME));			\
		new->data = value;													\
																			\
		prev->next = new;													\
		new->next = next;													\
	}																		\
	l->size++;																\
}																			\
\
void linked_list_##NAME##_delete(linked_list_##NAME *l,u32 index)			\
{																			\
	if(l->size == 0u || index > l->size - 1)								\
	{																		\
		printf("Cannot delete from index %d, because it "					\
		"exceeds %d. Exiting!",index,l->size-1);							\
		exit(-1);															\
	}																		\
																			\
	if(index == 0)															\
	{																		\
		link_node_##NAME *to_delete = l->head;								\
		l->head = to_delete->next;											\
		free(to_delete);													\
	}																		\
	else																	\
	{																		\
		link_node_##NAME *prev = l->head;									\
		link_node_##NAME *to_delete = prev->next;							\
		for(u32 i = 1u;i < index;i++)										\
		{																	\
			prev = to_delete;												\
			to_delete = to_delete->next;									\
		}																	\
																			\
		prev->next = to_delete->next;										\
		free(to_delete);													\
	}																		\
	l->size--;																\
}																			\
\
void linked_list_##NAME##_cleanup(linked_list_##NAME *l)					\
{																			\
	link_node_##NAME *curr = l->head;										\
	link_node_##NAME *next = NULL;											\
	while(curr != NULL)														\
	{																		\
		next = curr->next;													\
		free(curr);															\
		curr = next;														\
	}																		\
																			\
	l->head = NULL;															\
	l->size = 0u;															\
}																			\
\
void linked_list_##NAME##_reset(linked_list_##NAME *l)						\
{																			\
	linked_list_##NAME##_cleanup(l);										\
	linked_list_##NAME##_init(l);											\
}
