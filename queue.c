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
        return ERROR;

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
    if (q->front == q->rear)
        return TRUE;
    return FALSE;
}

Status queue_push(Queue *q, void *ele)
{
    if (!q || queue_is_full(q) == TRUE)
        return ERROR;

    q->rear = q->data + (q->rear - q->data + 1) % MAX_QUEUE;
    q->rear = ele;

    return OK;
}

void *queue_pop(Queue *q)
{
    void *ele = NULL;

    if (!q)
        return ERROR;

    ele = q->front;

    q->front = q->data + (q->front - q->data + 1) % MAX_QUEUE;

    return ele;
}

void *queue_getFront(const Queue *q)
{
    if (!q)
        return ERROR;

    return q->front;
}

void *queue_getBack(const Queue *q)
{
    if (!q)
        return ERROR;

    return (Queue *)q->data + (q->rear - q->data - 1) % MAX_QUEUE;
}

size_t queue_size(const Queue *q)
{
    if (!q)
        return ERROR;

    return (q->rear - q->front - 1) % MAX_QUEUE;
}

int queue_print(FILE *fp, const Queue *q, p_queue_ele_print f)
{

}

/*
    Private functions
*/

Bool queue_is_full(const Queue *q)
{
    if (q == NULL ||(q->rear + 1 - q->front) % MAX_QUEUE == 0)
        return TRUE;

    return FALSE;
}
