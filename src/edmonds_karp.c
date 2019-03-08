#include "../includes/lem_in.h"

/*

   algorithm EdmondsKarp
	input format:
		edge -> each edge should have three values (src, dest, capacity),
			although for our case the capacity will be always 1?
		node -> N[0] and N[n - 1] are supposed to be the start and the end


	input:
		graph -> graph[v]->links is the list of edges coming out of vertex
			v in the original graph and their corresponding constructed

		reverse edges -> which are used for push-back flow. Each edge should
			have a capacity, flow, source and sink as parameters, as well
			as a pointer to the reverse edge

		s -> source vertex
		t -> dst vertex

	output:
		flow -> value of maximum flow

	flow := 0
	repeat
		(Run a bfs to fin the shortest s-t path. We use 'pred' to store the
		 edge taken to get to each vertex, so we can recover the path after)
		q := queue()
		q.push(s)
		pred := array(graph.length)
		while not empyt(q)
			curr := q.pull()
			for Edge e in graph[cur]
				if pred[e.t] is NULL and e.t != s and e.cap > e.flow
					pred[e.t] := e
					q.push(e.t)

		if not pred[t] is NULL
			(We found an augmenting path. See how much flow we can send)
			df := infinite
*/
