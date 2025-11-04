#include <iostream>

const int SIZE = 4;
const int MAX_EL = 255;
const int MIN_EL = 0;

class IPv4
{
private:
    std::uint8_t ipv4[SIZE];

public:
    IPv4() : ipv4{0, 0, 0, 0} {}

    IPv4(const std::uint8_t data[SIZE]) {
        std::copy(data, data + SIZE, ipv4);
    }

    // prefix increment
    IPv4& operator++(){
        for (int ind_i = SIZE - 1; ind_i >= 0; --ind_i){
            if (ipv4[ind_i] < MAX_EL){
                ++ipv4[ind_i];
                break;
            }
            ipv4[ind_i] = 0;
        }
        return *this;
    }

    // postfix increment
    IPv4 operator++(int){
        IPv4 temp = *this;
        ++(*this);
        return temp;
    }

    // prefix increment
    IPv4& operator--(){
        for (int ind_i = SIZE - 1; ind_i >= 0; --ind_i){
            if (ipv4[ind_i] > MIN_EL){
                --ipv4[ind_i];
                break;
            }
            ipv4[ind_i] = 0;
        }
        return *this;
    }

    // postfix increment
    IPv4 operator--(int){
        IPv4 temp = *this;
        --(*this);
        return temp;
    }

    friend bool operator== (const IPv4& ip1, const IPv4& ip2){
        for (int ind_i = SIZE - 1; ind_i >= 0; --ind_i){
            if (ip1.ipv4[ind_i] != ip2.ipv4[ind_i]){
                return false;
            }
        }
        return true;
    }

    friend bool operator!= (const IPv4& ip1, const IPv4& ip2){
        return !(ip1 == ip2);
    }

    friend bool operator< (const IPv4& ip1, const IPv4& ip2){
        for (int ind_i = 0; ind_i < SIZE; ++ind_i){
            if (ip1.ipv4[ind_i] > ip2.ipv4[ind_i]){
                return false;
            }
            else if (ip1.ipv4[ind_i] < ip2.ipv4[ind_i]){
                return true;
            }
        }
        return false; // ip1 == ip2
    }

    friend bool operator> (const IPv4& ip1, const IPv4& ip2){
        return !(ip1 < ip2);
    }

    friend bool operator<= (const IPv4& ip1, const IPv4& ip2){
        return (ip1 < ip2 || ip1 == ip2);
    }

    friend bool operator>= (const IPv4& ip1, const IPv4& ip2){
        return (ip1 > ip2 || ip1 == ip2);
    }

    friend std::istream& operator>> (std::istream& is, IPv4& ip){
        for (size_t ind_i = 0; ind_i < SIZE; ++ind_i) {
            int tmp = 0;
            is >> tmp;
            if (tmp < MIN_EL || tmp > MAX_EL){
                throw std::runtime_error("Value shold be more than 0 and less than 255");
            }
            ip.ipv4[ind_i] = static_cast<std::uint8_t>(tmp);
        }
        return is;
    }

    friend std::ostream& operator<< (std::ostream& os, const IPv4& ip){
        for (size_t ind_i = 0; ind_i < SIZE - 1; ++ind_i) {
            os << static_cast<int>(ip.ipv4[ind_i]) << ".";
        }
        os << static_cast<int>(ip.ipv4[SIZE - 1]);
        return os;
    }

};

int main(){
    // --------------------------TESTS-------------------------- //
    std::uint8_t test_ip1[4];
    std::uint8_t test_ip2[4];

    IPv4 ipv4_1 (test_ip1);
    IPv4 ipv4_2 (test_ip2);

    std::cin >> ipv4_1;
    std::cin >> ipv4_2;

    auto flag_not_equal = ipv4_1 == ipv4_2;
    auto flag_equal = ipv4_1 != ipv4_2;
    auto flag_less = ipv4_1 < ipv4_2;
    auto flag_eq_less = ipv4_1 <= ipv4_2;
    auto flag_bigger = ipv4_1 > ipv4_2;
    auto flag_eq_bigger = ipv4_1 >= ipv4_2;

    std::cout << flag_not_equal << '\n';
    std::cout << flag_equal << '\n';
    std::cout << flag_less << '\n';
    std::cout << flag_eq_less << '\n';
    std::cout << flag_bigger << '\n';
    std::cout << flag_eq_bigger << '\n';

    ++ipv4_1;
    std::cout << ipv4_1 << '\n';

    --ipv4_1;
    std::cout << ipv4_1 << '\n';

    return 0;
}