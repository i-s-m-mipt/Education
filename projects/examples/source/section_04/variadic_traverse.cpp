#include <iostream>
#include <iterator>
#include <vector>

template < typename T > struct Node
{
	T value{};

	Node < T > * l = nullptr;
	Node < T > * r = nullptr;

}; // template < typename T > struct Node

template < typename R, typename... Paths > [[nodiscard]] inline R traverse(R root, Paths ... paths)
{
	return (root ->* ... ->* paths); // note: ((root ->* path_1) ->* path_2) ->* ...
}

int main()
{
	std::vector < Node < int > > nodes(5);

	for (std::size_t i = 0; i < std::size(nodes); ++i)
	{
		nodes[i].value = static_cast < int > (i);
	}

	Node < int > * root = nullptr;

	root             = &nodes[0];
	root->l          = &nodes[1];
	root->l->r       = &nodes[2];
	root->l->r->l    = &nodes[3];
	root->l->r->l->r = &nodes[4];

	const auto l = &Node < int > ::l; // note: pointer to data member l
	const auto r = &Node < int > ::r; // note: pointer to data member r

	std::cout << traverse(root, l, r, l, r)->value << std::endl;

	return 0;
}