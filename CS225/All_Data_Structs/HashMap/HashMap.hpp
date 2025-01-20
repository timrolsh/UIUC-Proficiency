#ifndef __HASHMap_HASHMap_HPP
#define __HASHMap_HASHMap_HPP

#include <functional>
#include <iostream>
#include "./../Array/Array.hpp"


// #define SEPARATE_CHAIN
#define OPEN_ADDR


#ifdef SEPARATE_CHAIN


#elif defined(OPEN_ADDR)

/*
Collision resolution: Open Addressing

Open as opposed to closed/fixed addressing (chaining)

in inserting, we attempt key, and if occupied jump according to probing scheme until next empty space is found
in probing, we start from key and jump according to probing scheme until next empty space is found.
It is impossible for there to be some empty spaces to be probed before the to-be-found key, as it would contradict the inserting mechanism

With open addr, load_factor cannot >= 1.
Common resizing threshold is .7

Resizing: compute new hash arr index by % w/ new num_bucket
*/

template <typename K, typename V>
struct Entry  : public std::pair<K, V>  { // for using pair funcs such as first & second
    bool occupied = false;
    bool deleted = false;

    // Default constructor
    Entry() : std::pair<K, V>(), occupied(false), deleted(false) {}
    // Parameterized constructor handling both copy and move in 1 imple
    // Need extra templating or K, V will be fixed by Entry instantiation, rendering below constructor to accept rvalues only
    // Perfect forwarding requires independent template deduction from factory function
    template <typename KeyType, typename ValType>
    Entry(KeyType&& key, ValType&& val, bool occ = false, bool del = false) : std::pair<K, V>(std::forward<KeyType>(key), std::forward<ValType>(val)), occupied(occ), deleted(del)  {}

    // Accessors for key and value
    K& key() { return this->first; }
    const K& key() const { return this->first; }

    V& val() { return this->second; }
    const V& val() const { return this->second; }

    // NOTE: references (T& key, V& val) CANNOT be class attrs, as they cannot be copied or moved!

/*
if one do not wish to inherit, one could imple:

// conversion to std::pair
operator std::pair<K, V>()  const  {
    return {key, val};
}

and desired functions such as first & second
*/
};

/*
Why maintain a deleted bool?
If we have occupied only and toggle it upon deletion,
then upon probing there will be unexpected holes rendering the probing to stop prematurely.
*/

template <typename K, typename V>
class HashMap {
private:

Array<Entry<K, V>> arr;

size_t num_keys = 0;
size_t num_buckets = 50;

size_t hash(const K& key) const  {    
    if (num_buckets == 0) throw std::runtime_error("Invalid number of buckets.");
    
    return std::hash<K>()(key) % num_buckets; // create a std::hash instance then call ()
}

public:

// note that nested class cannot access non static class members (even funcs!) so we have to pass a ref
template <bool IsConst>
class Iterator {
    using HashMapType = typename std::conditional<IsConst, const HashMap<K, V>, HashMap<K, V>>::type;
    using EntryType = typename std::conditional<IsConst, const Entry<K, V>, Entry<K, V>>::type;

private:
    HashMapType& Map; // Reference to HashMap (const or non-const)
    size_t index;         // Current index
    size_t visited;       // Number of valid elements visited
    bool is_end;          // Flag to indicate if this is the "end" iterator

    // Helper function to skip invalid or empty entries
    void skipInvalidEntries() {
        while (visited < Map.size()) {
            if (Map.arr[index].occupied && !Map.arr[index].deleted) {
                // Found a valid entry, stop skipping
                return;
            }
            // Move to the next bucket
            index = (index + 1) % Map.num_buckets;
        }
        // If we reach here, we've visited all valid entries
        is_end = true;
    }

public:
    // Constructor
    Iterator(HashMapType& Map_ref, size_t start, bool end = false)
        : Map(Map_ref), index(start), visited(0), is_end(end) {
        if (end || Map.size() == 0) {
            // Explicitly mark as "end" if requested or if the Map is empty
            is_end = true;
        } else {
            // Skip to the first valid entry
            skipInvalidEntries();
        }
    }

    // Dereference operator
    EntryType& operator*() {
        if (is_end) {
            throw std::out_of_range("Dereferencing end iterator");
        }
        return Map.arr[index];
    }

