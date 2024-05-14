#include <array>
#include <iostream>
#include <iterator>
#include <utility>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

int main()
{
    boost::adjacency_list < boost::vecS, boost::vecS, boost::directedS, boost::no_property, 
        
        boost::property < boost::edge_weight_t, unsigned int > > graph;

    boost::add_edge(0, 2, 1, graph);
    boost::add_edge(1, 1, 2, graph);
    boost::add_edge(1, 3, 3, graph);
    boost::add_edge(2, 1, 4, graph);
    boost::add_edge(2, 3, 5, graph);
    boost::add_edge(3, 1, 6, graph);
    boost::add_edge(3, 4, 7, graph);
    boost::add_edge(4, 0, 8, graph);
    boost::add_edge(4, 1, 9, graph);

	std::array < unsigned int, 5 > distances;

    const auto map = boost::distance_map(std::begin(distances));

	boost::dijkstra_shortest_paths(graph, 0, map); // complexity: O(E * log(V))

	for (auto distance : distances) std::cout << distance << ' ';

    std::cout << std::endl;

    return 0;
}