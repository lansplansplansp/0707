#include <iostream>
#include "smartptr.h"
using namespace std;

int main()
{
    // Test Constructor and Assignment Operator Overloaded
    SmartPtr<int> p1(new int(0));
    p1 = p1;
    // Test Copy Constructor
    SmartPtr<int> p2(p1);
    // Test Assignment Operator Overloaded
    SmartPtr<int> p3(new int(1));
    p3 = p1;
    
    return 0;
}