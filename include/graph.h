#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
struct Edge {
    std::string to_city;
};
struct City {
    float x;
    float y;
    std::vector<Edge> neighbors;
};
class CityGraph {
public:
    std::map<std::string, City> cities;
    void addCity(std::string name, float x, float y) {
        City newCity;
        newCity.x = x;
        newCity.y = y;
        cities[name] = newCity;
    }
    void addEdge(std::string from, std::string to) {
        Edge newEdge;
        newEdge.to_city = to;
        cities[from].neighbors.push_back(newEdge);
    }
};