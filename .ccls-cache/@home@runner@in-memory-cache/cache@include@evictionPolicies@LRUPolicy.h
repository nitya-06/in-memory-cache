#pragma once
#include "EvictionPolicy.h"
#include <list>
#include <unordered_map>
#include <mutex>

template <typename K>
class LRUPolicy : public EvictionPolicy<K> {
public:
    void access(const K& key) override;
    K evict() override;

private:
    std::list<K> lruList;
    std::unordered_map<K, typename std::list<K>::iterator> map;
    std::mutex policyMutex;
};