    const EntryType& operator*() const {
        if (is_end) {
            throw std::out_of_range("Dereferencing end iterator");
        }
        return Map.arr[index];
    }

    // Pre-increment
    Iterator& operator++() {
        if (is_end) {
            throw std::out_of_range("Incrementing end iterator");
        }
        ++visited;
        index = (index + 1) % Map.num_buckets;
        skipInvalidEntries();
        return *this;
    }

    // Post-increment
    Iterator operator++(int) {
        Iterator temp = *this;
        ++(*this);
        return temp;
    }

    // Equality operators
    bool operator==(const Iterator& other) const {
        return is_end == other.is_end && (is_end || (index == other.index && &Map == &other.Map));
    }

    bool operator!=(const Iterator& other) const {
        return !(*this == other);
    }
};

/*
    // To declare all specializations of Iterator as friends:
    template <bool IsConst>
    friend class Iterator;
*/

// Begin and end functions
// MuMap begin() and end()
Iterator<false> begin() {
    return Iterator<false>(*this, 0);
}

Iterator<false> end() {
    return Iterator<false>(*this, 0, true);
}

// Const begin() and end()
Iterator<true> begin() const {
    return Iterator<true>(*this, 0);
}

Iterator<true> end() const {
    return Iterator<true>(*this, 0, true);
}


HashMap()  {
    arr.resize(num_buckets, Entry<K, V>());
}

HashMap(const HashMap& other) : arr(other.arr), num_keys(other.num_keys), num_buckets(other.num_buckets) {}

HashMap& operator=(const HashMap& other)    {
    if (this != &other) {
        arr = other.arr;
        num_keys = other.num_keys;
        num_buckets = other.num_buckets;
    }
    return *this;
}

// Moving an int does not zero out the source value. The source value remains unchanged after the move operation.
// So we have to handle the move op explicitly to set the int attrs of the src.

HashMap(HashMap&& other) : arr(std::move(other.arr)), num_keys(other.num_keys), num_buckets(other.num_buckets)    {
    other.num_keys = 0;
    other.num_buckets = 0;
}


HashMap& operator=(HashMap&& other)    {
    if (this != &other) {
        arr = std::move(other.arr);
        num_keys = other.num_keys;
        num_buckets = other.num_buckets;

        other.num_keys = 0;
        other.num_buckets = 0;
    }
    return *this;
}


void insert(const K& key, const V& val);
void insert(const std::pair<K, V>& pair); // for pair overload
bool erase(const K& key);
void clear() {arr.clear(); num_keys = num_buckets = 0;}

bool contains(const K& key) const;
bool empty() const;
size_t size() const;

V& operator[](const K& key);
const V& operator[] (const K& key) const;
V& at(const K& key);

double load_factor() {return static_cast<double>(num_keys)/num_buckets;}

/*
The following imple for begin and end will NOT work as it doesn't acnum_keys for wrap around in open addressing
auto begin() const -> decltype(arr.begin()) { 
    auto begin = arr.begin();
    while  ( (*begin).deleted || !(*begin).occupied )   {
        ++begin;
    }
    return begin;
}
auto end() const -> decltype(arr.end()) {
    auto end = arr.end();
    while  ( (*(end + (-1)) ).deleted || !(*(end + (-1)) ).occupied )   {
        --end;
    }
    return end;
}
*/

};


template <typename K, typename V>
void HashMap<K, V>::insert(const K& key, const V& val) {
    if (load_factor() > 0.7)    {
        
        auto old_arr = std::move(arr); 
        // saving old arr goes first
        // involves adjustment of arr so we cannot use arr as src

        arr.resize(num_buckets*2, Entry<K, V>()); // not exception safe so goes second
        num_buckets = arr.size();
        num_keys = 0;

        for (const auto& entry : old_arr)   {
            if (entry.occupied && !entry.deleted) {
                insert(entry.key(), entry.val());
            }
        }

    }

try
{
    auto idx = hash(key);
    auto start_idx = idx;

    while (1) {
        auto& entry = arr[idx];
        if (entry.occupied && !entry.deleted && entry.key() == key)    {
            entry.val() = val; // if exists, update
            return;
        }
        if (!entry.occupied || entry.deleted) {
            entry.key() = key; 
            entry.val() = val;
            entry.occupied = true;
            if (entry.deleted) entry.deleted = false; // reactivated
            ++num_keys;
            break;
        }
        idx = (idx + 1) % num_buckets; // wrap around
        if (idx == start_idx) throw std::runtime_error("Map is full.\n");
    }
}
catch(const std::exception& e)
{
    std::cout << "insert failed" << '\n';
}

}

