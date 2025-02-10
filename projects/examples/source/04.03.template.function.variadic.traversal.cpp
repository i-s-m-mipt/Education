#include <cassert>
#include <vector>

////////////////////////////////////////////////////////////////////////////

template < typename T > struct Node 
{ 
	T data = T(); 
	
	Node * left = nullptr, * right = nullptr;
};

////////////////////////////////////////////////////////////////////////////

template < typename N, typename ... Ns > auto traverse(N node, Ns ... nodes)
{
	return (node ->* ... ->* nodes); // support: cppinsights.io
}

////////////////////////////////////////////////////////////////////////////

int main()
{
	std::vector < Node < int > > nodes(5);

	for (auto i = 0uz; i < std::size(nodes); ++i)
	{
		nodes[i].data = i + 1;
	}

	Node < int > * node = nullptr;
	
	node 						   = &nodes[0];
	node->left          		   = &nodes[1];
	node->left->right       	   = &nodes[2];
	node->left->right->left    	   = &nodes[3];
	node->left->right->left->right = &nodes[4];

	auto left = &Node < int > ::left, right = &Node < int > ::right;

	assert(traverse(node, left, right, left, right)->data == 5);
}