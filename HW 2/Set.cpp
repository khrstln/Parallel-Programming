#include <vector>
#include <algorithm>
#include <iostream>

template <typename T>
class Set {
private:
    std::vector<T> elements;

public:
    bool add(T value) {
        if (std::find(elements.begin(), elements.end(), value) == elements.end()) {
            elements.push_back(value);
            return true;
        }
        return false;
    }

    bool remove(T value) {
        if (std::find(elements.begin(), elements.end(), value) != elements.end()) {
            elements.erase(std::find(elements.begin(), elements.end(), value));
            return true;
        }
        return false;
    }

    bool contains(T value) const {
        return std::find(elements.begin(), elements.end(), value) != elements.end();
    }
};


int main() {
    Set<int> myset;

    myset.add(1);
    myset.add(2);
    myset.add(3);

    std::cout << "Set contains 1: " << myset.contains(1) << std::endl; 
    std::cout << "Set contains 2: " << myset.contains(2) << std::endl;
    std::cout << "Set contains 3: " << myset.contains(3) << std::endl;

    myset.remove(2);
    std::cout << std::endl;

    std::cout << "Set contains 1: " << myset.contains(1) << std::endl; 
    std::cout << "Set contains 2: " << myset.contains(2) << std::endl;
    std::cout << "Set contains 3: " << myset.contains(3) << std::endl;

    return 0;
}