#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "graph.h"

/**
 * Loads the graph from a file to data storage.
 * 
 * 1. Reads from the file iteratively
 * 2. In each iteration tries to find the vertex in the unordered map, if not found, creates a new vertex, if found, puts its neighbor to the storage
 * (the unordered map stores the vertex number value read from the file and the indexes of the vertices in the data storage)
*/
Graph::Graph(const std::string &input_path){
    std::ifstream input_file; input_file.open(input_path);
    int a, b, index_a, index_b;
    std::unordered_map<int, int> vertex_map;

    while (input_file >> a >> b){
        auto it_a = vertex_map.find(a);
        auto it_b = vertex_map.find(b);
        if (it_a == vertex_map.end()) {//vertex a not found, create a new vertex
            Vertex* new_vertex = new Vertex(a);
            data.push_back(new_vertex);
            index_a = data.size() - 1;
            vertex_map[a] = index_a;
        } 
        else index_a = it_a->second;//vertex a found, get its index from data storage
        if (it_b == vertex_map.end()){//vertex b not found, create a new vertex
            Vertex* new_vertex = new Vertex(b);
            data.push_back(new_vertex);
            index_b = data.size() - 1;
            vertex_map[b] = index_b;
        } 
        else index_b = it_b->second;//vertex b found, get its index from data storage
        //add the edges
        data[index_a]->edges.push_back(data[index_b]);
        data[index_b]->edges.push_back(data[index_a]);
    }
}

/**
 * Finds the largest component of the graph using BFS
 * 
 * 1. Finds vertex that has not been visited yet, changes its state and puts it in the temp component storage
 * 2. Puts it in the vector of not finished vertices
 * 3. Iterates over the vector elements until it reaches its end
 * 4. In each iteration puts the neighbor vertices into the vector, if not visited yet and changes its state and puts it in the temp component storage
 * 5. After one component has been found, pushes it to the all component storage
 * 6. After the whole graph has been visited, compares the sizes of the components and selects the largest of them
*/
void Graph::get_largest_component(){
    for (int v = 0; v<data.size(); v++){
        if(data[v]->state == 0){
            Vertex *current = data[v];
            std::vector<Vertex*> queue;
            queue.push_back(current);
            current->state = 1;
            component_vertices.push_back(current);

            for (int i = 0; i<queue.size(); i++){   
                current = queue[i];
                current->state = 2;
                for (int j = 0; j<current->edges.size(); j++){
                    if (current->edges[j]->state == 0){
                        component_vertices.push_back(current->edges[j]);
                        queue.push_back(current->edges[j]);
                        current->edges[j]->state = 1;
                    }
                }
            }
            components.push_back(component_vertices);
            component_vertices.clear();
        }
    }
    auto max_it = std::max_element(components.begin(), components.end(), [](const auto& v1, const auto& v2) {return v1.size() < v2.size();});
    largest_component = *max_it;
}

/**
 * Prints the largest component of the graph.
 */ 
void Graph::print_largest_component(){
    std::cout << "The largest component is: ";
    for (auto i: largest_component) std::cout << i->vertex_number << ", "; std::cout << std::endl;
}

/**
 * Computes the global clustering coefficient of the largest component.
 * 
 * 1. computes the denominator; the number of all triplets
 *      - coef_d += number_of_edges*(number_of_edges-1)) at each vertex
 * 2. computes the numerator; the number of triangles (closed triplets)
 *      - takes each vertex, its neighbors its neighbors+1 and checks if there is neighbor2 (n2) in the neighbors of neighbor1 (n1)
 */
void Graph::get_coefficient(){ 
    for (int i = 0; i<largest_component.size(); i++) if(largest_component[i]->edges.size()>=2) 
        coef_d += (largest_component[i]->edges.size()*(largest_component[i]->edges.size()-1));

    int triangle_count = 0;
    for (auto v : largest_component){
        for (int i = 0; i < v->edges.size(); i++){
            auto n1 = v->edges[i];
            for (int j = i+1; j < v->edges.size(); j++){
                auto n2 = v->edges[j];
                if (std::find(n1->edges.begin(), n1->edges.end(), n2) != n1->edges.end()) triangle_count++;
            }
        }
    }
    coef_n = 2*triangle_count;
}

/**
 * Prints the whole graph (NOT OPTIMIZED).
 */
void Graph::print(){
    for (const auto& vertex : data) std::cout << vertex->vertex_number << " ";
    std::cout << std::endl;
    for (int i = 0; i<data.size()-1; i++){
        for (int j = 0; j<data.size(); j++){
            if (i < data[j]->edges.size()) std::cout << data[j]->edges[i]->vertex_number << " ";
            else std::cout<<"X ";
        }
        std::cout << std::endl;
    }
}