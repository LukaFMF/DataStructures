#include <math.h>

#include "graph.h"

f32 least_cost_path_with_m_edges(graph *g,u32 src,u32 dst,u32 m)
{
	if(m == 0u)
		return src == dst ? 0.f : INFINITY;

	g->visited_vertices[src] = true;
	queue_edge *next_nodes = &g->edges.data[src];

	f32 least_cost = INFINITY;
	for(u32 i = 0u;i < next_nodes->size;i++)
	{
		const edge next_info = next_nodes->data[next_nodes->start + i];
		if(!g->visited_vertices[next_info.dst])
		{
			const f32 curr_least_cost = next_info.weight + least_cost_path_with_m_edges(g,next_info.dst,dst,m - 1);

			if(curr_least_cost < least_cost)
			{
				least_cost = curr_least_cost;
				// printf("%d: %d - %.1f\n",m,src,least_cost);
			}
		}
	}

	g->visited_vertices[src] = false;
	return least_cost;
}

i32 main()
{
	graph g;
	graph_init(&g,"exampleV.grph",true,true);

	const f32 min_cost = least_cost_path_with_m_edges(&g,2u,4u,9u);
	if(min_cost < INFINITY)
		printf("%.1f\n",min_cost);
	else
		printf("No viable path found!\n");

	// for(u32 i = 0;i < g.size;i++)
	// 	printf("%.2d - %s\n",i,g.visited_vertices[i] ? "visited" : "not visited");

	graph_cleanup(&g);
	return 0;
}