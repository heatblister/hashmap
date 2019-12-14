#include <iostream>
#include <string>
#include "anna_hash.h"

using std::cout;
using std::endl;

int main()
{
    anna_hashmap<unsigned, std::string> m;
    m.insert({14u, std::string("ololo")});
    m.insert({24u, std::string("ururu")});

    cout << m.at(14u) << endl;
    cout << m.at(24u) << endl;
    // cout << m.at(34u) << endl;

    return 0;
}
