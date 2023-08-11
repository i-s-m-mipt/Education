#include <iostream>
#include <istream>
#include <string>

int main()
{
    std::string s_1 = "What a wonderful day!";
    std::string s_2(s_1);
    std::string s_3(s_1, 7, 9);
    std::string s_4(s_1, 17);
    std::string s_5;
    std::string s_6(20, 'C');

    std::cout << s_1 << std::endl;
    std::cout << s_2 << std::endl;
    std::cout << s_3 << std::endl;
    std::cout << s_4 << std::endl;
    std::cout << s_5 << std::endl;
    std::cout << s_6 << std::endl;

    std::cout << std::endl;

    std::string scin;
    std::cin >> scin;
    std::getline(std::cin >> std::ws, scin);
    int n;
    std::cin >> n;

    std::cout << std::endl;

    std::cout << s_1.size() << std::endl;
    std::cout << s_2.length() << std::endl;
    std::cout << std::size(s_3) << std::endl;

    std::cout << std::endl;

    std::cout << std::boolalpha << s_4.empty() << std::endl;
    std::cout << std::boolalpha << s_5.empty() << std::endl;

    std::cout << std::endl;

    s_5 = s_3;

    std::cout << s_5 << std::endl;
    std::cout << s_1 + s_2 << std::endl;

    std::cout << std::endl;

    s_1 += s_2;

    std::cout << (s_1 == s_2) << std::endl;
    std::cout << (s_1 <  s_3) << std::endl;

    std::cout << std::endl;

    std::cout << s_1[0] << std::endl;
    std::cout << s_1.at(0) << std::endl;

    std::cout << std::endl;

    std::cout << s_1.substr(0, 3) << std::endl;
    std::cout << s_1.substr(1, 2) << std::endl;
    std::cout << s_1.substr(0, s_1.size() - 1) << std::endl;
    std::cout << s_1.substr(1) << std::endl;

    std::cout << std::endl;

    s_5.swap(s_6);

    std::cout << s_5 << std::endl;
    std::cout << s_6 << std::endl;

    std::cout << std::endl;

    s_6.clear();
    std::cout << std::boolalpha << s_6.empty() << std::endl;
    std::cout << s_5.erase() << std::boolalpha << s_5.empty() << std::endl;
    std::cout << s_3.erase(2, 3) << s_4 << std::endl;

    std::cout << std::endl;

    std::cout << s_6.insert(0, 20, 'C') << s_6 << std::endl;
    std::cout << s_6.insert(10, "++++") << s_6 << std::endl;
    std::cout << s_6.insert(10, s_3) << s_6 << std::endl;
    std::cout << s_6.insert(10, "-----", 4) << s_6 << std::endl;
    std::cout << s_6.insert(0, s_1, 0, 4) << s_6 << std::endl;

    std::cout << std::endl;

    s_5.push_back('C');
    std::cout << std::endl;

    std::cout << std::endl;

    std::cout << s_5.append(9, 'C') << std::endl;
    std::cout << s_5.append(s_4) << std::endl;
    std::cout << s_5.append(s_1, 7, 9) << std::endl;
    std::cout << s_5.append("++++", 2) << std::endl;
    std::cout << s_5.append("++++") << std::endl;

    std::cout << std::endl;

    std::cout << s_1.find("day") << std::endl;
    std::cout << s_1.find("hello") << std::endl;
    std::cout << s_1.find("a", 8) << std::endl;
    std::cout << s_1.rfind("a", 8) << std::endl;

    std::cout << std::endl;

    std::cout << s_6.replace(7, 9, "terrible") << std::endl;

    std::cout << std::endl;

    const char * cstr = s_3.c_str();
    printf("%s", cstr);

    std::cout << std::endl;

    return 0;
}