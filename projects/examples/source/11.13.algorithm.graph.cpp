#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>

int main()
{
	using default_graph_t = boost::adjacency_list < boost::vecS, boost::vecS, boost::directedS > ;

	default_graph_t default_graph;

//  ================================================================================================

	const auto vertex_1 = boost::add_vertex(default_graph);
	const auto vertex_2 = boost::add_vertex(default_graph);
	const auto vertex_3 = boost::add_vertex(default_graph);

	const auto vertices = boost::vertices(default_graph);

	std::ranges::for_each(vertices.first, vertices.second, [](auto vertex){ std::cout << vertex << std::endl; });

//  ================================================================================================

	assert(boost::add_edge(vertex_1, vertex_2, default_graph).second);
	assert(boost::add_edge(vertex_2, vertex_1, default_graph).second);
	assert(boost::add_edge(vertex_2, vertex_3, default_graph).second);
	assert(boost::add_edge(vertex_3, vertex_1, default_graph).second);

	const auto edges = boost::edges(default_graph);

	std::ranges::for_each(edges.first, edges.second, [](auto edge){ std::cout << edge << std::endl; });

//  ================================================================================================

	const auto [begin, end] = boost::adjacent_vertices(vertex_2, default_graph);

	assert(std::distance(begin, end) == 2);

//  ================================================================================================

	const auto out_edges = boost::out_edges(vertex_2, default_graph);

	std::ranges::for_each(out_edges.first, out_edges.second, [&default_graph](auto edge)
	{ 
		std::cout << boost::target(edge, default_graph) << std::endl;
	});

//  ================================================================================================

	using custom_graph_t = boost::adjacency_list < boost::setS, boost::vecS, boost::directedS, int, int > ;
	
	custom_graph_t custom_graph;

//  ================================================================================================

	const auto vertex_u = boost::add_vertex(custom_graph);
	const auto vertex_v = boost::add_vertex(custom_graph); 

	custom_graph[vertex_u] = 1;
	custom_graph[vertex_v] = 2;

	const auto edge_u_v = boost::add_edge(vertex_u, vertex_v, custom_graph).first; 

	custom_graph[edge_u_v] = 3;

//  ================================================================================================

	boost::write_graphviz(std::cout, custom_graph); // note: suppress warning 4458 im MSVC

	return 0;
}