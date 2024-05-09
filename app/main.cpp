#include <Graph.cpp>

int main() {
	Graph<int, double> graph1;
	graph1.add_vertex(1);
	graph1.add_vertex(2);
	graph1.add_vertex(3);
	graph1.add_vertex(4);
	graph1.add_edge(1, 2, 10.0);
	graph1.add_edge(1, 3, 10.0);
	graph1.add_edge(1, 4, 10.0);
	graph1.add_edge(4, 3, 5.0);
	graph1.remove_edge(graph1.edges(1)[0]);
	auto vertices = graph1.vertices();
	for (auto i: vertices) {
		std::cout << i << std::endl;
	}
	graph1.remove_vertex(1);
	auto vertices1 = graph1.vertices();
	for (auto i : vertices1) {
		std::cout << i << std::endl;
	}
	std::cout << graph1.order() << std::endl;
	std::cout << graph1.degree(1) << std::endl;
	std::cout << graph1.degree(2) << std::endl;
	std::cout << graph1.degree(3) << std::endl;
	std::cout << graph1.degree(4) << std::endl;
	std::cout << "______________________________" << std::endl;
	graph1.add_edge(2, 4, 5);
	graph1.add_edge(4, 3, 6);
	auto walk = graph1.walk(2);
	for (auto i : walk) {
		std::cout << i << std::endl;
	}
}