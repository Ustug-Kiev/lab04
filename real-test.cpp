#include "test.h"

#include <cassert>

void
test_positive()
{
    double min = 0;
    double max = 0;
    find_minmax({1, 2, 3}, min, max);
    assert(min == 1);
    assert(max == 3);
}

void
test_3otr()
{
    int a[3] = {-1, -2, -3};
    for (int i=0; i<3; i++)
    {
        assert (a[i] < 0);
    }

}

void
test_1()
{
    int count = 0;
    int a[1];
    for (int i=0; i<1; i++)
    {
        count++;
    }
    assert (count == 1);

}

void
test_rav()
{
    int a[3] = {1,1,1};
    for (int i=0; i<3; i++)
    {
        assert (a[i] == 1);
    }
}

void
test0()
{
    double min = 0;
    double max = 0;
    int a[0];
    find_minmax({a[0]}, min, max);
    assert(min == 0);
    assert(max == 0);
}


int
main()
{
    test_positive();
    test_3otr();
    test_1();
    test_rav();
    test0();

}
