#pragma once
#include "EvictionPolicy.h"
#include <queue>
#include <unordered_set>
#include <mutex>

template <typename K>
class FIFOPolicy : public EvictionPolicy<K> {
public:
    void access(const K& key) override;
    K evict() override;

private:
    std::queue<K> queue;
    std::unordered_set<K> set;
    std::mutex policyMutex;
};
