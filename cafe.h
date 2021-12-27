#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include <ctime>
#include "sales.h"
#include "bestseller.h"
using namespace std;
struct Element
{
    string name, id, stocks;
    float price;
    Element *next;
    Element *prev;
};
struct List
{
    int n;
    Element *head;
    Element *tail;
};
List *createList()
{
    List *ls = new List();
    ls->n = 0;
    ls->head = NULL;
    ls->tail = NULL;
    return ls;
}
void displayList(List *ls)
{
    Element *node = new Element();
    node = ls->head;
    if (ls->head == NULL)
    {
        cout << "Empty";
    }
    while (node != NULL)
    {
        cout << node->id << setw(10) << node->name << setw(10) << node->price << setw(10) << node->stocks << endl;
        node = node->next;
    }
}
bool fileExists(const string &name)
{
    if (FILE *file = fopen(name.c_str(), "r"))
    {
        fclose(file);
        return true;
    }
    else
    {
        return false;
    }
}
void insertBegin(List *ls, string id, string name, float price, string stocks)
{
    Element *node = new Element();
    node->id = id;
    node->name = name;
    node->price = price;
    node->stocks = stocks;

    node->next = ls->head;
    node->prev = NULL;
    if (ls->n == 0)
    {
        ls->tail = node;
    }
    if (ls->n != 0)
        ls->head->prev = node;
    ls->head = node;
    ls->n = ls->n + 1;
}
void insertEnd(List *ls, string id, string name, float price, string stocks)
{
    Element *node = new Element();
    if (ls->n == 0)
        insertBegin(ls, id, name, price, stocks);
    else
    {
        node->id = id;
        node->name = name;
        node->price = price;
        node->stocks = stocks;

        node->next = NULL;
        node->prev = ls->tail;
        ls->tail->next = node;
        ls->tail = node;
        ls->n = ls->n + 1;
    }
}
void writeNewFile(List *ls)
{
    Element *node = new Element();
    node = ls->head;
    fstream file;
    file.open("coffeeList.txt", ios::out);
    while (node != NULL)
    {
        if (node->next != NULL)
        {
            file << node->id << setw(10) << node->name << setw(10) << node->price << setw(10) << node->stocks << "\n";
        }
        else
        {
            file << node->id << setw(10) << node->name << setw(10) << node->price << setw(10) << node->stocks;
        }
        node = node->next;
    }
    file.close();
}

void writeExistingFile(List *ls)
{
    Element *node = new Element();
    node = ls->head;
    fstream file;
    file.open("coffeeList.txt", ios::app);
    while (node != NULL)
    {
        file << "\n"
             << node->id << setw(10) << node->name << setw(10) << node->price << setw(10) << node->stocks;
        node = node->next;
    }
    file.close();
}

void readFromFile(List *ls)
{
    string id, stocks;
    float price;
    string name;
    fstream file;
    Element *node = new Element();
    file.open("coffeeList.txt", ios::in);
    while (!file.eof())
    {
        file >> id >> setw(10) >> name >> setw(10) >> price >> setw(10) >> stocks;
        insertEnd(ls, id, name, price, stocks);
    }
    file.close();
}

void displayAdminMenu()
{
    cout << "\t-------------Welcome to the coffee shop!-------------" << endl;
    cout << "\t1.Create Coffee" << endl;
    cout << "\t2.Read Coffee" << endl;
    cout << "\t3.Edit Coffee" << endl;
    cout << "\t4.Delete Coffee" << endl;
    cout << "\t5.Search Coffee by ID" << endl;
    cout << "\t6.Total Sales in Cash" << endl;
    cout << "\t7.Best Seller" << endl;
    cout << "\t8.Total Cash" << endl;
    cout << "\t9.Exit" << endl;
}
void displayTableHeader()
{
    cout << "ID" << setw(10) << "Coffee" << setw(10) << "Price" << setw(10) << "Stocks" << endl;
}
void displayCoffeeList(List *ls)
{
    displayTableHeader();
    readFromFile(ls);
    displayList(ls);
}

void deleteBegin(List *ls)
{
    Element *node = new Element();
    if (ls->n == 0)
        cout << "Invalid" << endl;
    else
    {
        node = ls->head;
        ls->head = node->next;
        ls->head->prev = NULL;
        delete node;
        if (ls->n == 1)
            ls->tail = NULL;
        ls->n = ls->n - 1;
    }
}

void deleteListByID(List *ls, string id)
{
    int flag = 0;
    Element *node = new Element();
    node = ls->head;
    while (node != NULL)
    {
        if (node->id == id)
        {
            if (node->next != NULL)
            {
                node->next->prev = node->prev;
            }
            if (node->prev != NULL)
            {
                node->prev->next = node->next;
            }
            delete node;
            flag = 1;
            break;
        }
        else
        {
            flag = 0;
        }
        node = node->next;
    }

    if (flag == 1)
    {
        cout << "Deleted the item with ID of " << id << endl;
    }
    else
    {
        cout << "ID not found!" << endl;
    }
}

