#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>
#include <math.h>

void print_vector(std::vector<int> vec) {
  for (auto i: vec) {
    std::cout << i << " ";
  }
  std::cout << "\n";
}

class WheelFactoriser {
private:
  std::vector<int> base;
  std::vector<int> primes;
  int max_number;

  std::vector<int> eliminate_base_in_row (std::vector<int> base, std::vector<int> row) {
    auto filter_base = [base] (int x) -> bool {
                         return std::any_of(base.begin(), base.end(),
                                     [x] (int y) -> bool { return x % y == 0; } );
                           };
    for (int i = 0; i < row.size(); i++) {
      if(filter_base(row[i])) {
        row.erase(row.begin() + i);
      }
    }
    return row;
  }

  std::vector<int> next_row(int current_max, int new_prime) {
    int old_max = current_max;
    int new_max = current_max * new_prime;
    std::vector<int> v(new_max - old_max);
    std::generate(v.begin(), v.end(), [&old_max] {return old_max++;});
    return v;
  }

  void add_next_row () {
    int next_prime = primes[base.size()];
    std::cout << "Next prime: " << next_prime << "\n";
    std::cout << "Base: ";
    
    print_vector(base); print_vector(primes);
    std::vector<int> new_primes = eliminate_base_in_row(base, next_row(max_number, next_prime));
    
    max_number *= next_prime;
    primes.insert(primes.end(), new_primes.begin(), new_primes.end());
    base.push_back(next_prime);
    return;
  }

public:
  WheelFactoriser() {
    base.push_back(2);

    primes.push_back(2);
    primes.push_back(3);
    max_number = 2;
  }
  std::vector<int> get_primes_up_to (int n) {
    while(n > max_number) {
      add_next_row();
    }

    auto filter_above = [n] (int x) {
                          return x > n;
                        };
    std::vector<int> current_primes = primes; // Deep copy? I hope.
    for (int i = 0; i < current_primes.size(); i++) {
      if(filter_above(current_primes[i])) {
        current_primes.erase(current_primes.begin() + i);
      }
    }
    return current_primes;
  }
};














std::tuple<int, int> triangular_dimensions (int triangular_index) {
  double double_index = (double)triangular_index;
  int height = (int)(floor(double_index / 2) * 2) + 1;
  int width = (int)ceil(double_index /2);
  
  return {width, height};
}

int triangular (int index) {
  int triangle = 0;
  for (int i = 1; i <= index; i++) {
    triangle += i;
  }
  return triangle;
}

void print_dims (int triangular_index) {
  auto [width, height] = triangular_dimensions(triangular_index);
  printf("Dims of tri-%d = %d: %dx%d\n",
         triangular_index,
         triangular(triangular_index),
         width, height);
  return;
}

int main(int argc, char* argv[]) {
  WheelFactoriser wheel;
  print_vector(wheel.get_primes_up_to(50));
  return 0;
}

