#include <iostream>
#include <chrono>
#include <thrust/device_vector.h>
#include <thrust/functional.h>
#include <thrust/transform_reduce.h>

__device__ bool is_prime(unsigned long long n) {
    if (n <= 1) {
        return false;
    }
    else if (n == 2) {
        return true;
    }
    else if (n % 2 == 0) {
        return false;
    }
    else {
        unsigned long long i = 3;
        while (i * i <= n) {
            if (n % i == 0) {
                return false;
            }
            i += 2;
        }
        return true;
    }
}

int main() {
    unsigned long long num;
    std::cout << "Enter an integer up to 20 digits: ";
    std::cin >> num;

    auto start = std::chrono::high_resolution_clock::now();

    thrust::device_vector<unsigned long long> d_num(1);
    d_num[0] = num;

    bool result = thrust::transform_reduce(d_num.begin(), d_num.end(), is_prime, false, thrust::logical_or<bool>());

    if (result) {
        std::cout << num << " is a prime number." << std::endl;
    } else {
        std::cout << num << " is a composite number." << std::endl;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << duration.count() / 1000000.0 << std::endl;

    return 0;
}