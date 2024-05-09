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
	std::cout << graph1.order() << std::endl;
	std::cout << graph1.degree(1) << std::endl;
	std::cout << graph1.degree(2) << std::endl;
	std::cout << graph1.degree(3) << std::endl;
	std::cout << graph1.degree(4) << std::endl;
}