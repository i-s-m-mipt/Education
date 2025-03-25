#include <cassert>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/random_access_index.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////////

struct Entity 
{ 
	int x = 0, y = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T, typename M > using ONU_t = boost::multi_index::ordered_non_unique < T, M > ;

template < typename T, typename M > using HNU_t = boost::multi_index:: hashed_non_unique < T, M > ;

///////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T > using tag_t = boost::multi_index::tag < T > ;

///////////////////////////////////////////////////////////////////////////////////////////////////

template 
< 
	typename C, typename T, T C::*P 
> 
using member_t = boost::multi_index::member < C, T, P > ;

///////////////////////////////////////////////////////////////////////////////////////////////////

using container_t = boost::multi_index::multi_index_container 
< 
	Entity, boost::multi_index::indexed_by 
	<
		ONU_t < tag_t < struct ONU_x_tag > , member_t < Entity, int, &Entity::x > > ,

		HNU_t < tag_t < struct HNU_y_tag > , member_t < Entity, int, &Entity::y > > 
	>
> ;

///////////////////////////////////////////////////////////////////////////////////////////////////

void handler(Entity & entity)
{
	entity = Entity(2, 2);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	container_t container = { { 1, 1 }, { 2, 2 }, { 3, 3 }, { 4, 4 }, { 5, 5 } };

//  -----------------------------------------------------------------------------

	auto & ONU_x_index = container.get < ONU_x_tag > ();

	auto & HNU_y_index = container.get < HNU_y_tag > ();

//  -----------------------------------------------------------------------------

	assert(ONU_x_index.lower_bound(1)->x == 1);

	assert(ONU_x_index.upper_bound(1)->x == 2);

//  -----------------------------------------------------------------------------

	HNU_y_index.modify(HNU_y_index.find(1), handler);

//  -----------------------------------------------------------------------------

	assert(HNU_y_index.count(1) == 0);

	assert(HNU_y_index.count(2) == 2);
}