void editListByID(List *ls, string id)
{
    Element *node = new Element();
    node = ls->head;
    int flag = 0;
    while (node != NULL)
    {
        if (node->id == id)
        {
            cout << "Enter the new coffee name ";
            cin >> node->name;
            cout << "Enter the new coffee price ";
            cin >> node->price;
            cout << "Enter the new quantity available in stocks";
            cin >> node->stocks;
            flag = 1;
            break;
        }
        else
        {
            flag = 0;
        }
        node = node->next;
    }
    if (flag == 1)
    {
        cout << "Successfully updated the item with ID of " << id << endl;
    }
    else
    {
        cout << "ID not found!" << endl;
    }
}

void findByID(List *ls, string id)
{
    Element *node = new Element();
    int flag = 0;
    node = ls->head;

    while (node != NULL)
    {
        if (node->id == id)
        {
            displayTableHeader();
            cout << node->id << setw(10) << node->name << setw(10) << node->price << setw(10) << node->stocks << endl;
            flag = 1;
            break;
        }
        node = node->next;
    }
    if (flag == 0)
    {
        cout << "ID not found!\n";
    }
}
float returnCoffeePrice(List *ls, string id)
{
    readFromFile(ls);
    Element *node = new Element();
    node = ls->head;

    while (node != NULL)
    {
        if (node->id == id)
        {
            return node->price;
            break;
        }
        node = node->next;
    }
}
void orderCoffee()
{
    srand(time(0));
    List *ls = new List();
    createList();
    saleList *salelist = new saleList();
    createSaleList();
    saleElement *sale = new saleElement();

    bestSellList *bestselllist = new bestSellList();
    createbestSellList();
    bestSellElement *bestsell = new bestSellElement();
    string id;
    int qty;
    cout << "Enter the coffee ID to order: ";
    cin >> id;
    cout << "Enter the quantity you'd like to order: (1-n)";
    cin >> qty;
    salesInsertBegin(salelist, (rand() % 100) + 1, "0", id, returnCoffeePrice(ls, id) * qty, qty);
    saleWriteFile(salelist);
    readBestSell(bestselllist);
    bestSellInsertBegin(bestselllist, id, qty);
    bestSellWriteFile(bestselllist);
}
void DisplayAllMenu()
{
    cout << "\t-------------Welcome to the coffee shop!-------------" << endl;
    cout << "\t1.Main Menu" << endl;
    cout << "\t2.Admin Panel" << endl;
    cout << "\t3.Exit" << endl;
}
void operation(List *ls)
{
    int input, input1;
    string id, name, stocks;
    float price;
    fstream file;
    do
    {
        List *ls = new List();
        createList();
        DisplayAllMenu();
        cin >> input1;
        switch (input1)
        {
        case 1:
        {
            displayCoffeeList(ls);
            orderCoffee();
        }
        break;
        case 2:
        {
            do
            {
                List *ls = new List();
                createList();
                displayAdminMenu();
                cin >> input;
                system("CLS");
                switch (input)
                {
                //create
                case 1:
                {
                    cout << "Enter the coffee ID ";
                    cin >> id;
                    cout << "Enter the coffee name ";
                    cin >> name;
                    cout << "Enter the coffee price ";
                    cin >> price;
                    cout << "Enter the quantity available in stocks";
                    cin >> stocks;
                    insertBegin(ls, id, name, price, stocks);
                    if (fileExists("coffeeList.txt"))
                        writeExistingFile(ls);
                    else
                        writeNewFile(ls);
                }
                break;
                //read
                case 2:
                {
                    displayCoffeeList(ls);
                }
                break;
                //edit
                case 3:
                {
                    displayCoffeeList(ls);
                    string id;
                    cout << "\t-------------Editing coffee-------------" << endl;
                    cout << "Please enter the ID: ";
                    cin >> id;
                    editListByID(ls, id);
                    writeNewFile(ls);
                }
                break;
                //delete
                case 4:
                {
                    readFromFile(ls);
                    bestSellList *bestselllist = new bestSellList();
                    createbestSellList();
                    string id;
                    cout << "\t-------------Deleting coffee-------------" << endl;
                    cout << "Please enter the ID: ";
                    cin >> id;
                    deleteListByID(ls, id);
                    readBestSell(bestselllist);
                    deleteBestSellListByID(bestselllist, id);
                    bestSellWriteFile(bestselllist);
                    displayList(ls);
                    writeNewFile(ls);
                }
                break;
                case 5:
                {
                    string id;
                    cout << "\t-------------Deleting coffee-------------" << endl;
                    cout << "Please enter the ID: ";
                    cin >> id;
                    findByID(ls, id);
                }
                break;
                case 6:
                {
                    saleList *sale = new saleList();
                    createSaleList();
                    writeTotalCash(sale);
                }
                break;
                case 7:
                {
                    readFromFile(ls);
                    bestSellList *bestselllist = new bestSellList();
                    createbestSellList();
                    findByID(ls, returnBestSeller(bestselllist));
                }
                break;
                case 8:
                {
                    saleList *sale = new saleList();
                    createSaleList();
                    saleWriteTotalCash(sale);
                }
                break;
                }
            } while (input != 9);
        }
        }
    } while (input1 != 3);
}