template <typename K, typename V>
void HashMap<K, V>::insert(const std::pair<K, V>& pair) {
    if (load_factor() > 0.7)    {
        auto old_arr = std::move(arr); 
        // saving old arr goes first
        // involves adjustment of arr so we cannot use arr as src

        arr.resize(num_buckets*2, Entry<K, V>()); // not exception safe so goes second
        num_buckets = arr.size();
        num_keys = 0;

        for (const auto& entry : old_arr)   {
            if (entry.occupied && !entry.deleted) {
                insert(entry.key(), entry.val());
            }
        }

    }

    auto idx = hash(pair.first);
    auto start_idx = idx;

while (1) {
    auto& entry = arr[idx];
    if (entry.occupied && !entry.deleted && entry.key() == pair.first) {
        entry.val() = pair.second; // if exists, update
        return;
    }
    if (!entry.occupied || entry.deleted) {
        entry.key() = pair.first;
        entry.val() = pair.second;
        entry.occupied = true;
        if (entry.deleted) entry.deleted = false; // reactivated
        ++num_keys;
        break;
    }
    idx = (idx + 1) % num_buckets; // wrap around
    if (idx == start_idx) throw std::runtime_error("Map is full.\n");
}

}

template <typename K, typename V>
bool HashMap<K, V>::erase(const K& key) {
    auto idx = hash(key);
    auto start_idx = idx;
    while (1) {
        auto& entry = arr[idx];
        if (entry.key() == key && entry.occupied && !entry.deleted) {
            entry.deleted = true;
            --num_keys;
            return true;
        }
        if (!entry.occupied) {
            // Stop searching if an empty slot is found (key does not exist, as linear probing keys are contiguous)
            return false;
        }
        idx = (idx + 1) % num_buckets; // wrap around
        if (idx == start_idx) return false;
    }
    return false;
}

template <typename K, typename V>
bool HashMap<K, V>::contains(const K& key) const {
    auto idx = hash(key);
    auto start_idx = idx;
    while (1) {
        auto& entry = arr[idx];
        if (entry.key() == key && !entry.deleted && entry.occupied) {
            return true;
        }
        idx = (idx + 1) % num_buckets; // wrap around
        if (idx == start_idx)   return false;
    }
    return false;
}

template <typename K, typename V>
V& HashMap<K, V>::operator[](const K& key) {
    auto idx = hash(key);
    auto start_idx = idx;
    while (1) {
        auto& entry = arr[idx];
        if (entry.key() == key && entry.occupied && !entry.deleted) { // check occupied -- map is initialized w/ default keys w/ occupied = false
            return entry.val();
        }

        if (!entry.occupied || entry.deleted)  {
            insert(key, V());
            return this->operator[](key);
        }

        idx = (idx + 1) % num_buckets; // wrap around
        if (idx == start_idx) {throw std::runtime_error("Map is full.");}
    }
}

template <typename K, typename V>
const V& HashMap<K, V>::operator[](const K& key) const {
    auto idx = hash(key);
    auto start_idx = idx;
    while (1) {
        auto& entry = arr[idx];
        if (entry.key() == key && entry.occupied && !entry.deleted) {
            return entry.val();
        }
        idx = (idx + 1) % num_buckets; // wrap around
        if (idx == start_idx) throw std::invalid_argument("accessing nonexistent key through const []");
    }
}

template <typename K, typename V>
V& HashMap<K, V>::at(const K& key) {
    auto idx = hash(key);
    auto start_idx = idx;
    while (1) {
        auto& entry = arr[idx];
        if (entry.key() == key && entry.occupied && !entry.deleted) {
            return entry.val();
        }
        idx = (idx + 1) % num_buckets; // wrap around
        if (idx == start_idx) throw std::out_of_range("Key is not present.\n");
    }
    throw std::runtime_error("Key is not present.\n");
}


template <typename K, typename V>
bool HashMap<K, V>::empty() const {
    return num_keys == 0;
}

template <typename K, typename V>
size_t HashMap<K, V>::size() const {
    return num_keys;
}


#endif // imple toggle

#endif // __HASHMap_HASHMap_HPP