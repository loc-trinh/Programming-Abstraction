/*
 * File: pathfinder.cpp
 * ----------------
 * Name: Loc Trinh
 * Section: N/A
 * This file is the main starter file for Assignment #8, pathfinder.
 */

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "pathfinder-graph.h"
#include "pathfinder-graphics.h"
#include "error.h"
#include "gwindow.h"
#include "map.h"
#include "path.h"
#include "pqueue.h"
#include "point.h"
#include "tokenscanner.h"
#include "set.h"
#include "simpio.h"
#include "strlib.h"
#include "vector.h"
using namespace std;

/* Global variable */
bool hasPrintDEFAULT = false;

/**
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Describes the Pathfinder assignment on the console.  This text has
 * been retained in its original form to preserve the assignment history.
 */
static void giveInstructions() {
    cout << "This masterful piece of work is a graph extravaganza!" << endl;
    cout << "The main attractions include a lovely visual presentation" << endl;
    cout << "of the graph along with an implementation of Dijkstra's" << endl;
    cout << "shortest path algorithm and Kruskal's computation of" << endl;
    cout << "a minimal spanning tree.  Enjoy!" << endl << endl;
}

/***********************************************************************
 *				      Map Functions                                    *
 *---------------------------------------------------------------------*
 * Each functions is called to help draw the graph					   *
 * getStream() ask the user for map data file                          *
 * makeNode() read data from file and make node with name and point	   *
 * highlightNode()/highlightArc() change node/arc to red               *
 *																	   *
 ***********************************************************************/

/* Function: getStream
 * Usage: getStream(in);
 * ---------------------
 * Get the stream to read map files.
 */
void getStream(ifstream& infile){
	if(hasPrintDEFAULT){
		string filename;
		while(true){
			filename = getLine("Please enter the name of the graph data file: ");
			filename = "data-files/" + filename;
			infile.open(filename.c_str());
			if(infile.fail()){ cout << "ERROR: " << filename << " can't be open!\n" << endl; infile.clear();} else break;
		}
	}
	else { infile.open("data-files/USA.txt"); hasPrintDEFAULT = true; }
}

/* Function: makeNode
 * Usage: Node* newNode = makeNode(line);
 * ---------------------
 * A string is read into token scanner and each part is used in the making of the node.
 * The first string token is name followed by x and y coordinates
 * CAUTION: Map file must follow exact format in order to correctly generate node
 */
Node* makeNode(string line){
	TokenScanner scanner(line);
	scanner.ignoreWhitespace();
	string name = scanner.nextToken(), x = scanner.nextToken(), y = scanner.nextToken();
	GPoint temp(stringToInteger(x), stringToInteger(y));
	
	Node* newNode = new Node;
	newNode->name = name;
	newNode->loc = temp;	
	return newNode;
}

/* Function: makeArc
 * Usage: Arc* newArc = makeArc(line, map, 0);
 * ---------------------
 * A string is read into token scanner and each part is used in the making of the arc.
 * The first string token is starting node follow by the finishing node and the distance
 * Flag FORWARD is used to create forward arc and !FORWARD is used to create backward arc
 * CAUTION: Map file must follow exact format in order to correctly generate arc
 */
Arc* makeArc(string line, PathfinderGraph& map, bool FORWARD){
	TokenScanner scanner(line);
	scanner.ignoreWhitespace();

	Arc *newArc = new Arc;
	if(FORWARD){
		newArc->start = map.getNode(scanner.nextToken());
		newArc->finish = map.getNode(scanner.nextToken());
	}
	else if(!FORWARD){
		newArc->finish = map.getNode(scanner.nextToken());
		newArc->start = map.getNode(scanner.nextToken());
	}
	newArc->cost = stringToInteger(scanner.nextToken());
	return newArc;
}



/* Function: drawMap
 * Usage: drawMap(map, "normal") or drawMap(map, "red);
 * ---------------------
 * Draw the map using map file
 * foreach node and arcs, draw according to the color specified
 * "normal" give node and arc default color
 */
void drawMap(PathfinderGraph& map, string mode){
	string nodeColor, arcColor;
	if(mode == "normal"){ nodeColor = kNodeColor; arcColor = kArcColor;}
	else { nodeColor = arcColor = mode; }

	drawPathfinderMap(map.getMapFile()); //draw Map
	foreach(Node* node in map.getNodeSet()) // draw Nodes
		drawPathfinderNode(node->loc, nodeColor, node->name);
	foreach(Arc* arc in map.getArcSet()) // draw Arcs
		drawPathfinderArc(arc->start->loc, arc->finish->loc, arcColor);
}

