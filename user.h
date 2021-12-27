#include <iostream>
using namespace std;
struct userElement
{
    string userId, password;
    userElement *next;
    userElement *prev;
};
struct List
{
    int n;
    userElement *head;
    userElement *tail;
};
List *createUserList()
{
    List *ls = new List();
    ls->n = 0;
    ls->head = NULL;
    ls->tail = NULL;
    return ls;
}
void userinsertBegin(List *ls, string userid, string password)
{
    userElement *node = new userElement();

    node->userId = userid;
    node->password = password;

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
