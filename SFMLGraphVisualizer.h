//
// Created by hartings on 23.05.18.
//

#ifndef OOA3_SFMLGRAPHVISUALIZER_H
#define OOA3_SFMLGRAPHVISUALIZER_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GraphVisualizer.h"

class SFMLGraphVisualizer : public GraphVisualizer {
private:
    sf::RenderWindow window;
    sf::Font font;
    int getSelectedNode(DiGraph &graph, int mouseX, int mouseY);
    void moveNode (DiGraph &graph, int &nodePos);
    int changeName(DiGraph &graph);
    void drawUpdate();
    void calcNewDistance(DiGraph &graph, int &nodePos);
public:
    SFMLGraphVisualizer();
    void visualize(DiGraph &graph);
    void drawNode(Node &node, sf::Color nodeColor);
    void drawEdge(Edge &edge, sf::Color color, double weight, int thickness = 1, int arrowMagnitude = 20);
    void highlightPath(List<Edge *> path);
};
#endif //OOA3_SFMLGRAPHVISUALIZER_H
