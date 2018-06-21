//
// Created by hartings on 26.05.18.
//

#ifndef OOA3_DIGRAPH_H
#define OOA3_DIGRAPH_H

#include "List.h"
#include "Node.h"
#include "DiGraph.h"
#include "GraphVisualizer.h"
#include "FileInterface.h"

using namespace std;

class GraphVisualizer;
class DiGraph {
private:
    //List<Node *> *_nodeList;
    Node *getNodeAdress(string nodeKey);
    unsigned int getNodePos(Node *);
    GraphVisualizer *_graphViz;
public:
    List<Node *> *_nodeList;
    DiGraph();
    void addNode(Node *node);
    void addEdge(float weight, string startNodeKey, string endNodeKey);
    List<Node *> getNeighbours(string nodeKey);
    List<Edge *> getAllEdgesOfNode(string nodeKey);
    List<Node *> getAllNodes(void);
    List<Edge *>getShortestPathByDijkstra(string startNode, string endNode);
    void visualize();
    void setVisualizer(GraphVisualizer* graphVisualizer);
    GraphVisualizer* getVisualizer();
};

#endif //OOA3_DIGRAPH_H
