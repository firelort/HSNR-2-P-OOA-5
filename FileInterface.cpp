//
// Created by hartings on 13.06.18.
//

#include "FileInterface.h"
#include <sys/stat.h>
#include <cstring>
#include <math.h>

using namespace std;

FileInterface::FileInterface(string fileName, bool viceversa) {
    _fileName = fileName;
    _exist = fileExists();
    _viceversa = viceversa;
    if (_exist == true) {
        _file.open(_fileName.c_str(), fstream::in);
        cout << "File was opened successfully." << endl;
    } else {
        _file.open(_fileName.c_str(), fstream::app);
        createFile();
    }

}

FileInterface::~FileInterface() {
    updateFile();
    cout << "File was closed." << endl;
}

bool FileInterface::fileExists() {
    struct stat buf;
    if (stat(_fileName.c_str(), &buf) != -1)
        _exist = true;
    else
        _exist = false;
    return _exist;
}

void FileInterface::createFile() {
    _file << "############ Node and Edge List ############" << endl
          << "############ All nodes enter pls below" << endl
          << "############ Format: city/node (please use _ instead of space) Position X Position Y" << endl
          << "Krefeld 100 200" << endl
          << "Bad_Neuenahr 200  300" << endl
          << "Essen 300 400" << endl
          << "Mönchengladbach 400 500" << endl
          << "Aachen 500 600" << endl
          << "############ All edges enter pls below" << endl
          << "############ Format: StartNode EndNode (please use _ instead of space) Weight/Distance (enter nan to let the system calculate.)" << endl
          << "Krefeld Aachen 100" << endl
          << "Aachen Bad_Neuenahr 170" << endl
          << "Mönchengladbach Krefeld 200" << endl
          << "Essen Aachen nan" << endl
          << "Essen Bad_Neuenahr nan" << endl
          << "Mönchengladbach Bad_Neuenahr nan" << endl
          << "Krefeld Bad_Neuenahr nan" << endl
          << "Aachen Essen nan" << endl
          << "Mönchengladbach Aachen nan" << endl
          << "############ Node and Edge List ############" << endl;
    _file.flush();
    cout << "File was created successfully." << endl;
    _file.close();
    _file.open(_fileName, fstream::in);
}

void FileInterface::readFile() {
    string line,compareString, compareLine, cityOne, cityTwo;
    int posX, posY;
    float weight;
    Node * node;
    bool existent;

    while (getline(_file, line)) {
        compareLine = line;
        compareString = compareLine.substr(0,1);
        if (compareString.compare("#") != 0) { //If first char isn't a #
            Tokenizer tok(line, " ");

            if (tok.countTokens() != 3)
                throw MyExecption("FileInterface: File is corrupted.");

            if(tok.secArgIsInt() == true) {
                cityOne = tok.nextToken();
                posX = stoi(tok.nextToken());
                posY = stoi(tok.nextToken());

                _graph->addNode(new Node(cityOne, posX, posY));
            } else {
                cityOne = tok.nextToken();
                cityTwo = tok.nextToken();
                compareString = tok.nextToken();
                posX = compareString.compare("nan");
                if (posX == 0)
                    weight = calcDistance(cityOne, cityTwo);
                else
                    weight = stoi(compareString);
                _graph->addEdge(weight, cityOne, cityTwo);
                if (_viceversa) {
                    node = _graph->getAllNodes().getValueAtPos(getNodePos(cityTwo));
                    for (int i = 0; i < node->getEdges().getListSize() && !existent; i++) {
                        if (node->getEdges().getValueAtPos(i)->getEndNode()->getKey() == cityOne)
                            existent = true;
                    }

                    if (!existent)
                        _graph->addEdge(weight, cityTwo, cityOne);

                    existent = false;
                }
            }
        }
    }
}

void FileInterface::getFileName() {
    cout << "File name: " << _fileName << endl;
}

