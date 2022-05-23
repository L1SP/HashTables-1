#pragma once
#include <iostream>
bool isPrime(size_t n) {
    for (int i = 2; i < sqrt(n)+1; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}
size_t nearestPrime(size_t n) {
    while (!isPrime(n))
        n++;
    return n;
}