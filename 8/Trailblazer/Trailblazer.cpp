/******************************************************************************
 * File: Trailblazer.cpp
 *
 * Implementation of the graph algorithms that comprise the Trailblazer
 * assignment.
 */

#include "Trailblazer.h"
#include "TrailblazerGraphics.h"
#include "TrailblazerTypes.h"
#include "TrailblazerPQueue.h"
#include "map.h"
#include "random.h"
using namespace std;

/* Function: shortestPath
 * 
 * Finds the shortest path between the locations given by start and end in the
 * specified world.	 The cost of moving from one edge to the next is specified
 * by the given cost function.	The resulting path is then returned as a
 * Vector<Loc> containing the locations to visit in the order in which they
 * would be visited.	If no path is found, this function should report an
 * error.
 *
 * In Part Two of this assignment, you will need to add an additional parameter
 * to this function that represents the heuristic to use while performing the
 * search.  Make sure to update both this implementation prototype and the
 * function prototype in Trailblazer.h.
 */
struct Node{
	Color color;
	Loc parent;
	double cost;
};

void makeGrid(int row, int col, Map<Loc, Node>& grid){
	for(int i = 0; i < row; i++)
		for(int j = 0; j < col; j++){
			Loc newLoc = makeLoc(i,j);
			Node newNode = {GRAY, newLoc, 0};
			grid[newLoc] = newNode;}
}

Vector<Loc> Path(Loc start, Loc end, Map<Loc, Node> grid){
	Vector<Loc> path;
	while(end != start){
		path.insert(0, end);
		end = grid[end].parent;
	}
	path.insert(0, end);
	return path;
}  

Vector<Loc> shortestPath(Loc start, Loc end,
						 Grid<double>& world,
						 double costFn(Loc one, Loc two, Grid<double>& world),
						 double heuristic(Loc start, Loc end, Grid<double>& world)) {
	Map<Loc, Node> grid; // map is easiest to implement because of fast access and lookup
	makeGrid(world.numRows(), world.numCols(), grid);
	grid[start].color = YELLOW; //put start node in position

	TrailblazerPQueue<Loc> queue;
	queue.enqueue(start, heuristic(start, end, world));

	Loc cur;
	while(!queue.isEmpty()){
		cur = queue.dequeueMin(); //dequeue the minimally cost Node
		grid[start].color = GREEN; //set considering node to green
		colorCell(world, cur, GREEN);

		if(cur == end) break;

		for(int i = -1; i <= 1; i++) //navigate the 8-Directions around a Node
			for(int j = -1; j <= 1; j++){ 
				Loc explore = makeLoc(cur.row+i, cur.col+j);
				if(grid.containsKey(explore) && grid[explore].color == GRAY){ 
					grid[explore].parent = cur;
					grid[explore].cost = grid[cur].cost+costFn(cur, explore, world);	
					grid[explore].color = YELLOW;
					colorCell(world, explore, YELLOW);

					queue.enqueue(explore, grid[explore].cost+ heuristic(explore, end, world)); //added heuristic for hinting directions
				} //if gray(unexplored), then mark yellow and add to queue
				else if(grid.containsKey(explore) && grid[explore].color == YELLOW && grid[explore].cost > grid[cur].cost+costFn(cur, explore, world)){
					grid[explore].parent = cur;
					grid[explore].cost = grid[cur].cost+costFn(cur, explore, world);

					queue.decreaseKey(explore, grid[explore].cost + heuristic(explore, end, world));
				} // if yellow(explored) and new cost is shorter than old cost, update cost
			}
	}
	if(queue.isEmpty()) return Vector<Loc>(); // return empty vec if no path found
	else return Path(start, end, grid); // else rebuild path and return that Vector<Loc>
}

Set<Edge> createMaze(int numRows, int numCols) {
	Set<Edge> tree;

	//build all possible Edge and enqueue with random cost
	TrailblazerPQueue<Edge> queue;
	for(int  i = 0; i < numRows; i++)
		for(int j = 0; j < numCols-1; j++)
			queue.enqueue(makeEdge(makeLoc(i,j),makeLoc(i,j+1)), randomInteger(0,9));
	for(int  i = 0; i < numCols; i++)
		for(int j = 0; j < numRows-1; j++)
			queue.enqueue(makeEdge(makeLoc(j, i),makeLoc(j+1, i)), randomInteger(0,9));


	Vector<Set<Loc> > connected; //start up each connected group with its own node
	for(int i = 0; i < numRows; i++)
		for(int j = 0; j < numCols; j++){ //set up all nodes, each connected with itself
			Set<Loc> nodeList;
			nodeList.add(makeLoc(i,j));
			connected.add(nodeList);}

	while(queue.size() != 0){
		Edge edge = queue.dequeueMin();
		int i, j;
		for(i = 0; i < connected.size(); i++) if(connected[i].contains(edge.start)) break;
		for(j = 0; j < connected.size(); j++) if(connected[j].contains(edge.end)) break;
		if(i != j){ //if both endings of Edge aren't in same connected group, connect them
			connected[i]+=connected[j];
			connected.remove(j);
			tree.add(edge);}
	}
	return tree;
}
