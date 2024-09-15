#include <vector>
#include <stdexcept>
#include <sstream>

template <class K, class V>
class HashMap {
public:
    HashMap() = default;

    std::string operator[](int i) {
        if (i >= keys.size()) throw std::out_of_range("Key not found");
        std::stringstream k;
        k << keys[i];
        std::stringstream v;
        v << values[i];
        return "{" + k.str() + ": " + v.str() + "}";
    }

    friend std::ostream& operator<<(std::ostream& os, HashMap const& hm) { 
        os << "{";
        for (size_t i = 0; i < hm.keys.size(); i++) {
            std::stringstream ke;
            std::stringstream va;
            ke << hm.keys[i];
            va << hm.values[i];
            os << ke.str() << ": " << va.str();
            if (hm.keys.size() - i > 1) os << ", ";
        }
        os << "}";
        return os;
    }

    friend bool operator==(const HashMap<K, V>& lhs, const HashMap<K, V>& rhs) {
        return lhs.keys == rhs.keys && lhs.values == rhs.values;
    }

    void add(const K& key, const V& value) {
        int index = getPosition(key);
        if (index != -1) throw std::invalid_argument("Key already exists");
        keys.push_back(key);
        values.push_back(value);
    }

    void set(int index, const K& key, const V& value) {
        if (index < 0 || index >= keys.size()) throw std::out_of_range("Index out of range");
        int existingKeyIndex = getPosition(key);
        if (existingKeyIndex != -1 && existingKeyIndex != index) throw std::invalid_argument("Key already exists");
        keys[index] = key;
        values[index] = value;
    }

    V getValue(const K& key) const {
        int index = getPosition(key);
        if (index == -1) throw std::out_of_range("Key not found");
        return values[index];
    }

    void setValue(const K& key, const V& value) {
        int index = getPosition(key);
        if (index == -1) throw std::out_of_range("Key not found");
        values[index] = value;
    }

    void remove(const K& key) {
        int index = getPosition(key);
        if (index == -1) throw std::out_of_range("Key not found");
        keys.erase(keys.begin() + index);
        values.erase(values.begin() + index);
    }

    void remove(int index) {
        if (index < 0 || index >= keys.size()) throw std::out_of_range("Index out of range");
        keys.erase(keys.begin() + index);
        values.erase(values.begin() + index);
    }

    int getIndex(const K& key) const {
        int index = getPosition(key);
        if (index == -1) throw std::out_of_range("Key not found");
        return index;
    }

    int length() const {
        return keys.size();
    }

    void clear() {
        keys.clear();
        values.clear();
    }

private:
    std::vector<K> keys;
    std::vector<V> values;

    int getPosition(const K& key) const {
        for (int i = 0; i < keys.size(); i++) {
            if (keys[i] == key) return i;
        }
        return -1;
    }
};