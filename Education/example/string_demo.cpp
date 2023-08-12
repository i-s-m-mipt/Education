#include <iostream>
#include <string>

int main()
{
    const char * cstring = "What a wonderful day!";

    std::string s_1(cstring);   std::cout << s_1 << std::endl;
    std::string s_2(s_1);       std::cout << s_2 << std::endl;
    std::string s_3(s_1, 7, 9); std::cout << s_3 << std::endl;
    std::string s_4(s_1, 17);   std::cout << s_4 << std::endl;
    std::string s_5(20, 'a');   std::cout << s_5 << std::endl;
    std::string s_6;            std::cout << s_6 << std::endl;
    
    std::string scin; std::cin >> scin;
    
    auto x = 0; std::cin >> x;

    std::getline(std::cin >> std::ws, scin);
    
    std::cout << "========================================" << std::endl;

    std::cout << s_1.size()     << std::endl;
    std::cout << s_2.length()   << std::endl;
    std::cout << std::size(s_3) << std::endl;

    std::cout << std::boolalpha << std::empty(s_5) << std::endl;
    std::cout << std::boolalpha << std::empty(s_6) << std::endl;

    std::cout << "========================================" << std::endl;

    s_6 = s_3;

    std::cout << s_6       << std::endl;
    std::cout << s_1 + s_2 << std::endl;

    s_1 += s_2;

    std::cout << std::boolalpha << (s_1 == s_2) << std::endl;
    std::cout << std::boolalpha << (s_1 <  s_3) << std::endl;

    std::swap(s_5, s_6);

    std::cout << s_5 << std::endl;
    std::cout << s_6 << std::endl;

    std::cout << "========================================" << std::endl;

    std::cout << s_1[0]    << std::endl;
    std::cout << s_1.at(0) << std::endl;

    std::cout << "========================================" << std::endl;

    std::cout << s_1.substr(0, 3)                  << std::endl;
    std::cout << s_1.substr(1, 2)                  << std::endl;
    std::cout << s_1.substr(0, std::size(s_1) - 1) << std::endl;
    std::cout << s_1.substr(1)                     << std::endl;

    std::cout << "========================================" << std::endl;

    s_6.clear();

    std::cout << std::boolalpha << std::empty(s_6) << std::endl;
   
    std::cout << s_5.erase()     << std::endl;
    std::cout << s_3.erase(2, 3) << std::endl;

    std::cout << "========================================" << std::endl;

    std::cout << s_6.insert(0, 20, 'a') << std::endl;
    std::cout << s_6.insert(10, "++++") << std::endl;
    std::cout << s_6.insert(10, s_3)    << std::endl;

    s_5.push_back('C');

    std::cout << s_5.append(20, 'a') << std::endl;
    std::cout << s_5.append("++++")  << std::endl;
    std::cout << s_5.append(s_4)     << std::endl;
    
    std::cout << "========================================" << std::endl;

    std::cout << s_1.find("day")   << std::endl;
    std::cout << s_1.find("hello") << std::endl;
    std::cout << s_1.find("a", 8)  << std::endl;

    std::cout << s_6.replace(7, 9, "terrible") << std::endl;

    std::cout << "========================================" << std::endl;

    auto cstring_from_string = s_3.c_str();

    return 0;
}