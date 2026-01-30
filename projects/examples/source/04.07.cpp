////////////////////////////////////////////////////////////////

// chapter : Generic Programming

////////////////////////////////////////////////////////////////

// section : Function Templates

////////////////////////////////////////////////////////////////

// content : Type Node
//
// content : Traverse Algorithm
//
// content : Pointers to Data Members
//
// content : Operator ->*

////////////////////////////////////////////////////////////////

#include <cassert>
#include <vector>

////////////////////////////////////////////////////////////////

template < typename T > struct Node 
{ 
	T x = T();
	
	Node * left = nullptr, * right = nullptr;
};

////////////////////////////////////////////////////////////////

auto traverse(auto node, auto ... nodes)
{
	return (node ->* ... ->* nodes); // support : cppinsights.io
}

////////////////////////////////////////////////////////////////

int main()
{
	std::vector < Node < int > > nodes(5);

//  ---------------------------------------------------------

	for (auto i = 0uz; i < std::size(nodes); ++i)
	{
		nodes[i].x = i + 1;
	}

//  ---------------------------------------------------------

	Node < int > * node = nullptr;

//  ---------------------------------------------------------

	node 						   = &nodes.at(0);

	node->left          		   = &nodes.at(1);

	node->left->right       	   = &nodes.at(2);

	node->left->right->left    	   = &nodes.at(3);

	node->left->right->left->right = &nodes.at(4);

//  ---------------------------------------------------------

	auto  left = &Node < int > :: left;

	auto right = &Node < int > ::right;

//  ---------------------------------------------------------

	assert(traverse(node, left, right, left, right)->x == 5);
}

////////////////////////////////////////////////////////////////