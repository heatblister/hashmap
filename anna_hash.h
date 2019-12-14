#pragma once
#include <list>
#include <vector>
#include <utility>
#include <stdexcept>

const size_t DEFAULT_TABLE_SIZE = 10;

template <typename T>
class anna_hash {
public:
    static size_t hash(const T& x);
};

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

template <>
class anna_hash<char> {
public:
    static size_t hash(const char& x) {
        return static_cast<size_t>(x) << 24;
    }
};

template <>
class anna_hash<uint8_t> {
public:
    static size_t hash(const uint8_t& x) {
        return static_cast<size_t>(x) << 24;
    }
};

template <>
class anna_hash<int8_t> {
public:
    static size_t hash(const int8_t& x) {
        return static_cast<size_t>(x) << 24;
    }
};

template <>
class anna_hash<uint16_t> {
public:
    static size_t hash(const uint16_t& x) {
        return static_cast<size_t>(x) << 16;
    }
};

template <>
class anna_hash<int16_t> {
public:
    static size_t hash(const int16_t& x) {
        return static_cast<size_t>(x) << 16;
    }
};

template <>
class anna_hash<uint32_t> {
public:
    static size_t hash(const uint32_t& x) {
        return static_cast<size_t>(x);
    }
};

template <>
class anna_hash<int32_t> {
public:
    static size_t hash(const int32_t& x) {
        return static_cast<size_t>(x);
    }
};

template <>
class anna_hash<uint64_t> {
public:
    static size_t hash(const uint64_t& x) {
        return static_cast<size_t>(x >> 32) ^ static_cast<size_t>(x);
    }
};

template <>
class anna_hash<int64_t> {
public:
    static size_t hash(const int64_t& x) {
        return anna_hash<uint64_t>::hash(static_cast<uint64_t>(x));
    }
};

template <typename T>
class anna_hash<std::vector<T>> {
public:
    static size_t hash(const std::vector<T>& x) {
        size_t h = 0;
        for (const T& elem : x) {
            h ^= anna_hash<T>::hash(elem);
        }
        return h;
    }
};

template <>
class anna_hash<std::string> {
public:
    static size_t hash(const std::string& x) {
        size_t h = 0;
        for (const char& c : x) {
            h ^= anna_hash<char>::hash(c);
        }
        return h;
    }
};
