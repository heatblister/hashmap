#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "anna_hashmap.h"

using std::cout;
using std::endl;

int main()
{    
    anna_hashmap<std::vector<int>, std::string> m;
    m.insert({{1, 2}, "ololo"});
    m.insert({{3, -4, 0}, "ururu"});

    cout << m.at({1, 2}) << endl;
    cout << m.at({3, -4, 0}) << endl;

    cout << m.size() << endl;

    anna_hashmap<std::string, int> m2;
    m2.insert({"one", 1});
    m2.insert({"two", 2});
    m2.insert({"three", 3});
    m2.insert({"four", 4});
    for (auto it = m2.begin(); it != m2.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }

    auto info = m2.insert({"one", 101});
    cout << info.first->second << endl;

    return 0;
}
