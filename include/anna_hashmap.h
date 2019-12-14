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
    class iterator {
    public:
        iterator(anna_hashmap* hashmap, size_t bucket, size_t position)
            : hashmap_(hashmap), bucket_(bucket), position_(position) {}

        iterator(const iterator& it)
            : hashmap_(it.hashmap_),
              bucket_(it.bucket_),
              position_(it.position_) {}

        // префиксный
        iterator& operator++() {
            ++position_;
            while (position_ >= hashmap_->table_[bucket_].size()) {
                ++bucket_;
                position_ = 0;
            }
            return *this;
        }

        // постфиксный
        iterator operator++(int) {
            iterator copy(*this);
            ++position_;
            while (position_ >= hashmap_->table_[bucket_].size()) {
                ++bucket_;
                position_ = 0;
            }
            return copy;
        }

        std::pair<const K, V>& operator* ()
        {
            auto it = hashmap_->table_[bucket_].begin();
            std::advance(it, position_);
            return *it;
        }

        std::pair<const K, V>* operator-> ()
        {
            auto it = hashmap_->table_[bucket_].begin();
            std::advance(it, position_);
            return &(*it);
        }

        bool operator !=(const iterator& it) {
            return hashmap_ != it.hashmap_ || bucket_ != it.bucket_ ||
                    position_ != it.position_;
        }

    private:
        anna_hashmap* hashmap_;
        size_t bucket_;
        size_t position_;
    };

    anna_hashmap() : size_(0), table_(DEFAULT_TABLE_SIZE) {}

    iterator begin() {
        if (size_ == 0)
            return end();

        size_t bucket = 0;
        while (table_[bucket].empty()) {
            ++bucket;
        }
        return iterator(this, bucket, 0);
    }

    iterator end() {
        return iterator(this, table_.size(), 0);
    }

    void clear() noexcept {
        table_.assign(DEFAULT_TABLE_SIZE);
        size_ = 0;
    }

    size_t size() const noexcept {
        return size_;
    }

    std::pair<iterator, bool> insert(const std::pair<K, V>& value) {
        const K& key = value.first;
        const unsigned bucket = anna_hash<K>::hash(key) % table_.size();

        int position = 0;
        for (const auto& kv : table_[bucket]) {
            if (kv.first == key) {
                return {iterator(this, bucket, position), false};
            }
            ++position;
        }

        table_[bucket].push_back(value);
        ++size_;
        return {iterator(this, bucket, table_[bucket].size() - 1), true};
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
    std::vector<std::list<std::pair<const K, V>>> table_;
};
