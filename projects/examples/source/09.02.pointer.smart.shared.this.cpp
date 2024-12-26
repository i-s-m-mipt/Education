#include <cassert>
#include <exception>
#include <iostream>
#include <memory>
#include <stdexcept>

///////////////////////////////////////////////////////////////////

class Entity_v1
{
public:

    auto get()
    { 
        return std::shared_ptr < Entity_v1 > (this); 
    }
}; 

///////////////////////////////////////////////////////////////////

class Entity_v2 : public std::enable_shared_from_this < Entity_v2 >
{
public:

    auto get()
    { 
        return shared_from_this(); 
    }
};

///////////////////////////////////////////////////////////////////

class Entity_v3 : public std::enable_shared_from_this < Entity_v3 >
{
private:

    struct Key {};

public:

    Entity_v3(Key) {};

//  ---------------------------------------------------------------

    auto get()
    { 
        return shared_from_this(); 
    }

    static auto make()
    {
        return std::make_shared < Entity_v3 > (Key());
    }
};

///////////////////////////////////////////////////////////////////

int main()
{
    auto entity_v1_1 = std::make_shared < Entity_v1 > ();

//  auto entity_v1_2 = entity_v1_1->get(); // bad
    
    assert(entity_v1_1.use_count() == 1);
//  assert(entity_v1_2.use_count() == 1);

//  -------------------------------------------------------

    auto entity_v2_1 = std::make_shared < Entity_v2 > ();

    auto entity_v2_2 = entity_v2_1->get();

    assert(entity_v2_1.use_count() == 2);
    assert(entity_v2_2.use_count() == 2);

    try
    {
        Entity_v2 entity_v2_3;

        auto entity_v2_4 = entity_v2_3.get();
    }
    catch (const std::bad_weak_ptr & exception)
    {
        std::cerr << "main : " << exception.what() << '\n';
    }

//  -------------------------------------------------------

    auto entity_v3_1 = Entity_v3::make();

    auto entity_v3_2 = entity_v3_1->get();

    assert(entity_v3_1.use_count() == 2);
    assert(entity_v3_2.use_count() == 2);

//  Entity_v3 entity_v3(Key()); // error
}