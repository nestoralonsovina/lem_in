
# Lem-in
Project done in group with [Jorge Allen Soler](https://github.com/allen-soler).

## Graph's algorithm project

Subject --> [Lem-in](https://cdn.intra.42.fr/pdf/pdf/6161/lem-in.en.pdf)

Some of the constraints that we were imposed:
 1. Only START and END nodes can have more than one unit concurrently
 2. After exiting one of those nodes, only one unit can be at the same time in each node.
 
### Problem
With the constraints stated before, and having the number of units to move at the start. The problem is to find the combination of not-overlapping paths (Constraint 1) that will minimise the number of movements needed to move from START to END.

### Parsing

To achieve a good performance in this aspect of the program, we ended up using the combination of an AVL (Auto balanced tree) and hashing, to verify that all the information entered was correct, and that there were no mistakes in it.

To represent the graph we used a linked-list, were every node points to an array where we store all it's neighbours.

### Solution

Our program was required to achieve the best possible solution even when we have 1000, 2000, n paths. Solving up to 10.000 nodes problems in less than 1 second (which we solved in 0.6s, parsing included).

To solved this problem we approached it like a **Maximum flow, minimum cost** type of problem, which in a simpler situation, an already made algorithm would have directly solved our problem. But the task of modifying an already existing algorithm to supply our needs turned out to not be as simple.

For the constraints,  our final solution was to instead of putting capacities on the edges, as you normally would in a flow problem, we set the capacity of our nodes to be 1. So of two different paths crossing through a node, only the best of them would be taken, not both.
We also used a formula derived from testing to calculate the combination of paths that would best suit our need based on the number of ants that we had.

```c
double compute_ants(t_paths *head, t_paths *cur, t_graph *g)

{

	int nb_paths;

	nb_paths = count_paths(head);

	return ((g->nb_ant - ((nb_paths - 1) * (cur->len)\

		- (sum_lengths(head) - (cur->len)))) / nb_paths);

}
```

### Possible improvements that could be made

1. The memory management that we did on this project was not the best, although there are no leaks at the end of the program, in some instances we allocate more memory that what we need to and some of the free's could be done before the end of the program.


*Instructions to test the program will be added soon, Python 3.x, PHP, gcc and Make are needed to properly run the everything*


**Our final note in this project was 125/100.**
