#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		boost::adjacency_list < boost::vecS, boost::vecS, boost::directedS > graph;

		auto vertex_1 = boost::add_vertex(graph);
		
		auto vertex_2 = boost::add_vertex(graph);

		auto vertex_3 = boost::add_vertex(graph);

		auto vertices = boost::vertices(graph);

		std::ranges::for_each(vertices.first, vertices.second, []([[maybe_unused]] auto vertex){});

		assert(boost::add_edge(vertex_1, vertex_2, graph).second);

		assert(boost::add_edge(vertex_2, vertex_1, graph).second);

		assert(boost::add_edge(vertex_2, vertex_3, graph).second);

		assert(boost::add_edge(vertex_3, vertex_1, graph).second);

		auto edges = boost::edges(graph);

		std::ranges::for_each(edges.first, edges.second, []([[maybe_unused]] auto edge){});

		auto [begin, end] = boost::adjacent_vertices(vertex_2, graph);

		assert(std::distance(begin, end) == 2);

		auto out_edges = boost::out_edges(vertex_2, graph);

		std::ranges::for_each(out_edges.first, out_edges.second, []([[maybe_unused]] auto edge){});
	}

//  -----------------------------------------------------------------------------------------------

	{
		boost::adjacency_list < boost::setS, boost::vecS, boost::directedS, int, int > graph;

		auto vertex_1 = boost::add_vertex(graph); graph[vertex_1] = 1;

		auto vertex_2 = boost::add_vertex(graph); graph[vertex_2] = 2;		

		auto edge = boost::add_edge(vertex_1, vertex_2, graph).first; graph[edge] = 3;

		std::cout << "main : graph = "; boost::write_graphviz(std::cout, graph);
	}
}