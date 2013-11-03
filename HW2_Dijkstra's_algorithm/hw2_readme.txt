

With more of an electronics background, getting back to work with Graphs was quite interesting exercise.
I've chosen to represent the graph with an adjacent list, expecting that the use would be for more sparse graphs. The main structure is a vector of nodes, and each node is a vector of edges. The edge in its turn is a pair of a destination node, and a cost. As a secondary structure I have a vector for the node values, which implementation was suggested in the exercise, but not used in this particular algorithm.
Secondly the priority queue was another good challenge. I've tried several different approaches, but finally decided to go for a double vector of pointers to Paths. One vector is meant to have direct access the Path by its destination node as vector index. The second vector is a minimum heap, using standard lib implementation and it's meant to get access to the minimum cost in the queue. This way I would have efficient access in the two methods needed in the Dijktra's Shortest Path algorithm. I've decided to store a Path in the queue, because it would keep track of all related nodes and cost, and not only a final node.
With this two structures in hand, the implementation of the Dijkstra's algorithm and the Monte Carlo simulation was quite straight forward.
However I still have optimization opportunities to improve the algorithms performance, but I have not yet figured out where.
I ran my results on a Intel Celeron 420 @ 1.6GHz.
I used as reference for this exercise the class forums and the sites: Cplusplus.com and Stack Overflow.

Results:

C:\>hw2_dijkstra_s_algorithm.exe 10000 50 0.2

started computation at Sun Nov 03 19:37:32 2013

loops: 10000  nodes: 50  density: 0.2  cost: [1.0,10.0)
average path cost:      6.98
average path edges:     2.63
average graph edges:    244.83

finished computation at Sun Nov 03 19:39:51 2013
elapsed time: 138.38s


C:\>hw2_dijkstra_s_algorithm.exe 10000 50 0.4

started computation at Sun Nov 03 19:40:08 2013

loops: 10000  nodes: 50  density: 0.4  cost: [1.0,10.0)
average path cost:      4.71
average path edges:     2.29
average graph edges:    490.12

finished computation at Sun Nov 03 19:43:41 2013
elapsed time: 213.36s


Please find attached the source files.