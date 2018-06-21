//
// Created by hartings on 26.05.18.
//

#include <iostream>
#include <cmath>
#include "List.h"
#include "Node.h"
#include "DiGraph.h"
#include "Execption.h"
#include "PriorityQueue.h"


DiGraph::DiGraph() {
    _nodeList = new List<Node *>();
}

void DiGraph::addNode(Node * node) {
    _nodeList->insertNewEntry(node);
}
void DiGraph::addEdge(float weight, string startNodeKey, string endNodeKey) {
    Node *startNode = getNodeAdress(startNodeKey);
    Node *endNode = getNodeAdress(endNodeKey);
    if (startNode != endNode)
        startNode->setNewEdge(new Edge(weight, startNode, endNode));
}

List<Node *> DiGraph::getNeighbours(string nodeKey) {
    List<Node *> resultList;
    List<Edge *> neighboursList;
    neighboursList = getNodeAdress(nodeKey)->getEdges();

    for (int i = 0; i < neighboursList.getListSize(); i++) {
        resultList.insertNewEntry(neighboursList.getValueAtPos(i)->getEndNode());
    }

    return resultList;
}


List <Edge *> DiGraph::getAllEdgesOfNode(string nodeKey) {
    for (int i = 0; i < _nodeList->getListSize() ; i++) {
        if (nodeKey == _nodeList->getValueAtPos(i)->getKey()) {
            return _nodeList->getValueAtPos(i)->getEdges();
        }
    }
}

List <Node *> DiGraph::getAllNodes(void) {
    return *_nodeList;
}

Node* DiGraph::getNodeAdress(string nodeKey) {
    for (int i = 0; i < _nodeList->getListSize(); i++) {
        if(nodeKey == _nodeList->getValueAtPos(i)->getKey())
            return _nodeList->getValueAtPos(i);
    }
    throw MyExecption("Error: Can not get the node adress - IN: DiGraph");
}

unsigned int DiGraph::getNodePos(Node *pleseInsertAGoodName) {
    for (unsigned int i = 0; i < _nodeList->getListSize(); i++) {
        if (pleseInsertAGoodName->getKey() == _nodeList->getValueAtPos(i)->getKey())
            return i;
    }
}

List <Edge *> DiGraph::getShortestPathByDijkstra(string startNodeKey, string endNodeKey) {
    List<Edge *> shortestPath;
    if (startNodeKey == endNodeKey)
        return shortestPath;

    Node *startNode = getNodeAdress(startNodeKey);
    Node *endNode = getNodeAdress(endNodeKey);

    Node *helpPointer = nullptr, *endNoteOfEdgeList = nullptr;
    

    int nodeCount = _nodeList->getListSize();

    Node *prev[nodeCount] = {nullptr};
    float dist[nodeCount] = {0};
    float value = 0;

    PriorityQueue<Node *> *priorityQueue = new PriorityQueue<Node *>();

    for (int i = 0; i < nodeCount; i++) {
        if (_nodeList->getValueAtPos(i) == startNode)
            dist[i] = 0;
        else
            dist[i] = 9999999;

        prev[i] = nullptr;

        priorityQueue->insert(_nodeList->getValueAtPos(i), dist[i]);
    }

    while (priorityQueue->getSize() > 0) {
        helpPointer = priorityQueue->extractMin();

        for (int i = 0; i < helpPointer->getEdges().getListSize(); i++) {
            endNoteOfEdgeList = helpPointer->getEdges().getValueAtPos(i)->getEndNode();

            value = dist[getNodePos(helpPointer)] + helpPointer->getEdges().getValueAtPos(i)->getWeight();

            if ( value <  dist[getNodePos(endNoteOfEdgeList)]) {
                dist[getNodePos(endNoteOfEdgeList)] = value;
                prev[getNodePos(endNoteOfEdgeList)] = helpPointer;
                priorityQueue->decreaseKey(endNoteOfEdgeList,value);
            }
        }
    }

    helpPointer = endNode;

    while (prev[getNodePos(helpPointer)] != NULL) {
        for (int i = 0; i < prev[getNodePos(helpPointer)]->getEdges().getListSize(); i++) {
            if (prev[getNodePos(helpPointer)]->getEdges().getValueAtPos(i)->getEndNode() == helpPointer)
                shortestPath.insertNewEntry(prev[getNodePos(helpPointer)]->getEdges().getValueAtPos(i));
        }
        helpPointer = prev[getNodePos(helpPointer)];
    }
    return shortestPath;
}

void DiGraph::setVisualizer(GraphVisualizer* graphVisualizer) {
    _graphViz = graphVisualizer;
}

GraphVisualizer* DiGraph::getVisualizer() {
    return _graphViz;
}

void DiGraph::visualize() {
    DiGraph *graph = this;
    _graphViz->visualize(*graph); //TODO: SEG FAULT
}