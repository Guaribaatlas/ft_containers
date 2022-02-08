#include "tester/srcs/test_shared.hpp"
#include <stdlib.h>

void    minsert(ft::map<int, int>& mp, int val)
{
    mp.insert(ft::pair<int, int>(val, val));
}

int main()
{
    {
    ft::map<int, int>   map;

    minsert(map, 12);
    minsert(map, 21);
    }
}