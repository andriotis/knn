#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structures.h"
#include "utils.h"
#include "quickselect.h"
#include "vps_tree.h"

extern num_points;
extern dim;
extern **corpus;

VPTree *make_vps_tree(Set S)
{
    VPTree *list = (VPTree *)calloc(num_points, sizeof(VPTree));

    for (int i = S.start; i < S.end; i++)
    {
        VPTree item;
        item.idx = i;
        item.hist = 0;
    }
}

VPTree *recurse_vps_tree(VPTree *list)
{
}
