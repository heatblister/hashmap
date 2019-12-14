#pragma once
#include <forward_list>
#include <stdexcept>
#include <utility>
#include <vector>

#include "anna_hash.h"

const size_t DEFAULT_TABLE_SIZE = 10;
const size_t MAX_AVERAGE_BUCKET_SIZE = 10;

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
            while (bucket_ < hashmap_->bucket_sizes_.size() &&
                   position_ >= hashmap_->bucket_sizes_[bucket_]) {
                ++bucket_;
                position_ = 0;
            }
            return *this;
        }

        // постфиксный
        iterator operator++(int) {
            iterator copy(*this);
            ++(*this);
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

    anna_hashmap()
        : size_(0),
          table_(DEFAULT_TABLE_SIZE),
          bucket_sizes_(DEFAULT_TABLE_SIZE) {}

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
        bucket_sizes_.assign(DEFAULT_TABLE_SIZE, 0);
        size_ = 0;
    }

    size_t size() const noexcept {
        return size_;
    }

    // Для отладки
    size_t buckets_number() const noexcept {
        return table_.size();
    }

    std::pair<iterator, bool> insert(const std::pair<K, V>& value) {
        if (size_ / table_.size() > MAX_AVERAGE_BUCKET_SIZE)
            rehash(2 * table_.size());

        const K& key = value.first;
        const unsigned bucket = anna_hash<K>::hash(key) % table_.size();

        int position = 0;
        for (const auto& kv : table_[bucket]) {
            if (kv.first == key) {
                return {iterator(this, bucket, position), false};
            }
            ++position;
        }

        table_[bucket].push_front(value);
        ++size_;
        ++bucket_sizes_[bucket];

        return {iterator(this, bucket, 0), true};
    }

    size_t erase(const K& key) {
        const unsigned bucket = anna_hash<K>::hash(key) % table_.size();

        auto before_it = table_[bucket].before_begin();
        for (auto it = table_[bucket].begin(); it != table_[bucket].end(); ++it)
        {
            if (it->first == key) {
                table_[bucket].erase_after(before_it);
                --size_;
                --bucket_sizes_[bucket];
                return 1;
            }
            ++before_it;
        }
        return 0;
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
    void rehash(size_t table_size) {
        std::vector<std::forward_list<std::pair<const K, V>>> t(table_size);

        std::swap(table_, t);
        bucket_sizes_.assign(table_size, 0);
        size_ = 0;

        for (const auto& bucket : t) {
            for (const auto& kv : bucket) {
                // Не использую тут метод insert, потому что он делает долгую
                // и ненужную проверку на наличие key в таблице

                const K& key = kv.first;
                const unsigned bucket = anna_hash<K>::hash(key) % table_size;

                table_[bucket].push_front(kv);
                ++size_;
                ++bucket_sizes_[bucket];
            }
        }
    }

    size_t size_;
    std::vector<std::forward_list<std::pair<const K, V>>> table_;
    std::vector<size_t> bucket_sizes_;
};
