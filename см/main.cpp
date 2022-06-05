#include <iostream>

using namespace std;

int main()
{
    int mass[10];
    for (int i=0; i <10; i++)
    {
        cout << "введи число" << endl;
        cin >> mass[i];
    }
    for (int i=0; i<10; i++)
    {
        cout << mass[i] << endl;
    }

}
