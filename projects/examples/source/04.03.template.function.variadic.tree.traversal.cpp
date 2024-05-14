#include <iostream>
#include <iterator>
#include <vector>

//  ================================================================================================

struct Node { int value{}; Node * l{}, * r{}; };

//  ================================================================================================

template < typename R, typename ... Ns > [[nodiscard]] inline R traverse(R root, Ns ... nodes)
{
	return (root ->* ... ->* nodes); // detail: ((root ->* node_1) ->* node_2) ->* ...
}

//  ================================================================================================

int main()
{
	const std::size_t size = 5;

	std::vector < Node > nodes(size);

	for (std::size_t i = 0; i < std::size(nodes); ++i)
	{
		nodes[i].value = static_cast < int > (i);
	}

	Node * root = nullptr;

	root             = &nodes[0];
	root->l          = &nodes[1];
	root->l->r       = &nodes[2];
	root->l->r->l    = &nodes[3];
	root->l->r->l->r = &nodes[4];

	const auto l = &Node::l;
	const auto r = &Node::r;

	std::cout << traverse(root, l, r, l, r)->value << std::endl;

	return 0;
}