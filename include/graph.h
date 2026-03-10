#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <queue>
#include <limits>
#include <algorithm>

struct Edge {
    std::string to;
    int distance;
};

class CityGraph {
private:
    std::map<std::string, std::vector<Edge>> adjList;

public:

    void addRoute(const std::string& city1, const std::string& city2, int dist) {
        adjList[city1].push_back({city2, dist});
        adjList[city2].push_back({city1, dist});
    }


    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            return;
        }
        std::string c1, c2;
        int d;
        while (file >> c1 >> c2 >> d) {
            addRoute(c1, c2, d);
        }
    }


    void visualizeMap() {
        std::cout << "\n КАРТА УКРАЇНИ \n" << std::endl;
        for (auto const& [city, neighbors] : adjList) {
            std::cout << "  [" << city << "]" << std::endl;
            for (size_t i = 0; i < neighbors.size(); ++i) {

                std::string branch = (i == neighbors.size() - 1) ? "  \\-- " : "  |-- ";
                std::cout << branch << neighbors[i].to << " (" << neighbors[i].distance << " km)" << std::endl;
            }
            std::cout << std::endl;
        }
        std::cout << "=================================\n" << std::endl;
    }


    void findShortestPath(const std::string& start, const std::string& finish) {
        std::map<std::string, int> distances;
        std::map<std::string, std::string> previous;
        
        for (auto const& [city, _] : adjList) {
            distances[city] = std::numeric_limits<int>::max();
        }
        
        if (distances.find(start) == distances.end()) {
            std::cout << "Start city not found!" << std::endl;
            return;
        }

        distances[start] = 0;
        using pii = std::pair<int, std::string>;
        std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
        pq.push({0, start});

        while (!pq.empty()) {
            std::string u = pq.top().second;
            int d = pq.top().first;
            pq.pop();

            if (d > distances[u]) continue;
            if (u == finish) break;

            for (auto const& edge : adjList[u]) {
                if (distances[u] + edge.distance < distances[edge.to]) {
                    distances[edge.to] = distances[u] + edge.distance;
                    previous[edge.to] = u;
                    pq.push({distances[edge.to], edge.to});
                }
            }
        }

        if (distances.find(finish) == distances.end() || distances[finish] == std::numeric_limits<int>::max()) {
            std::cout << "Path to " << finish << " not found!" << std::endl;
        } else {
            std::cout << "Shortest distance from " << start << " to " << finish << ": " << distances[finish] << " km" << std::endl;
            std::vector<std::string> path;
            for (std::string v = finish; v != ""; v = previous[v]) path.size() > 0 ? path.push_back(v) : path.push_back(v); 

            path.clear();
            for (std::string v = finish; v != ""; v = previous[v]) {
                path.push_back(v);
            }
            std::reverse(path.begin(), path.end());
            
            std::cout << "Route: ";
            for (size_t i = 0; i < path.size(); ++i) {
                std::cout << path[i] << (i == path.size() - 1 ? "" : " -> ");
            }
            std::cout << std::endl;
        }
    }
};

#endif