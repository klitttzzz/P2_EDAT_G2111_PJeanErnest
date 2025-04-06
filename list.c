
#include "list.h"
/* In list.c */
typedef struct _NodeList
{
    void *data;
    struct _NodeList *next;
} NodeList;

struct _List
{
    NodeList *last;
};

List *list_new()
{
    List *pl = NULL;
    pl = (List *)malloc(sizeof(List));
    if (pl == NULL)
    {
        return NULL;
    }
    pl->last = NULL;
    return pl;
}

NodeList *node_new()
{
    NodeList *pn = NULL;
    pn = (NodeList *)malloc(sizeof(NodeList));
    if (pn == NULL)
    {
        return NULL;
    }
    pn->data = NULL;
    pn->next = NULL;
    return pn;
}

Bool list_isEmpty(const List *pl)
{
    if (pl == NULL)
    {
        return TRUE;
    }
    if (pl->last == NULL)
    {
        return TRUE;
    }
    return FALSE;
}

Status list_pushFront(List *pl, const void *e)
{
    NodeList *pn = NULL;
    if ((pl == NULL) || (e == NULL))
    {
        return ERROR;
    }
    pn = node_new();
    if (pn == NULL)
    {
        return ERROR;
    }
    pn->data = (void *)e;
    if (clist_is_empty(pl))
    {
        pn->next = pn;
        pl->last = pn;
    }
    else
    {
        pn->next = pl->last->next;
        pl->last->next = pn;
    }
    return OK;
}

Status list_pushBack(List *pl, const void *e)
{
    NodeList *pn = NULL;
    if ((pl == NULL) || (e == NULL))
    {
        return ERROR;
    }
    pn = node_new();
    if (pn == NULL)
    {
        return ERROR;
    }
    pn->data = (void *)e;

    if (clist_is_empty(pl) == TRUE)
    {
        pn->next = pn;
        pl->last = pn;
    }
    else
    {
        pn->next = pl->last->next;
        pl->last->next = pn;
        pl->last = pn;
    }
    return OK;
}

void *list_popFront(List *pl)
{
    void *pe = NULL;
    NodeList *pn = NULL;
    if ((pl == NULL) || (clist_is_empty(pl) == TRUE))
    {
        return NULL;
    }
    pn = pl->last->next;
    pe = pn->data;

    if (pl->last->next == pl->last)
    {
        pl->last = NULL;
    }
    else
    {
        pl->last->next = pn->next;
    }
    free((void *)pn);
    return pe;
}

void *list_popBack(List *pl)
{
    void *pe = NULL;
    NodeList *pn = NULL;
    if ((pl == NULL) || (clist_is_empty(pl) == TRUE))
    {
        return NULL;
    }
    if (pl->last->next == pl->last)
    {
        pe = pl->last->data;
        free((void *)pl->last);
        pl->last = NULL;
        return pe;
    }

    pn = pl->last;
    while (pn->next != pl->last)
    {
        pn = pn->next;
    }
    pe = pl->last->data;
    pn->next = pl->last->next;
    free((void *)pl->last);
    pl->last = pn;
    return pe;
}

void list_free(List *pl)
{
    if (pl == NULL)
    {
        return;
    }
    while (list_is_empty(pl) == FALSE)
    {
        list_pop_front(pl);
    }
    free((void *)pl);
}
