#include "../../include/evictionPolicies/LRUPolicy.h"

template <typename K>
void LRUPolicy<K>::access(const K& key) {
    std::lock_guard<std::mutex> lock(policyMutex);
    if (map.find(key) != map.end()) {
        lruList.erase(map[key]);
    }
    lruList.push_front(key);
    map[key] = lruList.begin();
}

template <typename K>
K LRUPolicy<K>::evict() {
    std::lock_guard<std::mutex> lock(policyMutex);
    K key = lruList.back();
    lruList.pop_back();
    map.erase(key);
    return key;
}
