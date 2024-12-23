#include <iostream>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/visitors.hpp>

///////////////////////////////////////////////////////////////////////////////////////////

class Visitor : public boost::default_dfs_visitor
{
public:

    template < typename V, typename G > void initialize_vertex(V vertex, const G & graph)
    {
        std::cout << "Visitor::initialize_vertex : vertex = " << vertex << '\n';

        boost::default_dfs_visitor::initialize_vertex(vertex, graph);
    }
    
    template < typename V, typename G > void start_vertex(V vertex, const G & graph)
    {
        std::cout << "Visitor::start_vertex : vertex = " << vertex << '\n';

        boost::default_dfs_visitor::start_vertex(vertex, graph);
    }

    template < typename V, typename G > void discover_vertex(V vertex, const G & graph)
    {
        std::cout << "Visitor::discover_vertex : vertex = " << vertex << '\n';

        boost::default_dfs_visitor::discover_vertex(vertex, graph);
    }

    template < typename V, typename G > void finish_vertex(V vertex, const G & graph)
    {
        std::cout << "Visitor::finish_vertex : vertex = " << vertex << '\n';

        boost::default_dfs_visitor::finish_vertex(vertex, graph);
    }
    
//  ---------------------------------------------------------------------------------------

    template < typename E, typename G > void examine_edge(E edge, const G & graph)
    {
        std::cout << "Visitor::examine_edge : edge = " << edge << '\n';

        boost::default_dfs_visitor::examine_edge(edge, graph);
    }

    template < typename E, typename G > void tree_edge(E edge, const G & graph)
    {
        std::cout << "Visitor::tree_edge : edge = " << edge << '\n';

        boost::default_dfs_visitor::tree_edge(edge, graph);
    }

    template < typename E, typename G > void back_edge(E edge, const G & graph)
    {
        std::cout << "Visitor::back_edge : edge = " << edge << '\n';

        boost::default_dfs_visitor::back_edge(edge, graph);
    }

    template < typename E, typename G > void forward_or_cross_edge(E edge, const G & graph)
    {
        std::cout << "Visitor::forward_or_cross_edge : edge = " << edge << '\n';

        boost::default_dfs_visitor::forward_or_cross_edge(edge, graph);
    }

    template < typename E, typename G > void finish_edge(E edge, const G & graph)
    {
        std::cout << "Visitor::finish_edge : edge = " << edge << '\n';

        boost::default_dfs_visitor::finish_edge(edge, graph);
    }
};

///////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    boost::adjacency_list < boost::vecS, boost::vecS, boost::directedS > graph;

    boost::add_edge(0, 2, graph);
    boost::add_edge(1, 1, graph);
    boost::add_edge(1, 3, graph);
    boost::add_edge(2, 1, graph);
    boost::add_edge(2, 3, graph);
    boost::add_edge(3, 1, graph);
    boost::add_edge(3, 4, graph);
    boost::add_edge(4, 0, graph);
    boost::add_edge(4, 1, graph);

    auto visitor = boost::visitor(Visitor());

    boost::depth_first_search(graph, visitor.root_vertex(0));
}