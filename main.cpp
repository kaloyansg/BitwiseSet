#include <iostream>
#include "Set.h"

int main()
{
    std::cout << "Hello World!\n";

    Set set(11);
    set.add(2);
    set.add(5);
    set.add(7);
    set.add(9);
    set.remove(5);

    Set set2(20);
    set2.add(0);
    set2.add(9);
    set2.add(14);
    set2.add(7);

    Set result = getUnion(set, set2);
    result.print();
}