#pragma once
#include <unordered_map>

template <typename K>
class EvictionPolicy {
public:
    virtual void access(const K& key) = 0;
    virtual K evict() = 0;
    virtual ~EvictionPolicy() = default;
};
