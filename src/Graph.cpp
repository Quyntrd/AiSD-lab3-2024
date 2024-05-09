﻿#pragma once

#include <vector>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <iterator>
#include <functional>
#include <iostream>
#include<unordered_set>
#include <queue>

template<typename Vertex, typename Distance = double>
class Graph {
public: 
    struct Edge {
        Vertex from;
        Vertex to;
        Distance distance;
        Edge(const Vertex& f, const Vertex& t, const Distance& d) : from(f), to(t), distance(d) {}
    };
private:
    std::unordered_map<Vertex, std::vector<Edge>> _graph;
public:
    bool has_vertex(const Vertex& v) const {
        return _graph.find(v) != _graph.end();
    }
    void add_vertex(const Vertex& v) {
        if (!has_vertex(v)) {
            _graph[v] = std::vector<Edge>();
        }
    }
    bool remove_vertex(const Vertex& v) {
        auto it = _graph.find(v);
        if (it != _graph.end()) {
            _graph.erase(it);
            for (auto& pair : _graph) {
                auto& edges = pair.second;
                edges.erase(std::remove_if(edges.begin(), edges.end(), [&v](const Edge& e) {
                    return e.to == v;
                    }), edges.end());
            }
            return true;
        }
        return false;
    }
    std::vector<Vertex> vertices() const {
        std::vector<Vertex> result;
        for (const auto& pair: _graph) {
            result.push_back(pair.first);
        }
        return result;
    }
    void add_edge(const Vertex& from, const Vertex& to, const Distance& d) {
        if (has_vertex(from) && has_vertex(to)) {
            _graph[from].push_back(Edge(from, to, d));
        }
    }
    bool remove_edge(const Vertex& from, const Vertex& to) {
        auto it = _graph.find(from);
        if (it != _graph.end()) {
            auto& edges = it->second;
            auto edge_it = std::remove_if(edges.begin(), edges.end(), [&to](const Edge& e) {return e.to == to; });
            if (edge_it != edges.end()) {
                edges.erase(edge_it, edges.end());
                return true;
            }
        }
        return false;
    }
    bool remove_edge(const Edge& e) {
        return remove_edge(e.from, e.to);
    }
    bool has_edge(const Vertex& from, const Vertex& to) const {
        auto it = _graph.find(from);
        if (it != _graph.end()) {
            const auto& edges = it->second;
            return std::any_of(edges.begin(), edges.end(), [&to](const Edge& e) {return e.to == to; });
        }
        return false;    
    }
    bool has_edge(const Edge& e) const {
        return has_edge(e.from, e.to);
    }
    std::vector<Edge> edges(const Vertex& vertex) {
        auto it = _graph.find(vertex);
        if (it != _graph.end()) {
            return it->second;
        }
        return std::vector<Edge>();
    }
    size_t order() const {
        return _graph.size();
    }
    size_t degree(const Vertex& v) const {
        auto it = _graph.find(v);
        if (it != _graph.end()) {
            return it->second.size();
        }
        return 0;
    }
    //поиск кратчайшего пути
    std::vector<Edge> shortest_path(const Vertex& from, const Vertex& to) const {}
    //обход
    std::vector<Vertex> walk(const Vertex& start_vertex) const {
        std::vector<Vertex> result;
        if (!has_vertex(start_vertex)) {
            return result;
        }
        std::unordered_map<Vertex, bool> visited;
        std::queue<Vertex> queue;

        visited[start_vertex] = true;
        queue.push(start_vertex);
        while (!queue.empty()) {
            Vertex current = queue.front();
            queue.pop();
            result.push_back(current);
            // Перебираем ребра для текущей вершины
            for (const auto& pair : _graph) {
                const auto& edges = pair.second;
                if (pair.first == current) {
                    for (const auto& edge : edges) {
                        if (!visited[edge.to]) {
                            visited[edge.to] = true;
                            queue.push(edge.to);
                        }
                    }
                    break;
                }
            }
        }
        return result;
    }
};