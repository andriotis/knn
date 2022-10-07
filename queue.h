#ifndef QUEUE_H
#define QUEUE_H

struct LinkedList
{
    int id;
    double distance;
    struct LinkedList *next;
};

struct LinkedList *newNode(int id, double distance);
void pop(struct LinkedList **head);
void push(struct LinkedList **head, int id, double distance);
struct LinkedList *peek(struct LinkedList **head);
int size(struct LinkedList **head);

#endif