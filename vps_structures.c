#include "vps_structures.h"

#include <stdio.h>
#include <stdlib.h>

void append_hist(ListNode **head_ref, double new_data)
{
  /* 1. allocate node */
  ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));
  ListNode *last = *head_ref; /* used in step 5*/
  /* 2. put in the data  */
  new_node->data = new_data;
  /* 3. This new node is going to be the last node, so make next of
        it as NULL*/
  new_node->next = NULL;
  /* 4. If the Linked List is empty, then make the new node as head */
  if (*head_ref == NULL)
  {
    *head_ref = new_node;
    return;
  }
  /* 5. Else traverse till the last node */
  while (last->next != NULL)
    last = last->next;
  /* 6. Change the next of last node */
  last->next = new_node;
  return;
}

ListNode *pop_hist(ListNode *head)
{
  if (head == NULL)
    return NULL;

  if (head->next == NULL)
  {
    free(head);
    return NULL;
  }

  // Find the second last node
  ListNode *second_last = head;
  while (second_last->next->next != NULL)
    second_last = second_last->next;

  // Delete last node
  free(second_last->next);

  // Change next of second last
  second_last->next = NULL;

  return head;
}

void append_list(VPSListNode **head_ref, VPSTree *new_data)
{
  /* 1. allocate node */
  VPSListNode *new_node = (VPSListNode *)malloc(sizeof(VPSListNode));
  VPSListNode *last = *head_ref; /* used in step 5*/
  /* 2. put in the data  */
  new_node->data = new_data;
  /* 3. This new node is going to be the last node, so make next of
        it as NULL*/
  new_node->next = NULL;
  /* 4. If the Linked List is empty, then make the new node as head */
  if (*head_ref == NULL)
  {
    *head_ref = new_node;
    return;
  }
  /* 5. Else traverse till the last node */
  while (last->next != NULL)
    last = last->next;
  /* 6. Change the next of last node */
  last->next = new_node;
  return;
}

VPSListNode *pop_list(VPSListNode *head)
{
  if (head == NULL)
    return NULL;

  if (head->next == NULL)
  {
    free(head);
    return NULL;
  }

  // Find the second last node
  ListNode *second_last = head;
  while (second_last->next->next != NULL)
    second_last = second_last->next;

  // Delete last node
  free(second_last->next);

  // Change next of second last
  second_last->next = NULL;

  return head;
}