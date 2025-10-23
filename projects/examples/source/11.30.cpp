///////////////////////////////////////////////////////////////////////////////////////////

// support : www.cs.usfca.edu/~galles/visualization/DFS.html

///////////////////////////////////////////////////////////////////////////////////////////

#include <print>

///////////////////////////////////////////////////////////////////////////////////////////

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/named_function_params.hpp>

///////////////////////////////////////////////////////////////////////////////////////////

class Visitor : public boost::default_dfs_visitor
{
public :

    template < typename V, typename G > void initialize_vertex(V vertex, G const & graph)
    {
        std::print("Visitor::initialize_vertex : vertex = {}\n", vertex);

        boost::default_dfs_visitor::initialize_vertex(vertex, graph);
    }

//  ---------------------------------------------------------------------------------------

    template < typename V, typename G > void start_vertex(V vertex, G const & graph)
    {
        std::print("Visitor::start_vertex : vertex = {}\n", vertex);

        boost::default_dfs_visitor::start_vertex(vertex, graph);
    }

//  ---------------------------------------------------------------------------------------

    template < typename V, typename G > void discover_vertex(V vertex, G const & graph)
    {
        std::print("Visitor::discover_vertex : vertex = {}\n", vertex);

        boost::default_dfs_visitor::discover_vertex(vertex, graph);
    }

//  ---------------------------------------------------------------------------------------

    template < typename V, typename G > void finish_vertex(V vertex, G const & graph)
    {
        std::print("Visitor::finish_vertex : vertex = {}\n", vertex);

        boost::default_dfs_visitor::finish_vertex(vertex, graph);
    }

//  ---------------------------------------------------------------------------------------

    template < typename E, typename G > void examine_edge(E edge, G const & graph)
    {
        std::print("Visitor::examine_edge : edge = {}\n", edge);

        boost::default_dfs_visitor::examine_edge(edge, graph);
    }

//  ---------------------------------------------------------------------------------------

    template < typename E, typename G > void tree_edge(E edge, G const & graph)
    {
        std::print("Visitor::tree_edge : edge = {}\n", edge);

        boost::default_dfs_visitor::tree_edge(edge, graph);
    }

//  ---------------------------------------------------------------------------------------

    template < typename E, typename G > void back_edge(E edge, G const & graph)
    {
        std::print("Visitor::back_edge : edge = {}\n", edge);

        boost::default_dfs_visitor::back_edge(edge, graph);
    }

//  ---------------------------------------------------------------------------------------

    template < typename E, typename G > void forward_or_cross_edge(E edge, G const & graph)
    {
        std::print("Visitor::forward_or_cross_edge : edge = {}\n", edge);

        boost::default_dfs_visitor::forward_or_cross_edge(edge, graph);
    }

//  ---------------------------------------------------------------------------------------

    template < typename E, typename G > void finish_edge(E edge, G const & graph)
    {
        std::print("Visitor::finish_edge : edge = {}\n", edge);

        boost::default_dfs_visitor::finish_edge(edge, graph);
    }
};

///////////////////////////////////////////////////////////////////////////////////////////

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

    boost::depth_first_search(graph, boost::visitor(Visitor()).root_vertex(1));
}

///////////////////////////////////////////////////////////////////////////////////////////