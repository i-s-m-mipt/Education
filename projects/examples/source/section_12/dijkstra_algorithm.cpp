#include <array>
#include <iostream>
#include <iterator>
#include <utility>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

int main()
{
	using vector = boost::vecS; using directed = boost::directedS; // note: directed graph

    using graph_t = boost::adjacency_list < vector, vector, directed,
		boost::no_property, 
		boost::   property < boost::edge_weight_t, unsigned int > > ;

    constexpr std::size_t size = 9; // note: number of edges

	constexpr std::array < std::pair < std::size_t, std::size_t > , size > data =
	{
		std::make_pair(0, 2),
		std::make_pair(1, 1),
		std::make_pair(1, 3),
		std::make_pair(2, 1),
		std::make_pair(2, 3),
		std::make_pair(3, 1),
        std::make_pair(3, 4),
        std::make_pair(4, 0),
        std::make_pair(4, 1),
	};

	constexpr std::array < unsigned int, size > weights = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	const graph_t graph(std::cbegin(data), std::cend(data), std::cbegin(weights), size);

	std::array < unsigned int, 5 > distances; // note: number of vertexes

	boost::dijkstra_shortest_paths(graph, 0, boost::distance_map(std::begin(distances))); // note: O(E*log(V)) complexity

	for (auto distance : distances) std::cout << distance << ' ';

    std::cout << std::endl;

    return 0;
}