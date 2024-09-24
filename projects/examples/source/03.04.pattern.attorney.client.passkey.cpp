class Computer_v1
{
private:

    class Key_v1 { private: Key_v1() = default; friend class User; };
    class Key_v2 { private: Key_v2() = default; friend class User; };
    class Key_v3 { private: Key_v3() = default;                    };

private:

    friend class User;

private:

    void test_v1(Key_v1) const {}
    void test_v2(Key_v2) const {}
    void test_v3(Key_v3) const {}

}; // class Computer_v1

//  ================================================================================================

class Computer_v2
{
private:

    friend class Attorney;

private:

    void test_v1() const {}
    void test_v2() const {}
    void test_v3() const {}

}; // class Computer_v2

//  ================================================================================================

class Attorney 
{
private:

    static void test_v1(const Computer_v2 & computer) { computer.test_v1(); }
    static void test_v2(const Computer_v2 & computer) { computer.test_v2(); }

    friend class User;

}; // class Attorney 

//  ================================================================================================

class User
{
public:

    void test(const Computer_v1 & computer) const
    {
        computer.test_v1({});
        computer.test_v2({});
//      computer.test_v3({}); // error
    }

    void test(const Computer_v2 & computer) const
    {
        Attorney::test_v1(computer);
        Attorney::test_v2(computer);
//      Attorney::test_v3(computer); // error
    }

}; // class User

//  ================================================================================================

int main()
{
    User().test(Computer_v1());
    User().test(Computer_v2());

    return 0;
}