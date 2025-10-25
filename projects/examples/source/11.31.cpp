////////////////////////////////////////////////////////////////////////////////

// support : www.cs.usfca.edu/~galles/visualization/DFS.html

////////////////////////////////////////////////////////////////////////////////

#include <iostream>

////////////////////////////////////////////////////////////////////////////////

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/named_function_params.hpp>

////////////////////////////////////////////////////////////////////////////////

class Visitor : public boost::default_dfs_visitor
{
public :

    void initialize_vertex(auto vertex, auto const & graph)
    {
        std::cout << "Visitor::initialize_vertex : vertex = " << vertex << '\n';

        boost::default_dfs_visitor::initialize_vertex(vertex, graph);
    }

//  ----------------------------------------------------------------------------
    
    void start_vertex(auto vertex, auto const & graph)
    {
        std::cout << "Visitor::start_vertex : vertex = " << vertex << '\n';

        boost::default_dfs_visitor::start_vertex(vertex, graph);
    }

//  ----------------------------------------------------------------------------

    void discover_vertex(auto vertex, auto const & graph)
    {
        std::cout << "Visitor::discover_vertex : vertex = " << vertex << '\n';

        boost::default_dfs_visitor::discover_vertex(vertex, graph);
    }

//  ----------------------------------------------------------------------------

    void finish_vertex(auto vertex, auto const & graph)
    {
        std::cout << "Visitor::finish_vertex : vertex = " << vertex << '\n';

        boost::default_dfs_visitor::finish_vertex(vertex, graph);
    }
    
//  ----------------------------------------------------------------------------

    void examine_edge(auto edge, auto const & graph)
    {
        std::cout << "Visitor::examine_edge : edge = " << edge << '\n';

        boost::default_dfs_visitor::examine_edge(edge, graph);
    }

//  ----------------------------------------------------------------------------

    void tree_edge(auto edge, auto const & graph)
    {
        std::cout << "Visitor::tree_edge : edge = " << edge << '\n';

        boost::default_dfs_visitor::tree_edge(edge, graph);
    }

//  ----------------------------------------------------------------------------

    void back_edge(auto edge, auto const & graph)
    {
        std::cout << "Visitor::back_edge : edge = " << edge << '\n';

        boost::default_dfs_visitor::back_edge(edge, graph);
    }

//  ----------------------------------------------------------------------------

    void forward_or_cross_edge(auto edge, auto const & graph)
    {
        std::cout << "Visitor::forward_or_cross_edge : edge = " << edge << '\n';

        boost::default_dfs_visitor::forward_or_cross_edge(edge, graph);
    }

//  ----------------------------------------------------------------------------

    void finish_edge(auto edge, auto const & graph)
    {
        std::cout << "Visitor::finish_edge : edge = " << edge << '\n';

        boost::default_dfs_visitor::finish_edge(edge, graph);
    }
};

////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////