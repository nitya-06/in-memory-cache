#ifndef CACHE_H
#define CACHE_H

#include "eviction_policy.h"
#include <unordered_map>
#include <memory>
#include <mutex>
#include <iostream>


template<typename Key, typename Value>
class Cache {
private:
    std::unordered_map<Key, Value> cache;
    std::unique_ptr<EvictionPolicy<Key>> evictionPolicy;
    size_t capacity;
    std::mutex mtx;

public:
    Cache(size_t cap, std::unique_ptr<EvictionPolicy<Key>> policy)
        : evictionPolicy(std::move(policy)), capacity(cap) {}

    void put(const Key& key, const Value& value) {
        std::lock_guard<std::mutex> lock(mtx);
        try{
            if (cache.size() >= capacity) {
                Key evictedKey = evictionPolicy->evict();
                std::cout << "Evicting key: " << evictedKey << std::endl;
                    cache.erase(evictedKey);
                    evictionPolicy->keyRemoved(evictedKey);
            }
    
            cache[key] = value;
            evictionPolicy->keyAdded(key);
        } catch (...) {
            std::cerr << "Error: Unable to insert key-value pair." << std::endl;
        }
    }

    Value get(const Key& key) {
        std::lock_guard<std::mutex> lock(mtx);
        Value result;
        try{
            auto it = cache.find(key);
            if (it != cache.end()) {
                evictionPolicy->keyAccessed(key);
                result = it->second;
            }
            else{
                std::cerr << "Key not found: " << key << std::endl;
            }
        } catch (...) {
            std::cerr << "Error: Unable to retrieve value for key." << std::endl;
        }
        return result;
    }

    bool exixts(const Key& key){
        std::lock_guard<std::mutex> lock(mtx);
        auto it = cache.find(key); 
        if (it != cache.end()) {
            return true;
        }
        return false;
    }

    void remove(const Key& key){
        std::lock_guard<std::mutex> lock(mtx);
        try{
            auto it = cache.find(key);
            if (it != cache.end()){
                cache.erase(it);
                evictionPolicy->keyRemoved(key);
            }
            else{
                std::cerr << "Key not found: " << key << std::endl;
                return;
            }
        } catch (...) {
            std::cerr << "Error: Unable to remove key-value pair." << std::endl;
        }
        
    }
    
};

#endif // CACHE_H
