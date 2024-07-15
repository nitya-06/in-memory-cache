#include <iostream>
#include "Cache.h"
#include "./include/evictionPolicies/FIFOPolicy.h"
#include "./include/evictionPolicies/LRUPolicy.h"
#include "./include/evictionPolicies/LIFOPolicy.h"

int main() {
    auto fifoPolicy = std::make_shared<FIFOPolicy<int>>();
    Cache<int, std::string> cacheFIFO(3, fifoPolicy);

    cacheFIFO.put(1, "one");
    cacheFIFO.put(2, "two");
    cacheFIFO.put(3, "three");

    std::cout << cacheFIFO.get(1).value_or("not found") << std::endl; // Should print "one"

    cacheFIFO.put(4, "four");

    std::cout << cacheFIFO.get(1).value_or("not found") << std::endl; // Should print "not found"
    std::cout << cacheFIFO.get(2).value_or("not found") << std::endl; // Should print "two"

    return 0;
}
