////////////////////////////////////////////////

// chapter : Software Engineering Patterns

////////////////////////////////////////////////

// content : Pattern Singleton
//
// content : Deleted Implementations
//
// content : Function Specifier delete

////////////////////////////////////////////////

#include <print>

////////////////////////////////////////////////

class Entity
{
public :

    Entity            (Entity const &) = delete;

//  --------------------------------------------

    Entity & operator=(Entity const &) = delete;

//  --------------------------------------------

    void test() const
    {
        std::print("Entity::test\n");
    }

//  --------------------------------------------

    static auto & get()
    {
        static Entity entity;

        return entity;
    }

private :

    Entity() = default;
};

////////////////////////////////////////////////

int main()
{
    Entity::get().test();
}

////////////////////////////////////////////////