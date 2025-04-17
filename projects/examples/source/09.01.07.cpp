///////////////////////////////////////////////////////////////////

#include <cassert>
#include <iostream>
#include <memory>
#include <tuple>

///////////////////////////////////////////////////////////////////

class Entity_v1
{
public :

    auto make_shared()
    { 
        return std::shared_ptr < Entity_v1 > (this);
    }
};

///////////////////////////////////////////////////////////////////

class Entity_v2 : public std::enable_shared_from_this < Entity_v2 >
{
public :

    auto make_shared()
    { 
        return shared_from_this();
    }
};

///////////////////////////////////////////////////////////////////

class Entity_v3 : public std::enable_shared_from_this < Entity_v3 >
{
private :

    struct Key {};

public :

    Entity_v3(Key) {}

//  ------------------------------

    auto make_shared()
    { 
        return shared_from_this();
    }

//  ------------------------------

    friend auto make_shared();
};

///////////////////////////////////////////////////////////////////

auto make_shared()
{
    return std::make_shared < Entity_v3 > (Entity_v3::Key());
}

///////////////////////////////////////////////////////////////////

int main()
{
    auto entity_v1_1 = std::make_shared < Entity_v1 > ();

//  auto entity_v1_2 = entity_v1_1->make_shared(); // error

//  -------------------------------------------------------

//  assert(entity_v1_1.use_count() == 1); // bad

//  assert(entity_v1_2.use_count() == 1); // bad

//  -------------------------------------------------------

    auto entity_v2_1 = std::make_shared < Entity_v2 > ();

    auto entity_v2_2 = entity_v2_1->make_shared();

//  -------------------------------------------------------

    assert(entity_v2_1.use_count() == 2);

    assert(entity_v2_2.use_count() == 2);

//  -------------------------------------------------------

    try
    {
        std::ignore = Entity_v2().make_shared();
    }
    catch (std::bad_weak_ptr const & exception)
    {
        std::cerr << "main : " << exception.what() << '\n';
    }

//  -------------------------------------------------------

    auto entity_v3_1 = make_shared();

    auto entity_v3_2 = entity_v3_1->make_shared();

//  -------------------------------------------------------
    
    assert(entity_v3_1.use_count() == 2);

    assert(entity_v3_2.use_count() == 2);
}

///////////////////////////////////////////////////////////////////