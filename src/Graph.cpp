#pragma once

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <iostream>
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
        auto it = _graph.find(e.from);
        if (it != _graph.end()) {
            auto& edges = it->second;
            auto edge_it = std::remove_if(edges.begin(), edges.end(), [&e](const Edge& edge) {
                return edge.from == e.from && edge.to == e.to && edge.distance == e.distance;
                });
            if (edge_it != edges.end()) {
                edges.erase(edge_it, edges.end());
                return true;
            }
        }
        return false;
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
        auto it = _graph.find(e.from);
        if (it != _graph.end()) {
            const auto& edges = it->second;
            return std::any_of(edges.begin(), edges.end(), [&e](const Edge& edge) {
                return edge.from == e.from && edge.to == e.to && edge.distance == e.distance;
                });
        }
        return false;
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
    std::vector<Edge> shortest_path(const Vertex& from, const Vertex& to) const {
        std::unordered_map<Vertex, Distance> dist;
        std::unordered_map<Vertex, Vertex> predecessor;
        for (const auto& vertex : vertices()) {
            dist[vertex] = std::numeric_limits<Distance>::infinity();
            predecessor[vertex] = Vertex();
        }
        dist[from] = 0;
        for (size_t i = 0; i < order() - 1; ++i) {
            for (const auto& vertex : vertices()) {
                auto it = _graph.find(vertex);
                if (it != _graph.end()) {
                    const auto& edges = it->second;
                    for (const auto& edge : edges) {
                        if (dist[vertex] + edge.distance < dist[edge.to]) {
                            dist[edge.to] = dist[vertex] + edge.distance;
                            predecessor[edge.to] = vertex;
                        }
                    }
                }
            }
        }
        std::vector<Edge> path;
        for (Vertex current = to; current != Vertex(); current = predecessor[current]) {
            Vertex pred = predecessor[current];
            path.push_back({ pred, current, dist[current] });
        }
        std::reverse(path.begin(), path.end());
        return path;
    }
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
template<typename Vertex, typename Distance = double>
Vertex find_optimal_warehouse(const Graph<Vertex, Distance>& graph) {
    std::vector<Vertex> trade_points = graph.vertices();
    Vertex optimal_warehouse = Vertex();
    Distance min_avg_distance = std::numeric_limits<Distance>::max();
    for (const auto& trade_point : trade_points) {
        Distance total_distance = 0;
        for (const auto& destination : trade_points) {
            if (trade_point != destination) {
                std::vector<typename Graph<Vertex, Distance>::Edge> shortest_paths = graph.shortest_path(trade_point, destination);
                for (const auto& edge : shortest_paths) {
                    total_distance += edge.distance;
                }
            }
        }
        Distance avg_distance = total_distance / (trade_points.size() - 1);
        if (avg_distance < min_avg_distance) {
            min_avg_distance = avg_distance;
            optimal_warehouse = trade_point;
        }
    }
    return optimal_warehouse;
}