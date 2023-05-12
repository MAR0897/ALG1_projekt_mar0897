#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>

class Graph{
public: 
    class Vertex{                                  
    public:
        int vertex_number;                          ///<Aka vertex ID
        int state = 0;                              ///<0 = not found, 1 = processing, 2 = finished
        std::vector<Vertex*> edges;                 ///<Neighbors of the vertex
        Vertex(int vertex_number) {this->vertex_number = vertex_number;}
    };                                      
    std::vector<Vertex*> data;                      ///<Full graph storage
    std::vector<std::vector<Vertex*>> components;   ///<All components storage
    std::vector<Vertex*> largest_component;         ///<The largest component
    int coef_n = 0;                                 ///<GCC numerator
    int coef_d = 0;                                 ///<GCC denominator
public:
    Graph(const std::string &input_path);
    int get_or_create_vertex(std::unordered_map<int, int> &vertex_map, int val);
    void get_largest_component();
    void get_coefficient();
    void print();
    void print_largest_component();
private:
    std::vector<Vertex*> component_vertices;        ///<Vertices of one component; temp storage
};