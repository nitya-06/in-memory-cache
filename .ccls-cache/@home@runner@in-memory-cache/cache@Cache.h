#pragma once
#include <unordered_map>
#include <memory>
#include <mutex>
#include <optional>
#include <experimental/optional>
#include "./include/evictionPolicies/EvictionPolicy.h"
#include "./include/evictionPolicies/FIFOPolicy.h"
#include "./include/evictionPolicies/LRUPolicy.h"
#include "./include/evictionPolicies/LIFOPolicy.h"

template <typename K, typename V>
class Cache {
public:
    Cache(size_t capacity, std::shared_ptr<EvictionPolicy<K>> policy);
    void put(const K& key, const V& value);
    std::experimental::optional<V> get(const K& key);

private:
    size_t capacity;
    std::unordered_map<K, V> storage;
    std::shared_ptr<EvictionPolicy<K>> evictionPolicy;
    std::mutex cacheMutex;
};
