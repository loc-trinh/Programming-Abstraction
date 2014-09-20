/**
 * File: pathfinder-graph.cpp
 * --------------------------
 * Provides the (fairly obvious) implementation of
 * the PathfinderGraph class.
 */

#include "pathfinder-graph.h"
using namespace std;

void PathfinderGraph::setMapFile(const string& filename) {
    mapFile = filename;
    highlightedNode = NULL;
}

const string& PathfinderGraph::getMapFile() const {
    return mapFile;
}

void PathfinderGraph::setHighlightedNode(Node *node) {
    highlightedNode = node;
}

Node *PathfinderGraph::getHighlightedNode() const {
    return highlightedNode;
}
