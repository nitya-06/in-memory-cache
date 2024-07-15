#include <iostream>
#include "fifo_policy.h"
#include "lru_policy.h"
#include "lifo_policy.h"
#include "cache.h"

int main() {
    try{
        // Create a cache with FIFO eviction policy
        auto fifoPolicy = std::make_unique<FIFOPolicy<int>>();
        Cache<int, std::string> fifoCache(3, std::move(fifoPolicy));
        std::cout << "Testing FIFO policy:" <<std:: endl;
        
        fifoCache.put(1, "one");
        fifoCache.put(2, "two");
        fifoCache.put(3, "three");
        
        std::cout << "Value for key 2: " << fifoCache.get(2) <<std:: endl; // Should be "two"
    
    
        fifoCache.put(4, "four");
        
       std:: cout << "Value for key 1 (should be evicted as it was the first inserted): ";
        std::string value_fifo = fifoCache.get(1);
        std::cout << value_fifo << std::endl; // Should be "Key not found: 1"
    
        // Create a cache with LRU eviction policy
        auto lruPolicy = std::make_unique<LRUPolicy<int>>();
        Cache<int, std::string> lruCache(3, std::move(lruPolicy));
        std::cout << "Testing LRU policy:" << std::endl;
    
    
        lruCache.put(1, "one");
        lruCache.put(2, "two");
        lruCache.put(3, "three");
    
        std::cout << "Value for key 1: " << lruCache.get(1) << std::endl; // Should be "one", Now 2 becomes least recently used
    
    
    
    
        lruCache.put(4, "four");
        std::cout << "Value for key 2 (should be evicted as it was the least recently used): ";
        std::string value_lru = lruCache.get(2);
        std::cout << value_lru << std::endl; // Should be "Key not found: 2"
    
    
        // Create a cache with LIFO eviction policy
        auto lifoPolicy = std::make_unique<LIFOPolicy<int>>();
        Cache<int, std::string> lifoCache(3, std::move(lifoPolicy));
        std::cout << "Testing LIFO policy:" << std::endl;
    
    
        lifoCache.put(1, "one");
        lifoCache.put(2, "two");
        lifoCache.put(3, "three");
        std::cout << "Value for key 2: " << lifoCache.get(2) << std::endl; // Should be "two"
    
    
        lifoCache.put(4, "four");
        std::cout << "Value for key 3 (should be evicted as it was the last inserted): ";
        std::string value_lifo = lifoCache.get(3);
        std::cout << value_lifo << std::endl; // Should be "Key not found: 3"
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    
    return 0;
}
