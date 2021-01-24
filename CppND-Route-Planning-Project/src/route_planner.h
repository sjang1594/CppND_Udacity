#ifndef ROUTE_PLANNER_H
#define ROUTE_PLANNER_H

#include <iostream>
#include <vector>
#include <string>
#include "route_model.h"


class RoutePlanner {
  public:
    RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y);
    // Add public variables or methods declarations here.
    float GetDistance() const {return distance;}
    void AStarSearch();
    
    void AddNeighbors(RouteModel::Node *current_node);
    float CalculateHValue(RouteModel::Node const *node);
    std::vector<RouteModel::Node> ConstructFinalPath(RouteModel::Node *current_node);
    RouteModel::Node *NextNode();
    
    
  private:
    // Add private variables or methods declarations here.
    
    RouteModel::Node *start_node;
    RouteModel::Node *end_node;
    std::vector<RouteModel::Node*> open_list;
    float distance = 0.0f;
    
    RouteModel &m_Model;
};

#endif