#pragma once

#include <vector>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <iterator>
#include <functional>

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
        auto it = _grapg.find(v);
        if (it != _graph.end()) {
            _graph.erase(it);
            for (auto& pair : _graph) {
                auto& edges = pair.second;
                edges.erase(std::remove_if(edges.begin(), edges.end(), [&v](const Edg& e) {
                    return e.to == v;
                    }), edges.end());
            }
            return true;
        }
        return false;
    }
    std::vector<Vertex> vertices() const {
        
    }


    //проверка-добавление-удаление ребер
    void add_edge(const Vertex& from, const Vertex& to, const Distance& d) {}
    bool remove_edge(const Vertex& from, const Vertex& to) {}
    bool remove_edge(const Edge& e) {} //c учетом расстояния
    bool has_edge(const Vertex& from, const Vertex& to) const {}
    bool has_edge(const Edge& e) const {} //c учетом расстояния в Edge

    //получение всех ребер, выходящих из вершины
        std::vector<Edge> edges(const Vertex& vertex) {}

        size_t order() const {}//порядок 
        size_t degree(const Vertex& v) const {} //степень вершины


    //поиск кратчайшего пути
    std::vector<Edge> shortest_path(const Vertex& from, const Vertex& to) const {}
    //обход
    std::vector<Vertex>  walk(const Vertex& start_vertex)const {}
};