#include <iostream>
#include <fstream>
#include <iomanip>
#include "cafe.h"
using namespace std;

main()
{
    List *ls = new List();
    createList();
    operation(ls);
}