#include <iostream>
#include "SFMLGraphVisualizer.h"
#include "FileInterface.h"

#include <string>
#include <cstring>

using namespace std;


int main() {
    FileInterface *file = new FileInterface("test.txt", true); //Please inserte the name of the file in string format. True or false will either create all opposite edges to the known ones in the file or not.
    try {
        DiGraph graph;

        SFMLGraphVisualizer graphviz;
        graph.setVisualizer(&graphviz);

        file->setGraph(&graph);
        file->readFile();
        graph.visualize();
        
    } catch (MyExecption execption) {
        cout << execption.getMessage() << endl;
    }
    delete file;

    return 0;
}