void FileInterface::updateFile() {
    _file.close();
    _file.open(_fileName,fstream::out);

    _file << "############ Node and Edge List ############" << endl
          << "############ All nodes enter pls below" << endl
          << "############ Format: city/node (please use _ instead of space) Position X Position Y" << endl;


    for (int nodeCounterForNode = 0; nodeCounterForNode < _graph->_nodeList->getListSize(); nodeCounterForNode++) {
        _file << _graph->_nodeList->getValueAtPos(nodeCounterForNode)->getKey() << " " << _graph->_nodeList->getValueAtPos(nodeCounterForNode)->getPosX() << " " << _graph->_nodeList->getValueAtPos(nodeCounterForNode)->getPosY() << endl;
    }

    _file << "############ All edges enter pls below" << endl
          << "############ Format: StartNode EndNode (please use _ instead of space) Weight/Distance (enter nan to let the system calculate.)" << endl;

    for (int nodeCounterForEdge = 0; nodeCounterForEdge < _graph->_nodeList->getListSize(); nodeCounterForEdge++) {
        for (int edgeCounter = 0; edgeCounter < _graph->_nodeList->getValueAtPos(nodeCounterForEdge)->getEdges().getListSize() ; edgeCounter++) {
            _file << _graph->_nodeList->getValueAtPos(nodeCounterForEdge)->getEdges().getValueAtPos(edgeCounter)->getStartNode()->getKey()  << " " << _graph->_nodeList->getValueAtPos(nodeCounterForEdge)->getEdges().getValueAtPos(edgeCounter)->getEndNode()->getKey() << " " << _graph->_nodeList->getValueAtPos(nodeCounterForEdge)->getEdges().getValueAtPos(edgeCounter)->getWeight() << endl;
        }
    }

    _file << "############ Node and Edge List ############" << endl;
    _file.flush();

    _file.close();
}

Node* FileInterface::getNodeAdress(string nodeKey) {
    for (int i = 0; i < _graph->_nodeList->getListSize(); i++) {
        if(nodeKey == _graph->_nodeList->getValueAtPos(i)->getKey())
            return _graph->_nodeList->getValueAtPos(i);
    }
    throw MyExecption("Error: Can not get the node adress - IN: DiGraph");
}

unsigned int FileInterface::getNodePos(string nodeKey) {
    for (int i = 0; i < _graph->_nodeList->getListSize(); i++) {
        if(nodeKey == _graph->_nodeList->getValueAtPos(i)->getKey())
            return (unsigned int) i;
    }
    throw MyExecption("Error: Can not get the node adress - IN: DiGraph");
}

float FileInterface::calcDistance(string startNodeKey, string endNodeKey) {
    Node *firstNode = getNodeAdress(startNodeKey);
    Node *secondNode = getNodeAdress(endNodeKey);
    float distance;
    int xValue, yValue;

    xValue = secondNode->getPosX() - firstNode->getPosX();
    yValue = secondNode->getPosY() - firstNode->getPosY();
    distance = (float) (yValue * yValue) + (xValue * xValue);
    distance = sqrtf(distance);

    for (int i = 0; i < firstNode->getEdges().getListSize(); i++) {
        if (firstNode->getEdges().getValueAtPos(i)->getEndNode() == secondNode)
            firstNode->getEdges().getValueAtPos(i)->setWeight(distance);
    }

    for (int j = 0; j < secondNode->getEdges().getListSize() ; j++) {
        if (secondNode->getEdges().getValueAtPos(j)->getEndNode() == firstNode)
            secondNode->getEdges().getValueAtPos(j)->setWeight(distance);
    }

    return distance;
}

void FileInterface::setGraph(DiGraph* graph) {
    _graph = graph;
}

DiGraph* FileInterface::getGraph() {
    return _graph;
}

Tokenizer::Tokenizer(string data, string separator) {
    _pos = 0;
    char *dat = (char *) data.c_str();
    char *sep = (char *) separator.c_str();

    char *tok = strtok(dat, sep);
    while (tok != 0) {
        _tokens.insertNewEntry(string(tok));
        tok = strtok(0, sep);
    }
}

int Tokenizer::countTokens() {
    return _tokens.getListSize();
}

bool Tokenizer::hasMoreTokens() {
    return _pos < _tokens.getListSize();
}

string Tokenizer::nextToken() {
    return _tokens.getValueAtPos(_pos++);
}

bool Tokenizer::secArgIsInt() {
    string compareString = _tokens.getValueAtPos(1); // An zweiter Stelle ist ein Int
    compareString = compareString.substr(0,1);
    for (int i = 1; i < 10; ++i) {
        if (compareString.compare(to_string(i)) == 0)
            return true;
    }
    return false;
}