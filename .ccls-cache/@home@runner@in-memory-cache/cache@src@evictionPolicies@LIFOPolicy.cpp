#include "../../include/evictionPolicies/LIFOPolicy.h"

template <typename K>
void LIFOPolicy<K>::access(const K& key) {
    std::lock_guard<std::mutex> lock(policyMutex);
    if (set.find(key) == set.end()) {
        stack.push(key);
        set.insert(key);
    }
}

template <typename K>
K LIFOPolicy<K>::evict() {
    std::lock_guard<std::mutex> lock(policyMutex);
    K key = stack.top();
    stack.pop();
    set.erase(key);
    return key;
}
