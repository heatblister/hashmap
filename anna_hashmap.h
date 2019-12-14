#pragma once
#include <list>
#include <stdexcept>
#include <utility>
#include <vector>

#include "anna_hash.h"

const size_t DEFAULT_TABLE_SIZE = 10;

template <typename K, typename V>
class anna_hashmap
{
public:
    anna_hashmap() : size_(0), table_(DEFAULT_TABLE_SIZE) {}

    void clear() noexcept {
        table_.assign(DEFAULT_TABLE_SIZE);
        size_ = 0;
    }

    size_t size() const noexcept {
        return size_;
    }

    // TODO: сделать возвращаемое значение как в std::unordered_map
    void insert(const std::pair<K, V>& value) {
        const K& key = value.first;
        const unsigned idx = anna_hash<K>::hash(key) % table_.size();

        table_[idx].push_back(value);
        ++size_;
    }

    V& at(const K& key) {
        const unsigned idx =  anna_hash<K>::hash(key) % table_.size();
        for (auto& kv : table_[idx]) {
            if (kv.first == key)
                return kv.second;
        }
        throw std::out_of_range(
                "container does not have an element with the specified key");
    }

    const V& at(const K& key) const {
        const unsigned idx =  anna_hash<K>::hash(key) % table_.size();
        for (const auto& kv : table_[idx]) {
            if (kv.first == key)
                return kv.second;
        }
        throw std::out_of_range(
                "container does not have an element with the specified key");
    }

private:
    size_t size_;
    std::vector<std::list<std::pair<K, V>>> table_;
};
