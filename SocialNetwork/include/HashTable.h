#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <list>
#include <string>

using namespace std;

template <typename K, typename V>
class HashTable
{
private:
    static const int TABLE_SIZE = 100;
    vector<list<pair<K, V>>> table;

    int hashFunction(const K &key) const
    {
        hash<K> hashFunc;
        return hashFunc(key) % TABLE_SIZE;
    }

public:
    HashTable() : table(TABLE_SIZE) {}

    void insert(const K &key, const V &value)
    {
        int index = hashFunction(key);
        table[index].push_back(make_pair(key, value));
    }

    V *get(const K &key)
    {
        int index = hashFunction(key);
        for (auto &pair : table[index])
        {
            if (pair.first == key)
            {
                return &pair.second;
            }
        }
        return nullptr; 
    }

    bool remove(const K &key)
    {
        int index = hashFunction(key);
        for (auto it = table[index].begin(); it != table[index].end(); ++it)
        {
            if (it->first == key)
            {
                table[index].erase(it);
                return true;
            }
        }
        return false;
    }
};

#endif