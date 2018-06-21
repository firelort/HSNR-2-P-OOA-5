//
// Created by hartings on 04.06.18.
//

#ifndef OOA4_GRAPHVISUALIZER_H
#define OOA4_GRAPHVISUALIZER_H
#include "DiGraph.h"
#include "List.h"

class DiGraph;
class GraphVisualizer{
protected:
    bool _updateWeight;
public:
    virtual void visualize(DiGraph &graph) = 0;
    virtual void highlightPath(List<Edge *> path) = 0;
};

#endif //OOA4_GRAPHVISUALIZER_H
