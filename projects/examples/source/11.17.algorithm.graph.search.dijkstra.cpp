#include <array>
#include <cassert>
#include <iterator>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

int main()
{
    using edge_property_t = boost::property < boost::edge_weight_t, unsigned int > ;

    boost::adjacency_list 
    < 
        boost::vecS, 
        boost::vecS, boost::directedS, boost::no_property, edge_property_t 
    >
    graph;

    boost::add_edge(1, 3, 1, graph);
    boost::add_edge(2, 2, 2, graph);
    boost::add_edge(2, 4, 3, graph);
    boost::add_edge(3, 2, 4, graph);
    boost::add_edge(3, 4, 5, graph);
    boost::add_edge(4, 2, 6, graph);
    boost::add_edge(4, 5, 7, graph);
    boost::add_edge(5, 1, 8, graph);
    boost::add_edge(5, 2, 9, graph);

	std::array < unsigned int, 5 > distances = {};

    auto map = boost::distance_map(std::begin(distances));

	boost::dijkstra_shortest_paths(graph, 1, map);

    std::array < unsigned int, 5 > result = { 0, 5, 1, 6, 13 };

	assert(distances == result);
}