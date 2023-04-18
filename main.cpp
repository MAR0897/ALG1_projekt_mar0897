#include <iostream>
#include <fstream>
#include "graph.h"

int main(int argv, char** argc){

    Graph graph(argc[1]);
    std::cout<<"Graph was successfully loaded"<<std::endl;

    graph.get_largest_component();
    std::cout<<"The largest component was found"<<std::endl;
    if(graph.largest_component.size()<30) graph.print_largest_component();

    graph.get_coefficient();
    std::cout<<"The global clustering coefficient of the graph is: "<<graph.coef_n<<"/"<<graph.coef_d<<std::endl;
    std::cout<<"Which is: "<<float(graph.coef_n)/float(graph.coef_d)<<std::endl;

return 0;
}