#include <iostream>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/visitors.hpp>

//  ================================================================================================

class Visitor : public boost::default_bfs_visitor
{
private:

    using base_t = boost::default_bfs_visitor;

public:

    template < typename V, typename G > auto initialize_vertex(V vertex, const G & graph)
    {
        std::cout << vertex << " (initialize vertex)" << std::endl;

        return base_t::initialize_vertex(vertex, graph);
    }

    template < typename V, typename G > auto discover_vertex(V vertex, const G & graph)
    {
        std::cout << vertex << " (discover vertex)" << std::endl;

        return base_t::discover_vertex(vertex, graph);
    }

    template < typename V, typename G > auto examine_vertex(V vertex, const G & graph)
    {
        std::cout << vertex << " (examine vertex)" << std::endl;

        return base_t::examine_vertex(vertex, graph);
    }

    template < typename V, typename G > auto finish_vertex(V vertex, const G & graph)
    {
        std::cout << vertex << " (finish vertex)" << std::endl;

        return base_t::finish_vertex(vertex, graph);
    }

//  ------------------------------------------------------------------------------------------------

    template < typename E, typename G > auto examine_edge(E edge, const G & graph)
    {
        std::cout << edge.m_source << " >> " << 
                     edge.m_target << " (examine edge)" << std::endl;

        return base_t::examine_edge(edge, graph);
    }

    template < typename E, typename G > auto tree_edge(E edge, const G & graph)
    {
        std::cout << edge.m_source << " >> " << 
                     edge.m_target << " (tree edge)" << std::endl;

        return base_t::tree_edge(edge, graph);
    }

    template < typename E, typename G > auto non_tree_edge(E edge, const G & graph)
    {
        std::cout << edge.m_source << " >> " << 
                     edge.m_target << " (non tree edge)" << std::endl;

        return base_t::non_tree_edge(edge, graph);
    }
    
//  ------------------------------------------------------------------------------------------------

    template < typename E, typename G > auto gray_target(E edge, const G & graph)
    {
        std::cout << edge.m_source << " >> " << 
                     edge.m_target << " (gray target)" << std::endl;

        return base_t::gray_target(edge, graph);
    }

    template < typename E, typename G > auto black_target(E edge, const G & graph)
    {
        std::cout << edge.m_source << " >> " << 
                     edge.m_target << " (black target)" << std::endl;

        return base_t::black_target(edge, graph);
    }
};

//  ================================================================================================

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

    boost::breadth_first_search(graph, 0, visitor);
}