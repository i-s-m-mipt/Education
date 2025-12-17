#include <iostream>
#include <memory>
#include <vector>

class Unit {
    std::string type;
    int hp, dmg;
public:
    Unit(std::string t, int h, int d) : type(t), hp(h), dmg(d) {}
    void show() { std::cout << type << " [" << hp << " HP, " << dmg << " DMG]\n"; }
};

class UnitBuilder {
    std::string type;
    int hp = 0, dmg = 0;
public:
    UnitBuilder& setType(std::string t) { type = t; return *this; }
    UnitBuilder& setHP(int h) { hp = h; return *this; }
    UnitBuilder& setDMG(int d) { dmg = d; return *this; }
    Unit build() { return Unit(type, hp, dmg); }
};

class GameObject {
public:
    virtual void display() = 0;
    virtual void move() = 0;
    virtual ~GameObject() = default;
};

class SingleUnit : public GameObject {
    Unit unit;
public:
    SingleUnit(Unit u) : unit(u) {}
    void display() override { unit.show(); }
    void move() override { std::cout << "Unit moves\n"; }
};

class Squad : public GameObject {
    std::vector<std::unique_ptr<GameObject>> units;
public:
    void add(std::unique_ptr<GameObject> obj) { units.push_back(std::move(obj)); }
    void display() override { 
        for (auto& u : units) u->display();
    }
    void move() override {
        for (auto& u : units) u->move();
    }
};

class AttackTemplate {
protected:
    virtual void selectTarget() = 0;
    virtual void animate() = 0;
    virtual void applyDamage() = 0;
public:
    void performAttack() {
        selectTarget();
        animate();
        applyDamage();
    }
    virtual ~AttackTemplate() = default;
};

class MeleeAttack : public AttackTemplate {
protected:
    void selectTarget() override { std::cout << "Select melee target\n"; }
    void animate() override { std::cout << "Swing weapon\n"; }
    void applyDamage() override { std::cout << "Deal 20 damage\n"; }
};

int main() {
    UnitBuilder builder;
    Unit soldier = builder.setType("Soldier").setHP(100).setDMG(10).build();
    Unit tank = builder.setType("Tank").setHP(300).setDMG(50).build();
    soldier.show();
    tank.show();
    
    auto squad = std::make_unique<Squad>();
    squad->add(std::make_unique<SingleUnit>(soldier));
    squad->add(std::make_unique<SingleUnit>(tank));
    squad->display();
    squad->move();
    
    MeleeAttack attack;
    attack.performAttack();
    
    return 0;
}