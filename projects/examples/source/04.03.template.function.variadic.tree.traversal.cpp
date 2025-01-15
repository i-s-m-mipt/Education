#include <cassert>
#include <vector>

////////////////////////////////////////////////////////////////////////////

template < typename T > struct Node 
{ 
	T data = T(); Node * left = nullptr, * right = nullptr; 
};

////////////////////////////////////////////////////////////////////////////

template < typename R, typename ... Ns > auto traverse(R root, Ns ... nodes)
{
	return (root ->* ... ->* nodes); // support: cppinsights.io
}

////////////////////////////////////////////////////////////////////////////

int main()
{
	std::vector < Node < int > > nodes(5);

	for (auto i = 0uz; i < std::size(nodes); ++i)
	{
		nodes[i].data = static_cast < int > (i) + 1;
	}

	Node < int > * root = nullptr;
	
	root 						   = &nodes[0];
	root->left          		   = &nodes[1];
	root->left->right       	   = &nodes[2];
	root->left->right->left    	   = &nodes[3];
	root->left->right->left->right = &nodes[4];

	auto left = &Node < int > ::left, right = &Node < int > ::right;

	assert(traverse(root, left, right, left, right)->data == 5);
}