/* Function: highlightNode
 * Usage: highlightNode(node);
 * ---------------------
 * Change node color to red.
 */
void highlightNode(Node* node){
	drawPathfinderNode(node->loc, kHighlightColor, node->name);
}

/* Function: highlightNode
 * Usage: highlightNode(node);
 * ---------------------
 * Change arc color to red.
 */
void highlightArc(Arc* arc){
	highlightNode(arc->start);
	highlightNode(arc->finish);
	drawPathfinderArc(arc->start->loc, arc->finish->loc, kHighlightColor);
}


/***********************************************************************
 *				      Helper Functions                                 *
 *---------------------------------------------------------------------*
 * Each functions is called to help clarify the codes.				   *
 * easyClick() creates a circle radius around point                    *
 *   help to identify nodes surrounding the use click.                 *
 * getNodeClick() return the node meant-to-be-clicked by user		   *
 * findShortestPath() implementation followed Dijikstra's algorithm	   *
 *  for shortest routing path.										   *
 * findSpanningTree() implementation followed Kruskal's algorithm	   *
 *	for minimm spanning tree.										   *
 *																	   *
 ***********************************************************************/



/* Function: easyClick
 * Usage: Vector<GPoint> ptList = easyClick(pt);
 * ---------------------
 * Return a vector of GPoints with radius around pt.
 * Help identify the regions near user-click.
 */
Vector<GPoint> easyClick(GPoint pt){
	const int radius = 5;
	Vector<GPoint> pointList;
	for(int i = -radius; i <= radius; i++)
		for(int j = -radius; j <= radius; j++){
				GPoint newPt(pt.getX() + i, pt.getY() + j);
				pointList.add(newPt);
			}
	return pointList;
}

/* Function: getNodeClick
 * Usage: Node* start = getNodeClick(map, 1);
 * ---------------------
 * Return node from map clicked by user.
 * START flag : indicate selecting a starting/ending node
 */
Node* getNodeClick(PathfinderGraph& map, bool START){
	while(true){
		if(START) cout << "Click on a starting position..." << flush;
		else cout << "Click on an ending position...." << flush;

		Vector<GPoint> ptList = easyClick(getMouseClick()); //get surrounding points
		foreach(Node* node in map.getNodeSet()){
			foreach(GPoint pt in ptList) //check each node if matching with the region clicked
				if(node->loc == pt) {
					cout << "\t" << node->name << " chosen." << endl; 
					return node;}
		}
		cout << "\tInvalid click. Please try again." << endl;
	}
}

/* Function: findShortestPath
 * Usage: Path shortestPath = findShortestPath(start, finish, map);
 * ---------------------
 * Return the shortest path between two points
 * Core implementation of Dijikstra's algorithm
 * Note: 
 *   1)Paths are explored in order of total distance rather than the number of hops.
 *		-PriorityQueue(cost)
 *   2)Distance to a node is fixed after each dequeue.
 */

Path findShortestPath(Node *start, Node *finish, PathfinderGraph& map){
	Path path;
	PriorityQueue<Path> queue; //help sort by distance
	Map<string, double> fixed; //record shorest distance to location

	while(start != finish){

		if(!fixed.containsKey(start->name)){ 
			fixed[start->name] = path.getCost(); //add to fixed
			foreach(Arc *arc in map.getArcSet(start)){ //get arcList starting at node*
				if(!fixed.containsKey(arc->finish->name)){ //if in fixed, skip arc
					path.add(arc);
					queue.enqueue(path, path.getCost()); //enqueue all paths one step from node in order of cost
					path.remove(path.size()-1);}
			}
		}

		if (queue.isEmpty()){ 
		path.clear();
		return path;
		}//if can't find a path, return empty path.

		path = queue.dequeue(); //get next shortest path
		start = path.getPath()[path.size() - 1]->finish; //move starting position
	}
	return path;
}


/* Function: findSpanningTree
 * Usage: Path tree = findSpanningTree(map);
 * ---------------------
 * Return the shortest spanning tree within the nodes
 * Core implementation of Kruskal's algorithm
 * Note: 
 *   1)Each node is a set of itself.
 *			When adding an arc, add the set of the start-node and end-node together.
 *			If both are in the same set, i.e. already connected, don't add arc
 */

