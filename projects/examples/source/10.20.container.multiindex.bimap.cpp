#include <cassert>

#include <boost/bimap.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/random_access_index.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////

struct Entity 
{ 
	int data_1 = 0, data_2 = 0; 
};

/////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T, typename M > using HNU = boost::multi_index:: hashed_non_unique < T, M > ;

template < typename T, typename M > using ONU = boost::multi_index::ordered_non_unique < T, M > ;

template < typename T > using tag_t = boost::multi_index::tag < T > ;

template 
< 
	typename C, typename T, T C::*P 
> 
using member_t = boost::multi_index::member < C, T, P > ;

/////////////////////////////////////////////////////////////////////////////////////////////////

using container_t = boost::multi_index::multi_index_container 
< 
	Entity, boost::multi_index::indexed_by 
	<
		HNU < tag_t < struct data_1_tag > , member_t < Entity, int, &Entity::data_1 > > ,

		ONU < tag_t < struct data_2_tag > , member_t < Entity, int, &Entity::data_2 > >
	>
> ; 

/////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		container_t container = { { 1, 1 }, { 2, 2 }, { 3, 3 }, { 4, 4 }, { 5, 5 } };

		auto & HNU_data_1_index = container.get < data_1_tag > ();

		auto & ONU_data_2_index = container.get < data_2_tag > ();

		if (HNU_data_1_index.contains(1))
		{
			HNU_data_1_index.modify
			(	
				HNU_data_1_index.find(1), [](auto && entity){ entity = Entity(2, 2); }
			);

			assert(HNU_data_1_index.count(1) == 0);

			assert(HNU_data_1_index.count(2) == 2);
		}

		assert(ONU_data_2_index.lower_bound(2)->data_2 == 2);

		assert(ONU_data_2_index.upper_bound(2)->data_2 == 3);
	}

//  ---------------------------------------------------------------------------------

	{
		boost::bimap < int, int > map; // support: boost::bimaps::(multi)set_of

		map.insert({ 1, 1 });

		assert(map.left.count(1) == map.right.count(1));

		for (const auto & element : map) 
		{
			assert(element.left == element.right);
		}
	}
}