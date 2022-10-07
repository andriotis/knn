#include <stdlib.h>
#include "queue.h"

struct LinkedList *newNode(int id, double distance)
{
    struct LinkedList *temp = (struct LinkedList *)malloc(sizeof(struct LinkedList));
    temp->id = id;
    temp->distance = distance;
    temp->next = NULL;

    return temp;
}

int size(struct LinkedList **head)
{
    struct LinkedList *temp = *head;
    int count = 0;

    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }

    return count;
}

struct LinkedList *peek(struct LinkedList **head)
{
    return *head;
}

void pop(struct LinkedList **head)
{
    struct LinkedList *temp = *head;
    (*head) = (*head)->next;
    free(temp);
}

void push(struct LinkedList **head, int id, double distance)
{
    struct LinkedList *start = (*head);

    struct LinkedList *temp = newNode(id, distance);

    if ((*head)->distance < distance)
    {

        temp->next = *head;
        (*head) = temp;
    }
    else
    {

        while (start->next != NULL && start->next->distance > distance)
        {
            start = start->next;
        }

        temp->next = start->next;
        start->next = temp;
    }
}