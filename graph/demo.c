#include <math.h>

#include "graph.h"

// invalidates graph g since it partially destorys its contents
f32 shortest_distance_with_m_edges(graph *g,u32 src,u32 dst,u32 m)
{
	if(m == 0u)
		return src == dst ? 0.f : INFINITY;

	priority_queue_edge *next_nodes = &g->edges.data[src];

	f32 least_cost = INFINITY;
	while(next_nodes->size != 0u)
	{
		const edge next_info = priority_queue_edge_pop(next_nodes);
		const f32 curr_least_cost = next_info.weight + shortest_distance_with_m_edges(g,next_info.dst,dst,m - 1);
		
		if(curr_least_cost < least_cost)
			least_cost = curr_least_cost;
	}

	return least_cost;
}

// useless on big graphs(v = 3500,e = 24000) with m > 5
f32 shortest_distance_with_m_edges_backtrack(graph *g,u32 src,u32 dst,u32 m)
{
	if(m == 0u)
		return src == dst ? 0.f : INFINITY;

	priority_queue_edge *next_nodes = &g->edges.data[src];

	f32 least_cost = INFINITY;
	for(u32 i = 0u;i < next_nodes->size;i++)
	{
		const edge next_info = next_nodes->data[next_nodes->start + i];
		const f32 curr_least_cost = next_info.weight + shortest_distance_with_m_edges_backtrack(g,next_info.dst,dst,m - 1);

		if(curr_least_cost < least_cost)
			least_cost = curr_least_cost;
	}

	return least_cost;
}

i32 main()
{
	graph g;
	graph_init(&g,"big.g",true,true);

	const f32 least_cost = shortest_distance_with_m_edges(&g,3u,2631u,5u);
	if(least_cost < INFINITY)
		printf("%.1f\n",least_cost);
	else
		printf("No viable path found!\n");

	graph_reset(&g,"big.g",true,true);

	const f32 least_cost_backtrack = shortest_distance_with_m_edges_backtrack(&g,3u,2631u,5u);
	if(least_cost_backtrack < INFINITY)
		printf("%.1f\n",least_cost_backtrack);
	else
		printf("No viable path found!\n");

	graph_cleanup(&g);
	return 0;
}