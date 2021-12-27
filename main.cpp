#include <iostream>
#include <fstream>
#include <iomanip>
// #include "user.h"
#include "cafe.h"
using namespace std;

main()
{
    List *ls = new List();
    createList();
    operation(ls);
    // readFromFile(ls);
    // cout<<returnCoffeePrice(ls, "3");
}