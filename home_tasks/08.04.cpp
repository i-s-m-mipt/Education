#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <algorithm>

const int N_MAX = 1000;

int main() {
    std::string target = "cat";
    
    double mutation_rate = 0.1;
    int copies = 50;
    
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<double> prob(0.0, 1.0);
    std::uniform_int_distribution<int> letter(0, 25); // a-z
    
    std::string current;
    for (size_t i = 0; i < target.size(); i++) {
        current += 'a' + letter(eng);
    }
    
    std::cout << "Цель: " << target << "\n";
    std::cout << "Начало: " << current << "\n\n";
    
    for (int iter = 0; iter < N_MAX; iter++) {
        std::vector<std::pair<int, std::string>> results;
        
        for (int c = 0; c < copies; c++) {
            std::string candidate = current;
            int errors = 0;
            
            for (size_t i = 0; i < target.size(); i++) {
                if (prob(eng) < mutation_rate) {
                    candidate[i] = 'a' + letter(eng);
                }
                if (candidate[i] != target[i]) {
                    errors++;
                }
            }
            
            if (errors == 0) {
                std::cout << "Найдено за " << iter + 1 << " итераций: " << candidate << "\n";
                return 0;
            }
            
            results.push_back({errors, candidate});
        }
        
        auto best = std::min_element(results.begin(), results.end(),
            [](auto& a, auto& b) { return a.first < b.first; });
        
        current = best->second;
        
        std::cout << "Итерация " << iter << ": " << current 
                  << " (ошибок: " << best->first << ")\n";
    }
    
    std::cout << "Не удалось найти за 1000 итераций\n";
    return 1;
}