#include <iostream>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/visitors.hpp>

class Visitor : public boost::default_dfs_visitor
{
private:

    using base_t = boost::default_dfs_visitor;

public:

    template < typename V, typename G > void initialize_vertex(V vertex, const G & graph)
    {
        std::cout << vertex << " (initialize vertex)" << std::endl;

        base_t::initialize_vertex(vertex, graph); // note: for other visitors
    }
    
    template < typename V, typename G > void start_vertex(V vertex, const G & graph)
    {
        std::cout << vertex << " (start vertex)" << std::endl;

        base_t::start_vertex(vertex, graph); // note: for other visitors
    }

    template < typename V, typename G > void discover_vertex(V vertex, const G & graph)
    {
        std::cout << vertex << " (discover vertex)" << std::endl;

        base_t::discover_vertex(vertex, graph); // note: for other visitors
    }

    template < typename V, typename G > void finish_vertex(V vertex, const G & graph)
    {
        std::cout << vertex << " (finish vertex)" << std::endl;

        base_t::finish_vertex(vertex, graph); // note: for other visitors
    }

    template < typename E, typename G > void examine_edge(E edge, const G & graph)
    {
        std::cout << edge.m_source << " >> " << edge.m_target << " (examine edge)" << std::endl;

        base_t::examine_edge(edge, graph); // note: for other visitors
    }

    template < typename E, typename G > void tree_edge(E edge, const G & graph)
    {
        std::cout << edge.m_source << " >> " << edge.m_target << " (tree edge)" << std::endl;

        base_t::tree_edge(edge, graph); // note: for other visitors
    }

    template < typename E, typename G > void back_edge(E edge, const G & graph)
    {
        std::cout << edge.m_source << " >> " << edge.m_target << " (back edge)" << std::endl;

        base_t::back_edge(edge, graph); // note: for other visitors
    }

    template < typename E, typename G > void forward_or_cross_edge(E edge, const G & graph)
    {
        std::cout << edge.m_source << " >> " << edge.m_target << " (forward or cross edge)" << std::endl;

        base_t::forward_or_cross_edge(edge, graph); // note: for other visitors
    }

    template < typename E, typename G > void finish_edge(E edge, const G & graph)
    {
        std::cout << edge.m_source << " >> " << edge.m_target << " (finish edge)" << std::endl;

        base_t::finish_edge(edge, graph); // note: for other visitors
    }

}; // class Visitor : public boost::default_dfs_visitor

int main()
{
	using vector = boost::vecS; using directed = boost::directedS; // note: directed graph

    boost::adjacency_list < vector, vector, directed > graph(5); // note: number of vertexes

    boost::add_edge(0, 2, graph);
    boost::add_edge(1, 1, graph);
    boost::add_edge(1, 3, graph);
    boost::add_edge(2, 1, graph);
    boost::add_edge(2, 3, graph);
    boost::add_edge(3, 1, graph);
    boost::add_edge(3, 4, graph);
    boost::add_edge(4, 0, graph);
    boost::add_edge(4, 1, graph);

    boost::depth_first_search(graph, boost::root_vertex(0).visitor(Visitor())); // note: O(V + E) complexity

    return 0;
}