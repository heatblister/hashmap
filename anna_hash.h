#pragma once
#include <list>
#include <vector>
#include <utility>
#include <stdexcept>

const size_t DEFAULT_TABLE_SIZE = 10;

template <typename T>
class anna_hash {
public:
    static unsigned hash(const T& x);
};

template <typename K, typename V>
class anna_hashmap
{
public:
    anna_hashmap() : table_(DEFAULT_TABLE_SIZE) {}

    // TODO: сделать возвращаемое значение как в std::unordered_map
    void insert(const std::pair<K, V>& value) {
        const K& key = value.first;
        const unsigned idx = anna_hash<K>::hash(key) % table_.size();

        table_[idx].push_back(value);
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
    std::vector<std::list<std::pair<K, V>>> table_;
};

template <>
class anna_hash<unsigned> {
public:
    static unsigned hash(const unsigned& x) {
        return x;
    }
};
