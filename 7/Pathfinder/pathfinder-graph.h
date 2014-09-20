/**
 * Exports a strongly typed subclass of the Graph template
 * that's Pathfinder-specific.
 */

#ifndef _pathfinder_graph_
#define _pathfinder_graph_

#include <string>
#include "graph.h"      // for template Graph class
#include "graphtypes.h" // for struct Node

/**
 * Class: PathfinderGraph
 * ----------------------
 * This class extends the standard Graph class so that the new
 * class incorporates the Node and Arc type parameters.  The
 * extended data structure also includes an image file name for
 * the map and the ability to designate a particular node as
 * highlighted.
 */

class PathfinderGraph : public Graph<Node,Arc> {
public:
    void setMapFile(const std::string& filename);
    const std::string& getMapFile() const;
    void setHighlightedNode(Node *node);
    Node *getHighlightedNode() const;
    
private:
    std::string mapFile;
    Node *highlightedNode;
};

#endif
