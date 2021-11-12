#include <stdio.h>
#include <stdlib.h>

#include "../utils/types.h"
#include "../dyn_array/dyn_array.h"
#include "../priority_queue/priority_queue.h"


typedef struct edge
{
	u32 dst;
	f32 weight;
} edge;

DEF_PRIORITY_QUEUE(edge,edge)
DEF_DYN_ARRAY(pq_edge,priority_queue_edge)

typedef struct graph
{
	bool directed;
	bool weighted;

	// array where each index represents a vertex and value at index is a 
	// priority queue of edges the vertex has
	dyn_array_pq_edge edges;
} graph;

void graph_init(graph *g,const char *filename,bool directed,bool weighted)
{
	FILE *file = fopen(filename,"r");
	if(!file)
	{
		printf("File \"%s\" could not be opened. Exiting!\n",filename);
		exit(1);
	}
	
	// first line contains number of vertices
	u32 num_verts;
	i32 ret_code;
	ret_code = fscanf(file,"%u",&num_verts);
	if(ret_code == EOF)
	{
		printf("File \"%s\" is empty. Exiting!\n",filename);
		exit(1);
	}
	else if(ret_code != 1)
	{
		printf("Error while reading file \"%s\", first line of the file"
		" should a single number - the number of vertices. Exiting!\n",filename);
		exit(1);
	}

	dyn_array_pq_edge_init(&g->edges,num_verts);

	// initialize priority queues for vertices
	for(u32 i = 0u;i < num_verts;i++)
		priority_queue_edge_init(&g->edges.data[i]);
	
	u32 src;
	u32 dst;
	f32 weight;
	while((ret_code = fscanf(file,"%u %f %u",&src,&weight,&dst)))
	{
		if(ret_code == EOF)
			break;
		else if(ret_code != 3)
		{
			printf("Error while reading file \"%s\", edges should be described"
			" by three numbers separated by space. Exiting!\n",filename);
			exit(1);
		}

		// if the graph isnt weighted every edge has a cost of 1
		if(!weighted)
			weight = 1.f;

		edge e = {.dst = dst,.weight = weight};
		priority_queue_edge_prioritized_insert(&g->edges.data[src],weight,e);

		// if the graph isnt directed the edge must also connect the dst vertex to the src
		if(!directed)
		{
			e.dst = src;
			priority_queue_edge_prioritized_insert(&g->edges.data[dst],weight,e);
		}
	}
	fclose(file);

	g->directed = directed;
	g->weighted = weighted;
}

void graph_cleanup(graph *g)
{
	for(u32 i = 0u;i < g->edges.size;i++)
		priority_queue_edge_cleanup(&g->edges.data[i]);

	dyn_array_pq_edge_cleanup(&g->edges);
}

void graph_reset(graph *g,const char *filename,bool directed,bool weighted)
{
	graph_cleanup(g);
	graph_init(g,filename,directed,weighted);
}