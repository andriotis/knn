#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structures.h"
#include "utils.h"
#include "quickselect.h"
#include "vps_structures.h"
#include "vps_tree.h"

extern num_points;
extern dim;
extern **corpus;

VPTree *make_vps_tree(Set S)
{
    VPSListNode *list = NULL;

    for (int i = S.start; i < S.end + 1; i++)
    {
        VPSTree *item = (VPSTree *)malloc(sizeof(VPSTree));
        item->id = i;
        append_hist(&item->hist, 0);
        // Add item into list
        append_list(&list, item);
    }

    return recurse_vps_tree(list);
}

VPTree *recurse_vps_tree(VPSListNode *list)
{
    if (list == NULL)
        return NULL;

    // Create new node
    VPSTree *node = (VPSTree *)malloc(sizeof(VPSTree));
    // node->vp = getLast element of list
    // pop_list

    // iterate through list
    for (VPSListNode *iter = list; iter != NULL; iter = iter->next)
    {
        // do something
    }
}
