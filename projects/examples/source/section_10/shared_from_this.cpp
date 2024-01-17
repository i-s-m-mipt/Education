#include <cassert>
#include <iostream>
#include <memory>

class Fail
{
public:

    auto get() { return std::shared_ptr < Fail > (this); }

}; // class Fail

class Good : public std::enable_shared_from_this < Good > // note: CRTP
{
public:

    auto get() { return shared_from_this(); }

}; // class Good : public std::enable_shared_from_this < Good >

class Best : public std::enable_shared_from_this < Best >
{
private:

    struct Key {}; // note: see also Passkey idiom

public:

    Best(Key) {}; // good: all instances are in shared_ptrs

    static auto create() // note: factory method
    {
        return std::make_shared < Best > (Key());
    }

    auto get() { return shared_from_this(); }

}; // class Best : public std::enable_shared_from_this < Best >

int main()
{
    auto fail_1 = std::make_shared < Fail > ();

//  auto fail_2 = fail_1->get(); // bad: undefined behaviour
    
    assert(fail_1.use_count() == 1);
//  assert(fail_2.use_count() == 1);

    auto good_1 = std::make_shared < Good > ();

    auto good_2 = good_1->get();

    assert(good_1.use_count() == 2);
    assert(good_2.use_count() == 2);

    try
    {
        Good good; // note: not managed by shared_ptr

        auto good_3 = good.get();
    }
    catch (const std::bad_weak_ptr & exception)
    {
        std::cerr << exception.what() << std::endl;
    }

    auto best_1 = Best::create();

    auto best_2 = best_1->get();

    assert(best_1.use_count() == 2);
    assert(best_2.use_count() == 2);

//  Best best(Key()); // error: requires private key

    return 0;
}