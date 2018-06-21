//
// Created by hartings on 26.05.18.
//
#include "Node.h"
#include "Execption.h"


Node::Node(string key, int posX, int posY) {
    _key = key;
    _posX = posX;
    _posY = posY;
    _edgeList = new List<Edge *>();
}

string Node::getKey(void){
    return _key;
}
int Node::getPosX(void) {
    return _posX;
}

int Node::getPosY(void) {
    return _posY;
}

List<Edge *> Node::getEdges(void) {
    return *_edgeList;
}

void Node::setKey(string newKey) {
    _key = newKey;
}
void Node::setPosX(int pos) {
    _posX = pos;
}
void Node::setPosY(int pos) {
    _posY = pos;
}
void Node::setNewEdge(Edge * edge) {
    _edgeList->insertNewEntry(edge);
}

Edge::Edge(float weight, Node *startNode, Node *endNode) {
    _weight = weight;
    _startNode = startNode;
    _endNode = endNode;
}

float Edge::getWeight(void) {
    return _weight;
}

Node *Edge::getStartNode(void) {
    return _startNode;
}

Node *Edge::getEndNode(void) {
    return _endNode;
}

void Edge::setWeight(float weight) {
    _weight = weight;
}
void Edge::setStartNode(Node *startNode) {
    throw MyExecption("Not yet implemented");
    //aus Edgeliste des Elements entferenen und in neue Edgeliste einfügen....
}
void Edge::setEndNode(Node * endNode) {
    _endNode = endNode;
}
