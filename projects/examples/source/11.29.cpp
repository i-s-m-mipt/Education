/////////////////////////////////////////////////////////////////////////////////////////

// support : www.cs.usfca.edu/~galles/visualization/BFS.html

/////////////////////////////////////////////////////////////////////////////////////////

#include <print>

/////////////////////////////////////////////////////////////////////////////////////////

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/named_function_params.hpp>

/////////////////////////////////////////////////////////////////////////////////////////

class Visitor : public boost::default_bfs_visitor
{
public :

    template < typename V, typename G > auto initialize_vertex(V vertex, G const & graph)
    {
        std::print("Visitor::initialize_vertex : vertex = {}\n", vertex);

        return boost::default_bfs_visitor::initialize_vertex(vertex, graph);
    }

//  -------------------------------------------------------------------------------------

    template < typename V, typename G > auto discover_vertex(V vertex, G const & graph)
    {
        std::print("Visitor::discover_vertex : vertex = {}\n", vertex);

        return boost::default_bfs_visitor::discover_vertex(vertex, graph);
    }

//  -------------------------------------------------------------------------------------

    template < typename V, typename G > auto examine_vertex(V vertex, G const & graph)
    {
        std::print("Visitor::examine_vertex : vertex = {}\n", vertex);

        return boost::default_bfs_visitor::examine_vertex(vertex, graph);
    }

//  -------------------------------------------------------------------------------------

    template < typename V, typename G > auto finish_vertex(V vertex, G const & graph)
    {
        std::print("Visitor::finish_vertex : vertex = {}\n", vertex);

        return boost::default_bfs_visitor::finish_vertex(vertex, graph);
    }

//  -------------------------------------------------------------------------------------

    template < typename E, typename G > auto examine_edge(E edge, G const & graph)
    {
        std::print("Visitor::examine_edge : edge = {}\n", edge);

        return boost::default_bfs_visitor::examine_edge(edge, graph);
    }

//  -------------------------------------------------------------------------------------

    template < typename E, typename G > auto tree_edge(E edge, G const & graph)
    {
        std::print("Visitor::tree_edge : edge = {}\n", edge);

        return boost::default_bfs_visitor::tree_edge(edge, graph);
    }

//  -------------------------------------------------------------------------------------

    template < typename E, typename G > auto non_tree_edge(E edge, G const & graph)
    {
        std::print("Visitor::non_tree_edge : edge = {}\n", edge);

        return boost::default_bfs_visitor::non_tree_edge(edge, graph);
    }

//  -------------------------------------------------------------------------------------

    template < typename E, typename G > auto gray_target(E edge, G const & graph)
    {
        std::print("Visitor::gray_target : edge = {}\n", edge);

        return boost::default_bfs_visitor::gray_target(edge, graph);
    }

//  -------------------------------------------------------------------------------------

    template < typename E, typename G > auto black_target(E edge, G const & graph)
    {
        std::print("Visitor::black_target : edge = {}\n", edge);

        return boost::default_bfs_visitor::black_target(edge, graph);
    }
};

/////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	boost::adjacency_list < boost::vecS, boost::vecS, boost::directedS > graph;

//  ---------------------------------------------------------------------------

    boost::add_edge(0, 2, graph);

    boost::add_edge(1, 1, graph);

    boost::add_edge(1, 3, graph);

    boost::add_edge(2, 1, graph);

    boost::add_edge(2, 3, graph);

    boost::add_edge(3, 1, graph);

    boost::add_edge(3, 4, graph);

    boost::add_edge(4, 0, graph);

    boost::add_edge(4, 1, graph);

//  ---------------------------------------------------------------------------

    boost::breadth_first_search(graph, 1, boost::visitor(Visitor()));
}

/////////////////////////////////////////////////////////////////////////////////////////