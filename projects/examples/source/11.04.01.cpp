#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>

///////////////////////////////////////////////////////////////////////////////

int main()
{
	boost::adjacency_list < boost::vecS, boost::vecS, boost::directedS > graph;

//  ---------------------------------------------------------------------------

	auto vertex_1 = boost::add_vertex(graph);
		
	auto vertex_2 = boost::add_vertex(graph);

	auto vertex_3 = boost::add_vertex(graph);

//  ---------------------------------------------------------------------------

	auto [begin_1, end_1] = boost::vertices(graph);

//  ---------------------------------------------------------------------------

	assert(std::distance(begin_1, end_1) == 3);

//  ---------------------------------------------------------------------------

	assert(boost::add_edge(vertex_1, vertex_2, graph).second);

	assert(boost::add_edge(vertex_2, vertex_1, graph).second);

	assert(boost::add_edge(vertex_2, vertex_3, graph).second);

	assert(boost::add_edge(vertex_3, vertex_1, graph).second);

//  ---------------------------------------------------------------------------

	auto [begin_2, end_2] = boost::edges(graph);

//  ---------------------------------------------------------------------------

	assert(std::distance(begin_2, end_2) == 4);

//  ---------------------------------------------------------------------------

	auto [begin_3, end_3] = boost::adjacent_vertices(vertex_2, graph);

//  ---------------------------------------------------------------------------

	assert(std::distance(begin_3, end_3) == 2);

//  ---------------------------------------------------------------------------

	auto [begin_4, end_4] = boost::out_edges(vertex_2, graph);

//  ---------------------------------------------------------------------------

	assert(std::distance(begin_4, end_4) == 2);

//  ---------------------------------------------------------------------------

	std::cout << "main : graph = "; boost::write_graphviz(std::cout, graph);
}