#include <iostream>
using namespace std;

int main(int argc, char const *argv[]) {
    int a = 1234;
    int *pint = &a;

    int **p2 = &pint;  // p2指针指向p指针

    cout << "*pint= " << *pint << endl;
    cout << "pint= " << pint << endl;
    cout << "&pint= " << &pint << endl;

    cout << "**p2= " << **p2 << endl;
    cout << "*p2= " << *p2 << endl;
    cout << "p2= " << p2 << endl;

    return 0;
}
