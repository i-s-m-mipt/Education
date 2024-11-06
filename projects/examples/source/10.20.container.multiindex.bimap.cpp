#include <cassert>
#include <iterator>
#include <string>

#include <boost/bimap.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/random_access_index.hpp>

//  ================================================================================================

struct Entity 
{ 
	int data_1 = 0; 
	int data_2 = 0; 
};

//  ================================================================================================

template < typename T, typename M > using HNU = boost::multi_index:: hashed_non_unique < T, M > ;
template < typename T, typename M > using ONU = boost::multi_index::ordered_non_unique < T, M > ;

template < typename T > using tag_t = boost::multi_index::tag < T > ;

template 
< 
	typename C, typename T, T C::*P 
> 
using member_t = boost::multi_index::member < C, T, P > ;

//  ================================================================================================

using multi_index_container_t = boost::multi_index::multi_index_container 
< 
	Entity, boost::multi_index::indexed_by 
	<
		HNU < tag_t < struct data_1_tag > , member_t < Entity, int, &Entity::data_1 > > ,
		ONU < tag_t < struct data_2_tag > , member_t < Entity, int, &Entity::data_2 > >
	>
> ; 

//  ================================================================================================

int main()
{
	multi_index_container_t multi_index_container({ { 1, 1 }, { 2, 2 }, { 3, 3 } });

//  ------------------------------------------------------------------------------------------------

	auto & HNU_data_1_index = multi_index_container.get < data_1_tag > ();
	auto & ONU_data_2_index = multi_index_container.get < data_2_tag > ();

//  ------------------------------------------------------------------------------------------------

	auto modifier = [](auto && entity){ entity.data_1 = entity.data_2 = 1; };

	assert(HNU_data_1_index.modify(HNU_data_1_index.find(2), modifier));

	assert(HNU_data_1_index.count(1) == 2);

//  ------------------------------------------------------------------------------------------------

	for (auto [begin, end] = ONU_data_2_index.equal_range(1); begin != end; ++begin)
	{
		assert
		(
			begin->data_1 == 1 &&
			begin->data_2 == 1
		);
	}

//  ------------------------------------------------------------------------------------------------
	
	boost::bimap < int, int > bimap; // support: boost::bimaps::(multi)set_of

	bimap.insert({ 1, 1 });
	bimap.insert({ 2, 2 });
	bimap.insert({ 3, 3 });

	assert(bimap.left .count(1) == 1);
	assert(bimap.right.count(1) == 1);

	for (const auto & element : bimap) 
	{
		assert(element.left == element.right);
	}
}