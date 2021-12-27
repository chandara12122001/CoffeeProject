#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
struct bestSellElement
{
    string coffeeId;
    int qty;
    bestSellElement *next;
    bestSellElement *prev;
};
struct bestSellList
{
    int n;
    bestSellElement *head;
    bestSellElement *tail;
};
bestSellList *createbestSellList()
{
    bestSellList *ls = new bestSellList();
    ls->n = 0;
    ls->head = NULL;
    ls->tail = NULL;
    return ls;
}
bool searchCofee(bestSellList *ls, string coffeeid)
{
    bestSellElement *node = new bestSellElement();
    node = ls->head;

    while (node != NULL)
    {
        if (node->coffeeId == coffeeid)
        {
            return true;
            break;
        }
        node = node->next;
    }
    return false;
}
void bestSellInsertBegin(bestSellList *ls, string coffeeId, int qty = 1)
{
    if (searchCofee(ls, coffeeId))
    {
        bestSellElement *node = new bestSellElement();
        node = ls->head;
        while (node != NULL)
        {
            if (node->coffeeId == coffeeId)
            {
                node->qty = node->qty + qty;
                break;
            }
            node = node->next;
        }
    }
    else
    {
        bestSellElement *node = new bestSellElement();
        node->coffeeId = coffeeId;
        node->qty = qty;
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
}
void bestSellInsertEnd(bestSellList *ls, string coffeeId, int qty)
{
    bestSellElement *node = new bestSellElement();
    if (ls->n == 0)
        bestSellInsertBegin(ls, coffeeId, qty);
    else
    {
        node->coffeeId = coffeeId;
        node->qty = qty;
        node->prev = ls->tail;
        ls->tail->next = node;
        ls->tail = node;
        ls->n = ls->n + 1;
    }
}

void bestSellWriteFile(bestSellList *ls)
{
    bestSellElement *sale = new bestSellElement();
    fstream file;
    sale = ls->head;
    file.open("bestSell.txt", ios::out);
    while (sale != NULL)
    {
        if (sale->next != NULL)
        {
            file << sale->coffeeId << setw(10) << sale->qty << "\n";
        }
        else
        {
            file << sale->coffeeId << setw(10) << sale->qty;
        }
        sale = sale->next;
    }
    file.close();
}

void readBestSell(bestSellList *ls)
{
    bestSellElement *sale = new bestSellElement();
    fstream file;
    string coffeeid;
    int qty;
    file.open("bestSell.txt", ios::in);
    while (!file.eof())
    {
        file >> coffeeid >> qty;
        bestSellInsertEnd(ls, coffeeid, qty);
    }
}
void deleteBestSellListByID(bestSellList *ls, string id)
{
    int flag = 0;
    bestSellElement *node = new bestSellElement();
    node = ls->head;
    while (node != NULL)
    {
        if (node->coffeeId == id)
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
string returnBestSeller(bestSellList *ls)
{
    readBestSell(ls);
    bestSellElement *node = new bestSellElement();
    bestSellElement *maxi = new bestSellElement();
    node = maxi = ls->head;
    while (node != NULL)
    {
        if (node->qty > maxi->qty)
        {
            maxi = node;
        }
        node = node->next;
    }
    return maxi->coffeeId;
}