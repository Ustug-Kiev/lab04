#include "svg.h"

#include <cassert>

void test_1()
{
    assert(check(10, 900) == false);
}

void test_2()
{
    assert(check(10, 50) == false);
}

void test_3()
{
    assert(check(10, 700) == true);
}


int main()
{
    test_1();
    test_2();
    test_3();

    return 0;
}
