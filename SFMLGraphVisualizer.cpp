//
// Created by hartings on 23.05.18.
//

#include <sstream>
#include <math.h>
#include "SFMLGraphVisualizer.h"
#include <iostream>
#include "Node.h"

#define NODERADIUS 10
using namespace std;


SFMLGraphVisualizer::SFMLGraphVisualizer() {
    this->font.loadFromFile("../FreeMono.ttf");
}

void SFMLGraphVisualizer::visualize(DiGraph &graph) {

    window.create(sf::VideoMode(1024, 1024), "SFML Graph Window");
    List<Node *> allNodes = graph.getAllNodes();

    string startNodeKey = "NULL", endNodeKey = "NULL";
    int nodePos = -1, nodeId;

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::U) {
                        _updateWeight = !_updateWeight;
                    } else if (event.key.code == sf::Keyboard::L) {
                        _drawLabelOfEdge = !_drawLabelOfEdge;
                    } else if (event.key.code == sf::Keyboard::S) {
                        if (-1 < (nodeId = changeName(graph))) {
                            startNodeKey = graph.getAllNodes().getValueAtPos(nodeId)->getKey();
                            cout << "Die Startnode wurde zu " << startNodeKey << " gesetzt." << endl;
                        }
                    } else if (event.key.code == sf::Keyboard::E) {
                        if (-1 < (nodeId = changeName(graph))) {
                            endNodeKey = graph.getAllNodes().getValueAtPos(nodeId)->getKey();
                            cout << "Die Endnode wurde zu " << endNodeKey << " gesetzt." << endl;
                        }
                    }
                    break;
                case sf::Event::MouseButtonReleased:
                    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        if (_updateWeight)
                            calcNewDistance(graph, nodePos);
                        nodePos = -1;
                    }
                case sf::Event::MouseMoved:
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        moveNode(graph, nodePos);
                    break;
                default:
                    break;
            }
        }

        window.clear(sf::Color::White);

        for (int i = 0; i < allNodes.getListSize(); i++) {
            Node *node = allNodes.getValueAtPos(i);
            sf::Color color(255, 0, 0);
            drawNode(*node, color);
            List<Edge *> allEdges = graph.getAllEdgesOfNode(node->getKey());
            for (unsigned int j = 0; j < allEdges.getListSize(); j++) {
                drawEdge(*(allEdges.getValueAtPos(j)), sf::Color::Black, allEdges.getValueAtPos(j)->getWeight(), 1);
            }
        }
        if (startNodeKey.compare("NULL") != 0 && endNodeKey.compare("NULL") != 0)
            highlightPath(graph.getShortestPathByDijkstra(startNodeKey, endNodeKey));

        if (_updateWeight || !_drawLabelOfEdge) {
            if (_updateWeight && !_drawLabelOfEdge)
                drawUpdate("The weight of edges is updated and the label of edges isn't visable.");
            else if (_updateWeight)
                drawUpdate("The weight of edges is updated.");
            else
                drawUpdate("The label of edges isn't visable.");
        }
        window.display();
    }
}

void SFMLGraphVisualizer::drawNode(Node &node, sf::Color nodeColor) {
    sf::CircleShape Circle(NODERADIUS);
    Circle.setPosition(node.getPosX() - NODERADIUS, node.getPosY() - NODERADIUS);
    Circle.setFillColor(sf::Color::White);
    Circle.setOutlineColor(nodeColor);
    Circle.setOutlineThickness(5);

    window.draw(Circle);

    sf::Text Label(node.getKey(), font, 32);
    Label.setPosition(node.getPosX() - NODERADIUS / 2 + 5, node.getPosY() - NODERADIUS / 2 - 5);
    Label.setColor(sf::Color::Blue);

    window.draw(Label);
}

void SFMLGraphVisualizer::drawUpdate(string myString) {
    sf::Text text;
    text.setFont(font);
    text.setString(myString);
    text.setCharacterSize(24);
    text.setColor(sf::Color::Blue);

    window.draw(text);
}

