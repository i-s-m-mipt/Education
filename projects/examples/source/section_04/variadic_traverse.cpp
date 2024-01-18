#include <iostream>
#include <vector>

template < typename T > struct Node
{
	T x = T();

	Node < T > * l = nullptr;
	Node < T > * r = nullptr;

}; // template < typename T > struct Node

template < typename R, typename... Paths > auto traverse(R root, Paths ... paths)
{
	return (root ->* ...->*paths); // np ->* paths1 ->* paths2 ...
}

int main()
{
	std::vector < Node < int > > nodes(5);

	for (std::size_t i = 0; i < std::size(nodes); ++i)
	{
		nodes[i].x = static_cast < int > (i);
	}

	Node < int > * root = nullptr;

	root             = &nodes[0];
	root->l          = &nodes[1];
	root->l->r       = &nodes[2];
	root->l->r->l    = &nodes[3];
	root->l->r->l->r = &nodes[4];

	auto l = &Node < int > ::l; // note: pointer to data member l
	auto r = &Node < int > ::r; // note: pointer to data member r

	std::cout << traverse(root, l, r, l, r)->x << std::endl;

	return 0;
}