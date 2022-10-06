#ifndef VPS_STRUCTURES_H
#define VPS_STRUCTURES_H

typedef struct
{
    VPSTree data;
    VPSListNode *next;
} VPSListNode;

typedef struct
{
    double data;
    ListNode *next;
} ListNode;

typedef struct
{
    int id;
    ListNode *hist;
    VPSTree *inner;
    VPSTree *outer;
} VPSTree;

void append_hist(ListNode **head_ref, double new_data);
void pop_hist(ListNode **head_ref);

void append_list(VPSListNode **head_ref, VPSTree new_data);
void pop_list(VPSListNode **head_ref);

#endif