void SFMLGraphVisualizer::drawEdge(Edge &edge, sf::Color color, double weight, int thickness, int arrowMagnitude) {
    sf::Vector2f p(edge.getStartNode()->getPosX(), edge.getStartNode()->getPosY());
    sf::Vector2f q(edge.getEndNode()->getPosX(), edge.getEndNode()->getPosY());

    // WINKEL BERECHNUNG
    const double PI = 3.141592653;
    double angle = atan2((double) p.y - q.y, (double) p.x - q.x);

    //  Berechne  verkuerzten  Pfeil
    q.x = (int) (q.x + NODERADIUS * cos(angle));
    q.y = (int) (q.y + NODERADIUS * sin(angle));
    p.x = (int) (p.x - NODERADIUS * cos(angle));
    p.y = (int) (p.y - NODERADIUS * sin(angle));

    sf::Vertex line[2] =
            {
                    sf::Vertex(sf::Vector2f(p.x, p.y), color),
                    sf::Vertex(sf::Vector2f(q.x, q.y), color)
            };

    //  thickness
    window.draw(line, 2, sf::Lines);

    if (_drawLabelOfEdge) {
        std::stringstream weightstring;
        weightstring << weight;
        sf::Text Labelweight(weightstring.str(), font, 32);
        int size = sqrt(pow(p.x - q.x, 2) + pow(p.y - q.y, 2));
        Labelweight.setPosition(p.x - (size / 2) * cos(angle) + 10 * sin(angle),
                                p.y - (size / 2) * sin(angle) + 10 * cos(angle));
        Labelweight.setColor(sf::Color::Blue);
        window.draw(Labelweight);
    }

// Erstes  Segment
    p.x = (int) (q.x + arrowMagnitude * cos(angle + PI / 8));
    p.y = (int) (q.y + arrowMagnitude * sin(angle + PI / 8));
    sf::Vertex first[2] =
            {
                    sf::Vertex(sf::Vector2f(p.x, p.y), color),
                    sf::Vertex(sf::Vector2f(q.x, q.y), color)
            };
    window.draw(first, 2, sf::Lines);

// Zweites  Segment
    p.x = (int) (q.x + arrowMagnitude * cos(angle - PI / 8));
    p.y = (int) (q.y + arrowMagnitude * sin(angle - PI / 8));

    sf::Vertex second[2] =
            {
                    sf::Vertex(sf::Vector2f(p.x, p.y), color),
                    sf::Vertex(sf::Vector2f(q.x, q.y), color)
            };
    window.draw(second, 2, sf::Lines);

}

void SFMLGraphVisualizer::highlightPath(List<Edge *> path) {
    for (unsigned int j = 0; j < path.getListSize(); j++) {
        drawEdge(*(path.getValueAtPos(j)), sf::Color::Green, path.getValueAtPos(j)->getWeight(), 1);
    }
}

int SFMLGraphVisualizer::getSelectedNode(DiGraph &graph, int mouseX, int mouseY) {
    int calcX, calcY;

    for (int nodeCounter = graph.getAllNodes().getListSize() - 1;
         nodeCounter >= 0; nodeCounter--) { //Damit überlappende Element nicht zum Problem werden......
        calcX = mouseX - graph.getAllNodes().getValueAtPos(nodeCounter)->getPosX();
        calcY = mouseY - graph.getAllNodes().getValueAtPos(nodeCounter)->getPosY();
        if (calcX < 0)
            calcX *= -1;
        if (calcY < 0)
            calcY *= -1;

        if (calcX < NODERADIUS && calcY < NODERADIUS)
            return nodeCounter;
    }
    return -1;

}

void SFMLGraphVisualizer::moveNode(DiGraph &graph, int &nodePos) {
    int mouseX = sf::Mouse::getPosition(window).x, mouseY = sf::Mouse::getPosition(window).y;

    if (nodePos < 0) {
        nodePos = getSelectedNode(graph, mouseX, mouseY);
    }

    if (nodePos >= 0) {
        graph.getAllNodes().getValueAtPos(nodePos)->setPosX(mouseX);
        graph.getAllNodes().getValueAtPos(nodePos)->setPosY(mouseY);
    }
}

int SFMLGraphVisualizer::changeName(DiGraph &graph) {
    int mouseX = sf::Mouse::getPosition(window).x, mouseY = sf::Mouse::getPosition(window).y;
    return getSelectedNode(graph, mouseX, mouseY);
}

void SFMLGraphVisualizer::calcNewDistance(DiGraph &graph, int &nodePos) {
    if (nodePos < 0)
        return;

    Node *node = graph.getAllNodes().getValueAtPos(nodePos), *secNode;
    int posX = node->getPosX();
    int posY = node->getPosY();

    float distance;
    int xValue, yValue;

    for (int i = 0; i < node->getEdges().getListSize(); i++) { // Alle Kanten von Node ausgehend
        secNode = node->getEdges().getValueAtPos(i)->getEndNode();

        xValue = secNode->getPosX() - posX;
        yValue = secNode->getPosY() - posY;

        distance = (float) (yValue * yValue) + (xValue * xValue);
        distance = sqrtf(distance);

        node->getEdges().getValueAtPos(i)->setWeight(distance);
    }

    for (int j = 0; j < graph.getAllNodes().getListSize(); j++) {
        secNode = graph.getAllNodes().getValueAtPos(j);
        if (secNode != node) {
            for (int i = 0; i < secNode->getEdges().getListSize(); ++i) {
                if (secNode->getEdges().getValueAtPos(i)->getEndNode() == node) {
                    xValue = secNode->getPosX() - posX;
                    yValue = secNode->getPosY() - posY;

                    distance = (float) (yValue * yValue) + (xValue * xValue);
                    distance = sqrtf(distance);
                    secNode->getEdges().getValueAtPos(i)->setWeight(distance);
                }
            }
        }
    }
}