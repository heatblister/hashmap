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
    for (auto it = m2.begin(); it != m2.end(); it++) {
        cout << it->first << " " << it->second << endl;
    }

    cout<< "Deleting element" << endl;
    m2.erase("four");
    for (auto it = m2.begin(); it != m2.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }

    auto info = m2.insert({"one", 101});
    cout << info.first->second << endl;

    anna_hashmap<std::pair<int,int>, std::string> m3;
    m3.insert({{4,5},"lalala"});
    cout << m3.at({4,5}) << endl;

    anna_hashmap<std::array<int,4>, std::vector<std::string>> m4;
    m4.insert({{13,16,18,10},{"okok","ghghg"}});
    cout << m4.at({13,16,18,10})[0] << endl;

    anna_hashmap<double,std::string> m5;
    m5.insert({24.0001,"covfefe"});
    m5.insert({0.035903,"abyrlavg"});

    for (auto it = m5.begin(); it != m5.end(); it++) {
        cout << it->first << " " << it->second << endl;
    }

    return 0;
}
