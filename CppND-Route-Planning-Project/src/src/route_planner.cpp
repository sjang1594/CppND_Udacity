#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
    // Convert inputs to percentage:
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;

    //Store the nodes you find in the RoutePlanner's start_node and end_node attributes.
    start_node = &m_Model.FindClosestNode(start_x, start_y);
    end_node = &m_Model.FindClosestNode(end_x, end_y);
}


// Implement the CalculateHValue method.
// Use distance to the end_node for the h value. distance method is in route_model.h.
// Basically, find the distance to another node. (use the distance to the end_node for the h value.)
float RoutePlanner::CalculateHValue(RouteModel::Node const *node) {
    return node->distance(*(this->end_node));
}


// AddNeighbors method to expand the current node by adding all unvisited neighbors to the open list.
// Tips:
// - Use the FindNeighbors() method of the current_node to populate current_node.neighbors vector with all the neighbors.
// - For each node in current_node.neighbors, set the parent, the h_value, the g_value. 
// - Use CalculateHValue below to implement the h-Value calculation.
// - For each node in current_node.neighbors, add the neighbor to open_list and set the node's visited attribute to true.

void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {
    current_node->RouteModel::Node::FindNeighbors();
    for (RouteModel::Node* neighbor : current_node->neighbors){
        neighbor->parent = current_node;
        neighbor->g_value = current_node->g_value + current_node->distance(*neighbor);
        neighbor->h_value = this->CalculateHValue(neighbor);

        //Add the neibor to open_list and set the node's visited attribute to true.
        this->open_list.push_back(neighbor);
        neighbor->visited = true;
    }
}


// NextNode method to sort the open list and return the next node.
RouteModel::Node *RoutePlanner::NextNode() {
    //Sort the open_list according to the sum of the h vaue and g value by using helper function
    std::sort(this->open_list.begin(), this->open_list.end(),CompareFvals);
    //Create a pointer to the node in the list with the lowest sum
    RouteModel::Node* lowest_sum = this->open_list.back();
    //remove that node from the open_list
    this->open_list.pop_back();
    //Return pointer
    return lowest_sum;
}

// Just helper function for compare and sum up the h value and g value
// Use a same syntax from A* search lecture
// --------------------------------------------------------
// bool Compare(const vector<int> a, const vector<int> b){
// int f1 = a[2] + a[3] //f1 = g1 + h1
// int f2 = b[2] + b[3] //f2 = g2 + h2
// return f1 > f2;}
// --------------------------------------------------------
// Then this function will be used for NextNode like CellSort() function in A* Search Lecture
bool RouteModel::CompareFvals(RouteModel::Node *node_a, RouteModel::Node *node_b){
    return node_a->g_value + node_a->h_value > node_b->g_value + node_b->h_value;
}


// Complete the ConstructFinalPath method to return the final path found from your A* search.
// Tips:
// - This method should take the current (final) node as an argument and iteratively follow the 
//   chain of parents of nodes until the starting node is found.
// - For each node in the chain, add the distance from the node to its parent to the distance variable.
// - The returned vector should be in the correct order: the start node should be the first element
//   of the vector, the end node should be the last element.

std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
    // Create path_found vector
    distance = 0.0f;
    std::vector<RouteModel::Node> path_found;

    RouteModel::Node* cur_node = current_node;

    //If the current node(parent) is empty or null
    while(cur_node){
        //Add the current node to the parent. 
        path_found.push_back(*cur_node);

        //if the currnet node is parent, add distance component to its parent.
        if(cur_node->parent){
            this->distance += cur_node->distance(*cur_node->parent);
        }

        //Then update the current node.
        cur_node = cur_node->parent;
    }
    
    distance *= m_Model.MetricScale(); // Multiply the distance by the scale of the map to get meters.
    return path_found;

}


// TODO 7: Write the A* Search algorithm here.
// Tips:
// - Use the AddNeighbors method to add all of the neighbors of the current node to the open_list.
// - Use the NextNode() method to sort the open_list and return the next node.
// - When the search has reached the end_node, use the ConstructFinalPath method to return the final path that was found.
// - Store the final path in the m_Model.path attribute before the method exits. This path will then be displayed on the map tile.

void RoutePlanner::AStarSearch() {
    RouteModel::Node *current_node = nullptr;
    
    // TODO: Implement your solution here.

}