Path findSpanningTree(PathfinderGraph& map){
	Path tree;

	PriorityQueue<Arc *> queue;
	foreach(Arc* arc in map.getArcSet()) //enqueue all path
		queue.enqueue(arc, arc->cost);

	Vector<Set<Node *> > connected;
	foreach(Node* node in map.getNodeSet()){ //set up all nodes, each connected with itself
		Set<Node *> nodeList;
		nodeList.add(node);
		connected.add(nodeList);}

	while(queue.size() != 0){
		Arc *arc = queue.dequeue();
		int i, j;
		for(i = 0; i < connected.size(); i++) if(connected[i].contains(arc->start)) break;
		for(j = 0; j < connected.size(); j++) if(connected[j].contains(arc->finish)) break;
		if(i != j){
			connected[i]+=connected[j];
			connected.remove(j);
			tree.add(arc);}
	}
	return tree;
}





/***********************************************************************
 *				      Button Functions                                 *
 *---------------------------------------------------------------------*
 * Each button coordinates to a function to be read from user-clicks.  *
 * quitAction() exits the program.									   *
 * getMap() read data file and create graph structure.				   *
 * route() implementation followed Dijikstra's algorithm			   *
 *  for shortest routing path.										   *
 * tree() implementation followed Kruskal's algorithm				   *
 *	for minimm spanning tree.										   *
 *																	   *
 ***********************************************************************/


/* Function: quitAction
 * Usage: quitAction(g);
 * ---------------------
 * Called when the user clicks the Quit button in the control strip.
 */
static void quitAction() {
   exitGraphics();
}

/* Function: getMap
 * Usage: getMap(map);
 * --------------
 * A stream ask for and open a map data file
 * Getline is used to read each line and token scanner is used to make the nodes and arcs
 * Date structure of map is build from map file
 * CAUTION: If map data file doesn't follow the format, building of data structure could be disastrous.
 */
static void getMap(PathfinderGraph& map) {
	map.clear(); 

	ifstream input;
	getStream(input);

	string line;
	bool hasSeenNODES = false, hasSeenARCS = false;

	while(getline(input, line)){
		if(line == "NODES"){ hasSeenNODES = true; hasSeenARCS = false;} //if NODES flag has not been reach
		else if(line == "ARCS"){ hasSeenNODES = false; hasSeenARCS= true;} // if ARCS has not been reach
		else if(hasSeenNODES) // read a node
			map.addNode(makeNode(line));
		else if(hasSeenARCS){ // read an arc
			map.addArc(makeArc(line, map, 1));
			map.addArc(makeArc(line, map, 0));
		}// bidirectional arcs
		else map.setMapFile("images/" + line); //read map file name
	}	

	drawMap(map, "normal"); //normal status give node/arc color
}

/* Function: route
 * Usage: route(map);
 * --------------
 * Map is drawn from data structure.
 * Get start and finish node and highlight them.
 * Use Dijikstra's algorithm to find the shortest path
 * between two locations.
 */
static void route(PathfinderGraph& map){
	drawMap(map, "normal");
	Node *start = getNodeClick(map, 1);
	highlightNode(start);// start-node recorded

	Node *finish;
	while((finish = getNodeClick(map, 0)) == start) // can't pick the same node as start
		cout << "\tSilly, you are already at " << finish->name << endl;
	highlightNode(finish);// end-node reocorded
	
	Path path = findShortestPath(start,finish, map);
	if(!path.isEmpty()){
		drawMap(map, kDimColor); 
		foreach(Arc* arc in path.getPath()) //hightlight path
			highlightArc(arc);
	}
	else cout << "ERROR: No path found!" << endl;

	cout  << "Shortest path found: " << path.toString() << " (" << path.getCost() << " miles)"<< endl;
}

/* Function: tree
 * Usage: tree(map);
 * --------------
 * Map wihtout arcs is drawn from data structure.
 * Use Kruskal's algorithm to find the shortest spanningTree
 * within all of the nodes.
 * Higlight the path.
 */

static void tree(PathfinderGraph& map){
	drawPathfinderMap(map.getMapFile());
	Path spanningTree = findSpanningTree(map);
	foreach(Arc* arc in spanningTree.getPath())
		highlightArc(arc);
	cout << "Shortest spanning network found: " << spanningTree.getCost() << " miles" << endl;
}

/**
 * Function: main
 * --------------
 * Defines the entry point for the entire application.
 */
int main() {
    GWindow gw(kWindowWidth, kWindowHeight + kControlStripHeight);
    initPathfinderGraphics(gw);
    giveInstructions();
	PathfinderGraph myMap;
	getMap(myMap);
	addButton("Map", getMap, myMap);
	addButton("Route", route, myMap);
	addButton("Tree", tree, myMap);
    addButton("Quit", quitAction);
    pathfinderEventLoop();
    return 0;
}
