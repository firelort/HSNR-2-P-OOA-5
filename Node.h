//
// Created by Robert Hartings on 23.05.18.
//

#ifndef OOA3_NODE_H
#define OOA3_NODE_H

#include <iostream>
#include "List.h"

using namespace std;

class Edge;
class Node {
private:
    string _key;
    int _posX, _posY;
    List<Edge *> *_edgeList;
public:
    Node(string key, int posX, int PosY);
    string getKey(void);
    int getPosX(void);
    int getPosY(void);
    List<Edge *> getEdges(void);
    void setKey(string newKey);
    void setPosX(int pos);
    void setPosY(int pos);
    void setNewEdge(Edge * edge);
};

class Edge {
private:
    float _weight;
    Node * _startNode, * _endNode;
public:
    Edge(float weight, Node *startNode, Node *endNode);
    float getWeight(void);
    Node *getStartNode(void);
    Node *getEndNode(void);
    void setWeight(float weight);
    void setStartNode(Node *startNode);
    void setEndNode(Node * endNode);
};
#endif //OOA3_NODE_H
