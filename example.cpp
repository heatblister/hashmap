#include <iostream>
#include <string>
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
    m2.insert({"ololo", 17});
    cout << m2.at("ololo") << endl;

    return 0;
}
