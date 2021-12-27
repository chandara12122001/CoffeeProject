#include <iostream>
#include <fstream>
using namespace std;
struct saleElement
{
    string userId, coffeeId;
    int saleId;
    float coffeePrice;
    int qty;
    saleElement *next;
    saleElement *prev;
};
struct saleList
{
    int n;
    saleElement *head;
    saleElement *tail;
};
saleList *createSaleList()
{
    saleList *ls = new saleList();
    ls->n = 0;
    ls->head = NULL;
    ls->tail = NULL;
    return ls;
}

void salesInsertBegin(saleList *ls, int saleId, string userid, string coffeeid, float coffeePrice, int qty)
{
    saleElement *node = new saleElement();
    node->saleId = saleId;
    node->userId = userid;
    node->coffeeId = coffeeid;
    node->coffeePrice = coffeePrice;
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
void salesInsertEnd(saleList *ls, int saleId, string userid, string coffeeid, float coffeePrice, int qty)
{
    saleElement *node = new saleElement();
    if (ls->n == 0)
        salesInsertBegin(ls, saleId, userid, coffeeid, coffeePrice, qty);
    else
    {
        node->saleId = saleId;
        node->userId = userid;
        node->coffeeId = coffeeid;
        node->coffeePrice = coffeePrice;
        node->qty = qty;
        node->next = NULL;
        node->prev = ls->tail;
        ls->tail->next = node;
        ls->tail = node;
        ls->n = ls->n + 1;
    }
}
void writeTotalCash(saleList *ls)
{
    saleElement *sale = new saleElement();
    fstream file;
    int saleId;
    string userid, coffeeid;
    float coffeeprice;
    int qty;
    file.open("sale.txt", ios::in);
    while (!file.eof())
    {
        file >> saleId >> userid >> coffeeid >> coffeeprice >> qty;
        salesInsertEnd(ls, saleId, userid, coffeeid, coffeeprice, qty);
    }
    file.close();
    sale = ls->head;
    float totalCash = 0;
    while (sale != NULL)
    {
        totalCash += sale->coffeePrice * sale->qty;
        sale = sale->next;
    }
    cout << "The total sales in cash is: " << totalCash << endl;
}
void saleWriteFile(saleList *ls)
{
    saleElement *sale = new saleElement();
    sale = ls->head;
    fstream file;
    file.open("sale.txt", ios::app);
    while (sale != NULL)
    {
        if(sale->next !=NULL){
            file << sale->saleId << " " << sale->userId << " " << sale->coffeeId << " " << sale->coffeePrice << " " << sale->qty<<"\n";
        }
        else{
            file << sale->saleId << " " << sale->userId << " " << sale->coffeeId << " " << sale->coffeePrice << " " << sale->qty;
        }
        sale = sale->next;
    }
    file.close();
}
void saleWriteTotalCash(saleList *ls)
{
    saleElement *sale = new saleElement();
    fstream file;
    int saleid;
    string userid, coffeeid;
    float coffeeprice;
    int qty;
    file.open("sale.txt", ios::in);
    while (!file.eof())
    {
        file >> saleid >> userid >> coffeeid >> coffeeprice >> qty;
        salesInsertEnd(ls, saleid, userid, coffeeid, coffeeprice, qty);
    }
    file.close();
    sale = ls->head;
    float totalCash = 0;
    while (sale != NULL)
    {
        totalCash += sale->coffeePrice * sale->qty;
        sale = sale->next;
    }
    cout << "The total sales in cash is: "<<totalCash<<endl;
}