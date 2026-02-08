#include <iostream>
#include <cstdint>
#include <limits>

// Для типа int
int floorLog2_int(int x) {
    unsigned int ux = static_cast<unsigned int>(x);
    int log = -1;
    
    while (ux > 0) {
        ux >>= 1;
        log++;
    }
    
    return log;
}

// Для типа float
int floorLog2_float(float f) {
    union {
        float f_val;
        uint32_t u_val;
    } converter;
    
    converter.f_val = f;
    uint32_t bits = converter.u_val;
    uint32_t exponent = (bits >> 23) & 0xFF;
    uint32_t mantissa = bits & 0x7FFFFF;

    if (exponent > 0 && exponent < 0xFF) {
        return static_cast<int>(exponent) - 127;
    }
    else if (exponent == 0 && mantissa != 0) {
        int log = -150;
        
        while (mantissa > 0) {
            mantissa >>= 1;
            log++;
        }
        
        return log;
    }
    else if (exponent == 0 && mantissa == 0) {
        return std::numeric_limits<int>::min();
    }
    else {
        if (mantissa == 0) {
            return std::numeric_limits<int>::max();
        }
        return std::numeric_limits<int>::min();
    }
}

int main() {
    // Тестирование для int
    std::cout << "Тесты для int:" << std::endl;
    int int_values[] = {1, 2, 3, 4, 8, 15, 16, 255, 256, 65535, 65536};
    for (int x : int_values) {
        std::cout << "floor(log2(" << x << ")) = " << floorLog2_int(x) << std::endl;
    }
    
    // Тестирование для float
    std::cout << "\nТесты для float:" << std::endl;
    float float_values[] = {0.5f, 1.0f, 2.0f, 3.0f, 4.0f, 8.0f, 
                          0.25f, 0.125f, 10.0f, 100.0f, 0.0f};
    
    for (float f : float_values) {
        if (f > 0) {
            std::cout << "floor(log2(" << f << ")) = " << floorLog2_float(f) << std::endl;
        }
    }
    
    // Специальные случаи float
    std::cout << "\nСпециальные случаи float:" << std::endl;
    float inf = std::numeric_limits<float>::infinity();
    float nan = std::numeric_limits<float>::quiet_NaN();
    
    std::cout << "floor(log2(inf)) = " << floorLog2_float(inf) << std::endl;
    std::cout << "floor(log2(NaN)) = " << floorLog2_float(nan) << std::endl;
    
    // Минимальное денормализованное число
    float min_denorm = std::numeric_limits<float>::denorm_min();
    std::cout << "floor(log2(min_denorm)) = " << floorLog2_float(min_denorm) << std::endl;
    
    return 0;
}