#ifndef QUEUE_H
#define QUEUE_H

struct LinkedList
{
    int id;
    double distance;
    struct LinkedList *next;
};

struct LinkedList *newNode(int id, double distance);
int queue_size(struct LinkedList **head);
struct LinkedList *peek(struct LinkedList **head);
void pop(struct LinkedList **head);
void push(struct LinkedList **head, int id, double distance);

#endif