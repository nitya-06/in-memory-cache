#include "../../include/evictionPolicies/FIFOPolicy.h"

template <typename K>
void FIFOPolicy<K>::access(const K& key) {
    std::lock_guard<std::mutex> lock(policyMutex);
    if (set.find(key) == set.end()) {
        queue.push(key);
        set.insert(key);
    }
}

template <typename K>
K FIFOPolicy<K>::evict() {
    std::lock_guard<std::mutex> lock(policyMutex);
    K key = queue.front();
    queue.pop();
    set.erase(key);
    return key;
}
