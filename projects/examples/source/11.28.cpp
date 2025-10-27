///////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <iostream>
#include <iterator>
#include <print>

///////////////////////////////////////////////////////////////////////////////

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

	auto vertices = boost::vertices(graph);

//  ---------------------------------------------------------------------------

	assert(std::distance(vertices.first, vertices.second) == 3);

//  ---------------------------------------------------------------------------

	assert(boost::add_edge(vertex_1, vertex_2, graph).second);

	assert(boost::add_edge(vertex_2, vertex_1, graph).second);

	assert(boost::add_edge(vertex_2, vertex_3, graph).second);

	assert(boost::add_edge(vertex_3, vertex_1, graph).second);

//  ---------------------------------------------------------------------------

	auto edges = boost::edges(graph);

//  ---------------------------------------------------------------------------

	assert(std::distance(edges.first, edges.second) == 4);

//  ---------------------------------------------------------------------------

	std::print("main : graph = "); boost::write_graphviz(std::cout, graph);
}

///////////////////////////////////////////////////////////////////////////////