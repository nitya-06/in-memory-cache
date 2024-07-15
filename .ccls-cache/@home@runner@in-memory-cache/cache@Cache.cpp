#include "Cache.h"
#include <experimental/optional>


template <typename K, typename V>
Cache<K, V>::Cache(size_t capacity, std::shared_ptr<EvictionPolicy<K>> policy)
    : capacity(capacity), evictionPolicy(policy) {}

template <typename K, typename V>
void Cache<K, V>::put(const K& key, const V& value) {
    std::lock_guard<std::mutex> lock(cacheMutex);
    if (storage.size() >= capacity) {
        K evictKey = evictionPolicy->evict();
        storage.erase(evictKey);
    }
    storage[key] = value;
    evictionPolicy->access(key);
}

template <typename K, typename V>
std::experimental::optional<V> Cache<K, V>::get(const K& key) {
    std::lock_guard<std::mutex> lock(cacheMutex);
    if (storage.find(key) != storage.end()) {
        evictionPolicy->access(key);
        return storage[key];
    }
    return std::experimental::nullopt;
}
