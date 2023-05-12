#include <iostream>
#include <fstream>
#include "graph.h"

int main(int argv, char** argc){

    //First we load the graph from a txt file
    Graph graph("graf.txt");
    std::cout<<"Graph was successfully loaded"<<std::endl;

    //Then, we extract the largest component of the graph
    graph.get_largest_component();
    std::cout<<"The largest component was found"<<std::endl;
    if(graph.largest_component.size()<20) graph.print_largest_component();

    //Finally we calculate the global clustering coefficient of the largest component
    graph.get_coefficient();
    std::cout<<"The global clustering coefficient of the graph is: "<<graph.coef_n<<"/"<<graph.coef_d<<std::endl;
    std::cout<<"Which is: "<<float(graph.coef_n)/float(graph.coef_d)<<std::endl;

return 0;
}