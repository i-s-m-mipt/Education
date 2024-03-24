#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>

int main()
{
	using vector = boost::vecS; using directed = boost::directedS;

	using default_graph_t = boost::adjacency_list < vector, vector, directed > ;

	default_graph_t default_graph;

	const auto vertex_1 = boost::add_vertex(default_graph);
	const auto vertex_2 = boost::add_vertex(default_graph);
	const auto vertex_3 = boost::add_vertex(default_graph);

	const auto vertices = boost::vertices(default_graph);

	std::ranges::for_each(vertices.first, vertices.second, [](auto vertex){ std::cout << vertex << std::endl; });

	assert(boost::add_edge(vertex_1, vertex_2, default_graph).second);
	assert(boost::add_edge(vertex_2, vertex_1, default_graph).second);
	assert(boost::add_edge(vertex_2, vertex_3, default_graph).second);
	assert(boost::add_edge(vertex_3, vertex_1, default_graph).second);

	assert(boost::add_edge(vertex_1, vertex_2, default_graph).second == false);

	const auto edges = boost::edges(default_graph);

	std::ranges::for_each(edges.first, edges.second, [](auto edge){ std::cout << edge << std::endl; });

	const auto [begin, end] = boost::adjacent_vertices(vertex_2, default_graph);

	assert(std::distance(begin, end) == 2);

	const auto out_edges = boost::out_edges(vertex_2, default_graph);

	std::ranges::for_each(out_edges.first, out_edges.second, [&default_graph](auto edge)
	{ 
		std::cout << boost::target(edge, default_graph) << std::endl;
	});

	using set = boost::setS;

	using custom_graph_t = boost::adjacency_list < set, vector, directed, int, int > ;
	
	custom_graph_t custom_graph;

	const auto u = boost::add_vertex(custom_graph);
	const auto v = boost::add_vertex(custom_graph); 

	const auto e = boost::add_edge(u, v, custom_graph).first; 
	
	custom_graph[u] = 1;
	custom_graph[v] = 2;
	custom_graph[e] = 3;

	boost::write_graphviz(std::cout, custom_graph); // note: suppress warning 4458 im MSVC

	return 0;
}