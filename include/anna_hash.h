#pragma once
#include <array>
#include <list>
#include <string>
#include <utility>
#include <vector>

template <typename T>
class anna_hash {
public:
    static size_t hash(const T& x);
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

template <>
class anna_hash<double>{
public:
    static size_t hash(const double& x) {
        uint64_t const & y = reinterpret_cast<uint64_t const&>(x);
        return anna_hash<uint64_t>::hash(y);
    }
};

template <>
class anna_hash<float>{
public:
    static size_t hash(const float& x) {
        uint32_t const & y = reinterpret_cast<uint32_t const&>(x);
        return anna_hash<uint32_t>::hash(y);
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

template <typename T, size_t size>
class anna_hash<std::array<T, size>> {
public:
    static size_t hash(const std::array<T, size>& x) {
        size_t h = 0;
        for (const T& elem : x) {
            h ^= anna_hash<T>::hash(elem);
        }
        return h;
    }
};

template <typename F, typename S>
class anna_hash<std::pair<F,S>> {
public:
    static size_t hash(const std::pair<F,S>& x) {
        return anna_hash<F>::hash(x.first) ^ anna_hash<S>::hash(x.second);
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
