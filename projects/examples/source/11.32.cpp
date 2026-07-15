/////////////////////////////////////////////////////////////////////////////////////

// chapter : Programming with Algorithms

/////////////////////////////////////////////////////////////////////////////////////

// content : Weighted Graphs
//
// content : Dijkstra Shortest Paths Algorithm
//
// content : Time Complexity O(E*log(V))

/////////////////////////////////////////////////////////////////////////////////////

// support : https://www.cs.usfca.edu/~galles/visualization/Dijkstra.html

/////////////////////////////////////////////////////////////////////////////////////

#include <array>
#include <cassert>
#include <iterator>

/////////////////////////////////////////////////////////////////////////////////////

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/named_function_params.hpp>

/////////////////////////////////////////////////////////////////////////////////////

int main()
{
    using graph_t = boost::adjacency_list
    <
        boost::vecS, boost::vecS, boost::directedS,

        boost::no_property, boost::property < boost::edge_weight_t, int >
    > ;

//  ---------------------------------------------------------------------------------

    graph_t graph;

//  ---------------------------------------------------------------------------------

    boost::add_edge(0, 1, 1, graph);

    boost::add_edge(1, 2, 1, graph);

    boost::add_edge(1, 3, 1, graph);

    boost::add_edge(2, 4, 1, graph);

    boost::add_edge(3, 4, 1, graph);

    boost::add_edge(4, 5, 1, graph);

//  ---------------------------------------------------------------------------------

	std::array < int, 6 > array = {};

//  ---------------------------------------------------------------------------------

	boost::dijkstra_shortest_paths(graph, 0, boost::distance_map(std::begin(array)));

//  ---------------------------------------------------------------------------------

	assert((array == std::array < int, 6 > ({ 0, 1, 2, 2, 3, 4 })));
}

/////////////////////////////////////////////////////////////////////////////////////