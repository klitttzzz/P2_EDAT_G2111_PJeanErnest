#include "queue.h"
#include <stdlib.h>

#define MAX_QUEUE 100

Bool queue_is_full(const Queue *q);

struct _Queue
{
    void *data[MAX_QUEUE];
    void **front;
    void **rear;
};

Queue *queue_new()
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    int i;

    if (!q)
        return NULL;

    for (i = 0; i < MAX_QUEUE; i++)
        q->data[i] = NULL;

    q->front = &q->data[0];
    q->rear = &q->data[0];

    return q;
}

void queue_free(Queue *q)
{
    if (!q)
        return;
    free(q);
}

Bool queue_isEmpty(const Queue *q)
{
    if (!q || q->front == q->rear)
        return TRUE;
    return FALSE;
}

Status queue_push(Queue *q, void *ele)
{
    if (!q || queue_is_full(q) == TRUE)
        return ERROR;

    *q->rear = ele;
    q->rear = q->data + (q->rear - q->data + 1) % MAX_QUEUE;

    return OK;
}

void *queue_pop(Queue *q)
{
    void *ele = NULL;

    if (!q || queue_isEmpty(q))
        return NULL;

    ele = *q->front;
    q->front = q->data + (q->front - q->data + 1) % MAX_QUEUE;

    return ele;
}

void *queue_getFront(const Queue *q)
{
    if (!q || queue_isEmpty(q))
        return NULL;

    return *q->front;
}

void *queue_getBack(const Queue *q)
{
    if (!q || queue_isEmpty(q))
        return NULL;

    return *(q->rear == q->data ? q->data + MAX_QUEUE - 1 : q->rear - 1);
}

size_t queue_size(const Queue *q)
{
    if (!q)
        return 0;

    return (q->rear >= q->front) ? (q->rear - q->front) : (MAX_QUEUE - (q->front - q->rear));
}

int queue_print(FILE *fp, const Queue *q, p_queue_ele_print f)
{
    int i, size = 0;

    if (!q || queue_isEmpty(q))
        return 0;

    for (i = (q->front - q->data) % MAX_QUEUE; i != (q->rear - q->data) % MAX_QUEUE; i = (i + 1) % MAX_QUEUE)
        if (f(fp, q->data[i]))
            size++;
    
    return size;
}

/*
    Private functions
*/

Bool queue_is_full(const Queue *q)
{
    if (!q)
        return FALSE;

    return ((q->rear + 1 - q->data) % MAX_QUEUE == (q->front - q->data) % MAX_QUEUE);
}
