#pragma once
#include "EvictionPolicy.h"
#include <stack>
#include <unordered_set>
#include <mutex>

template <typename K>
class LIFOPolicy : public EvictionPolicy<K> {
public:
    void access(const K& key) override;
    K evict() override;

private:
    std::stack<K> stack;
    std::unordered_set<K> set;
    std::mutex policyMutex;
};
