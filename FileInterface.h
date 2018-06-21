//
// Created by hartings on 13.06.18.
//

#ifndef OOA5_FILEINTERFACE_H
#define OOA5_FILEINTERFACE_H

#include <iostream>
#include <fstream>
#include "DiGraph.h"

using namespace std;
class DiGraph;

class FileInterface{
protected:
    string _fileName;
    bool _exist;
    fstream _file;
    bool _viceversa;
    //DiGraph *_graph;

    bool fileExists();
    void createFile();
    void updateFile();
    Node* getNodeAdress(string nodeKey);
    unsigned int getNodePos(string nodeKey);
    List <Node *> *_nodeList;
    float calcDistance(string startNodeKey, string endNodeKey);
public:
    DiGraph *_graph;
    ~FileInterface();
    FileInterface(string fileName, bool viceversa);
    void readFile();
    void getFileName();
    void setGraph(DiGraph* graph);
    DiGraph* getGraph();
};

class Tokenizer {
protected:
    unsigned int _pos;
    List<string> _tokens;
public:
    Tokenizer(string data, string separator);
    int countTokens();
    string nextToken();
    bool hasMoreTokens();
    bool secArgIsInt();
};

#endif //OOA5_FILEINTERFACE_H
