#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <iterator>
#include <utility>

#include <boost/array.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/named_function_params.hpp>

int main()
{
	using    set = boost::setS; using   directed = boost::  directedS;
	using vector = boost::vecS; using undirected = boost::undirectedS;

	using default_graph_t = boost::adjacency_list < set, vector, directed > ;

	default_graph_t default_graph;

	auto vertex_1 = boost::add_vertex(default_graph);
	auto vertex_2 = boost::add_vertex(default_graph);
	auto vertex_3 = boost::add_vertex(default_graph);

	using vertex_t = default_graph_t::vertex_descriptor;

	auto vertices = boost::vertices(default_graph);

	std::ranges::copy(vertices.first, vertices.second, std::ostream_iterator < vertex_t > (std::cout, "\n"));

	assert(boost::add_edge(vertex_1, vertex_2, default_graph).second);
	assert(boost::add_edge(vertex_2, vertex_1, default_graph).second);
	assert(boost::add_edge(vertex_2, vertex_3, default_graph).second);
	assert(boost::add_edge(vertex_3, vertex_1, default_graph).second);

	assert(boost::add_edge(vertex_1, vertex_2, default_graph).second == false);

	using edge_t = default_graph_t::edge_descriptor;

	auto edges = boost::edges(default_graph);

	std::ranges::copy(edges.first, edges.second, std::ostream_iterator < edge_t > (std::cout, "\n"));

	auto [begin, end] = boost::adjacent_vertices(vertex_2, default_graph);

	assert(std::distance(begin, end) == 2);

	auto out_edges = boost::out_edges(vertex_2, default_graph);

	std::ranges::for_each(out_edges.first, out_edges.second, [&default_graph](edge_t edge)
	{ 
		std::cout << boost::target(edge, default_graph) << std::endl;
	});

	using custom_graph_t = boost::adjacency_list < vector, vector, directed, int, int > ;
	
	custom_graph_t custom_graph;

	auto u = boost::add_vertex(custom_graph);
	auto v = boost::add_vertex(custom_graph); 

	auto e = boost::add_edge(u, v, custom_graph).first; 
	
	custom_graph[u] = 1;
	custom_graph[v] = 2;
	custom_graph[e] = 3;

	boost::write_graphviz(std::cout, custom_graph); // note: suppress warning 4458

	const std::size_t size = 6;

	std::array < std::pair < std::size_t, std::size_t >, size > data =
	{
		std::make_pair(0, 1),
		std::make_pair(1, 2),
		std::make_pair(1, 3),
		std::make_pair(2, 4),
		std::make_pair(3, 4),
		std::make_pair(4, 5)
	};

	std::array < double, size > weights = { 1.0, 2.0, 1.0, 2.0, 1.0, 1.0 };

	using weighted_graph_t = boost::adjacency_list < vector, vector, undirected,
		boost::no_property, 
		boost::   property < boost::edge_weight_t, double > > ;

	weighted_graph_t weighted_graph(std::begin(data), std::end(data), std::begin(weights), size);

	boost::array < std::size_t, size > directions; // note: only this container works here

	boost::dijkstra_shortest_paths(weighted_graph, 5, boost::predecessor_map(std::begin(directions)));

	for (std::size_t p = 0; p != 5; std::cout << (p = directions[p]) << std::endl);

	return 0;
}