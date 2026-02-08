#include <iostream>

class Entity_v1
{
private:
    int val;

public:
    int get_val() const{
        return val;
    }

};

class Entity_v2
{
public:
    int val;

};

union HackUnion {
    Entity_v1 ent_v1;
    int val;
};

int main(){
    Entity_v1 ent_v1;
    Entity_v1 &lnk_v1 = ent_v1;

    Entity_v2& lnk_v2 = reinterpret_cast<Entity_v2&>(lnk_v1);

    // Test
    lnk_v2.val = 100;

    std::cout << lnk_v1.get_val() << '\n';

    // Another way (Union)
    HackUnion hu;
    hu.val = 999;

    std::cout << hu.ent_v1.get_val() << '\n';

    return 0;
}